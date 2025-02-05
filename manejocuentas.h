#ifndef MANEJOCUENTAS_H
#define MANEJOCUENTAS_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>

struct Maestro {
    QString id;
    QString nombre;
    QString profesion;
    float sueldo;
    QString usuario;
    QString password;
    QString rol;
    bool activo;
};

class manejoCuentas
{
public:
    manejoCuentas();
    QString validarUsuario(const QString &usuario, const QString &password);
    bool existeUsuario(const QString &id, const QString &usuario,  const QString &tipoCuenta);
    QList<Maestro> obtenerListaMaestros();

private:
    QString validarEnArchivo(const QString &archivo, const QString &usuario, const QString &password);
    bool validarEnArchivoUsuario(const QString &archivo, const QString &usuario, const QString &id);
};



#endif // MANEJOCUENTAS_H
