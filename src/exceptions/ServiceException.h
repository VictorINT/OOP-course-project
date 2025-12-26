#ifndef SERVICE_EXCEPTION_H
#define SERVICE_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

// Exceptie de baza pentru aplicatie
class ServiceException : public exception {
protected:
    string mesaj;
    
public:
    explicit ServiceException(const string&);
    const char* what() const noexcept override;
};

// Exceptie pentru CNP invalid
class InvalidCNPException : public ServiceException {
public:
    explicit InvalidCNPException(const string&);
};

// Exceptie pentru varsta invalida
class InvalidAgeException : public ServiceException {
public:
    explicit InvalidAgeException(const string&);
};

// Exceptie pentru date invalide
class InvalidDataException : public ServiceException {
public:
    explicit InvalidDataException(const string&);
};

// Exceptie pentru operatie nesuportata
class OperationNotAllowedException : public ServiceException {
public:
    explicit OperationNotAllowedException(const string&);
};

#endif

