import json
import requests
import unittest



# Precondiciones:
# Intereses:
# 	No debe haber ningun usuario en el Shared que tenga "interesUnico"
#


Address = "http://localhost:8000"
#Tal vez mandar las URIs a sus respectivas clases
URIResgistro = "/registro"
URILogin = "/login"
URIPedirCandidato = "/perfil"
URIEliminar = "/eliminar"


def crearHeadersParaRegistro(usuario):
    return {'Usuario': usuario,'Password': "password"}#, 'Content-Type': 'application/json' }

def crearHeadersParaElLogin(usuario):
    return {'Usuario': usuario,'Password': "password", 'TokenGCM': "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ" }

def abrirJson(ruta):
    with open(ruta, 'r') as archivoJson:
        parseado = json.load(archivoJson)
        return parseado

def crearHeadersParaBuscarCandidatos(usuario,token):
    return {'Usuario': usuario, 'Token': token}

class TestBusquedaCandidatos(unittest.TestCase):

    usuario1 = 'usuarioCandidato1'
    usuario2 = 'usuarioCandidato2'
    usuarioSinIntereses = "./usuario.json"

    passwordCorrecto = 'password' #lo uso para todos los usuarios

    #Una categoria que SI o SI esta en el Shared
    categoriaValida  = "outdoors"
    interesUnico = "INTERES UNICO QUE NO TIENE NADIE MAS"

    msgNoSeEncontraronCandidatos = "Candidato no encontrado"


    def agregarEmailAlUsuario(self, bodyUsuario, email):
        bodyUsuario["user"]["email"] = email

    def agregarValorDeInteresAlUsuario(self,bodyUsuario, valorDeInteres):
        interes = json.loads('{}')
        interes["category"] = self.categoriaValida
        interes["value"] = valorDeInteres
        bodyUsuario["user"]["interests"].append(interes)

    def hacerLoginDeUsuario(self, usuario):
        headUsuarioRegistrado = crearHeadersDeUsuarioYPassword( usuario, self.passwordCorrecto)
        reply = requests.get(Address + URILogin,headers=headUsuarioRegistrado)
        return reply

    usuariosParaBorrar = []

    def tearDown(self):
        for usuario in self.usuariosParaBorrar:
            headEliminarUsuario = {'Usuario': usuario,'Password': self.passwordCorrecto }
            replyDelete = requests.delete(Address + URIEliminar, headers=headEliminarUsuario)

        del self.usuariosParaBorrar[:]


    def test_UsuarioPideUnCandidatoPeroNoSeEncuentra(self):
        #Para esto no debe haber ningun usuario en el shared con el interes "interesUnico"
        #Aca creo el body del usuario con un interes unico, ningun otro lo debe usar
        nombreUsuario = "test_UsuarioPideUnCandidatoPeroNoSeEncuentra.com"
        bodyUsuario = abrirJson(self.usuarioSinIntereses)
        self.agregarEmailAlUsuario(bodyUsuario, nombreUsuario)
        self.agregarValorDeInteresAlUsuario(bodyUsuario, self.interesUnico)
        headRegistrarUsuario = crearHeadersParaRegistro("test_mandoUnRegistroAlServer")
        replyRegistro = requests.put(Address + URIResgistro, headers=headRegistrarUsuario, data=json.dumps(bodyUsuario))

        #Se loguea
        headLoginUsuario = crearHeadersParaElLogin(nombreUsuario)
        replyLogin = requests.get(Address + URILogin, headers=headLoginUsuario)

        #Pide un candidato
        headPedirCandidatos = crearHeadersParaBuscarCandidatos(nombreUsuario,replyLogin.headers["Token"])
        replyPedirCandidatos = requests.get(Address + URIPedirCandidato, headers=headPedirCandidatos)

        self.assertEqual(replyPedirCandidatos.reason,self.msgNoSeEncontraronCandidatos)
        self.assertEqual(replyPedirCandidatos.status_code,201)

        self.usuariosParaBorrar.extend([nombreUsuario])
