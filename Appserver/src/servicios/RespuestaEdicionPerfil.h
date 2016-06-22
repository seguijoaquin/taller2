#ifndef RESPUESTAEDICIONPERFIL_H
#define RESPUESTAEDICIONPERFIL_H

#include <RespuestaDelServicio.h>


class RespuestaEdicionPerfil : public RespuestaDelServicio
{
    public:
        RespuestaEdicionPerfil();
        virtual ~RespuestaEdicionPerfil();
        void setRespuestaEdicioncionCorrecta();
        void setRespuestaEdicionEnServerIncorrecta();
        void setRespuestaNoTienePermisoDeEdicion();

    protected:
    private:

};

#endif // RESPUESTAEDICIONPERFIL_H
