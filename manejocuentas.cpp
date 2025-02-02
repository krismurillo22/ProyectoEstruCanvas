#include "manejocuentas.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

manejoCuentas::manejoCuentas()
{

}

QString manejoCuentas::validarUsuario(const QString &usuario, const QString &password) {
    QString tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return tipoCuenta;
        }

        tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return tipoCuenta;
        }

        tipoCuenta = validarEnArchivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm", usuario, password);
        if (!tipoCuenta.isEmpty()) {
            return tipoCuenta;
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
