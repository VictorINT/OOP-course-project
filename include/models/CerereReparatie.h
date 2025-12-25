#pragma once

#include "Electrocasnic.h"
#include <string>
#include <memory>

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
    std::shared_ptr<Electrocasnic> aparat;
    string descriereDefect;
    StatusCerere status;
    std::weak_ptr<Tehnician> tehnicianAlocat;
    long long dataInregistrare;
    long long dataFinalizare;
    double costPiese;
    double costManopera;

public:
    CerereReparatie();
    CerereReparatie(int, std::shared_ptr<Electrocasnic>, const string&);
    ~CerereReparatie();
    
    // Getters
    int getId() const;
    std::shared_ptr<Electrocasnic> getAparat() const;
    string getDescriereDefect() const;
    StatusCerere getStatus() const;
    std::shared_ptr<Tehnician> getTehnicianAlocat() const;
    long long getDataInregistrare() const;
    long long getDataFinalizare() const;
    double getCostPiese() const;
    double getCostManopera() const;
    
    // Setters
    void setStatus(StatusCerere);
    void setTehnicianAlocat(std::shared_ptr<Tehnician>);
    void setDataFinalizare(long long);
    void setDataInregistrare(long long);
    void setCostPiese(double);
    void setCostManopera(double);
    
    // Calcule
    double getCostTotal() const;
    int getDurataReparatie() const;
};
