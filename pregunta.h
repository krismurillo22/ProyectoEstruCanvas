#ifndef PREGUNTA_H
#define PREGUNTA_H

#include <QString>
#include <QDataStream>

class Pregunta {
private:
    QString texto;
    QString respuestaCorrecta;
    QString respuestaIncorrecta;
    int tipo;  // 0 = Verdadero/Falso, 1 = Selección Múltiple, 2 = Enumerada

public:
    Pregunta();
    Pregunta(QString txt, QString respC, QString respI, int tipo);

    void guardar(QDataStream &out) const;
    void cargar(QDataStream &in);

    QString obtenerTexto() const;
    QString obtenerRespuestaCorrecta() const;
    QString obtenerRespuestaIncorrecta() const;
    int obtenerTipo() const;
};

#endif // PREGUNTA_H
