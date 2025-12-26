#include "CerereReparatie.h"
#include "Tehnician.h"
#include "../exceptions/ServiceException.h"

using namespace std;

int CerereReparatie::nextId = 1;

CerereReparatie::CerereReparatie(shared_ptr<Electrocasnic> app, 
                                 const string& ts, int comp)
    : id(nextId++), aparat(app), timestamp(ts), complexitate(comp),
      durataEstimata(0), durataRamasa(0), pretReparatie(0.0),
      status("in_asteptare"), tehnicianAlocat(nullptr) {
    
    if (complexitate < 0 || complexitate > 5) {
        throw InvalidDataException("Complexitate trebuie sa fie intre 0 si 5");
    }
    
    calculeazaDurata();
    calculeazaPret();
}

int CerereReparatie::getId() const { return id; }
shared_ptr<Electrocasnic> CerereReparatie::getAparat() const { return aparat; }
string CerereReparatie::getTimestamp() const { return timestamp; }
int CerereReparatie::getComplexitate() const { return complexitate; }
int CerereReparatie::getDurataEstimata() const { return durataEstimata; }
int CerereReparatie::getDurataRamasa() const { return durataRamasa; }
double CerereReparatie::getPretReparatie() const { return pretReparatie; }
string CerereReparatie::getStatus() const { return status; }

shared_ptr<Tehnician> CerereReparatie::getTehnicianAlocat() const {
    return tehnicianAlocat;
}

void CerereReparatie::setStatus(const string& s) {
    status = s;
}

void CerereReparatie::setTehnicianAlocat(shared_ptr<Tehnician> teh) {
    tehnicianAlocat = teh;
}

void CerereReparatie::proceseaza() {
    if (durataRamasa > 0) {
        durataRamasa--;
    }
}

bool CerereReparatie::esteFinalizata() const {
    return durataRamasa == 0 && status == "in_lucru";
}

void CerereReparatie::calculeazaDurata() {
    if (complexitate == 0) {
        durataEstimata = 0;
        durataRamasa = 0;
        return;
    }
    
    int vechime = aparat->calculeazaVechime();
    durataEstimata = vechime * complexitate;
    durataRamasa = durataEstimata;
}

void CerereReparatie::calculeazaPret() {
    pretReparatie = aparat->getPretCatalog() * durataEstimata;
}

