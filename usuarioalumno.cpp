#include "usuarioalumno.h"

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

void usuarioAlumno::guardar() {
    QFile archivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm");

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
        out << activo_ << cuenta_ << nombre_ << carrera_ << clases_ << user_ << password_ << rol_;
        archivo.close();
        qDebug() << "Usuario de maestro guardado correctamente.";
}

void usuarioAlumno::cargarUsuarios() {
    QFile archivo("usuarios_alumnos.dat");
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        while (!in.atEnd()) {
            bool activo;
            QString cuenta, nombre, carrera, clases, user, password, rol;
            in >> activo >> cuenta >> nombre >> carrera >> clases >> user >> password >> rol;
            qDebug() << "Cuenta:" << cuenta << "| Nombre:" << nombre << "| Carrera:" << carrera << "| Clases:" << clases;
        }
        archivo.close();
    } else {
        qDebug() << "Error al abrir el archivo para lectura.";
    }
}
