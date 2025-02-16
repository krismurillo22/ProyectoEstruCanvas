#ifndef TAREA_H
#define TAREA_H

#include <QString>
#include <QStringList>

class tarea {
private:
    QString clase;
    QString titulo;
    QString descripcion;
    int prioridad;  // 1 = Baja, 2 = Media, 3 = Alta
    int tiempoEstimado; // en minutos
    QString estado;  // Completada o incompleta
    QString tipoArchivo;
    QStringList recursos;


public:
    tarea(const QString& clase,const QString& titulo, const QString& desc, int prioridad, int tiempo, const QString& est, const QString& tipo, const QStringList& rec);

    QString getDescripcion() const;
    QString getClase() const;
    QString getTitulo() const;
    int getPrioridad() const;
    int getTiempoEstimado() const;
    QString getEstado() const;
    QString getTipoArchivo() const;
    QStringList getRecursos() const;

    void setTitulo(const QString& titulo);
    void setDescripcion(const QString& desc);
    void setPrioridad(int pri);
    void setTiempoEstimado(int tiempo);
    void setEstado(const QString& est);
    void setTipoArchivo(const QString& tipo);
    void setRecursos(const QStringList& rec);

    void agregarRecurso(const QString& recurso);

    void guardarTarea(QDataStream& out) const;
    void cargarTarea(QDataStream& in);
};

#endif // TAREA_H
