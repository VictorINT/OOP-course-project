#ifndef CERERE_REPARATIE_H
#define CERERE_REPARATIE_H

#include <string>
#include <memory>
#include "Electrocasnic.h"

using namespace std;

class Tehnician;

class CerereReparatie {
private:
    int id;
    shared_ptr<Electrocasnic> aparat;
    string timestamp;
    int complexitate;
    int durataEstimata;
    int durataRamasa;
    double pretReparatie;
    string status;  // "in_asteptare", "in_lucru", "finalizata"
    shared_ptr<Tehnician> tehnicianAlocat;
    
    static int nextId;
    
public:
    CerereReparatie(shared_ptr<Electrocasnic>, const string&, int);
    
    // Getters
    int getId() const;
    shared_ptr<Electrocasnic> getAparat() const;
    string getTimestamp() const;
    int getComplexitate() const;
    int getDurataEstimata() const;
    int getDurataRamasa() const;
    double getPretReparatie() const;
    string getStatus() const;
    shared_ptr<Tehnician> getTehnicianAlocat() const;
    
    // Setters
    void setStatus(const string&);
    void setTehnicianAlocat(shared_ptr<Tehnician>);
    
    // Metode pentru simulare
    void proceseaza();  // Reduce durata ramasa cu 1
    bool esteFinalizata() const;
    
    // Calcule
    void calculeazaDurata();
    void calculeazaPret();
};

#endif

