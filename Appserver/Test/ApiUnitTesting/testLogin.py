import json
import requests
import unittest



# Precondiciones:
# - La base de datos del servidor no debe contener usuarios.
# - El servidor debe cumplir las especificaciones de la api.#
# - La base de datos tiene un usuario registrado con el nombre "usuario" y password "password"
# Login:
# - La base de datos NO tiene un usuario registrado con el nombre "usuarioFalso" y password "passwordFalso"
# Registro:
# - La base de datos NO tiene un usuario registrado con el nombre "usuarioNuevo" y password "passwordNuevo"


Address = "http://localhost:8000"
#Tal vez mandar las URIs a sus respectivas clases
URILogin = "/login"
URIResgistro = "/registro"

usuarioCorrecto = 'usuario'
passwordCorrecto = 'password'

def crearHeadersDeUsuarioYPassword(usuario, password):
    return {'Usuario': usuario,'Password': password }

class TestLogin(unittest.TestCase):

    msgLoginCorrecto = "Se logueo correctamente"
    msgLoginIncorrecto = "No coinciden los datos"

    usuarioIncorrecto = 'usuarioFalso'
    passwordIncorrecto = 'passwordFalso'

    def test_LoginConUnUsuarioRegistrado(self):
        headUsuarioRegistrado = crearHeadersDeUsuarioYPassword( usuarioCorrecto, passwordCorrecto)
        request = requests.get(Address + URILogin,headers=headUsuarioRegistrado)
        self.assertEqual(request.reason,self.msgLoginCorrecto)
        self.assertEqual(request.status_code,200)
        self.assertIsNotNone(request.headers["Token"])

    def test_LoginConUnUsuarioYPasswordIncorrectos(self):
        headUsuarioYPasswordIncorrectos = crearHeadersDeUsuarioYPassword( self.usuarioIncorrecto, self.passwordIncorrecto)
        request = requests.get(Address + URILogin,headers=headUsuarioYPasswordIncorrectos)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)
        self.assertEqual(request.status_code,400)


    def test_LoginConUnUsuarioIncorrecto(self):
        headUsuarioIncorrecto = crearHeadersDeUsuarioYPassword( self.usuarioIncorrecto, passwordCorrecto)
        request = requests.get(Address + URILogin,headers=headUsuarioIncorrecto)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)
        self.assertEqual(request.status_code,400)

    def test_LoginConUnPasswordIncorrecto(self):
        headPasswordIncorrecto = crearHeadersDeUsuarioYPassword( usuarioCorrecto, self.passwordIncorrecto)
        request = requests.get(Address + URILogin,headers=headPasswordIncorrecto)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)
        self.assertEqual(request.status_code,400)
