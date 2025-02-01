#ifndef USUARIOALUMNO_H
#define USUARIOALUMNO_H
#include <QString>

class usuarioAlumno {
public:
    usuarioAlumno(QString cuenta, QString nombre, QString carrera, QString clases, QString user, QString password, QString rol);
    usuarioAlumno();
    QString getCuenta() const;
    QString getNombre() const;
    QString getCarrera() const;
    QString getClases() const;
    QString getUser() const;
    QString getPassword() const;
    QString getRol() const;
private:
    QString cuenta_;
    QString nombre_;
    QString carrera_;
    QString clases_;
    QString user_;
    QString password_;
    QString rol_;
};

#endif // USUARIOALUMNO_H
