#ifndef USUARIOREGISTRO_H
#define USUARIOREGISTRO_H

#include <QString>


class UsuarioRegistro {
public:
    UsuarioRegistro(QString nombre, QString user, QString password);
    UsuarioRegistro();
    QString getNombre() const;
    QString getPassword() const;
    QString getUser() const;
private:
    QString nombre_;
    QString user_;
    QString password_;
};

#endif // USUARIOREGISTRO_H
