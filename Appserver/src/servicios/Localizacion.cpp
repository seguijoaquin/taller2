#include "Localizacion.h"

Localizacion::Localizacion(string jsonLocalizacion){
    JsonObject posicion(jsonLocalizacion);
    this->latitud = posicion.getDouble("latitude");
    this->longitud = posicion.getDouble("longitude");
}

Localizacion::~Localizacion(){
    //dtor
}

JsonObject Localizacion::toJsonObject(){
    JsonObject posicion;
    posicion.agregarClaveValor("latitude", this->latitud );
    posicion.agregarClaveValor("longitude", this->longitud );
    return posicion;
}

double Localizacion::getLatitud(){
    return this->latitud;
}

double Localizacion::getLongitud(){
    return this->longitud;
}

void Localizacion::setLatitud(double latitud){
    this->latitud = latitud;
}

void Localizacion::setLongitud(double longitud){
    this->longitud = longitud;
}

double Localizacion::getDistancia(Localizacion& localizacion){
    //http://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(this->latitud);
    lon1r = deg2rad(this->longitud);
    lat2r = deg2rad(localizacion.getLatitud());
    lon2r = deg2rad(localizacion.getLongitud());
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


double Localizacion::deg2rad(double deg){
  return (deg * pi / 180);
}


double Localizacion::rad2deg(double rad){
  return (rad * 180 / pi);
}




