#ifndef MENSAJEHTTPREQUEST_H
#define MENSAJEHTTPREQUEST_H

#include "StringUtil.h"
#include "MensajeHTTP.h"

using namespace std;

class MensajeHTTPRequest: public MensajeHTTP
{
    public:
        //SACAR ESTE CONSTRUCTOR; LO DEJO POR AHORA PARA PROBAR ALGO
        MensajeHTTPRequest();
        MensajeHTTPRequest(http_message* mensajeMG);
        virtual ~MensajeHTTPRequest();

        string getMetodo();
        string getURI();
        string toString();
    protected:
    private:
        string metodo;
        string uri;
};

#endif // MENSAJEHTTPREQUEST_H
