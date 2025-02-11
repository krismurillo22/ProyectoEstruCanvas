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
#include "clasesplantilla.h"

class manejoCuentas
{
public:
    manejoCuentas();
    ~manejoCuentas();
    void agregarMaestro(const usuarioMaestro& maestro);
    void agregarRegistro(const UsuarioRegistro& registro);
    void agregarAlumno(const usuarioAlumno& alumno);
    void agregarClases(const clasesPlantilla& clase);

    std::vector<usuarioMaestro>& getMaestros();
    std::vector<usuarioAlumno>& getAlumnos();
    std::vector<UsuarioRegistro>& getRegistros();
    std::vector<clasesPlantilla>& getClases();

    bool usuarioMaestroExiste(const usuarioMaestro& usuario);
    bool usuarioAlumnoExiste(const usuarioAlumno& usuario);
    bool usuarioRegistroExiste(const UsuarioRegistro& usuario);
    bool ClaseExiste(const clasesPlantilla& clase);

    template <typename T>
    void cargarUsuarios(const QString& archivo, std::vector<T>& lista);

    template <typename T>
    void guardarUsuarios(const QString& archivo, const std::vector<T>& lista);

    QString validarUsuario(const QString& usuario, const QString& password);

    QList<usuarioMaestro> obtenerListaMaestros() const;
    QList<UsuarioRegistro> obtenerListaRegistros() const;
    QList<usuarioAlumno> obtenerListaAlumnos() const;
    QList<clasesPlantilla> obtenerListaClases() const;

    void crearClase(const QString& idClase);
    bool matricularUsuarioEnClase(const QString& claseID, const QString& username, bool esMaestro);
    QList<QString> obtenerUsuariosMatriculadosEnClase(const QString& claseID);

    QString obtenerIDClaseXNombre(const QString& nombreClase);
    usuarioMaestro obtenerMaestroXUser(const QString& user);
    QList<QString> obtenerClasesDeMaestro(const QString& usuarioMaestro);

private:
    std::vector<usuarioAlumno> alumnos;
    std::vector<UsuarioRegistro> registros;
    std::vector<usuarioMaestro> maestros;
    std::vector<clasesPlantilla> clases;

    QString archivoMaestros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad";
    QString archivoRegistros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat";
    QString archivoAlumnos = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm";
    QString archivoClases = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/lista_clases.cla";

};



#endif // MANEJOCUENTAS_H
