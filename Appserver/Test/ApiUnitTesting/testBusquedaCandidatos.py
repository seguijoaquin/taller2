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
    interesCompartido = "INTERES QUE SOLO DEBE SER COMPARTIDO POR DOS USUARIOS"

    msgNoSeEncontraronCandidatos = "Candidato no encontrado"
    msgSeEncontraronCandidatos = "Candidato encontrado"


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
        headRegistrarUsuario = crearHeadersParaRegistro(nombreUsuario)
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

    def crearBodyConUnInteres(self, email, interes):
        bodyUsuario = abrirJson(self.usuarioSinIntereses)
        self.agregarEmailAlUsuario(bodyUsuario, email)
        self.agregarValorDeInteresAlUsuario(bodyUsuario, interes)
        return bodyUsuario

    def registrarUsuario(self, nombreUsuario, bodyUsuario):
        headRegistrarUsuario = crearHeadersParaRegistro(nombreUsuario)
        return requests.put(Address + URIResgistro, headers=headRegistrarUsuario, data=json.dumps(bodyUsuario))

    def loguearUsuario(self, nombreUsuario):
        headLoginUsuario = crearHeadersParaElLogin(nombreUsuario)
        return requests.get(Address + URILogin, headers=headLoginUsuario)

    def pedirCandidato(self, nombreUsuario, replyLogin):
        headPedirCandidatos = crearHeadersParaBuscarCandidatos(nombreUsuario,replyLogin.headers["Token"])
        return requests.get(Address + URIPedirCandidato, headers=headPedirCandidatos)


    def test_DosUsuariosConUnInteresEspecificoPidenUnCandidatoYSeEncuentranUnoAlOtro(self):

        nombreUsuario1 = "test_DosUsuariosConUnInteresEspecificoPidenUnCandidatoYSeEncuentranUnoAlOtro1"
        nombreUsuario2 = "test_DosUsuariosConUnInteresEspecificoPidenUnCandidatoYSeEncuentranUnoAlOtro2"

        bodyUsuario1 = self.crearBodyConUnInteres(nombreUsuario1, self.interesCompartido)
        bodyUsuario2 = self.crearBodyConUnInteres(nombreUsuario2, self.interesCompartido)

        replyRegistro1 = self.registrarUsuario(nombreUsuario1, bodyUsuario1)
        replyRegistro2 = self.registrarUsuario(nombreUsuario2, bodyUsuario2)

        replyLogin1 = self.loguearUsuario(nombreUsuario1)
        replyLogin2 = self.loguearUsuario(nombreUsuario2)

        #Pide un candidato
        replyPedirCandidatos1 = self.pedirCandidato(nombreUsuario1, replyLogin1)
        replyPedirCandidatos2 = self.pedirCandidato(nombreUsuario2, replyLogin2)

        self.assertEqual(replyPedirCandidatos1.reason,self.msgSeEncontraronCandidatos)
        self.assertEqual(replyPedirCandidatos1.status_code,200)

        self.assertEqual(replyPedirCandidatos2.reason,self.msgSeEncontraronCandidatos)
        self.assertEqual(replyPedirCandidatos2.status_code,200)

        self.usuariosParaBorrar.extend([nombreUsuario1, nombreUsuario2])
