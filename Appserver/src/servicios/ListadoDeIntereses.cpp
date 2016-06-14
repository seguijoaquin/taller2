#include "ListadoDeIntereses.h"

ListadoDeIntereses::ListadoDeIntereses()
{
    //ctor
}

ListadoDeIntereses::~ListadoDeIntereses(){
     for (set<Interes*>::iterator it = this->intereses.begin(); it != this->intereses.end(); ++it){
        delete (*it);
    }
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
    this->intereses.insert(new Interes(jsonInteres));
}
