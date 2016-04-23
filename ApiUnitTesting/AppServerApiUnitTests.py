import json
import requests
import unittest



# Precondiciones:
# - La base de datos del servidor no debe contener usuarios.
# - El servidor debe cumplir las especificaciones de la api.

class TestLogin(unittest.TestCase):

    port = 8000

    URI = 'http://10.1.151.198:' + str(port);

    # --------------------------------------------------------------------------
    # ----------------------------- Status CODE --------------------------------
    #---------------------------------------------------------------------------


    #   Tests que deberian dar status code 400 <--------------------------------

    # def test_LoginConUnUsuarioInvalido(self):
    #     head = {'Usuario': 'Frezzer',
    #     'PassWord': '123456'}
    #     request = requests.get(self.URI +'/login',headers=head)
    #     self.assertEqual(request.status_code,400)



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

    port = 8000

    URI = 'http://10.1.151.198:' + str(port);


    def test_RegistroDeUnUsuarioValido(self):
        head = {
            'Usuario': 'Usuariooooasdasooooo',
            'PassWord': '123456'
        }


        request = requests.put(self.URI+'/registro',headers=head)
        self.assertEqual(request.status_code,200)








if __name__ == '__main__':
    unittest.main()
