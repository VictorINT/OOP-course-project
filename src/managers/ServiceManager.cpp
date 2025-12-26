#include "ServiceManager.h"
#include "../exceptions/ServiceException.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

ServiceManager& ServiceManager::getInstance() {
    static ServiceManager instance;
    return instance;
}

void ServiceManager::adaugaAngajat(shared_ptr<Employee> angajat) {
    angajati.push_back(angajat);
}

void ServiceManager::stergeAngajat(const string& cnp) {
    auto it = remove_if(angajati.begin(), angajati.end(),
        [&cnp](const shared_ptr<Employee>& ang) {
            return ang->getCNP() == cnp;
        });
    
    if (it == angajati.end()) {
        throw InvalidDataException("Angajat cu CNP " + cnp + " nu a fost gasit");
    }
    
    angajati.erase(it, angajati.end());
}

void ServiceManager::modificaNumeAngajat(const string& cnp, 
                                         const string& numeNou,
                                         const string& prenumeNou) {
    auto angajat = cautaAngajatDupaCNP(cnp);
    if (!angajat) {
        throw InvalidDataException("Angajat cu CNP " + cnp + " nu a fost gasit");
    }

    if (!numeNou.empty()) angajat->setNume(numeNou);
    if (!prenumeNou.empty()) angajat->setPrenume(prenumeNou);
}

shared_ptr<Employee> ServiceManager::cautaAngajatDupaCNP(const string& cnp) const {
    auto it = find_if(angajati.begin(), angajati.end(),
        [&cnp](const shared_ptr<Employee>& ang) {
            return ang->getCNP() == cnp;
        });
    
    return (it != angajati.end()) ? *it : nullptr;
}

void ServiceManager::afiseazaAngajati() const {
    if (angajati.empty()) {
        cout << "Nu exista angajati in sistem.\n";
        return;
    }
    
    for (const auto& ang : angajati) {
        ang->afiseazaDetalii();
        cout << "Salariu: " << fixed << setprecision(2) 
                  << ang->calculeazaSalariu() << " RON\n";
        cout << "---\n";
    }
}

bool ServiceManager::poateFunctiona() const {
    int nrTehniciemi = 0;
    int nrReceptioneri = 0;
    int nrSupervizori = 0;
    
    for (const auto& ang : angajati) {
        if (ang->getTipAngajat() == "Tehnician") nrTehniciemi++;
        else if (ang->getTipAngajat() == "Receptioner") nrReceptioneri++;
        else if (ang->getTipAngajat() == "Supervizor") nrSupervizori++;
    }
    
    return nrTehniciemi >= 3 && nrReceptioneri >= 1 && nrSupervizori >= 1;
}

void ServiceManager::adaugaAparatReparabil(const string& tip, 
                                           const string& marca,
                                           const ApparatInfo& info) {
    aparateReparabile[tip][marca].push_back(info);
}

void ServiceManager::stergeAparatReparabil(const string& tip, 
                                           const string& marca,
                                           const string& model) {
    if (aparateReparabile.find(tip) == aparateReparabile.end()) return;
    if (aparateReparabile[tip].find(marca) == aparateReparabile[tip].end()) return;
    
    auto& modele = aparateReparabile[tip][marca];
    modele.erase(remove_if(modele.begin(), modele.end(),
        [&model](const ApparatInfo& info) {
            return info.model == model;
        }), modele.end());
}

bool ServiceManager::poateRepara(const string& tip, 
                                  const string& marca,
                                  const string& model) const {
    auto itTip = aparateReparabile.find(tip);
    if (itTip == aparateReparabile.end()) return false;
    
    auto itMarca = itTip->second.find(marca);
    if (itMarca == itTip->second.end()) return false;
    
    const auto& modele = itMarca->second;
    return any_of(modele.begin(), modele.end(),
        [&model](const ApparatInfo& info) {
            return info.model == model;
        });
}

