#ifndef MANEJOCUENTAS_H
#define MANEJOCUENTAS_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <vector>
#include "usuarioalumno.h"
#include "usuariomaestro.h"
#include "UsuarioRegistro.h"

class manejoCuentas
{
public:
    manejoCuentas();
    ~manejoCuentas();
    void agregarMaestro(const usuarioMaestro& maestro);
    void agregarRegistro(const UsuarioRegistro& registro);
    void agregarAlumno(const usuarioAlumno& alumno);

    std::vector<usuarioMaestro>& getMaestros();
    std::vector<usuarioAlumno>& getAlumnos();
    std::vector<UsuarioRegistro>& getRegistros();

    bool usuarioMaestroExiste(const usuarioMaestro& usuario);
    bool usuarioAlumnoExiste(const usuarioAlumno& usuario);
    bool usuarioRegistroExiste(const UsuarioRegistro& usuario);

    template <typename T>
    void cargarUsuarios(const QString& archivo, std::vector<T>& lista);

    template <typename T>
    void guardarUsuarios(const QString& archivo, const std::vector<T>& lista);

    QString validarUsuario(const QString& usuario, const QString& password);
    QList<usuarioMaestro> obtenerListaMaestros() const;



private:
    std::vector<usuarioAlumno> alumnos;
    std::vector<UsuarioRegistro> registros;
    std::vector<usuarioMaestro> maestros;

    QString archivoMaestros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad";
    QString archivoRegistros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat";
    QString archivoAlumnos = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm";

};



#endif // MANEJOCUENTAS_H
