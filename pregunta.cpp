#include "pregunta.h"

Pregunta::Pregunta() {}

Pregunta::Pregunta(QString txt, QString respC, QString respI, int tipo)
    : texto(txt), respuestaCorrecta(respC), respuestaIncorrecta(respI), tipo(tipo) {}

void Pregunta::guardar(QDataStream &out) const {
    out << texto << respuestaCorrecta << respuestaIncorrecta << tipo;
}

void Pregunta::cargar(QDataStream &in) {
    in >> texto >> respuestaCorrecta >> respuestaIncorrecta >> tipo;
}

QString Pregunta::obtenerTexto() const {
    return texto;
}

QString Pregunta::obtenerRespuestaCorrecta() const {
    return respuestaCorrecta;
}
QString Pregunta::obtenerRespuestaIncorrecta() const {
    return respuestaIncorrecta;
}

int Pregunta::obtenerTipo() const {
    return tipo;
}
