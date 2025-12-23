#pragma once

#include "Electrocasnic.h"
#include <string>

using namespace std;

class Tehnician;

enum class StatusCerere {
    IN_ASTEPTARE,
    IN_LUCRU,
    FINALIZATA,
    ANULATA
};

class CerereReparatie {
private:
    int id;
    Electrocasnic* aparat;
    string descriereDefect;
    StatusCerere status;
    Tehnician* tehnicianAlocat;
    long long dataInregistrare;
    long long dataFinalizare;
    double costPiese;
    double costManopera;

public:
    CerereReparatie();
    CerereReparatie(int, Electrocasnic*, const string&);
    ~CerereReparatie();
    
    // Getters
    int getId() const;
    Electrocasnic* getAparat() const;
    string getDescriereDefect() const;
    StatusCerere getStatus() const;
    Tehnician* getTehnicianAlocat() const;
    long long getDataInregistrare() const;
    long long getDataFinalizare() const;
    double getCostPiese() const;
    double getCostManopera() const;
    
    // Setters
    void setStatus(StatusCerere);
    void setTehnicianAlocat(Tehnician*);
    void setDataFinalizare(long long);
    void setCostPiese(double);
    void setCostManopera(double);
    
    // Calcule
    double getCostTotal() const;
    int getDurataReparatie() const;
};
