#ifndef LOCALIZACION_H
#define LOCALIZACION_H


#include "JsonObject.h"
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

/** Clase que gestiona la localizacion y la logica de calculo de distancias*/

class Localizacion
{
    public:
        Localizacion(string jsonLocalizacion);
        virtual ~Localizacion();
        JsonObject toJsonObject();

        double getLatitud();
        double getLongitud();

        void setLatitud(double latitud);
        void setLongitud(double longitud);

        /** Devuelve la distancia entre la localizacion que llama al metodo y
        * la pasada por parametro.
        */
        double getDistancia(Localizacion& localizacion);
    protected:
    private:
        double latitud;
        double longitud;

        double deg2rad(double deg);
        double rad2deg(double rad);
};

#endif // LOCALIZACION_H
