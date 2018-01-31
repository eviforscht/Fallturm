#ifndef FALLTURMEXCEPTION_H
#define FALLTURMEXCEPTION_H

#include <exception>
#include <string>

#include <QString>

class FallturmException : public std::exception
{
public:
    FallturmException() = default;
    FallturmException(QString error) :errorMsg(error) {}
    FallturmException(std::string error) : errorMsg(QString::fromStdString(error)) {}
    const char* what();

private:
    QString errorMsg;
};

class SerialException : public FallturmException
{
public:
    SerialException() = default;
    SerialException(QString error) : FallturmException(error) {}
    SerialException(std::string error) : FallturmException(error) {}
};

#endif // FALLTURMEXCEPTION_H
