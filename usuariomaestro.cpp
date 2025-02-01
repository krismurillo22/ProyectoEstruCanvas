#include "usuariomaestro.h"

usuarioMaestro::usuarioMaestro(QString id, QString nombre, QString profesion, float sueldo, QString user, QString password, QString rol)
    : id_(id), nombre_(nombre), profesion_(profesion), sueldo_(sueldo), user_(user), password_(password), rol_(rol) {}

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
