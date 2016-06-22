#include "ListadoDeIntereses.h"

ListadoDeIntereses::ListadoDeIntereses()
{
    //ctor
}

ListadoDeIntereses::~ListadoDeIntereses(){
    /*
     for (set<Interes*>::iterator it = this->intereses.begin(); it != this->intereses.end(); ++it){
        delete (*it);
    }
    */
}


string ListadoDeIntereses::toString(){
    JsonArray intereses;
    for (vector<Interes>::iterator it = this->intereses.begin(); it != this->intereses.end(); ++it ){
        JsonObject interesActual = (*it).toJsonObject();
        intereses.agregar(interesActual);
    }
    JsonObject listado;
    listado.agregarClaveValor("interests", intereses);

    string listadoString = listado.toString();
    Logger::Instance()->log(DEBUG, "Listado de intereses toString():\n" + listadoString);
    return listadoString;
}



void ListadoDeIntereses::agregarIntereses(string jsonListadoIntereses){
    Logger::Instance()->log(INFO, "Se agregan intereses al listado de intereses");
    JsonObject jsonListado(jsonListadoIntereses);
    JsonArray arrayIntereses = jsonListado.getJsonArray("interests");

    string jsonInteres;
    while (arrayIntereses>>jsonInteres){
        this->agregarInteres(jsonInteres);
    }
}

void ListadoDeIntereses::agregarInteres(string jsonInteres){
    Interes nuevoInteres(jsonInteres);
    if (!this->tieneInteres(nuevoInteres)){
        this->intereses.push_back(nuevoInteres);
    }
}

bool ListadoDeIntereses::tieneInteres(Interes& interes){
    bool encontrado = false;
    vector<Interes>::iterator it = this->intereses.begin();
    while ( (!encontrado) && (it != this->intereses.end()) ){
        encontrado = (*it).comparar(interes);
        ++it;
    }
    return encontrado;
}

int ListadoDeIntereses::size(){
    return this->intereses.size();
}

Interes ListadoDeIntereses::getInteres(int i){
    if ( ( i>= 1) && (i <= this->size() ) ){
        return this->intereses[i-1];
    }
    else{
        Logger::Instance()->log(WARNING, "En el listado de intereses se pidio un Interes fuera de rango, se devuelve un interes vacio");
        return Interes("");
    }
}

