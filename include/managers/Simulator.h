#pragma once
#include "../models/CerereReparatie.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Simulator {
private:
    long long timpCurent;
    int tickDurata;

public:
    Simulator();
    Simulator(int);
    
    void ruleazaTick();
    void ruleazaSimulare(int);
    
    long long getTimpCurent() const;
    void setTimpCurent(long long);
    
private:
    void initializeazaTimpStart();
    long long calculeazaDurataEstimata(const std::shared_ptr<CerereReparatie>&) const;
    bool specializarePotrivita(const string&, const string&) const;
    void alocaTehniciAutomatPentruCereri();
    void actualizeazaStatusuriCereri();
};
