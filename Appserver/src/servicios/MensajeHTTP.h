#ifndef MENSAJEHTTP_H
#define MENSAJEHTTP_H

#include <string>
#include "mongoose.h"
#include <map>
#include "StringUtil.h"

using namespace std;

/*!
 * Clase que abstrae del comportamiento de la biblioteca utilizada para el manejo de mensajes http
 */

class MensajeHTTP
{
    public:
        MensajeHTTP();
        MensajeHTTP(http_message* mensajeMG);
        virtual ~MensajeHTTP();


        bool tieneHeader(string header);/*!< Devuelve true si el header fue seteado para este mensaje*/
    
        //Por ahora si NO tiene el header devuelve "", deberia devolder error?
        string getHeader(string header);/*!< Devuelve el valor del header correspondiente*/
        string getBody();/*!< Devuelve el body del mensaje*/

        void setBody(string body);/*!< Setea el body del mensaje*/
        //Si esta repetido lo actualiza, si no existe lo crea
        void agregarHeader(string header, string valor);/*!< Agrega un header al mensaje*/

        virtual string toString() = 0;/*!< Devuelve el contenido del mensaje http en formato de string*/
    protected:
        string body;
        map<string,string> headers;
        void cargarHeaders(http_message* mensajeMG);
        string mg_strToString(mg_str& mgStr);
        string headersToString();
    private:

};

#endif // MENSAJEHTTP_H
