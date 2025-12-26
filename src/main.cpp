#include <iostream>
#include <chrono>
#include <thread>
#include <ranges>

#include "managers/ServiceManager.h"
#include "factories/EmployeeFactory.h"
#include "factories/ElectrocasnicFactory.h"
#include "reporting/RaportGenerator.h"
#include "utils/FileReader.h"
#include "utils/TimestampUtil.h"
#include "exceptions/ServiceException.h"

using namespace std;

void afiseazaMeniuPrincipal() {
    cout << "\n=== FixItNow - Service Electrocasnice ===\n";
    cout << "1. Gestiune angajati\n";
    cout << "2. Gestiune electrocasnice\n";
    cout << "3. Procesare cereri\n";
    cout << "4. Raportare\n";
    cout << "0. Iesire\n";
    cout << "Optiune: ";
}

void afiseazaMeniuAngajati() {
    cout << "\n=== Gestiune Angajati ===\n";
    cout << "1. Adauga angajat\n";
    cout << "2. Modifica nume angajat\n";
    cout << "3. Sterge angajat\n";
    cout << "4. Afiseaza detalii angajat (dupa CNP)\n";
    cout << "5. Afiseaza lista angajati\n";
    cout << "6. Incarca angajati din fisier\n";
    cout << "0. Inapoi\n";
    cout << "Optiune: ";
}

void afiseazaMeniuElectrocasnice() {
    cout << "\n=== Gestiune Electrocasnice ===\n";
    cout << "1. Adauga aparat reparabil\n";
    cout << "2. Sterge aparat reparabil\n";
    cout << "3. Afiseaza toate aparatele reparabile\n";
    cout << "4. Afiseaza aparate nereparabile\n";
    cout << "5. Incarca aparate din fisier\n";
    cout << "0. Inapoi\n";
    cout << "Optiune: ";
}

void afiseazaMeniuCereri() {
    cout << "\n=== Procesare Cereri ===\n";
    cout << "1. Incarca cereri din fisier\n";
    cout << "2. Porneste simulare reparatii\n";
    cout << "0. Inapoi\n";
    cout << "Optiune: ";
}

void afiseazaMeniuRaportare() {
    cout << "\n=== Raportare ===\n";
    cout << "1. Top 3 angajati cu cel mai mare salariu\n";
    cout << "2. Tehnicianul cu cea mai lunga reparatie\n";
    cout << "3. Cereri in asteptare (grupate)\n";
    cout << "0. Inapoi\n";
    cout << "Optiune: ";
}

void adaugaAngajat(ServiceManager& sm) {
    string tip, nume, prenume, cnp, dataAngajarii, oras;
    
    cout << "Tip (Receptioner/Tehnician/Supervizor): ";
    cin >> tip;
    cout << "Nume: ";
    cin >> nume;
    cout << "Prenume: ";
    cin >> prenume;
    cout << "CNP: ";
    cin >> cnp;
    cout << "Data angajarii (YYYY-MM-DD): ";
    cin >> dataAngajarii;
    cout << "Oras: ";
    cin >> oras;
    
    try {
        auto angajat = EmployeeFactory::creeazaAngajat(tip, nume, prenume, cnp, 
                                                       dataAngajarii, oras);
        
        // Daca e tehnician, adauga specializari
        if (tip == "Tehnician") {
            auto tehnician = dynamic_pointer_cast<Tehnician>(angajat);
            cout << "Numar specializari: ";
            int nrSpec;
            cin >> nrSpec;
            
            for (int i = 0; i < nrSpec; i++) {
                string tipAparat, marca;
                cout << "Specializare " << (i+1) << " - Tip: ";
                cin >> tipAparat;
                cout << "Specializare " << (i+1) << " - Marca: ";
                cin >> marca;
                tehnician->adaugaSpecializare(tipAparat, marca);
            }
        }
        
        sm.adaugaAngajat(angajat);
        cout << "Angajat adaugat cu succes!\n";
    } catch (const ServiceException& e) {
        cerr << "Eroare: " << e.what() << "\n";
    }
}

