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
#include "examen.h"
#include "tarea.h"
#include <stack>

//Esto es para el arreglo de examenes para que sea mas facil
struct ExamenInfo {
    QString nombreExamen;
    QString idClase;
    QString rutaArchivo;
};

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

    void cargarExamenes();
    void guardarExamenes();

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
    void registrarExamen(const QString& nombreExamen, const QString& idClase, const QDateTime& fechaHora, int duracion, int puntaje, const QVector<Pregunta>& preguntas);
    QList<QString> obtenerExamenesDeMaestro(const QString& usuarioMaestro);
    void eliminarExamen(const QString& nombreExamen);

    void guardarTareas();
    void cargarTareas();
    void agregarTarea(const QString& clase, const QString& titulo, const QString& descripcion, int prioridad, int tiempoEstimado, const QString& estado, const QString& tipoArchivo, const QStringList& recursos);
    std::vector<tarea>& getTareas();
    void marcarTareaComoCompletada(const QString& titulo);

    usuarioAlumno obtenerAlumnoXUser(const QString& user);
    QList<QString> obtenerClasesDeAlumno(const QString& nombre);
    QList<QString> obtenerExamenesDeAlumno(const QString& usuario);

    Examen obtenerExamenDesdeArchivo(const QString &datosExamen);


private:
    std::vector<usuarioAlumno> alumnos;
    std::vector<UsuarioRegistro> registros;
    std::vector<usuarioMaestro> maestros;
    std::vector<clasesPlantilla> clases;
    std::vector<ExamenInfo> examenes;
    std::vector<tarea> tareas;


    QString archivoMaestros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_maestros.mad";
    QString archivoRegistros = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_registro.dat";
    QString archivoAlumnos = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/usuarios_alumnos.alm";
    QString archivoClases = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/lista_clases.cla";

};



#endif // MANEJOCUENTAS_H
