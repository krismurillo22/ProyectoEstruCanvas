#include "manejocuentas.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

manejoCuentas::manejoCuentas()
{

}
//esto es para ingresar y que de su tipo de cuenta
QString manejoCuentas::validarUsuario(const QString &usuario, const QString &password) {
    QString tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return "registro";
        }

        tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return "maestro";
        }

        tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return "alumno";
        }
        return "";
}

QString manejoCuentas::validarEnArchivo(const QString &archivo, const QString &usuario, const QString &password) {
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error al abrir el archivo:" << archivo;
        return "";
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        bool activo;
        QString nombre, user, pass, cuenta, clases, rol, carrera, id, profesion;
        float sueldo;

        if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat") {
            in >> activo >> nombre >> user >> pass;
        } else if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad") {
            in >> activo >> id >> nombre >> profesion >> sueldo >> user >> pass >> rol;
        } else if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm") {
            in >> activo >> cuenta >> nombre >> carrera >> clases >> user >> pass >> rol;
        }

        if (user == usuario && pass == password) {
            file.close();
            return archivo;
        }
    }

    file.close();
    return "";
}


//para saber si existe
bool manejoCuentas::existeUsuario(const QString &id, const QString &usuario,  const QString &tipoCuenta) {
    QString archivo;
    if (tipoCuenta == "registro") {
        archivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat";
    } else if (tipoCuenta == "maestro") {
        archivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad";
    } else if (tipoCuenta == "alumno") {
        archivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm";
    } else {
        qDebug() << "Tipo de cuenta inválido";
        return false;
    }

    return validarEnArchivoUsuario(archivo, usuario, id);
}

bool manejoCuentas::validarEnArchivoUsuario(const QString &archivo, const QString &usuario, const QString &id) {
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error al abrir el archivo:" << archivo;
        return false;
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        bool activo;
        QString nombre, user, pass, cuenta, clases, rol, carrera, idMaestro, profesion;
        float sueldo;

        if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat") {
            in >> activo >> nombre >> user >> pass;
            if (activo && user == usuario) {
                file.close();
                return true;
            }
        } else if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad") {
            in >> activo >> idMaestro >> nombre >> profesion >> sueldo >> user >> pass >> rol;
            if (activo && (user == usuario || idMaestro == id)) {
                file.close();
                return true;
            }
        } else if (archivo == "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm") {
            in >> activo >> cuenta >> nombre >> carrera >> clases >> user >> pass >> rol;
            if (activo && user == usuario) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}
