#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include "manejocuentas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //alumnoDefault(true, "000000", "Alumno", "no", "no", "alumno", "1", "Estudiante"),
    //maestroDefault(true, "000000", "Maestro", "no", 0.0, "maestro", "1", "Docente"),
    //registroDefault(true, "Admin", "admin", "1")
{
    ui->setupUi(this);
    //registroDefault.guardar();
    //maestroDefault.guardar();
    //alumnoDefault.guardar();
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    this->move(screenGeometry.center() - this->rect().center());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString usuario = ui->usuario->text();
    QString password = ui->password->text();

    if (!usuario.isEmpty() && !password.isEmpty()) {
        manejoCuentas manejoCuentas;
        QString tipoCuenta = manejoCuentas.validarUsuario(usuario, password);
        if (!tipoCuenta.isEmpty()) {
            if (tipoCuenta == "registro") {
                ui->stackedWidget->setCurrentIndex(1);
            } else if (tipoCuenta == "maestro") {
                ui->stackedWidget->setCurrentIndex(2);
            } else if (tipoCuenta == "alumno") {
                ui->stackedWidget->setCurrentIndex(3);
            }
            ui->usuario->clear();
            ui->password->clear();
        } else {
            QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
        }
    } else {
        QMessageBox::warning(this, "Advertencia", "Se debe de ingresar ambos datos.");
    }
}


void MainWindow::on_cerrarRegistro_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_cerrarMaestro_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_cerrarAlumno_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_registrarMaestro_clicked()
{
    ui->submenuRegistro->setCurrentIndex(1);
}


void MainWindow::on_registrarAlumnos_clicked()
{
    ui->submenuRegistro->setCurrentIndex(2);
}


void MainWindow::on_registrarClases_clicked()
{
    ui->submenuRegistro->setCurrentIndex(3);
}


void MainWindow::on_registrarAsignar_clicked()
{
    ui->submenuRegistro->setCurrentIndex(4);
}


void MainWindow::on_agregarMaestro_clicked()
{

}


void MainWindow::on_modificarMaestro_clicked()
{

}


void MainWindow::on_eliminarMaestro_clicked()
{

}

