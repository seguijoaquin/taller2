import json
import requests

Address = "http://localhost:8000"
URIResgistro = "/registro"
URILogin = "/login"
URIPedirCandidato = "/perfil"
URIEliminar = "/eliminar"
URIPedirUsuario = "/info"
URIModificarPosicion = "/gps"
URIModificarFoto = "/foto"
URIModificarPerfil = "/editar"
URIVotarCandidato = "/matcheo"


def abrirJson(ruta):
    with open(ruta, 'r') as archivoJson:
        parseado = json.load(archivoJson)
        return parseado

def agregarEmailAlUsuario(bodyUsuario, email):
    bodyUsuario["user"]["email"] = email

def abrirUsuarioConEmail(email):
    bodyUsuario = abrirJson("./usuarioSinEmail.json")
    agregarEmailAlUsuario(bodyUsuario, email)
    return bodyUsuario

def registrarUsuarioSinEmail(emailUsuario):
    bodyUsuario = abrirJson("./usuarioSinEmail.json")
    agregarEmailAlUsuario(bodyUsuario, emailUsuario)
    headRegistrarUsuario = {'Password': "password"}
    return requests.put(Address + URIResgistro, headers=headRegistrarUsuario, data=json.dumps(bodyUsuario))


def registrarUsuarioSinEmailYSinIntereses(emailUsuario, categoria, valor):
    bodyUsuario = abrirJson("./usuarioSinEmailYSinIntereses.json")
    agregarEmailAlUsuario(bodyUsuario, emailUsuario)

    interes = {}
    interes["category"] = categoria
    interes["value"] = valor
    bodyUsuario["user"]["interests"] = [interes]
    headRegistrarUsuario = {'Password': "password"}
    return requests.put(Address + URIResgistro, headers=headRegistrarUsuario, data=json.dumps(bodyUsuario))






def crearHeadersParaElLogin(usuario):
    return {'Usuario': usuario,'Password': "password", 'TokenGCM': "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ" }

def loguearAlUsuario(usuario):
    headLogin = crearHeadersParaElLogin(usuario)
    replyLogin = requests.get(Address + URILogin, headers=headLogin)
    return replyLogin.headers["Token"]

def registrarYLoguearAlUsuarioSinEmail(usuario):
    registrarUsuarioSinEmail(usuario)
    return loguearAlUsuario(usuario)





def pedirCandidato(usuario, token):
    headPedirCandidato = {'Usuario': usuario, "Token": token }
    candidatoPedido = requests.get(Address + URIPedirCandidato, headers=headPedirCandidato)
    jsonBody = candidatoPedido
    return jsonBody.json()["user"]["email"]

def likearCandidato(usuario, token, candidato):
    headerLikearCandidato = {'Usuario': usuario, "Token": token, "Candidato": candidato, "Resultado": "like" }
    return requests.post(Address + URIVotarCandidato, headers=headerLikearCandidato)




def pedirPerfil(usuario, token, usuarioPedido):
    headPedirUsuario = {'Usuario': usuario, "Token": token, "UsuarioPedido": usuarioPedido}
    replyInfo = requests.get(Address + URIPedirUsuario, headers=headPedirUsuario)
    return replyInfo.json()


def modificarPosicion(usuario,token, nuevaLatitud, nuevaLongitud):
    nuevaPosicion = {}
    nuevaPosicion["latitude"] = nuevaLatitud
    nuevaPosicion["longitude"] = nuevaLongitud
    headerModificarPosicion = {'Usuario': usuario, "Token": token}
    requests.put(Address + URIModificarPosicion, headers=headerModificarPosicion, data=json.dumps(nuevaPosicion))



def borrarUsuarios(usuariosParaBorrar):
    for usuario in usuariosParaBorrar:
        headEliminarUsuario = {'Usuario': usuario,'Password': "password" }
        replyDelete = requests.delete(Address + URIEliminar, headers=headEliminarUsuario)
    del usuariosParaBorrar[:]

def modificarFotoPerfil(usuario, token, nuevaFoto):
    headModificarFoto = {'Usuario': usuario, "Token": token}
    requests.put(Address + URIModificarFoto, headers=headModificarFoto, data=nuevaFoto)

def modificarPerfil(usuario, token, nuevoPerfil):
    headModificarPerfil = {'Usuario': usuario, "Token": token}
    bodyAMandar = {}
    bodyAMandar["user"] = nuevoPerfil
    requests.put(Address + URIModificarPerfil, headers=headModificarPerfil, data=json.dumps(bodyAMandar))