void incarcaAngajatiDinFisier(ServiceManager& sm) {
    string numeFisier;
    cout << "Nume fisier: ";
    cin >> numeFisier;
    
    // Cauta automat in folderul tests/ daca nu contine /
    if (numeFisier.find('/') == string::npos) {
        numeFisier = "tests/" + numeFisier;
    }
    
    auto linii = FileReader::citesteFisier(numeFisier);
    int numarLinie = 0;
    
    for (const auto& linie : linii) {
        numarLinie++;
        
        // Sari peste header
        if (numarLinie == 1) continue;
        
        try {
            auto elemente = FileReader::parseazaLinieCSV(linie);
            
            if (elemente.size() < 6) { // 6 - miniul de oloane necesare, restul sunt optionale
                FileReader::raporteazaEroare(numarLinie, 
                    "Numar insuficient de campuri");
                continue;
            }
            
            auto angajat = EmployeeFactory::creeazaAngajat(
                elemente[0], elemente[1], elemente[2], 
                elemente[3], elemente[4], elemente[5]
            );
            
            // Daca e tehnician si are specializari
            if (elemente[0] == "Tehnician" && elemente.size() > 6) { // > 6 -> are specializare
                auto tehnician = dynamic_pointer_cast<Tehnician>(angajat);
                
                for (size_t i = 6; i < elemente.size(); i += 2) {
                    if (i + 1 < elemente.size()) {
                        tehnician->adaugaSpecializare(elemente[i], elemente[i+1]);
                    }
                }
            }
            
            sm.adaugaAngajat(angajat);
            
        } catch (const ServiceException& e) {
            FileReader::raporteazaEroare(numarLinie, e.what());
        }
    }
    
    cout << "Incarcare finalizata.\n";
}

void incarcaAparateDinFisier(ServiceManager& sm) {
    string numeFisier;
    cout << "Nume fisier: ";
    cin >> numeFisier;
    
    // Cauta automat in folderul tests/ daca nu contine /
    if (numeFisier.find('/') == string::npos) {
        numeFisier = "tests/" + numeFisier;
    }
    
    auto linii = FileReader::citesteFisier(numeFisier);
    int numarLinie = 0;
    
    for (const auto& linie : linii) {
        numarLinie++;
        
        if (numarLinie == 1) continue;  // Sari peste header
        
        try {
            auto elemente = FileReader::parseazaLinieCSV(linie);
            
            if (elemente.size() < 5) {
                FileReader::raporteazaEroare(numarLinie, 
                    "Numar insuficient de campuri");
                continue;
            }
            
            ApparatInfo info;
            info.model = elemente[2];
            info.anFabricatie = stoi(elemente[3]);
            info.pretCatalog = stod(elemente[4]);
            info.detaliiSpecifice = (elemente.size() > 5) ? elemente[5] : "";
            
            sm.adaugaAparatReparabil(elemente[0], elemente[1], info);
            
        } catch (const exception& e) {
            FileReader::raporteazaEroare(numarLinie, e.what());
        }
    }
    
    cout << "Incarcare finalizata.\n";
}

void incarcaCereriDinFisier(ServiceManager& sm) {
    string numeFisier;
    cout << "Nume fisier: ";
    cin >> numeFisier;
    
    // Cauta automat in folderul tests/ daca nu contine /
    if (numeFisier.find('/') == string::npos) {
        numeFisier = "tests/" + numeFisier;
    }
    
    auto linii = FileReader::citesteFisier(numeFisier);
    int numarLinie = 0;
    
    for (const auto& linie : linii) {
        numarLinie++;
        
        if (numarLinie == 1) continue;  // Sari peste header
        
        try {
            auto elemente = FileReader::parseazaLinieCSV(linie);
            
            if (elemente.size() < 7) {
                FileReader::raporteazaEroare(numarLinie, 
                    "Numar insuficient de campuri");
                continue;
            }
            
            // Creeaza electrocasnicul
            auto electrocasnic = ElectrocasnicFactory::creeazaElectrocasnic(
                elemente[0],  // tip
                elemente[1],  // marca
                elemente[2],  // model
                stoi(elemente[3]),  // an
                stod(elemente[4]),  // pret
                elemente[5]   // detalii specifice
            );
            
            // Creeaza cererea
            auto cerere = make_shared<CerereReparatie>(
                electrocasnic,
                elemente[6],  // timestamp
                stoi(elemente[7])  // complexitate
            );
            
            sm.adaugaCerere(cerere);
            cout << "Cerere " << cerere->getId() << " inregistrata.\n";
            
        } catch (const exception& e) {
            FileReader::raporteazaEroare(numarLinie, e.what());
        }
    }
    
    cout << "Incarcare finalizata.\n";
}

