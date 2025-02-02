#ifndef USUARIOMAESTRO_H
#define USUARIOMAESTRO_H
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class usuarioMaestro {
public:
    usuarioMaestro(bool activo, QString id, QString nombre, QString profesion, float sueldo, QString user, QString password, QString rol);
    usuarioMaestro();
    bool getActivo() const;
    QString getID() const;
    QString getNombre() const;
    QString getProfesion() const;
    float getSueldo() const;
    QString getUser() const;
    QString getPassword() const;
    QString getRol() const;
    void guardar();
    void cargarUsuarios();

private:
    bool activo_;
    QString id_;
    QString nombre_;
    QString profesion_;
    float sueldo_;
    QString user_;
    QString password_;
    QString rol_;
};


#endif // USUARIOMAESTRO_H
