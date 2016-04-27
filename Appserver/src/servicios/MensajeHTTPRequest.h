#ifndef MENSAJEHTTPREQUEST_H
#define MENSAJEHTTPREQUEST_H

#include "StringUtil.h"
#include <string>
#include "mongoose.h"
#include <map>

using namespace std;

class MensajeHTTPRequest
{
    public:
        //SACAR ESTE CONSTRUCTOR; LO DEJO POR AHORA PARA PROBAR ALGO
        MensajeHTTPRequest();
        MensajeHTTPRequest(http_message* mensajeMG);
        virtual ~MensajeHTTPRequest();

        string getMetodo();
        string getURI();
        bool tieneHeader(string header);
        //Por ahora si NO tiene el header devuelve "", deberia devolder error?
        string getHeader(string header);

        /*// Por ahora no lo necesito
        string getBody();
        */
    protected:
    private:
        string metodo;
        string uri;

        map<string,string> headers;
        void cargarHeaders(http_message* mensajeMG);
        //string body;
        string mg_strToString(mg_str& mgStr);
};

#endif // MENSAJEHTTPREQUEST_H
