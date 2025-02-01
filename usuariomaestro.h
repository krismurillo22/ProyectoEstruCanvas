#ifndef USUARIOMAESTRO_H
#define USUARIOMAESTRO_H
#include <QString>


class usuarioMaestro {
public:
    usuarioMaestro(QString id, QString nombre, QString profesion, float sueldo, QString user, QString password, QString rol);
    usuarioMaestro();
    QString getID() const;
    QString getNombre() const;
    QString getProfesion() const;
    float getSueldo() const;
    QString getUser() const;
    QString getPassword() const;
    QString getRol() const;
private:
    QString id_;
    QString nombre_;
    QString profesion_;
    float sueldo_;
    QString user_;
    QString password_;
    QString rol_;
};


#endif // USUARIOMAESTRO_H
