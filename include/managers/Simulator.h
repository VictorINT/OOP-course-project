#pragma once
#include "../models/CerereReparatie.h"
#include <vector>

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
    void alocaTehniciAutomatPentruCereri();
    void actualizeazaStatusuriCereri();
};
