#ifndef CLASESPLANTILLA_H
#define CLASESPLANTILLA_H
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class clasesPlantilla {
public:
    clasesPlantilla(bool activo, QString id, QString nombre, QString hora, int uv, int semestre, int periodo, int year);
    clasesPlantilla();
    bool getActivo() const;
    QString getID() const;
    QString getNombre() const;
    QString getHora() const;
    int getUV() const;
    int getSemestre() const;
    int getPeriodo() const;
    int getYear() const;
    void guardar();
private:
    bool activo_;
    QString id_;
    QString nombre_;
    QString hora_;
    int uv_;
    int semestre_;
    int periodo_;
    int year_;
};


#endif // CLASESPLANTILLA_H
