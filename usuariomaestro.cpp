#include "usuariomaestro.h"

usuarioMaestro::usuarioMaestro() {}

usuarioMaestro::usuarioMaestro(bool activo, QString id, QString nombre, QString profesion, float sueldo, QString user, QString password, QString rol)
    : activo_(activo), id_(id), nombre_(nombre), profesion_(profesion), sueldo_(sueldo), user_(user), password_(password), rol_(rol) {}

bool usuarioMaestro::getActivo() const{
    return activo_;
}

QString usuarioMaestro::getID() const {
    return id_;
}

QString usuarioMaestro::getNombre() const {
    return nombre_;
}

QString usuarioMaestro::getProfesion() const {
    return profesion_;
}

float usuarioMaestro::getSueldo() const {
    return sueldo_;
}

QString usuarioMaestro::getUser() const {
    return user_;
}

QString usuarioMaestro::getPassword() const {
    return password_;
}

QString usuarioMaestro::getRol() const {
    return rol_;
}

void usuarioMaestro::cargar(QDataStream& in) {
    in >> activo_ >> id_ >> nombre_ >> profesion_ >> sueldo_ >> user_ >> password_ >> rol_;
}

void usuarioMaestro::guardar(QDataStream& out) const {
    out << activo_ << id_ << nombre_ << profesion_ << sueldo_ << user_ << password_ << rol_;
}

void usuarioMaestro::setActivo(bool activo) {
    activo_ = activo;
}

void usuarioMaestro::setNombre(QString nombre) {
    nombre_ = nombre;
}

void usuarioMaestro::setProfesion(QString profesion) {
    profesion_ = profesion;
}

void usuarioMaestro::setSueldo(float sueldo) {
    sueldo_ = sueldo;
}

void usuarioMaestro::setPassword(QString password) {
    password_ = password;
}

void usuarioMaestro::setRol(QString rol) {
    rol_ = rol;
}
