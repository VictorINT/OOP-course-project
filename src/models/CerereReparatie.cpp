#include "../../include/models/CerereReparatie.h"
#include "../../include/models/Tehnician.h"

CerereReparatie::CerereReparatie() : id(0), aparat(nullptr), descriereDefect(""), status(StatusCerere::IN_ASTEPTARE), tehnicianAlocat(nullptr), dataInregistrare(0), dataFinalizare(0), costPiese(0.0), costManopera(0.0) {}

CerereReparatie::CerereReparatie(int id, Electrocasnic* aparat, const string& descriere) : id(id), aparat(aparat), descriereDefect(descriere), status(StatusCerere::IN_ASTEPTARE), tehnicianAlocat(nullptr), dataInregistrare(0), dataFinalizare(0), costPiese(0.0), costManopera(0.0) {}

CerereReparatie::~CerereReparatie() {}

int CerereReparatie::getId() const {
    return id;
}

Electrocasnic* CerereReparatie::getAparat() const {
    return aparat;
}

string CerereReparatie::getDescriereDefect() const {
    return descriereDefect;
}

StatusCerere CerereReparatie::getStatus() const {
    return status;
}

Tehnician* CerereReparatie::getTehnicianAlocat() const {
    return tehnicianAlocat;
}

long long CerereReparatie::getDataInregistrare() const {
    return dataInregistrare;
}

long long CerereReparatie::getDataFinalizare() const {
    return dataFinalizare;
}

double CerereReparatie::getCostPiese() const {
    return costPiese;
}

double CerereReparatie::getCostManopera() const {
    return costManopera;
}

void CerereReparatie::setStatus(StatusCerere status) {
    this->status = status;
}

void CerereReparatie::setTehnicianAlocat(Tehnician* tehnician) {
    tehnicianAlocat = tehnician;
}

void CerereReparatie::setDataFinalizare(long long data) {
    dataFinalizare = data;
}

void CerereReparatie::setDataInregistrare(long long data) {
    dataInregistrare = data;
}

void CerereReparatie::setCostPiese(double cost) {
    costPiese = cost;
}

void CerereReparatie::setCostManopera(double cost) {
    costManopera = cost;
}

double CerereReparatie::getCostTotal() const {
    return costPiese + costManopera;
}

int CerereReparatie::getDurataReparatie() const {
    if (dataFinalizare <= 0 || dataInregistrare <= 0) {
        return 0;
    }

    long long durata = dataFinalizare - dataInregistrare;
    if (durata < 0) {
        return 0;
    }

    return static_cast<int>(durata);
}
