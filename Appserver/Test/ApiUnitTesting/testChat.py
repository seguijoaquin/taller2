import json
import requests
import unittest



# Precondiciones:
# Conversaciones:
# 	Debe haber un usuario en la base de datos que se llame "usuarioTestChat1" y "usuarioTestChat2" con contrasenia "password"
#


Address = "http://localhost:8000"
#Tal vez mandar las URIs a sus respectivas clases
URILogin = "/login"
URIChat = "/chat"
URIMensajes = "/mensajes"


def crearHeadersDeUsuarioYPassword(usuario, password):
    return {'Usuario': usuario,'Password': password, 'TokenGCM': "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ" }


class TestChat(unittest.TestCase):

    usuario1 = 'usuarioTestChat1'
    usuario2 = 'usuarioTestChat2'
    passwordCorrecto = 'password' #lo uso para ambos usuarios

    msgMensajeEnviadoCorrectamente = "OK"

    usuarioIncorrecto = 'usuarioFalso'
    passwordIncorrecto = 'passwordFalso'

    def hacerLoginDeUsuario(self, usuario):
        headUsuarioRegistrado = crearHeadersDeUsuarioYPassword( usuario, self.passwordCorrecto)
        reply = requests.get(Address + URILogin,headers=headUsuarioRegistrado)
        return reply

    def crearHeadersDeChat(self, usuario, receptor, token):
        return {'Usuario': usuario,'Receptor': receptor, 'Token': token }

    def crearHeadersDePedirMensajes(self, usuario1, usuario2, token, cantidad, desde):
        return {'Usuario1': usuario1,'Usuario2': usuario2, 'Token': token, 'Cantidad': cantidad, 'Desde': desde }

    def test_Usuario1LeMandaUnMensajeAlUsuario2(self):
        reply1 = self.hacerLoginDeUsuario(self.usuario1)
        reply2 = self.hacerLoginDeUsuario(self.usuario2)
        mensajeUsuario1AlUsuario2 = "Hola\n"
        headChat = self.crearHeadersDeChat(self.usuario1, self.usuario2, reply1.headers["Token"])

        replyChat = requests.post(Address + URIChat, headers=headChat, data=mensajeUsuario1AlUsuario2)
        self.assertEqual(replyChat.reason,self.msgMensajeEnviadoCorrectamente)
        self.assertEqual(replyChat.status_code,200)

    def test_Usuario1LeMandaUnMensajeAlUsuario2YSePideElUltimoMensajeParaVerificarQueSeaElMismo(self):
        #Se loguean
        reply1 = self.hacerLoginDeUsuario(self.usuario1)
        reply2 = self.hacerLoginDeUsuario(self.usuario2)
        #Manda el mensaje
        mensajeUsuario1AlUsuario2 = "test_Usuario1LeMandaUnMensajeAlUsuario2YSePideElUltimoMensajeParaVerificarQueSeaElMismo"
        headChat = self.crearHeadersDeChat(self.usuario1, self.usuario2, reply1.headers["Token"])
        requests.post(Address + URIChat, headers=headChat, data=mensajeUsuario1AlUsuario2)
        #Se pide el ultimo mensaje
        headMensajes = self.crearHeadersDePedirMensajes(self.usuario1, self.usuario2, reply1.headers["Token"], 1, 1)
        replyMensajes = requests.get(Address + URIMensajes, headers=headMensajes)
        self.assertEqual(replyMensajes.json()[0]["emisor"], self.usuario1)
        self.assertEqual(replyMensajes.json()[0]["mensaje"], mensajeUsuario1AlUsuario2)
