#ifndef ATENDEDORHTTP_H
#define ATENDEDORHTTP_H


#include "servicioRegistro.h"
#include "servicioLogin.h"


class AtendedorHTTP
{
    public:
        AtendedorHTTP(http_message* mensajeHTTP, rocksdb::DB* credencialesUsuarios, mg_mgr* manager);
        virtual ~AtendedorHTTP();

        string getRespuesta();
    protected:
    private:
        /*Por ahora solo la necesito para llamar al registrador y al logginer, tal vez quede mejor poniendolo como
         una variable estatica de una clase "Servicio"
         Lo mismo con el manager....
         La otra serie hacer que esta clase setee EVENTOS en el Server y que otra clase dentro del server se encargue de instanciar los servicios
         Lo malo de ese caso es que si quiero agregar un servicio tendria que agreagarlo al atendedor, a la lista de eventos y al case que maneje lanzar los servicios
         Lo bueno es que AtendedorHTTP solo se manejaria con los parametros que necesita

         Lo malo de ESTA implementacion (la que estoy usando) es que si necesito lanzar un servicio con otro tipo de parametro, tendria que agregarlo al constructor
         y a la larga podria quedar un constructor enorme
         Lo bueno es que si quiero agregar un servicio solo tengo que hacerlo en una porcion especifica de codigo, en vez de 3

         Creo que lo que define es la cantidad de cosas diferentes que necesite (y si se las tendría que pasar al atendedorHTTP)
         por ejemplo conversaciones
         O podria poner esas cosas como variables de clase(staticas)
        */
        rocksdb::DB* credencialesUsuarios;
        mg_mgr* manager;

        http_message* mensajeHTTP;
        string respuesta;

        void atenderMesajeHTTP();
        bool compararMetodoHTTP(http_message* mensajeHTTP, char* metodo);
        bool compararUriHTTP(http_message* mensajeHTTP, char* uri);
};

#endif // ATENDEDORHTTP_H
