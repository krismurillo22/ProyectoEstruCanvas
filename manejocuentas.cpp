#include "manejocuentas.h"
#include "UsuarioRegistro.h"
#include "usuarioalumno.h"
#include "usuariomaestro.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <typeinfo>


manejoCuentas::manejoCuentas() {
    qDebug() << "Constructor de manejoCuentas llamado";
    cargarUsuarios(archivoMaestros, maestros);
    cargarUsuarios(archivoRegistros, registros);
    cargarUsuarios(archivoAlumnos, alumnos);
    cargarUsuarios(archivoClases, clases);
}

manejoCuentas::~manejoCuentas() {
    qDebug() << "Destructor de manejoCuentas llamado";
    guardarUsuarios(archivoMaestros, maestros);
    guardarUsuarios(archivoRegistros, registros);
    guardarUsuarios(archivoAlumnos, alumnos);
    guardarUsuarios(archivoClases, clases);
}

void manejoCuentas::agregarMaestro(const usuarioMaestro& maestro) {
    maestros.push_back(maestro);
}

void manejoCuentas::agregarRegistro(const UsuarioRegistro& registro) {
    registros.push_back(registro);
}

void manejoCuentas::agregarAlumno(const usuarioAlumno& alumno) {
    alumnos.push_back(alumno);
}

void manejoCuentas::agregarClases(const clasesPlantilla &clase){
    clases.push_back(clase);
}

std::vector<usuarioMaestro>& manejoCuentas::getMaestros() {
    return maestros;
}

std::vector<usuarioAlumno>& manejoCuentas::getAlumnos() {
    return alumnos;
}

std::vector<UsuarioRegistro>& manejoCuentas::getRegistros() {
    return registros;
}

std::vector<clasesPlantilla>& manejoCuentas::getClases() {
    return clases;
}

template <typename T>
void manejoCuentas::cargarUsuarios(const QString& archivo, std::vector<T>& lista) {
    QFile file(archivo);

    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "No se pudo crear el archivo" << archivo;
            return;
        }
        file.close();
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir" << archivo;
        return;
    }

    QDataStream in(&file);
    lista.clear();

    while (!in.atEnd()) {
        T usuario;
        usuario.cargar(in);
        lista.push_back(usuario);
    }

    file.close();
}

template <typename T>
void manejoCuentas::guardarUsuarios(const QString& archivo, const std::vector<T>& lista) {
    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "No se pudo abrir" << archivo;
        return;
    }

    QDataStream out(&file);
    for (const auto& usuario : lista) {
        usuario.guardar(out);
    }

    file.close();
}

QString manejoCuentas::validarUsuario(const QString& usuario, const QString& password) {
    for (const auto& reg : registros) {
        if (reg.getUser() == usuario && reg.getPassword() == password && reg.getActivo()) {
            return "registro";
        }
    }

    for (const auto& maestro : maestros) {
        if (maestro.getUser() == usuario && maestro.getPassword() == password && maestro.getActivo()) {
            return "maestro";
        }
    }

    for (const auto& alumno : alumnos) {
        if (alumno.getUser() == usuario && alumno.getPassword() == password && alumno.getActivo()) {
            return "alumno";
        }
    }

    return "";
}

bool manejoCuentas::usuarioMaestroExiste(const usuarioMaestro& usuario) {
    for (const auto& u : maestros) {
        if (u.getID() == usuario.getID() || u.getUser() == usuario.getUser()) {
            return true;
        }
    }
    return false;
}

bool manejoCuentas::usuarioAlumnoExiste(const usuarioAlumno& usuario) {
    for (const auto& u : alumnos) {
        if (u.getCuenta() == usuario.getCuenta() || u.getUser() == usuario.getUser()) {
            return true;
        }
    }
    return false;
}

bool manejoCuentas::usuarioRegistroExiste(const UsuarioRegistro& usuario) {
    for (const auto& u : registros) {
        if (u.getUser() == usuario.getUser()) {
            return true;
        }
    }
    return false;
}

bool manejoCuentas::ClaseExiste(const clasesPlantilla &clase) {
    for (const auto& u : clases) {
        if (u.getID() == clase.getID()) {
            return true;
        }
    }
    return false;
}

QList<usuarioMaestro> manejoCuentas::obtenerListaMaestros() const {
    QList<usuarioMaestro> listaMaestros;
    for (const auto& maestro : maestros) {
        listaMaestros.append(maestro);
    }

    return listaMaestros;
}

QList<UsuarioRegistro> manejoCuentas::obtenerListaRegistros() const {
    QList<UsuarioRegistro> listaRegistro;
    for (const auto& registro : registros) {
        listaRegistro.append(registro);
    }

    return listaRegistro;
}

QList<usuarioAlumno> manejoCuentas::obtenerListaAlumnos() const {
    QList<usuarioAlumno> listaAlumnos;
    for (const auto& alumno : alumnos) {
        listaAlumnos.append(alumno);
    }

    return listaAlumnos;
}

QList<clasesPlantilla> manejoCuentas::obtenerListaClases() const {
    QList<clasesPlantilla> listaClases;
    for (const auto& clase : clases) {
        listaClases.append(clase);
    }

    return listaClases;
}

void manejoCuentas::crearClase(const QString& idClase) {
    QString nombreArchivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/clase_" + idClase + ".clas";
    QFile file(nombreArchivo);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "No se pudo crear el archivo para la clase" << idClase;
        return;
    }

    file.close();
    qDebug() << "Archivo creado para la clase" << idClase;
}

void manejoCuentas::matricularUsuarioEnClase(const QString& idClase, const QString& usuario) {
    QString nombreArchivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/clase_" + idClase + ".clas";
    QFile file(nombreArchivo);

    if (!file.open(QIODevice::Append)) {
        qDebug() << "No se pudo abrir el archivo para la clase" << idClase;
        return;
    }

    QTextStream out(&file);
    out << usuario << "\n";

    file.close();
    qDebug() << "Usuario" << usuario << "matriculado en la clase" << idClase;
}

QList<QString> manejoCuentas::obtenerUsuariosMatriculadosEnClase(const QString& idClase) {
    QString nombreArchivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/clase_" + idClase + ".clas";
    QFile file(nombreArchivo);

    QList<QString> usuariosMatriculados;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el archivo para la clase" << idClase;
        return usuariosMatriculados;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString usuario = in.readLine();
        usuariosMatriculados.append(usuario);
    }

    file.close();
    return usuariosMatriculados;
}
