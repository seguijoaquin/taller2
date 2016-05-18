#ifndef CONVERSACIONESTESTS_H
#define CONVERSACIONESTESTS_H
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <vector>
#include "Conversaciones.h"

using namespace std;


class ConversacionesTests : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( ConversacionesTests );
    CPPUNIT_TEST( testObtenerMensajesEntreUsuariosQueNoConversaronDevuelveUnaConversacionVacia );
    CPPUNIT_TEST( testObtenerElMensajeDeUnaConversacionConUnUnicoMensaje );
    CPPUNIT_TEST( testElMensajeDeMenorIndiceEsElMensajeMasNuevo );
    CPPUNIT_TEST( testSiSePidenMasMensajesDeLosQueHaySeDevuelvenTodosLosMensajes );
    CPPUNIT_TEST( testPedirUnaCantidadDeMensajesDesdeUnMensajeQueNoSeaElPrimero );
    CPPUNIT_TEST( testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado );

    CPPUNIT_TEST_SUITE_END();

  public:
    ConversacionesTests();
    ~ConversacionesTests();
    void setUp();
    void tearDown();

    void testObtenerMensajesEntreUsuariosQueNoConversaronDevuelveUnaConversacionVacia();
    void testObtenerElMensajeDeUnaConversacionConUnUnicoMensaje();
    void testElMensajeDeMenorIndiceEsElMensajeMasNuevo();
    void testSiSePidenMasMensajesDeLosQueHaySeDevuelvenTodosLosMensajes();
    void testPedirUnaCantidadDeMensajesDesdeUnMensajeQueNoSeaElPrimero();
    void testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado();

  private:
    Conversaciones* conversaciones;
    bool verificarMensajeVacio(Mensajes& mensajes, int indice);
    bool compararMensajeConLista(Mensajes& mensajes, int indiceMensajes, vector<pair<string,string>>& listaMensajes, int indiceLista);
    vector<pair<string,string>> crearListaDeMensajes(string usuario1, string usuario2, int cantidad);
    void agregarMensajesAConversaciones(string usuario1, string usuario2, vector<pair<string,string>>& listaMensajes);
};


#endif // CONVERSACIONESTESTS_H
