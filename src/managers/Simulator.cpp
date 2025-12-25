#include "../../include/managers/Simulator.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Tehnician.h"
#include "../../include/utils/DateUtils.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <memory>

using namespace std;

Simulator::Simulator() : timpCurent(0), tickDurata(1) {}

Simulator::Simulator(int tickDurata) : timpCurent(0), tickDurata(tickDurata) {}

void Simulator::ruleazaTick() {
    actualizeazaStatusuriCereri();
    alocaTehniciAutomatPentruCereri();
    timpCurent += tickDurata;
}

void Simulator::ruleazaSimulare(int numarTickuri) {
    initializeazaTimpStart();
    for (int i = 0; i < numarTickuri; i++) {
        ruleazaTick();
    }
}

long long Simulator::getTimpCurent() const {
    return timpCurent;
}

void Simulator::setTimpCurent(long long timp) {
    timpCurent = timp;
}

void Simulator::alocaTehniciAutomatPentruCereri() {
    ServiceManager& service = ServiceManager::getInstance();
    const vector<shared_ptr<Angajat>>& angajati = service.getAngajati();
    const vector<shared_ptr<CerereReparatie>>& cereri = service.getCereri();

    vector<shared_ptr<CerereReparatie>> inAsteptare;
    for (auto cerere : cereri) {
        if (cerere == nullptr || cerere->getStatus() != StatusCerere::IN_ASTEPTARE) {
            continue;
        }
        long long ts = cerere->getDataInregistrare();
        if (ts == 0) {
            cerere->setDataInregistrare(timpCurent);
            ts = timpCurent;
        }
        if (ts <= timpCurent) {
            inAsteptare.push_back(cerere);
        }
    }

    sort(inAsteptare.begin(), inAsteptare.end(), [](const shared_ptr<CerereReparatie>& a, const shared_ptr<CerereReparatie>& b) {
        if (a->getDataInregistrare() == b->getDataInregistrare()) {
            return a->getId() < b->getId();
        }
        return a->getDataInregistrare() < b->getDataInregistrare();
    });

    auto loadForTech = [&](shared_ptr<Tehnician> tech) {
        int active = 0;
        long long durataRamasa = 0;
        for (auto c : cereri) {
            if (c != nullptr && c->getTehnicianAlocat() == tech && c->getStatus() == StatusCerere::IN_LUCRU) {
                active++;
                long long ramas = c->getDataFinalizare() - timpCurent;
                durataRamasa += ramas > 0 ? ramas : 0;
            }
        }
        return make_pair(active, durataRamasa);
    };

    for (auto cerere : inAsteptare) {
        if (cerere->getAparat() == nullptr) {
            continue;
        }

        shared_ptr<Tehnician> candidat = nullptr;
        pair<int, long long> incarcBest = {numeric_limits<int>::max(), numeric_limits<long long>::max()};

        for (auto angajat : angajati) {
            auto tech = dynamic_pointer_cast<Tehnician>(angajat);
            if (tech == nullptr) {
                continue;
            }

            if (!specializarePotrivita(tech->getSpecializare(), cerere->getAparat()->getTip())) {
                continue;
            }

            auto incarcare = loadForTech(tech);
            if (incarcare.first >= 3) {
                continue;
            }

            if (incarcare.second < incarcBest.second || (incarcare.second == incarcBest.second && incarcare.first < incarcBest.first)) {
                candidat = tech;
                incarcBest = incarcare;
            }
        }

        if (candidat != nullptr) {
            cerere->setTehnicianAlocat(candidat);
            cerere->setStatus(StatusCerere::IN_LUCRU);
            long long durata = calculeazaDurataEstimata(cerere);
            cerere->setDataFinalizare(timpCurent + durata);
            cerere->setCostManopera(durata * 100.0);
            service.adaugaEveniment(timpCurent, "Cerere " + to_string(cerere->getId()) + " alocata tehnician " + candidat->getNume());
        }
    }
}

void Simulator::actualizeazaStatusuriCereri() {
    ServiceManager& service = ServiceManager::getInstance();
    const vector<shared_ptr<CerereReparatie>>& cereri = service.getCereri();

    for (auto cerere : cereri) {
        if (cerere == nullptr) {
            continue;
        }

        if (cerere->getStatus() == StatusCerere::IN_LUCRU && cerere->getDataFinalizare() <= timpCurent) {
            cerere->setStatus(StatusCerere::FINALIZATA);
            auto tech = cerere->getTehnicianAlocat();
            if (tech != nullptr) {
                tech->adaugaReparatie(cerere);
            }
            service.adaugaEveniment(timpCurent, "Cerere " + to_string(cerere->getId()) + " finalizata");
        }
    }
}

void Simulator::initializeazaTimpStart() {
    if (timpCurent != 0) {
        return;
    }

    ServiceManager& service = ServiceManager::getInstance();
    const vector<shared_ptr<CerereReparatie>>& cereri = service.getCereri();
    long long minTimestamp = numeric_limits<long long>::max();
    for (auto cerere : cereri) {
        if (cerere != nullptr && cerere->getDataInregistrare() > 0) {
            minTimestamp = min(minTimestamp, cerere->getDataInregistrare());
        }
    }

    if (minTimestamp != numeric_limits<long long>::max()) {
        timpCurent = minTimestamp;
    } else {
        timpCurent = DateUtils::getTimpCurent();
    }
}

long long Simulator::calculeazaDurataEstimata(const shared_ptr<CerereReparatie>& cerere) const {
    auto aparat = cerere->getAparat();
    int anFabricatie = aparat ? aparat->getAnFabricatie() : 0;
    long long refTime = cerere->getDataInregistrare() > 0 ? cerere->getDataInregistrare() : timpCurent;
    time_t timpRef = static_cast<time_t>(refTime > 0 ? refTime : DateUtils::getTimpCurent());
    tm* t = localtime(&timpRef);
    int anCurent = t ? (1900 + t->tm_year) : 1970;
    int vechime = anFabricatie > 0 ? max(1, anCurent - anFabricatie) : 1;
    const int complexitateImplicita = 3;
    int durata = vechime * complexitateImplicita;
    return static_cast<long long>(durata > 0 ? durata : 1);
}

bool Simulator::specializarePotrivita(const string& specializare, const string& tipAparat) const {
    auto normalize = [](string value) {
        string lower;
        lower.resize(value.size());
        transform(value.begin(), value.end(), lower.begin(), [](unsigned char c) { return static_cast<char>(tolower(c)); });
        if (lower.find("frig") == 0) return string("frigider");
        if (lower.find("telev") == 0) return string("televizor");
        if (lower.find("masin") == 0) return string("masinaspalat");
        return lower;
    };

    string specNorm = normalize(specializare);
    string tipNorm = normalize(tipAparat);
    return specNorm == tipNorm || specNorm.find(tipNorm) != string::npos || tipNorm.find(specNorm) != string::npos;
}