void simulareReparatii(ServiceManager& sm) {
    if (!sm.poateFunctiona()) {
        cout << "Service-ul nu poate functiona!\n";
        cout << "Este nevoie de: minim 3 tehnicieni, 1 receptioner, 1 supervizor\n";
        return;
    }
    
    cout << "Durata simularii (in secunde): ";
    int durata;
    cin >> durata;
    
    cout << "\n=== Simulare inceputa ===\n\n";
    
    for (int timp : views::iota(1, durata + 1)) { // i in range(..) din python :)
        cout << "[Timp " << timp << "]\n";
        sm.simulareUnTic();
        sm.afiseazaStatusCurent();
        cout << "\n";
        
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    cout << "=== Simulare finalizata ===\n\n";
    
    // Generare automata rapoarte
    cout << "Generare rapoarte automate...\n";
    system("mkdir -p rapoarte");
    
    // Raport simulare
    auto istoric = sm.getIstoricSimulare();
    RaportGenerator::genereazaRaportSimulare(istoric, "rapoarte/simulare.txt");
    
    // Raport top salarii
    auto top = sm.getTop3Salarii();
    RaportGenerator::genereazaTopSalarii(top, "rapoarte/top_salarii.csv");
    
    // Raport tehnician
    auto tehnician = sm.getTehnicianCeaMaiLungaReparatie();
    RaportGenerator::genereazaRaportTehnician(tehnician, "rapoarte/tehnician_lunga_reparatie.csv");
    
    // Raport cereri asteptare
    auto cereri = sm.getCereriInAsteptareGrupate();
    RaportGenerator::genereazaCereriAsteptare(cereri, "rapoarte/cereri_asteptare.csv");
    
    cout << "\nToate rapoartele au fost generate in folderul 'rapoarte/'\n";
}

void gestioneazaAngajati(ServiceManager& sm) {
    int optiune;
    
    do {
        afiseazaMeniuAngajati();
        cin >> optiune;
        
        try {
            switch (optiune) {
                case 1:
                    adaugaAngajat(sm);
                    break;
                    
                case 2: {
                    string cnp, nume, prenume;
                    cout << "CNP angajat: ";
                    cin >> cnp;
                    cout << "Nume nou (sau - pentru a nu modifica): ";
                    cin >> nume;
                    cout << "Prenume nou (sau - pentru a nu modifica): ";
                    cin >> prenume;
                    
                    sm.modificaNumeAngajat(cnp, (nume != "-") ? nume : "", (prenume != "-") ? prenume : "");
                    cout << "Angajat modificat!\n";
                    break;
                }
                    
                case 3: {
                    string cnp;
                    cout << "CNP angajat de sters: ";
                    cin >> cnp;
                    sm.stergeAngajat(cnp);
                    cout << "Angajat sters!\n";
                    break;
                }
                    
                case 4: {
                    string cnp;
                    cout << "CNP angajat: ";
                    cin >> cnp;
                    
                    auto angajat = sm.cautaAngajatDupaCNP(cnp);
                    if (angajat) {
                        angajat->afiseazaDetalii();
                        cout << "Salariu: " << angajat->calculeazaSalariu() << " RON\n";
                    } else {
                        cout << "Angajat nu a fost gasit.\n";
                    }
                    break;
                }
                    
                case 5:
                    sm.afiseazaAngajati();
                    break;
                    
                case 6:
                    incarcaAngajatiDinFisier(sm);
                    break;
                    
                case 0:
                    break;
                    
                default:
                    cout << "Optiune invalida!\n";
            }
        } catch (const ServiceException& e) {
            cerr << "Eroare: " << e.what() << "\n";
        }
        
    } while (optiune != 0);
}

void gestioneazaElectrocasnice(ServiceManager& sm) {
    int optiune;
    
    do {
        afiseazaMeniuElectrocasnice();
        cin >> optiune;
        
        try {
            switch (optiune) {
                case 1: {
                    string tip, marca, model, detalii;
                    int an;
                    double pret;
                    
                    cout << "Tip: ";
                    cin >> tip;
                    cout << "Marca: ";
                    cin >> marca;
                    cout << "Model: ";
                    cin >> model;
                    cout << "An fabricatie: ";
                    cin >> an;
                    cout << "Pret catalog: ";
                    cin >> pret;
                    cout << "Detalii specifice: ";
                    cin >> detalii;
                    
                    ApparatInfo info{model, an, pret, detalii};
                    sm.adaugaAparatReparabil(tip, marca, info);
                    cout << "Aparat adaugat!\n";
                    break;
                }
                    
                case 2: {
                    string tip, marca, model;
                    cout << "Tip: ";
                    cin >> tip;
                    cout << "Marca: ";
                    cin >> marca;
                    cout << "Model: ";
                    cin >> model;
                    
                    sm.stergeAparatReparabil(tip, marca, model);
                    cout << "Aparat sters!\n";
                    break;
                }
                    
                case 3:
                    sm.afiseazaAparateReparabile();
                    break;
                    
                case 4:
                    sm.afiseazaAparateNereparabile();
                    break;
                    
                case 5:
                    incarcaAparateDinFisier(sm);
                    break;
                    
                case 0:
                    break;
                    
                default:
                    cout << "Optiune invalida!\n";
            }
        } catch (const ServiceException& e) {
            cerr << "Eroare: " << e.what() << "\n";
        }
        
    } while (optiune != 0);
}

void gestioneazaCereri(ServiceManager& sm) {
    int optiune;
    
    do {
        afiseazaMeniuCereri();
        cin >> optiune;
        
        try {
            switch (optiune) {
                case 1:
                    incarcaCereriDinFisier(sm);
                    break;
                    
                case 2:
                    simulareReparatii(sm);
                    break;
                    
                case 0:
                    break;
                    
                default:
                    cout << "Optiune invalida!\n";
            }
        } catch (const ServiceException& e) {
            cerr << "Eroare: " << e.what() << "\n";
        }
        
    } while (optiune != 0);
}

void gestioneazaRaportari(ServiceManager& sm) {
    int optiune;
    
    // Creeaza folder rapoarte daca nu exista
    // la fel ca mai sus, speram ca se foloseste o distributie derivata din UNIX
    system("mkdir -p rapoarte");
    
    do {
        afiseazaMeniuRaportare();
        cin >> optiune;
        
        try {
            switch (optiune) {
                case 1: {
                    auto top = sm.getTop3Salarii();
                    RaportGenerator::genereazaTopSalarii(top, "rapoarte/top_salarii.csv");
                    break;
                }
                    
                case 2: {
                    auto tehnician = sm.getTehnicianCeaMaiLungaReparatie();
                    RaportGenerator::genereazaRaportTehnician(tehnician, 
                        "rapoarte/tehnician_lunga_reparatie.csv");
                    break;
                }
                    
                case 3: {
                    auto cereri = sm.getCereriInAsteptareGrupate();
                    RaportGenerator::genereazaCereriAsteptare(cereri, 
                        "rapoarte/cereri_asteptare.csv");
                    break;
                }
                    
                case 0:
                    break;
                    
                default:
                    cout << "Optiune invalida!\n";
            }
        } catch (const ServiceException& e) {
            cerr << "Eroare: " << e.what() << "\n";
        }
        
    } while (optiune != 0);
}

int main() {
    ServiceManager& sm = ServiceManager::getInstance();
    int optiune;
    
    cout << "Bine ati venit la FixItNow!\n";
    
    do {
        afiseazaMeniuPrincipal();
        cin >> optiune;
        
        switch (optiune) {
            case 1:
                gestioneazaAngajati(sm);
                break;
                
            case 2:
                gestioneazaElectrocasnice(sm);
                break;
                
            case 3:
                gestioneazaCereri(sm);
                break;
                
            case 4:
                gestioneazaRaportari(sm);
                break;
                
            case 0:
                cout << "La revedere!\n";
                break;
                
            default:
                cout << "Optiune invalida!\n";
        }
        
    } while (optiune != 0);
    
    return 0;
}

