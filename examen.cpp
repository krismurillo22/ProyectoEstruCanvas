#include "examen.h"

Examen::Examen(QString idClase, QDateTime fechaHora, int duracion, int puntaje)
    : idClase(idClase), fechaHora(fechaHora), duracion(duracion), puntaje(puntaje) {}

void Examen::agregarPregunta(const Pregunta &pregunta) {
    preguntas.append(pregunta);
}

bool Examen::guardar() {
    QString ruta = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase;
    QDir().mkpath(ruta);
    QFile archivo(ruta + "/" + fechaHora.toString("yyyyMMdd_HHmm") + ".exam");

    if (!archivo.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&archivo);
    out << fechaHora << duracion << puntaje << preguntas.size();

    for (int i = 0; i < preguntas.size(); ++i) {
        preguntas[i].guardar(out);
    }

    archivo.close();
    return true;
}

QDateTime Examen::getFechaHora()const {
    return fechaHora;
}

QString Examen::getIdClase()const {
    return idClase;
}

int Examen::getDuracion()const {
    return duracion;
}

int Examen::getPuntaje()const {
    return puntaje;
}

QVector<Pregunta> Examen::getPreguntas() const {
    return preguntas;
}
