import json
import requests
import unittest
import Utilities


class TestManejarPerfil(unittest.TestCase):
    usuariosParaBorrar = []

    def tearDown(self):
        Utilities.borrarUsuarios(self.usuariosParaBorrar)

    def compararJsons(self, perfilEsperado,perfilPedido, key):
        self.assertEqual(perfilEsperado[key] ,perfilPedido[key])

    def compararJsonsPosicion(self, perfilEsperado,perfilPedido):
        self.assertAlmostEqual(perfilEsperado["location"]["latitude"], perfilPedido["location"]["latitude"], places=3, msg=None, delta=None)
        self.assertAlmostEqual(perfilEsperado["location"]["longitude"], perfilPedido["location"]["longitude"], places=3, msg=None, delta=None)

    def compararPerfilEsperadConElObtenido(self,perfilEsperado,perfilPedido):
        self.compararJsons(perfilEsperado,perfilPedido, "email")
        self.compararJsons(perfilEsperado,perfilPedido, "name")
        self.compararJsons(perfilEsperado,perfilPedido, "interests")
        self.compararJsons(perfilEsperado,perfilPedido, "alias")
        self.compararJsons(perfilEsperado,perfilPedido, "sex")
        self.compararJsons(perfilEsperado,perfilPedido, "age")
        self.compararJsonsPosicion(perfilEsperado,perfilPedido)

    def test_ObtenerPerfilDebeDevolverElMismoPerfil(self):
        usuario = Utilities.transformarEnMail("test_ObtenerPerfil")
        tokenSesion = Utilities.registrarYLoguearAlUsuarioSinEmail(usuario)
        perfilPedido = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];
        perfilEsperado = Utilities.abrirUsuarioConEmail(usuario)["user"]

        self.compararPerfilEsperadConElObtenido(perfilEsperado,perfilPedido)

        self.usuariosParaBorrar.extend([usuario])

    def test_ActualizarPosicion(self):
        usuario = Utilities.transformarEnMail("test_ActualizarPosicion1")
        tokenSesion = Utilities.registrarYLoguearAlUsuarioSinEmail(usuario)
        #VALORES DIFERENTES A LOS QUE SE CARGAN EN EL JSON DE Utilities.registrarYLoguearAlUsuarioSinEmail
        nuevaLatitud = 55.4444000
        nuevaLongitud = 15.4243744
        Utilities.modificarPosicion(usuario,tokenSesion, nuevaLatitud, nuevaLongitud)

        perfilPedido = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];
        self.assertAlmostEqual(perfilPedido["location"]["latitude"], nuevaLatitud, places=3, msg=None, delta=None)
        self.assertAlmostEqual(perfilPedido["location"]["longitude"], nuevaLongitud, places=3, msg=None, delta=None)

        self.usuariosParaBorrar.extend([usuario])



    def test_ActualizarFotoDePerfil(self):
        usuario = Utilities.transformarEnMail("test_ActualizarFotoDePerfil")
        tokenSesion = Utilities.registrarYLoguearAlUsuarioSinEmail(usuario)
        #Ejemplo de base64 sacado de wikipedia https://en.wikipedia.org/wiki/Base64
        nuevaFoto = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="
        Utilities.modificarFotoPerfil(usuario,tokenSesion, nuevaFoto)

        perfilPedido = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];
        self.assertEqual(nuevaFoto, perfilPedido["photo_profile"])
        self.usuariosParaBorrar.extend([usuario])

    def test_ModificarDatosDelPerfil(self):
        usuario = Utilities.transformarEnMail("test_ModificarDatosDelPerfil")
        tokenSesion = Utilities.registrarYLoguearAlUsuarioSinEmail(usuario)
        #pido el perfil inicial
        perfilPedido = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];

        #lo copio a un nuevo perfil
        nuevoPerfil = perfilPedido
        #lo modifico
        nuevoPerfil["name"] = "NUEVO_NOMBRE_DE_test_ActualizarFotoDePerfil"
        nuevoPerfil["alias"] = "NUEVO_ALIAS_DE_test_ActualizarFotoDePerfil"
        nuevoPerfil["alias"] = "NUEVO_ALIAS_DE_test_ActualizarFotoDePerfil"
        nuevoPerfil["age"] = 99
        #mando la modificacion
        Utilities.modificarPerfil(usuario, tokenSesion, nuevoPerfil)
        #lo pido de nuevo
        perfilPedidoLuegoDeLaModificacion = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];
        #EL nuevo perfil pedido debe ser igual al perfil modificado
        self.compararPerfilEsperadConElObtenido(nuevoPerfil,perfilPedidoLuegoDeLaModificacion)
        self.usuariosParaBorrar.extend([usuario])
