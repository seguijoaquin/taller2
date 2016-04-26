#ifndef CONSTANTESEVENTOSSERVICIOS_INCLUDED
#define CONSTANTESEVENTOSSERVICIOS_INCLUDED

//En comparacion a los define me evito tener que poner los nros a mano y tener que poner "#define"
//Ademas tira Warnings si falta abarcar algun enum en algun switch
enum ServicioALanzar {
    LANZAR_SERVICIO_REGISTRO,
    LANZAR_SERVICIO_LOGIN,
    LANZAR_SERVICIO_SIN_PERMISO,
    LANZAR_SERVICIO_CERRAR
};






#endif // CONSTANTESEVENTOSSERVICIOS_INCLUDED
