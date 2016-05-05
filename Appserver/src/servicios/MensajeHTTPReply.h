#ifndef MENSAJEHTTPREPLY_H
#define MENSAJEHTTPREPLY_H

#include "StringUtil.h"
#include "MensajeHTTP.h"

using namespace std;

class MensajeHTTPReply : public MensajeHTTP
{
    public:
        MensajeHTTPReply();
        MensajeHTTPReply(http_message* mensajeMG);
        virtual ~MensajeHTTPReply();

        int getCodigo();
        string getMensajeDeEstado();
        string toString();
    protected:
    private:
        int codigo;
        string mensajeDeEstado;
};

#endif // MENSAJEHTTPREPLY_H
