#include "UsuarioRegistro.h"

UsuarioRegistro::UsuarioRegistro() {}

UsuarioRegistro::UsuarioRegistro(bool activo, QString nombre, QString user, QString password)
    : activo_(activo), nombre_(nombre), user_(user), password_(password) {}

bool UsuarioRegistro::getActivo() const{
    return activo_;
}

QString UsuarioRegistro::getNombre() const {
    return nombre_;
}

QString UsuarioRegistro::getPassword() const {
    return password_;
}

QString UsuarioRegistro::getUser() const {
    return user_;
}

void UsuarioRegistro::cargar(QDataStream& in) {
    in >> activo_ >> nombre_ >> user_ >> password_;
}

void UsuarioRegistro::guardar(QDataStream& out) const {
    out << activo_ << nombre_ << user_ << password_;
}

