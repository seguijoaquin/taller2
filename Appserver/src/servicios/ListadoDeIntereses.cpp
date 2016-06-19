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


void ListadoDeIntereses::agregarIntereses(string jsonListadoIntereses){
    JsonObject jsonListado(jsonListadoIntereses);
    JsonArray arrayIntereses = jsonListado.getJsonArray("interests");

    string jsonInteres;
    while (arrayIntereses>>jsonInteres){
        this->agregarInteres(jsonInteres);
    }
}

void ListadoDeIntereses::agregarInteres(string jsonInteres){
    this->intereses.push_back(Interes(jsonInteres));
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
