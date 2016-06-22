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

    def compararPerfilEsperadConElObtenido(self,perfilEsperado,perfilPedido):
        self.compararJsons(perfilEsperado,perfilPedido, "email")
        self.compararJsons(perfilEsperado,perfilPedido, "name")
        self.compararJsons(perfilEsperado,perfilPedido, "interests")
        self.compararJsons(perfilEsperado,perfilPedido, "alias")
        self.compararJsons(perfilEsperado,perfilPedido, "sex")
        self.compararJsons(perfilEsperado,perfilPedido, "age")
        self.compararJsonsPosicion(perfilEsperado,perfilPedido)

    def test_ObtenerPerfilDebeDevolverElMismoPerfil(self):
        usuario = "test_ObtenerPerfil"
        tokenSesion = Utilities.registrarYLoguearAlUsuarioSinEmail(usuario)
        perfilPedido = Utilities.pedirPerfil(usuario, tokenSesion, usuario)["user"];
        perfilEsperado = Utilities.abrirUsuarioConEmail(usuario)["user"]

        self.compararPerfilEsperadConElObtenido(perfilEsperado,perfilPedido)

        self.usuariosParaBorrar.extend([usuario])
