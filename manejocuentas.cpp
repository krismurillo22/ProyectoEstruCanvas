#include "manejocuentas.h"
#include "UsuarioRegistro.h"
#include "usuarioalumno.h"
#include "usuariomaestro.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <typeinfo>
#include <QDir>
#include <QMessageBox>

manejoCuentas::manejoCuentas() {
    qDebug() << "Constructor de manejoCuentas llamado";
    cargarUsuarios(archivoMaestros, maestros);
    cargarUsuarios(archivoRegistros, registros);
    cargarUsuarios(archivoAlumnos, alumnos);
    cargarUsuarios(archivoClases, clases);
    cargarExamenes();
    cargarTareas();
}

manejoCuentas::~manejoCuentas() {
    qDebug() << "Destructor de manejoCuentas llamado";
    guardarUsuarios(archivoMaestros, maestros);
    guardarUsuarios(archivoRegistros, registros);
    guardarUsuarios(archivoAlumnos, alumnos);
    guardarUsuarios(archivoClases, clases);
    guardarExamenes();
    guardarTareas();
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
    QString rutaClase = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase;

    QDir dir;
    if (!dir.exists(rutaClase)) {
        if (!dir.mkpath(rutaClase)) {
            qDebug() << "No se pudo crear la carpeta para la clase" << idClase;
            return;
        }
    }

    QString nombreArchivo = rutaClase + "/estudiantes.clas";
    QFile file(nombreArchivo);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "No se pudo crear el archivo de estudiantes para la clase" << idClase;
        return;
    }

    file.close();
    qDebug() << "Clase creada: " << idClase << " con archivo de estudiantes.";
}

bool manejoCuentas::matricularUsuarioEnClase(const QString& idClase, const QString& usuario, bool esMaestro) {
    QString rutaClase = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase;
    QString nombreArchivo = rutaClase + "/estudiantes.clas";
    QFile file(nombreArchivo);
    QList<QString> lineas;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            lineas.append(in.readLine());
        }
        file.close();
    }

    if (esMaestro) {
        for (const QString& usuarioExistente : lineas) {
            if (usuarioExistente.startsWith("M:")) {
                return false;
            }
        }
        lineas.append("M:" + usuario);
    } else {
        if (lineas.contains(usuario)) {
            return false;
        }
        lineas.append(usuario);
    }
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString& linea : lineas) {
            out << linea << "\n";
        }
        file.close();
    }
    return true;
}

QList<QString> manejoCuentas::obtenerUsuariosMatriculadosEnClase(const QString& idClase) {
    QString rutaClase = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase;
    QString nombreArchivo = rutaClase + "/estudiantes.clas";
    QFile file(nombreArchivo);
    QList<QString> usuariosMatriculados;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo de estudiantes para la clase" << idClase;
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

QString manejoCuentas::obtenerIDClaseXNombre(const QString& nombreClase) {
    for (const auto& clase : clases) {
        if (clase.getNombre() == nombreClase) {
            return clase.getID();
        }
    }
    return "";
}

usuarioMaestro manejoCuentas::obtenerMaestroXUser(const QString& user) {
   usuarioMaestro h;
    for (const auto& maestro : maestros) {
        if (maestro.getUser() == user) {
            h = maestro;
            return h;
        }
    }
    return h;
}

QList<QString> manejoCuentas::obtenerClasesDeMaestro(const QString& usuarioMaestro) {
    QList<QString> clasesMatriculadas;
    QString nombre= obtenerMaestroXUser(usuarioMaestro).getNombre();
    for (int i = 0; i < static_cast<int>(clases.size()); ++i){
        QString idClase = clases[i].getID();
        QString rutaClase = QDir::toNativeSeparators("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase);
        QString nombreArchivo = QDir(rutaClase).filePath("estudiantes.clas");

        if (!QDir(rutaClase).exists()) {
            continue;
        }

        if (!QFile::exists(nombreArchivo)) {
            continue;
        }

        QFile file(nombreArchivo);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        QTextStream in(&file);
        QString contenido = in.readAll();
        file.close();

        if (contenido.contains("M:" + nombre)) {
            qDebug() << "Maestro encontrado en la clase:" << clases[i].getNombre();
            clasesMatriculadas.append(clases[i].getNombre());
        }
    }

    return clasesMatriculadas;
}

void manejoCuentas::registrarExamen(const QString& nombreExamen, const QString& idClase, const QDateTime& fechaHora, int duracion, int puntaje, const QVector<Pregunta>& preguntas) {
    QString rutaArchivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase + "/" + fechaHora.toString("yyyyMMdd_HHmm") + ".exam";

    Examen examen(nombreExamen, idClase, fechaHora, duracion, puntaje);
    for (const auto& pregunta : preguntas) {
        examen.agregarPregunta(pregunta);
    }
    if (!examen.guardar()) {
        qDebug() << "Error al guardar el examen en:" << rutaArchivo;
        return;
    }
    examenes.push_back({nombreExamen, idClase, rutaArchivo});
}

void manejoCuentas::cargarExamenes() {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/examenes.gen");
    if (!file.exists()) {
        qDebug() << "El archivo de exámenes no existe. Se creará al registrar el primer examen.";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo de exámenes.";
        return;
    }

    examenes.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList partes = linea.split("|");
        if (partes.size() < 3)
            continue;
        examenes.push_back({ partes[0], partes[1], partes[2] });
    }
    file.close();
}

void manejoCuentas::guardarExamenes() {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/examenes.gen");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo para guardar los examenes.";
        return;
    }

    QTextStream out(&file);
    for (const auto &examen : examenes) {
        out << examen.nombreExamen << "|" << examen.idClase << "|" << examen.rutaArchivo << "\n";
    }
    file.close();
    qDebug() << "Examenes guardados.";
}

