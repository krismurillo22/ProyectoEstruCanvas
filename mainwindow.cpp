#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include "manejocuentas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    alumnoDefault(true, "000000", "Alumno", "Sin asignar", "Ninguna", "alumno", "1", "Estudiante"),
    maestroDefault(true, "000000", "Maestro", "Sin asignar", 0.0, "maestro", "1", "Docente"),
    registroDefault(true, "Admin", "admin", "1")
{
    ui->setupUi(this);
    registroDefault.guardar();
    maestroDefault.guardar();
    alumnoDefault.guardar();
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
            ui->stackedWidget->setCurrentIndex(1);
            qDebug() << "Usuario de tipo" << tipoCuenta << "valido.";
        } else {
            QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
        }
    } else {
        QMessageBox::warning(this, "Advertencia", "Se debe de ingresar ambos datos.");
    }
}

