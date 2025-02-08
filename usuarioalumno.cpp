#include "usuarioalumno.h"

usuarioAlumno::usuarioAlumno() {}

usuarioAlumno::usuarioAlumno(bool activo, QString cuenta, QString nombre, QString carrera, QString clases, QString user, QString password, QString rol)
    : activo_(activo), cuenta_(cuenta), nombre_(nombre), carrera_(carrera), clases_(clases), user_(user), password_(password), rol_(rol) {}

bool usuarioAlumno::getActivo() const{
    return activo_;
}

QString usuarioAlumno::getCuenta() const {
    return cuenta_;
}

QString usuarioAlumno::getNombre() const {
    return nombre_;
}

QString usuarioAlumno::getCarrera() const {
    return carrera_;
}

QString usuarioAlumno::getClases() const {
    return clases_;
}

QString usuarioAlumno::getUser() const {
    return user_;
}

QString usuarioAlumno::getPassword() const {
    return password_;
}

QString usuarioAlumno::getRol() const {
    return rol_;
}

void usuarioAlumno::cargar(QDataStream& in) {
    in >> activo_ >> cuenta_ >> nombre_ >> carrera_ >> clases_ >> user_ >> password_ >> rol_;
}

void usuarioAlumno::guardar(QDataStream& out) const {
    out << activo_ << cuenta_ << nombre_ << carrera_ << clases_ << user_ << password_ << rol_;
}

void usuarioAlumno::setActivo(bool activo) {
    activo_ = activo;
}

void usuarioAlumno::setNombre(QString nombre) {
    nombre_ = nombre;
}

void usuarioAlumno::setCarrera(QString carrera) {
    carrera_ = carrera;
}

void usuarioAlumno::setClases(QString clases) {
    clases_ = clases;
}

void usuarioAlumno::setPassword(QString password) {
    password_ = password;
}

void usuarioAlumno::setRol(QString rol) {
    rol_ = rol;
}
