import json
import requests
import unittest



# Precondiciones:
# - La base de datos del servidor no debe contener usuarios.
# - El servidor debe cumplir las especificaciones de la api.

class TestLogin(unittest.TestCase):

    port = 5000

    URI = 'http://localhost:' + str(port);

    # --------------------------------------------------------------------------
    # ----------------------------- Status CODE --------------------------------
    #---------------------------------------------------------------------------


    #   Tests que deberian dar status code 400 <--------------------------------

    def test_LoginConUnUsuarioInvalido(self):
        parametros = 'user=damecincopepacompraesevi&password=patomarconlospienlaplaaza'
        rrequest = requests.get(self.URI +'/login?'+parametros)
        self.assertEqual(request.status_code,400)


    def test_LoginSinUsuario(self):
        parametros = 'password=algo'

    def test_LoginSinPassword(self):
        parametros = 'user=diego'
        request = requests.get(self.URI +'/login?'+parametros)
        self.assertEqual(request.status_code,400)

    def test_ParametroUserVacio(self):
        parametros = 'user=&password=3333122'
        request = requests.get(self.URI +'/login?'+parametros)
        self.assertEqual(request.status_code,400)

    def test_ParametroPasswordVacio(self):
        parametros = 'user=asdasdasd&password='
        request = requests.get(self.URI +'/login?'+parametros)
        self.assertEqual(request.status_code,400)


    # Tests que deberian dar status code 200 -----------------------------------


    # TODO: Hacerlos despues de subir el registro.

    # def test_LoginConUsuarioValido(self):
    #     # TODO: registrar al usuario para que sea valido
    #     parametros = 'user=diego&password=12345678'
    #     request = requests.get(self.URI +'/login?'+parametros)
    #     self.assertEqual(request.status_code,200)
    #
    # def test_LoginConTokenValido(self):
    #
    #     # TODO: registrar al usuario para que sea valido
    #     # TODO: Hacer el login para obtener el token y despues hacer login nuevamente.
    #
    #     parametros = 'user=diego&password=12345678'
    #     request = requests.get(self.URI +'/login?'+parametros)
    #     self.assertEqual(request.status_code,200)










if __name__ == '__main__':
    unittest.main()
