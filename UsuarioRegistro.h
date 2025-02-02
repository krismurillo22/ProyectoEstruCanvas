#ifndef USUARIOREGISTRO_H
#define USUARIOREGISTRO_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>


class UsuarioRegistro {
public:
    UsuarioRegistro(bool activo, QString nombre, QString user, QString password);
    UsuarioRegistro();
    bool getActivo()const ;
    QString getNombre() const;
    QString getPassword() const;
    QString getUser() const;
    void guardar();
    void cargarUsuarios();

private:
    bool activo_;
    QString nombre_;
    QString user_;
    QString password_;
};

#endif // USUARIOREGISTRO_H
