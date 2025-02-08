#ifndef USUARIOALUMNO_H
#define USUARIOALUMNO_H
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class usuarioAlumno {
public:
    usuarioAlumno(bool activo, QString cuenta, QString nombre, QString carrera, QString clases, QString user, QString password, QString rol);
    usuarioAlumno();
    bool getActivo() const;
    QString getCuenta() const;
    QString getNombre() const;
    QString getCarrera() const;
    QString getClases() const;
    QString getUser() const;
    QString getPassword() const;
    QString getRol() const;

    void setActivo(bool activo);
    void setNombre(QString nombre);
    void setCarrera(QString carrera);
    void setClases(QString clases);
    void setPassword(QString password);
    void setRol(QString rol);

    void cargar(QDataStream& in);
    void guardar(QDataStream& out) const;

private:
    bool activo_;
    QString cuenta_;
    QString nombre_;
    QString carrera_;
    QString clases_;
    QString user_;
    QString password_;
    QString rol_;
};

#endif // USUARIOALUMNO_H
