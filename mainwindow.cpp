#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include "manejocuentas.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manejo = new manejoCuentas();
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    this->move(screenGeometry.center() - this->rect().center());

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manejo;
}


void MainWindow::on_pushButton_clicked()
{
    QString usuario = ui->usuario->text();
    QString password = ui->password->text();

    if (!usuario.isEmpty() && !password.isEmpty()) {
        QString tipoCuenta = manejo->validarUsuario(usuario, password);
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

    ui->idMaestro->setEnabled(true);
    ui->userMaestro->setEnabled(true);
    ui->idMaestro->clear();
    ui->nombreMaestro->clear();
    ui->profesionMaestro->clear();
    ui->userMaestro->clear();
    ui->passwordMaestro->clear();
    ui->rolMaestro->clear();
    ui->sueldoMaestro->clear();
}


void MainWindow::on_modificarMaestro_clicked()
{
    QList<usuarioMaestro> maestrosLista = manejo->obtenerListaMaestros();
    QStringList nombresMaestros;
    for (int i = 0; i < maestrosLista.size(); ++i) {
        nombresMaestros.append(maestrosLista[i].getNombre());
    }

    bool ok;
    QString maestroSeleccionado = QInputDialog::getItem(nullptr, "Seleccionar Maestro",
                                                            "Eliga el maestro que desea modificar:",
                                                            nombresMaestros, 0, false, &ok);

    for (int i = 0; i < maestrosLista.size(); ++i) {
        if (maestrosLista[i].getNombre() == maestroSeleccionado) {
            ui->formularioRegistro->setCurrentIndex(1);
            ui->tituloMaestro->setText("MODIFICAR MAESTRO");

            ui->idMaestro->setText(maestrosLista[i].getID());
            ui->rolMaestro->setText(maestrosLista[i].getRol());
            ui->nombreMaestro->setText(maestrosLista[i].getNombre());
            ui->profesionMaestro->setText(maestrosLista[i].getProfesion());
            ui->sueldoMaestro->setText(QString::number(maestrosLista[i].getSueldo(), 'f', 2));
            ui->userMaestro->setText(maestrosLista[i].getUser());
            ui->passwordMaestro->setText(maestrosLista[i].getPassword());

            ui->idMaestro->setEnabled(false);
            ui->userMaestro->setEnabled(false);
            break;
        }


    }
 }


void MainWindow::on_eliminarMaestro_clicked()
{
    std::vector<usuarioMaestro>& maestrosLista = manejo->getMaestros();
    QStringList nombresMaestros;
    for (const auto& maestro : maestrosLista) {
        nombresMaestros.append(maestro.getNombre());
    }

    bool ok;
    QString maestroSeleccionado = QInputDialog::getItem(nullptr, "Seleccionar Maestro",
                                                            "Eliga el maestro que desea eliminar:",
                                                            nombresMaestros, 0, false, &ok);

    if (ok && !maestroSeleccionado.isEmpty()) {
        for (auto it = maestrosLista.begin(); it != maestrosLista.end(); ++it) {
            if (it->getNombre() == maestroSeleccionado) {
                maestrosLista.erase(it);
                QMessageBox::information(this, "Éxito", "Maestro eliminado correctamente.");
                return;
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "No se ha seleccionado un maestro.");
    }

}


void MainWindow::on_agregarClase_clicked()
{
    ui->formularioRegistro->setCurrentIndex(4);
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
        usuarioMaestro usernuevo(true, id, nombre, profesion, sueldo, user, password, rol);

        if (manejo->usuarioMaestroExiste(usernuevo)) {
            QMessageBox::warning(this, "Error", "El usuario o ID ya existen en el sistema.");
            return;
        }

        manejo->agregarMaestro(usernuevo);
        QMessageBox::information(this, "Éxito", "Maestro agregado correctamente.");

        ui->idMaestro->clear();
        ui->nombreMaestro->clear();
        ui->profesionMaestro->clear();
        ui->userMaestro->clear();
        ui->passwordMaestro->clear();
        ui->rolMaestro->clear();
        ui->sueldoMaestro->clear();

    }else if(ui->tituloMaestro->text()=="MODIFICAR MAESTRO"){
        std::vector<usuarioMaestro>& maestrosLista = manejo->getMaestros();
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

        bool ok;
        float sueldo = sueldoTexto.toFloat(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "El sueldo ingresado no es válido.");
            return;
        }

        for (std::vector<usuarioMaestro>::size_type i = 0; i < maestrosLista.size(); ++i) {
            if (maestrosLista[i].getID() == id) {
                maestrosLista[i].setNombre(nombre);
                maestrosLista[i].setProfesion(profesion);
                maestrosLista[i].setSueldo(sueldo);
                maestrosLista[i].setPassword(password);
                maestrosLista[i].setRol(rol);

                QMessageBox::information(this, "Éxito", "Maestro modificado correctamente.");
                break;
            }
        }

        ui->idMaestro->clear();
        ui->nombreMaestro->clear();
        ui->profesionMaestro->clear();
        ui->userMaestro->clear();
        ui->passwordMaestro->clear();
        ui->rolMaestro->clear();
        ui->sueldoMaestro->clear();
    }
}


void MainWindow::on_registrarRegistro_clicked()
{
    ui->submenuRegistro->setCurrentIndex(5);
}


void MainWindow::on_agregarRegistro_clicked()
{
    ui->formularioRegistro->setCurrentIndex(2);
}


void MainWindow::on_agregarAlumno_clicked()
{
    ui->formularioRegistro->setCurrentIndex(3);
}




