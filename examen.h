#ifndef EXAMEN_H
#define EXAMEN_H
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QDir>
#include "pregunta.h"

class Examen {
private:
    QString idClase;
    QDateTime fechaHora;
    int duracion;
    int puntaje;
    QVector<Pregunta> preguntas;

public:
    Examen(QString idClase, QDateTime fechaHora, int duracion, int puntaje);

    void agregarPregunta(const Pregunta &pregunta);
    bool guardar();
};


#endif // EXAMEN_H
