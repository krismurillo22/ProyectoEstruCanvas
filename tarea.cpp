#include "tarea.h"
#include <QDataStream>

tarea::tarea(const QString& clase, const QString& titul ,const QString& desc, int pri, int tiempo, const QString& est, const QString& tipo, const QStringList& rec)
    : clase(clase),  titulo(titul) , descripcion(desc), prioridad(pri), tiempoEstimado(tiempo), estado(est), tipoArchivo(tipo), recursos(rec) {}

QString tarea::getClase() const {
    return clase;
}

QString tarea::getTitulo() const {
    return titulo;
}

QString tarea::getDescripcion() const {
    return descripcion;
}

int tarea::getPrioridad() const {
    return prioridad;
}

int tarea::getTiempoEstimado() const {
    return tiempoEstimado;
}

QString tarea::getEstado() const {
    return estado;
}

QString tarea::getTipoArchivo() const {
    return tipoArchivo;
}

QStringList tarea::getRecursos() const {
    return recursos;
}

void tarea::setTitulo(const QString& titul) {
    titulo = titul;
}

void tarea::setDescripcion(const QString& desc) {
    descripcion = desc;
}

void tarea::setPrioridad(int pri) {
    prioridad = pri;
}

void tarea::setTiempoEstimado(int tiempo) {
    tiempoEstimado = tiempo;
}

void tarea::setEstado(const QString& est) {
    estado = est;
}

void tarea::setTipoArchivo(const QString& tipo) {
    tipoArchivo = tipo;
}

void tarea::setRecursos(const QStringList& rec) {
    recursos = rec;
}

void tarea::agregarRecurso(const QString& recurso) {
    recursos.append(recurso);
}

void tarea::guardarTarea(QDataStream& out) const {
    out << clase <<titulo << descripcion << prioridad << tiempoEstimado << estado << tipoArchivo << recursos;
}

void tarea::cargarTarea(QDataStream& in) {
    in >> clase>> titulo>> descripcion >> prioridad >> tiempoEstimado >> estado >> tipoArchivo >> recursos;
}
