#include "../../include/managers/Simulator.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Tehnician.h"

using namespace std;

Simulator::Simulator() : timpCurent(0), tickDurata(1) {}

Simulator::Simulator(int tickDurata) : timpCurent(0), tickDurata(tickDurata) {}

void Simulator::ruleazaTick() {
    timpCurent += tickDurata;
    alocaTehniciAutomatPentruCereri();
    actualizeazaStatusuriCereri();
}

void Simulator::ruleazaSimulare(int numarTickuri) {
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
    ServiceManager* service = ServiceManager::getInstance();
    const vector<Angajat*>& angajati = service->getAngajati();
    vector<CerereReparatie*>& cereri = const_cast<vector<CerereReparatie*>&>(service->getCereri());

    auto loadForTech = [&](Tehnician* tech) {
        int active = 0;
        for (auto c : cereri) {
            if (c != nullptr && c->getTehnicianAlocat() == tech && c->getStatus() == StatusCerere::IN_LUCRU) {
                active++;
            }
        }
        return active;
    };

    for (auto cerere : cereri) {
        if (cerere == nullptr || cerere->getStatus() != StatusCerere::IN_ASTEPTARE) {
            continue;
        }

        Tehnician* candidat = nullptr;
        for (auto angajat : angajati) {
            Tehnician* tech = dynamic_cast<Tehnician*>(angajat);
            if (tech == nullptr) {
                continue;
            }

            if (tech->getSpecializare() != cerere->getAparat()->getTip()) {
                continue;
            }

            int incarcare = loadForTech(tech);
            if (incarcare >= 3) {
                continue;
            }

            if (candidat == nullptr || loadForTech(candidat) > incarcare) {
                candidat = tech;
            }
        }

        if (candidat != nullptr) {
            cerere->setTehnicianAlocat(candidat);
            cerere->setStatus(StatusCerere::IN_LUCRU);
            if (cerere->getDataInregistrare() == 0) {
                cerere->setDataInregistrare(timpCurent);
            }
            if (cerere->getDataFinalizare() == 0) {
                int durata = 5; // durata implicita in unitati de timp
                cerere->setDataFinalizare(timpCurent + durata);
                cerere->setCostManopera(durata * 100.0);
            }
        }
    }
}

void Simulator::actualizeazaStatusuriCereri() {
    ServiceManager* service = ServiceManager::getInstance();
    vector<CerereReparatie*>& cereri = const_cast<vector<CerereReparatie*>&>(service->getCereri());

    for (auto cerere : cereri) {
        if (cerere == nullptr) {
            continue;
        }

        if (cerere->getStatus() == StatusCerere::IN_LUCRU && cerere->getDataFinalizare() <= timpCurent) {
            cerere->setStatus(StatusCerere::FINALIZATA);
            Tehnician* tech = cerere->getTehnicianAlocat();
            if (tech != nullptr) {
                tech->adaugaReparatie(cerere);
            }
        }
    }
}
