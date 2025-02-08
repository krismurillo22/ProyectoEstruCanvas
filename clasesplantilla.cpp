#include "clasesplantilla.h"

clasesPlantilla::clasesPlantilla() {}

clasesPlantilla::clasesPlantilla(bool activo, QString id, QString nombre, QString hora, int uv, int semestre, int periodo, int year)
    : activo_(activo), id_(id), nombre_(nombre), hora_(hora), uv_(uv), semestre_(semestre), periodo_(periodo), year_(year) {}

bool clasesPlantilla::getActivo() const{
    return activo_;
}

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

void clasesPlantilla::cargar(QDataStream& in) {
    in >> activo_ >> id_ >> nombre_ >> hora_ >> uv_ >> semestre_ >> periodo_ >> year_;
}

void clasesPlantilla::guardar(QDataStream& out) const {
    out << activo_ << id_ << nombre_ << hora_ << uv_ << semestre_ << periodo_ << year_;
}

void clasesPlantilla::setActivo(bool activo) {
    activo_ = activo;
}

void clasesPlantilla::setHora(QString hora) {
    hora_ = hora;
}

void clasesPlantilla::setPeriodo(int periodo) {
    periodo_ = periodo;
}

void clasesPlantilla::setSemestre(int semestre) {
    semestre_ = semestre;
}

void clasesPlantilla::setYear(int year) {
    year_ = year;
}

void clasesPlantilla::setUV(int uv) {
    uv_ = uv;
}
