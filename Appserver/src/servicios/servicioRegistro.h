#ifndef SERVICIOREGISTRO_H
#define SERVICIOREGISTRO_H

//#include "mongoose.h"
#include <iostream>
#include <map>

//#include "json/json.h"
#include "JsonObject.h"
#include "JsonArray.h"

#include <fstream>
#include "MensajeHTTPRequest.h"
#include "CredencialesDeUsuarios.h"

#include "RespuestaDelRegistro.h"

#include "Servicio.h"
#include "SharedDataBase.h"
#include "AdministradorCandidatos.h"

//class ManejadorDeConexiones;
using namespace std;

/** Clase encargada de gestionar el registro
 * de usuarios al sistema.
 * registra al usuario en el Shared, 
 * en las Credenciales y lo inicializa en el Adminsitrador
 * a partir de un mensaje http
 */

class servicioRegistro : public Servicio
{
    public:
        servicioRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos);
        ~servicioRegistro();

        //string getRespuesta();
    protected:
    private:
        SharedDataBase* shared;
        MensajeHTTPRequest mensajeHTTP;
        CredencialesDeUsuarios* usuariosRegistrados;
        AdministradorCandidatos* administradorCandidatos;

        //string crearMensajeParaAlta(string usuario);
        //void agregarInteresAlJarray(string interes, string valor, JsonArray& jarray );

        void atenderRegistro();
        //void realizarRegistro(string usuario, string password);
        void realizarRegistro(Usuario& usuario, string password);

        string getClaveParaRegistrarse(Usuario& usuario);





};

#endif // SERVICIOREGISTRO_H
