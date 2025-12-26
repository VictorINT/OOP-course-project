#include "ServiceException.h"

using namespace std;

ServiceException::ServiceException(const string& msg) : mesaj(msg) {}

const char* ServiceException::what() const noexcept {
    return mesaj.c_str();
}

InvalidCNPException::InvalidCNPException(const string& msg) 
    : ServiceException(msg) {}

InvalidAgeException::InvalidAgeException(const string& msg) 
    : ServiceException(msg) {}

InvalidDataException::InvalidDataException(const string& msg) 
    : ServiceException(msg) {}

OperationNotAllowedException::OperationNotAllowedException(const string& msg) 
    : ServiceException(msg) {}

