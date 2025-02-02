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
    ui->formularioRegistro->setCurrentIndex(0);
}


void MainWindow::on_registrarClases_clicked()
{
    ui->submenuRegistro->setCurrentIndex(3);
    ui->formularioRegistro->setCurrentIndex(0);
}


void MainWindow::on_registrarAsignar_clicked()
{
    ui->submenuRegistro->setCurrentIndex(4);
    ui->formularioRegistro->setCurrentIndex(0);
}


void MainWindow::on_agregarMaestro_clicked()
{
    ui->formularioRegistro->setCurrentIndex(1);
    ui->tituloMaestro->setText("AGREGAR MAESTRO");
}


void MainWindow::on_modificarMaestro_clicked()
{
    ui->formularioRegistro->setCurrentIndex(1);
    ui->tituloMaestro->setText("MODIFICAR MAESTRO");
}


void MainWindow::on_eliminarMaestro_clicked()
{

}


void MainWindow::on_agregarClase_clicked()
{

}


void MainWindow::on_aceptarMaestro_clicked()
{
    if (ui->tituloMaestro->text()=="AGREGAR MAESTRO"){
        QString id= ui->idMaestro->text();
        QString nombre= ui->nombreMaestro->text();
        QString profesion= ui->profesionMaestro->text();
        QString user= ui->userMaestro->text();
        QString password=ui->passwordMaestro->text();
        QString rol= ui->rolMaestro->text();
        QString sueldoTexto = ui->sueldoMaestro->text();

        if (id.isEmpty() || nombre.isEmpty() || profesion.isEmpty() || user.isEmpty() ||
            password.isEmpty() || rol.isEmpty() || sueldoTexto.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        //para saber si se convirtio bien
        bool ok;
        float sueldo = sueldoTexto.toFloat(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "El sueldo ingresado no es válido.");
            return;
        }

        manejoCuentas manejo;
        if (manejo.existeUsuario(id, user, "maestro")) {
            QMessageBox::warning(this, "Error", "El usuario o ID ya existen en el sistema.");
            return;
        }
        usuarioMaestro maestroNuevo(true, id, nombre, profesion, sueldo, user, password, rol);
        maestroNuevo.guardar();
        QMessageBox::information(this, "Éxito", "Maestro agregado correctamente.");

        ui->idMaestro->clear();
        ui->nombreMaestro->clear();
        ui->profesionMaestro->clear();
        ui->userMaestro->clear();
        ui->passwordMaestro->clear();
        ui->rolMaestro->clear();
        ui->sueldoMaestro->clear();

    }else if(ui->tituloMaestro->text()=="MODIFICAR MAESTRO"){

    }
}


void MainWindow::on_registrarRegistro_clicked()
{
    ui->submenuRegistro->setCurrentIndex(5);
}


void MainWindow::on_agregarRegistro_clicked()
{

}

