#include "UsuarioRegistro.h"

UsuarioRegistro::UsuarioRegistro(QString nombre, QString user, QString password)
    : nombre_(nombre), user_(user), password_(password) {}

QString UsuarioRegistro::getNombre() const {
    return nombre_;
}

QString UsuarioRegistro::getPassword() const {
    return password_;
}

QString UsuarioRegistro::getUser() const {
    return user_;
}
