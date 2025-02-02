#include "usuariomaestro.h"

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

void usuarioMaestro::guardar() {
    QFile archivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad");

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
        out << activo_ << id_ << nombre_ << profesion_ << sueldo_ << user_ << password_ << rol_;
        archivo.close();
        qDebug() << "Usuario de maestro guardado correctamente.";
}


void usuarioMaestro::cargarUsuarios() {
    QFile archivo("usuarios_maestros.dat");
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        while (!in.atEnd()) {
            bool activo;
            QString id, nombre, profesion, user, password, rol;
            float sueldo;
            in >> activo >> id >> nombre >> profesion >> sueldo >> user >> password >> rol;
            qDebug() << "ID:" << id << "| Nombre:" << nombre << "| Profesión:" << profesion << "| Sueldo:" << sueldo;
        }
        archivo.close();
    } else {
        qDebug() << "Error al abrir el archivo para lectura.";
    }
}
