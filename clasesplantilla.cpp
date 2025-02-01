#include "clasesplantilla.h"

clasesPlantilla::clasesPlantilla(QString id, QString nombre, QString hora, int uv, int semestre, int periodo, int year)
    : id_(id), nombre_(nombre), hora_(hora), uv_(uv), semestre_(semestre), periodo_(periodo), year_(year) {}

QString clasesPlantilla::getID() const {
    return id_;
}

QString clasesPlantilla::getNombre() const {
    return nombre_;
}

QString clasesPlantilla::getHora() const {
    return hora_;
}

int clasesPlantilla::getUV() const {
    return uv_;
}

int clasesPlantilla::getSemestre() const {
    return semestre_;
}

int clasesPlantilla::getPeriodo() const {
    return periodo_;
}

int clasesPlantilla::getYear() const {
    return year_;
}


