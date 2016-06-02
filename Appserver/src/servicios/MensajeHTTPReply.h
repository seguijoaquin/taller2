#ifndef MENSAJEHTTPREPLY_H
#define MENSAJEHTTPREPLY_H


#include "MensajeHTTP.h"

using namespace std;

class MensajeHTTPReply : public MensajeHTTP
{
    public:
        MensajeHTTPReply();
        MensajeHTTPReply(http_message* mensajeMG);
        virtual ~MensajeHTTPReply();

        void setCodigo(int codigo);
        int getCodigo();

        void setMensajeDeEstado(string mensaje);
        string getMensajeDeEstado();

        string toString();
    protected:
    private:
        int codigo;
        string mensajeDeEstado;
};

#endif // MENSAJEHTTPREPLY_H
