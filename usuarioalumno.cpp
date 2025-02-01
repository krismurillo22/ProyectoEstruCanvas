#include "usuarioalumno.h"

usuarioAlumno::usuarioAlumno(QString cuenta, QString nombre, QString carrera, QString clases, QString user, QString password, QString rol)
    : cuenta_(cuenta), nombre_(nombre), carrera_(carrera), clases_(clases), user_(user), password_(password), rol_(rol) {}

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
