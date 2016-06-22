import json
import requests
import unittest
import Utilities
from testLogin import *
from testChat import *
from testBusquedaCandidatos import *
from testPerfil import *



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




class TestRegistro(unittest.TestCase):

    headUsuarioYaRegistrado = crearHeadersDeUsuarioYPassword(usuarioCorrecto, 'cualquierPassword')
    msgUsuarioYaRegistrado = "Usuario existente"
    msgUsuarioNuevoRegistrado = "Se pudo registrar el usuario"

    usuarioNuevo = "usuarioNuevo"
    passwordNuevo = "passwordNuevo"
    headUsuarioNuevo = crearHeadersDeUsuarioYPassword(usuarioNuevo, passwordNuevo)

    def crearBodyUsuario(self, nombre):
        body = Utilities.abrirJson("./usuarioCompleto.json")
        body["user"]["email"] = nombre
        return body

    def load_tests(loader, tests, pattern):
	suite = TestSuite()
	for test_class in test_cases:
		tests = loader.loadTestsFromTestCase(test_class)
		suite.addTests(tests)
    	return suite

    def test_RegistroDeUnUsuarioYaRegistrado(self):

        bodyUsuario = self.crearBodyUsuario(usuarioCorrecto)
        request = requests.put(Address + URIResgistro, headers=self.headUsuarioYaRegistrado, data=json.dumps(bodyUsuario) )

        self.assertEqual(request.reason,self.msgUsuarioYaRegistrado)
        self.assertEqual(request.status_code,400)


    def test_RegistroDeUnUsuarioNuevo(self):
        bodyUsuario = self.crearBodyUsuario(self.usuarioNuevo)
        request = requests.put(Address + URIResgistro, headers=self.headUsuarioNuevo, data=json.dumps(bodyUsuario))
        self.assertEqual(request.reason,self.msgUsuarioNuevoRegistrado)
        self.assertEqual(request.status_code,201)



class TestRegistroYLogin(unittest.TestCase):

    headUsuarioYaRegistrado = crearHeadersDeUsuarioYPassword(usuarioCorrecto, 'cualquierPassword')

    msgLoginCorrecto = "Se logueo correctamente"
    msgLoginIncorrecto = "No coinciden los datos"

    msgUsuarioYaRegistrado = "Usuario existente"
    msgUsuarioNuevoRegistrado = "Se pudo registrar el usuario"

    def crearBodyUsuario(self, nombre):
        body = Utilities.abrirJson("./usuarioCompleto.json")
        body["user"]["email"] = nombre
        return body

    def test_IntentoDeLoginDeUnUsuarioNoRegistrado_SeLoRegistra_SeDebePoderLoguearCorrectamente(self):

	#Me intento loguear con un usuario no registrado y no puedo
        #headUsuario = crearHeadersDeUsuarioYPassword( "IntentoDeLoginDeUnUsuarioNoRegistrado_SeLoRegistra_SeDebePoderLoguearCorrectamente", "12345")
        headUsuario = crearHeadersDeUsuarioYPassword( "IntentoDeLoginDeUnUsuarioNoRegistrado", "12345")
        request = requests.get(Address + URILogin,headers=headUsuario)
        self.assertEqual(request.status_code,400)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)

	#Lo registro
        bodyUsuario = self.crearBodyUsuario("IntentoDeLoginDeUnUsuarioNoRegistrado")
        request = requests.put(Address + URIResgistro, headers=headUsuario, data=json.dumps(bodyUsuario))
        self.assertEqual(request.status_code,201)
        self.assertEqual(request.reason,self.msgUsuarioNuevoRegistrado)

	#Ahora me puedo loguear correctamente
        request = requests.get(Address + URILogin,headers=headUsuario)
        self.assertEqual(request.status_code,200)
        self.assertEqual(request.reason,self.msgLoginCorrecto)
        self.assertIsNotNone(request.headers["Token"])







if __name__ == '__main__':
    unittest.main()
