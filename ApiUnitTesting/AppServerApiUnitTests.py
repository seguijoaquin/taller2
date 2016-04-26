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
        self.assertEqual(request.status_code,200)
        self.assertEqual(request.reason,self.msgLoginCorrecto)
        self.assertIsNotNone(request.headers["Token"])

    def test_LoginConUnUsuarioYPasswordIncorrectos(self):
        headUsuarioYPasswordIncorrectos = crearHeadersDeUsuarioYPassword( self.usuarioIncorrecto, self.passwordIncorrecto)
        request = requests.get(Address + URILogin,headers=headUsuarioYPasswordIncorrectos)
        self.assertEqual(request.status_code,400)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)

    def test_LoginConUnUsuarioIncorrecto(self):        
        headUsuarioIncorrecto = crearHeadersDeUsuarioYPassword( self.usuarioIncorrecto, passwordCorrecto)
        request = requests.get(Address + URILogin,headers=headUsuarioIncorrecto)
        self.assertEqual(request.status_code,400)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)

    def test_LoginConUnPasswordIncorrecto(self):        
        headPasswordIncorrecto = crearHeadersDeUsuarioYPassword( usuarioCorrecto, self.passwordIncorrecto)
        request = requests.get(Address + URILogin,headers=headPasswordIncorrecto)
        self.assertEqual(request.status_code,400)
        self.assertEqual(request.reason,self.msgLoginIncorrecto)

    # --------------------------------------------------------------------------
    # ----------------------------- Status CODE --------------------------------
    #---------------------------------------------------------------------------


    #   Tests que deberian dar status code 400 <--------------------------------

    #VER QUE ONDA SI ES RESPONSABILIDAD DEL APP SERVER O DEL CLIENTE.

    # def test_LoginSinUsuario(self):
    #     phead = {'PassWord': 'alskdjflaksdf'}
    #     request = requests.get(self.URI +'/login',headers=head)
    #     self.assertEqual(request.status_code,400)
    #
    # def test_LoginSinPassword(self):
    #     head = {'Usuario': 'hola'}
    #     request = requests.get(self.URI +'/login',headers=head)
    #     self.assertEqual(request.status_code,400)

    # def test_ParametroUserVacio(self):
    #     head = {'Usuario': '',
    #             'PassWord': 'alskdjflaksdf'}
    #     request = requests.get(self.URI +'/login',headers=head)
    #     self.assertEqual(request.status_code,400)
    #
    # def test_ParametroPasswordVacio(self):
    #     head = {'Usuario': 'hola',
    #             'PassWord': ''}
    #     request = requests.get(self.URI +'/login',headers=head)
    #     self.assertEqual(request.status_code,400)


    # Tests que deberian dar status code 200 -----------------------------------


    # TODO: Hacerlos despues de subir el registro.

    # def test_LoginConUsuarioValido(self):
    #     # TODO: registrar al usuario para que sea valido
    #     head= {'Usuario': 'usuario1',
    #         'PassWord': 'password1'}
    #     request = requests.get(self.URI +'/login', headers=head)
    #     self.assertEqual(request.status_code,200)

    # def test_LoginConTokenValido(self):
    #
    #     # TODO: registrar al usuario para que sea valido
    #     # TODO: Hacer el login para obtener el token y despues hacer login nuevamente.
    #     head= {'Usuario': 'usuario1',
    #         'PassWord': 'password1'}
    #     request = requests.get(self.URI +'/login', headers=head)
    #     token = request.headers['Token']
    #     token = { 'Token': token}
    #     request = requests.get(self.URI +'/login', headers=token)
    #     self.assertEqual(request.status_code,200)



class TestRegistro(unittest.TestCase):

    headUsuarioYaRegistrado = crearHeadersDeUsuarioYPassword(usuarioCorrecto, 'cualquierPassword')
    msgUsuarioYaRegistrado = "Usuario existente"
    msgUsuarioNuevoRegistrado = "Se pudo registrar el usuario"

    usuarioNuevo = "usuarioNuevo"
    passwordNuevo = "passwordNuevo"
    headUsuarioNuevo = crearHeadersDeUsuarioYPassword(usuarioNuevo, passwordNuevo)

    def test_RegistroDeUnUsuarioYaRegistrado(self):
        request = requests.put(Address + URIResgistro, headers=self.headUsuarioYaRegistrado)
        self.assertEqual(request.status_code,400)
        self.assertEqual(request.reason,self.msgUsuarioYaRegistrado)

    def test_RegistroDeUnUsuarioNuevo(self):
        request = requests.put(Address + URIResgistro, headers=self.headUsuarioNuevo)
        self.assertEqual(request.status_code,201)
        self.assertEqual(request.reason,self.msgUsuarioNuevoRegistrado)







if __name__ == '__main__':
    unittest.main()
