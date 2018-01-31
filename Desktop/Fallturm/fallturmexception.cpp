#include "fallturmexception.h"

const char* FallturmException::what()
{
    QByteArray ba = errorMsg.toLatin1();
    const char* ca = ba.data();
    return ca;
}
