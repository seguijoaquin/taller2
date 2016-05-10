#ifndef MENSAJEHTTP_H
#define MENSAJEHTTP_H

#include <string>
#include "mongoose.h"
#include <map>

using namespace std;

class MensajeHTTP
{
    public:
        MensajeHTTP();
        MensajeHTTP(http_message* mensajeMG);
        virtual ~MensajeHTTP();


        bool tieneHeader(string header);
        //Por ahora si NO tiene el header devuelve "", deberia devolder error?
        string getHeader(string header);
        string getBody();

        void setBody(string body);
        //Si esta repetido lo actualiza, si no existe lo crea
        void agregarHeader(string header, string valor);

        virtual string toString() = 0;
    protected:
        string body;
        map<string,string> headers;
        void cargarHeaders(http_message* mensajeMG);
        string mg_strToString(mg_str& mgStr);
        string headersToString();
    private:

};

#endif // MENSAJEHTTP_H
