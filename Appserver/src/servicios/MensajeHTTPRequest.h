#ifndef MENSAJEHTTPREQUEST_H
#define MENSAJEHTTPREQUEST_H


#include "MensajeHTTP.h"

using namespace std;

/*!
 * Clase que asbtrae los pedidos por medio de mensajes http
 */

class MensajeHTTPRequest: public MensajeHTTP
{
    public:
        //SACAR ESTE CONSTRUCTOR; LO DEJO POR AHORA PARA PROBAR ALGO
        MensajeHTTPRequest();
        MensajeHTTPRequest(http_message* mensajeMG);
        virtual ~MensajeHTTPRequest();

        string getMetodo();/*!< Devuelve el metodo del pedido: PUT, POST, GET, etc*/
        string getURI();/*!< Devuelve la URI del pedido*/
        string toString();/*!< Devuelve el mensaje en formato de string*/

        void setMetodo(string metodo);/*!< Setea el metodo del mensaje de peticion*/
        void setURI(string uri);/*!< Setea la uri del mensaje de peticion*/
    protected:
    private:
        string metodo;
        string uri;
};

#endif // MENSAJEHTTPREQUEST_H
