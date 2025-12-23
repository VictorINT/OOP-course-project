#include "../../include/managers/Simulator.h"
#include "../../include/managers/ServiceManager.h"

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
    // TODO: Implement automatic technician allocation
}

void Simulator::actualizeazaStatusuriCereri() {
    // TODO: Implement request status updates
}