QList<QString> manejoCuentas::obtenerExamenesDeMaestro(const QString& usuarioMaestro) {
    QList<QString> examenesDelMaestro;
    QList<QString> clasesDelMaestro = obtenerClasesDeMaestro(usuarioMaestro);
    for (int i = 0; i < examenes.size(); ++i) {
        for (int j = 0; j < clasesDelMaestro.size(); ++j) {
            QString idClase = obtenerIDClaseXNombre(clasesDelMaestro[j]);
            if (examenes[i].idClase == idClase) {
                qDebug() << "Examen encontrado: " << examenes[i].nombreExamen;
                examenesDelMaestro.append(examenes[i].idClase+ " - " + clasesDelMaestro[j] + " - " + examenes[i].nombreExamen);
            }
        }
    }

    return examenesDelMaestro;
}

void manejoCuentas::eliminarExamen(const QString& nombreExamen) {
    for (auto it = examenes.begin(); it != examenes.end(); ++it) {
        if (it->nombreExamen == nombreExamen) {
            examenes.erase(it);
            qDebug() << "Examen eliminado del vector: " << nombreExamen;
            return;
        }
    }
}


void manejoCuentas::agregarTarea(const QString& clase, const QString& titulo, const QString& descripcion, int prioridad, int tiempoEstimado, const QString& estado, const QString& tipoArchivo, const QStringList& recursos) {
    tarea nuevaTarea(clase, titulo, descripcion, prioridad, tiempoEstimado, estado, tipoArchivo, recursos);
    tareas.push_back(nuevaTarea);
}

std::vector<tarea>& manejoCuentas::getTareas() {
    return tareas;
}

void manejoCuentas::guardarTareas() {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/tareas.gen");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "No se pudo abrir el archivo para guardar las tareas.";
        return;
    }

    QDataStream out(&file);
    out << tareas.size();

    for (const tarea& t : tareas) {
        out << t.getClase() << t.getTitulo() << t.getDescripcion() << t.getPrioridad()
            << t.getTiempoEstimado() << t.getEstado() << t.getTipoArchivo() << t.getRecursos();
    }

    file.close();
    qDebug() << "Tareas guardadas correctamente.";
}

void manejoCuentas::cargarTareas() {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/tareas.gen");
    if (!file.exists()) {
        qDebug() << "El archivo de tareas no existe. Se creará al registrar la primera tarea.";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el archivo de tareas.";
        return;
    }

    QDataStream in(&file);
    int tareaCount = 0;
    in >> tareaCount;

    tareas.clear();

    for (int i = 0; i < tareaCount; ++i) {
        QString clase, titulo, descripcion, estado, tipoArchivo;
        int prioridad, tiempoEstimado;
        QStringList recursos;

        in >> clase >> titulo >> descripcion >> prioridad >> tiempoEstimado >> estado >> tipoArchivo >> recursos;

        tarea nuevaTarea(clase, titulo, descripcion, prioridad, tiempoEstimado, estado, tipoArchivo, recursos);
        tareas.push_back(nuevaTarea);
    }

    file.close();
    qDebug() << "Tareas cargadas correctamente. Total: " << tareas.size();
}

