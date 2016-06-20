#ifndef MENSAJEHTTPREPLY_H
#define MENSAJEHTTPREPLY_H


#include "MensajeHTTP.h"

using namespace std;

/*!
 * Permite abstraer las respuestas a los mensajes http
 */

class MensajeHTTPReply : public MensajeHTTP
{
    public:
        MensajeHTTPReply();
        MensajeHTTPReply(http_message* mensajeMG);
        virtual ~MensajeHTTPReply();

        void setCodigo(int codigo);/*!< Esta funcion nos permite setear el codigo de respuesta. Nos interesara en caso de ser quienes enviamos el mensaje*/
        int getCodigo();/*!< Esta funcion nos permite ver el codigo de la respuesta. Nos interesara en el caso de ser quienes enviamos el mensaje y queremos ver cual es el codigo de la respuesta*/

        void setMensajeDeEstado(string mensaje); /*!< Nos permite setear un mensaje de estado a la respuesta*/
        string getMensajeDeEstado();/*!< Nos permite obtener el mensaje de estado de una respuesta*/

        string toString();/*!< Devuelve el contenido del mensaje en formato de string*/
    protected:
    private:
        int codigo;
        string mensajeDeEstado;
};

#endif // MENSAJEHTTPREPLY_H
