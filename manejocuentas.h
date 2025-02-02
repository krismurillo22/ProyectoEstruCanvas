#ifndef MANEJOCUENTAS_H
#define MANEJOCUENTAS_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class manejoCuentas
{
public:
    manejoCuentas();
    QString validarUsuario(const QString &usuario, const QString &password);
private:
    QString validarEnArchivo(const QString &archivo, const QString &usuario, const QString &password);
};

#endif // MANEJOCUENTAS_H
