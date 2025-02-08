#ifndef USUARIOREGISTRO_H
#define USUARIOREGISTRO_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>


class UsuarioRegistro {
public:
    UsuarioRegistro();
    UsuarioRegistro(bool activo, QString nombre, QString user, QString password);
    bool getActivo()const ;
    QString getNombre() const;
    QString getPassword() const;
    QString getUser() const;
    void cargar(QDataStream& in);
    void guardar(QDataStream& out) const;

private:
    bool activo_;
    QString nombre_;
    QString user_;
    QString password_;
};

#endif // USUARIOREGISTRO_H
