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
    return listado.toString();
}



void ListadoDeIntereses::agregarIntereses(string jsonListadoIntereses){
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
        return Interes("");
    }
}

