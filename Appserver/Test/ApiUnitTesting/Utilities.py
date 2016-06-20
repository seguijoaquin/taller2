import json

def abrirJson(ruta):
    with open(ruta, 'r') as archivoJson:
        parseado = json.load(archivoJson)
        return parseado
