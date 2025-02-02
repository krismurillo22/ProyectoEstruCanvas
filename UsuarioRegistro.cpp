#include "UsuarioRegistro.h"

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

void UsuarioRegistro::guardar() {
    QFile archivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat");

        if (!archivo.exists()) {
            if (!archivo.open(QIODevice::WriteOnly)) {
                qDebug() << "Error al crear el archivo para escritura.";
                return;
            }
        } else {
            if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append)) {
                qDebug() << "Error al abrir el archivo para escritura.";
                return;
            }
        }

        QDataStream out(&archivo);
        out << activo_ << nombre_ << user_ << password_;
        archivo.close();
        qDebug() << "Usuario de registro guardado correctamente.";
}

void UsuarioRegistro::cargarUsuarios() {
    QFile archivo("usuarios_registro.dat");
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        while (!in.atEnd()) {
            bool activo;
            QString nombre, user, password;
            in >> activo >> nombre >> user >> password;
            qDebug() << "Usuario:" << nombre << "| Usuario:" << user << "| Activo:" << activo;
        }
        archivo.close();
    } else {
        qDebug() << "Error al abrir el archivo para lectura.";
    }
}
