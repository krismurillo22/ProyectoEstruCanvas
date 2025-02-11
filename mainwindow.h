#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usuarioalumno.h"
#include "usuariomaestro.h"
#include "UsuarioRegistro.h"
#include "manejocuentas.h"
#include "pregunta.h"
#include "examen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    manejoCuentas *manejo;

    QString maestro;
private slots:
    void on_pushButton_clicked();

    void on_cerrarRegistro_clicked();

    void on_cerrarMaestro_clicked();

    void on_cerrarAlumno_clicked();

    void on_registrarMaestro_clicked();

    void on_registrarAlumnos_clicked();

    void on_registrarClases_clicked();

    void on_agregarMaestro_clicked();

    void on_modificarMaestro_clicked();

    void on_eliminarMaestro_clicked();

    void on_agregarClase_clicked();

    void on_aceptarMaestro_clicked();

    void on_registrarRegistro_clicked();

    void on_agregarRegistro_clicked();

    void on_agregarAlumno_clicked();

    void on_aceptarRegistro_clicked();

    void on_modificarRegistro_clicked();

    void on_eliminarRegistro_clicked();

    void on_modificarAlumno_clicked();

    void on_eliminarAlumno_clicked();

    void on_aceptarAlumnos_clicked();

    void on_modificarClase_clicked();

    void on_eliminarClase_clicked();

    void on_aceptarClases_clicked();

    void on_AsignarMaestro_clicked();

    void on_matricularAlumnos_clicked();

    void on_aceptarAsignacion_clicked();

    void on_registrarAsignar_2_clicked();

    void on_aceptarMatricula_clicked();

    void on_examenesMaestro_clicked();

    void on_tareasMaestro_clicked();

    void on_crearExamen_clicked();

    void on_agregarPregunta_clicked();

    void on_nuevaTarea_clicked();

    void on_nuevoExamen_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Pregunta> preguntas;
};
#endif // MAINWINDOW_H