void ServiceManager::afiseazaAparateReparabile() const {
    if (aparateReparabile.empty()) {
        cout << "Nu exista aparate reparabile in sistem.\n";
        return;
    }
    
    for (const auto& [tip, marci] : aparateReparabile) {
        cout << "Tip: " << tip << "\n";
        for (const auto& [marca, modele] : marci) {
            cout << "  Marca: " << marca << "\n";
            for (const auto& info : modele) {
                cout << "    Model: " << info.model 
                          << ", An: " << info.anFabricatie
                          << ", Pret: " << info.pretCatalog << " RON\n";
            }
        }
    }
}

void ServiceManager::afiseazaAparateNereparabile() const {
    if (aparateNereparabile.empty()) {
        cout << "Nu exista aparate nereparabile.\n";
        return;
    }
    
    // Sorteaza descrescator dupa numar aparitii
    vector<pair<string, int>> sortate(
        aparateNereparabile.begin(), aparateNereparabile.end());
    
    sort(sortate.begin(), sortate.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    
    cout << "Aparate nereparabile (sortate dupa numar aparitii):\n";
    for (const auto& [aparat, numar] : sortate) {
        cout << aparat << ": " << numar << " aparitii\n";
    }
}

void ServiceManager::adaugaCerere(shared_ptr<CerereReparatie> cerere) {
    toateCererile.push_back(cerere);
    
    // Verifica daca poate fi reparata
    auto aparat = cerere->getAparat();
    if (cerere->getComplexitate() == 0 || 
        !poateRepara(aparat->getTip(), aparat->getMarca(), aparat->getModel())) {
        
        string cheie = aparat->getMarca() + ":" + aparat->getModel();
        aparateNereparabile[cheie]++;
        cerere->setStatus("nereparabil");
        return;
    }
    
    // Incearca alocarea
    if (!alocareCerere(cerere)) {
        cereriInAsteptare.push(cerere);
    }
}

bool ServiceManager::alocareCerere(shared_ptr<CerereReparatie> cerere) {
    auto aparat = cerere->getAparat();
    auto tehnician = gasesteTehnicianOptim(aparat->getTip(), aparat->getMarca());
    
    if (!tehnician) return false;
    
    cerere->setTehnicianAlocat(tehnician);
    cerere->setStatus("in_lucru");
    tehnician->adaugaCerereActiva(cerere);
    
    string mesaj = "[Asignare] Cerere " + to_string(cerere->getId()) + 
                        " (" + aparat->getTip() + " " + aparat->getMarca() + " " + aparat->getModel() +
                        ", durata: " + to_string(cerere->getDurataEstimata()) + " sec" +
                        ", pret: " + to_string(static_cast<int>(cerere->getPretReparatie())) + " RON) " +
                        "-> Tehnician " + tehnician->getNume() + " " + tehnician->getPrenume();
    cout << mesaj << "\n";
    istoricSimulare.push_back(mesaj);
    
    return true;
}

void ServiceManager::procesareCereriInAsteptare() {
    queue<shared_ptr<CerereReparatie>> cereriRamase;
    
    while (!cereriInAsteptare.empty()) {
        auto cerere = cereriInAsteptare.front();
        cereriInAsteptare.pop();
        
        if (!alocareCerere(cerere)) {
            cereriRamase.push(cerere);
        }
    }
    
    cereriInAsteptare = cereriRamase;
}

void ServiceManager::simulareUnTic() {
    auto tehnicieni = getTehnicieni();
    
    for (auto& tehnician : tehnicieni) {
        auto cereriActive = tehnician->getCereriActive();
        
        for (auto& cerere : cereriActive) {
            if (cerere->getStatus() == "in_lucru") {
                cerere->proceseaza();
                
                if (cerere->esteFinalizata()) {
                    string mesaj = "[Finalizat] Tehnician " + tehnician->getNume() 
                              + " " + tehnician->getPrenume() 
                              + " a finalizat cererea " + to_string(cerere->getId());
                    cout << mesaj << "\n";
                    istoricSimulare.push_back(mesaj);
                    
                    tehnician->adaugaValoareReparatie(cerere->getPretReparatie());
                    cerere->setStatus("finalizata");
                    tehnician->eliminaCerereActiva(cerere);
                    cereriFinalizate.push_back(cerere);
                }
            }
        }
    }
    
    procesareCereriInAsteptare();
}

void ServiceManager::afiseazaStatusCurent() const {
    auto tehnicieni = getTehnicieni();
    
    for (const auto& tehnician : tehnicieni) {
        auto cereriActive = tehnician->getCereriActive();
        
        for (const auto& cerere : cereriActive) {
            if (cerere->getStatus() == "in_lucru") {
                cout << "Tehnician " << tehnician->getNume() << " " 
                          << tehnician->getPrenume() 
                          << " proceseaza cererea " << cerere->getId()
                          << " (raman " << cerere->getDurataRamasa() << " unitati)\n";
            }
        }
    }
    
    if (!cereriInAsteptare.empty()) {
        cout << "Cereri in asteptare: ";
        auto copy = cereriInAsteptare;
        while (!copy.empty()) {
            cout << copy.front()->getId();
            copy.pop();
            if (!copy.empty()) cout << ", ";
        }
        cout << "\n";
    }
}

vector<shared_ptr<Employee>> ServiceManager::getTop3Salarii() const {
    auto copie = angajati;
    
    sort(copie.begin(), copie.end(),
        [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
            double salA = a->calculeazaSalariu();
            double salB = b->calculeazaSalariu();
            if (salA != salB) return salA > salB;
            
            string numeA = a->getNume() + " " + a->getPrenume();
            string numeB = b->getNume() + " " + b->getPrenume();
            return numeA < numeB;
        });
    
    if (copie.size() > 3) copie.resize(3);
    return copie;
}

shared_ptr<Tehnician> ServiceManager::getTehnicianCeaMaiLungaReparatie() const {
    shared_ptr<Tehnician> rezultat;
    int durataMaxima = 0;
    
    for (const auto& cerere : cereriFinalizate) {
        if (cerere->getDurataEstimata() > durataMaxima) {
            durataMaxima = cerere->getDurataEstimata();
            rezultat = cerere->getTehnicianAlocat();
        }
    }
    
    return rezultat;
}

map<string, vector<shared_ptr<CerereReparatie>>> 
ServiceManager::getCereriInAsteptareGrupate() const {
    map<string, vector<shared_ptr<CerereReparatie>>> grupate;
    
    auto copy = cereriInAsteptare;
    while (!copy.empty()) {
        auto cerere = copy.front();
        copy.pop();
        
        auto aparat = cerere->getAparat();
        string cheie = aparat->getTip() + ":" + aparat->getMarca() + ":" + aparat->getModel();
        grupate[cheie].push_back(cerere);
    }
    
    return grupate;
}

const vector<shared_ptr<Employee>>& ServiceManager::getAngajati() const {
    return angajati;
}

const vector<shared_ptr<CerereReparatie>>& ServiceManager::getToateCererile() const {
    return toateCererile;
}

vector<shared_ptr<Tehnician>> ServiceManager::getTehnicieni() const {
    vector<shared_ptr<Tehnician>> tehnicieni;
    
    for (const auto& ang : angajati) {
        if (ang->getTipAngajat() == "Tehnician") {
            tehnicieni.push_back(dynamic_pointer_cast<Tehnician>(ang));
        }
    }
    
    return tehnicieni;
}

shared_ptr<Tehnician> ServiceManager::gasesteTehnicianOptim(
    const string& tip, const string& marca) {
    
    auto tehnicieni = getTehnicieni();
    shared_ptr<Tehnician> optim;
    double durataMinima = -1;
    
    for (auto& tehnician : tehnicieni) {
        if (!tehnician->poateRepara(tip, marca)) continue;
        if (!tehnician->areLoc()) continue;
        
        double durata = tehnician->getDurataTotala();
        if (durataMinima < 0 || durata < durataMinima) {
            durataMinima = durata;
            optim = tehnician;
        }
    }
    
    return optim;
}

vector<string> ServiceManager::getIstoricSimulare() const {
    return istoricSimulare;
}

