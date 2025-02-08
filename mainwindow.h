#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usuarioalumno.h"
#include "usuariomaestro.h"
#include "UsuarioRegistro.h"
#include "manejocuentas.h"

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

private slots:
    void on_pushButton_clicked();

    void on_cerrarRegistro_clicked();

    void on_cerrarMaestro_clicked();

    void on_cerrarAlumno_clicked();

    void on_registrarMaestro_clicked();

    void on_registrarAlumnos_clicked();

    void on_registrarClases_clicked();

    void on_registrarAsignar_clicked();

    void on_agregarMaestro_clicked();

    void on_modificarMaestro_clicked();

    void on_eliminarMaestro_clicked();

    void on_agregarClase_clicked();

    void on_aceptarMaestro_clicked();

    void on_registrarRegistro_clicked();

    void on_agregarRegistro_clicked();

    void on_agregarAlumno_clicked();

private:
    Ui::MainWindow *ui;

    //usuarioAlumno alumnoDefault;
    //usuarioMaestro maestroDefault;
    //UsuarioRegistro registroDefault;
};
#endif // MAINWINDOW_H