void manejoCuentas::marcarTareaComoCompletada(const QString& titulo) {
    for (auto& t : tareas) {
        if (t.getTitulo() == titulo && t.getEstado() == "Incompleto") {
            t.setEstado("Completada");
            qDebug() << "Tarea marcada como completada: " << titulo;
            return;
        }
    }
    qDebug() << "No se encontró la tarea o ya está completada: " << titulo;
}

usuarioAlumno manejoCuentas::obtenerAlumnoXUser(const QString& user) {
   usuarioAlumno h;
    for (const auto& alumno : alumnos) {
        if (alumno.getUser() == user) {
            h = alumno;
            return h;
        }
    }
    return h;
}

QList<QString> manejoCuentas::obtenerClasesDeAlumno(const QString& user) {
    QList<QString> clasesMatriculadas;
    QString usuarioAlumno = obtenerAlumnoXUser(user).getNombre();
    for (int i = 0; i < static_cast<int>(clases.size()); ++i) {
        QString idClase = clases[i].getID();
        QString rutaClase = QDir::toNativeSeparators("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase);
        QString nombreArchivo = QDir(rutaClase).filePath("estudiantes.clas");

        if (!QDir(rutaClase).exists()) {
            continue;
        }

        if (!QFile::exists(nombreArchivo)) {
            continue;
        }

        QFile file(nombreArchivo);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        QTextStream in(&file);
        QString contenido = in.readAll();
        file.close();
        QStringList lineas = contenido.split("\n");
        lineas.removeAll("");
        if (lineas.contains(usuarioAlumno)) {
            qDebug() << "Alumno encontrado en la clase:" << clases[i].getNombre();
            clasesMatriculadas.append(clases[i].getNombre());
        }
    }

    return clasesMatriculadas;
}

QList<QString> manejoCuentas::obtenerExamenesDeAlumno(const QString &usuario) {
    QList<QString> examenesDelAlumno;
    QList<QString> clasesDelAlumno = obtenerClasesDeMaestro(usuario);
    for (int i = 0; i < examenes.size(); ++i) {
        for (int j = 0; j < clasesDelAlumno.size(); ++j) {
            QString idClase = obtenerIDClaseXNombre(clasesDelAlumno[j]);
            if (examenes[i].idClase == idClase) {
                qDebug() << "Examen encontrado: " << examenes[i].nombreExamen;
                examenesDelAlumno.append(examenes[i].idClase+ " - " + clasesDelAlumno[j] + " - " + examenes[i].nombreExamen);
            }
        }
    }

    return examenesDelAlumno;
}

Examen manejoCuentas::obtenerExamenDesdeArchivo(const QString &datosExamen) {
    QStringList partes = datosExamen.split(" - ");
    if (partes.size() < 3) {
        qDebug() << "Error: Formato incorrecto en la cadena de datos del examen.";
        return Examen("", "", QDateTime(), 0, 0);
    }

    QString idClase = partes[0];
    QString nombreExamen = partes[2];
    QString rutaArchivo;
    for (const auto &examen : examenes) {
        if (examen.nombreExamen == nombreExamen && examen.idClase == idClase) {
            rutaArchivo = examen.rutaArchivo;
            break;
        }
    }

    if (rutaArchivo.isEmpty()) {
        qDebug() << "No se encontró el examen en la lista.";
        return Examen("", "", QDateTime(), 0, 0);
    }

    QFile file(rutaArchivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el archivo del examen: " << rutaArchivo;
        return Examen("", "", QDateTime(), 0, 0);
    }

    QDataStream in(&file);
    QDateTime fechaHora;
    int duracion, puntaje, numPreguntas;
    QString titulo, claseID;

    in >> titulo >> claseID >> fechaHora >> duracion >> puntaje >> numPreguntas;
    qDebug() << "Leyendo examen - Duración:" << duracion;

    Examen examen(titulo, claseID, fechaHora, duracion, puntaje);

    for (int i = 0; i < numPreguntas; ++i) {
        Pregunta pregunta;
        pregunta.cargar(in);
        examen.agregarPregunta(pregunta);
    }

    file.close();
    qDebug() << "Examen cargado correctamente: " << examen.getIdClase() << " - " << examen.getFechaHora().toString();

    return examen;
}
