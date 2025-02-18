#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include "manejocuentas.h"
#include <QInputDialog>
#include <QDir>
#include "examen.h"
#include "pregunta.h"
#include <QFileDialog>
#include <queue>
#include <QTimer>
#include <QThread>
#include <QVBoxLayout>
#include <QRadioButton>

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
                maestro = usuario;
                ui->nombreUsuarioMaestro->setText("Bienvenido " + maestro);
            } else if (tipoCuenta == "alumno") {
                ui->stackedWidget->setCurrentIndex(3);
                alumnoRegistrado = usuario;
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
    ui->tituloClases->setText("AGREGAR CLASE");

    ui->idClases->setEnabled(true);
    ui->nombreClases->setEnabled(true);
    ui->idClases->clear();
    ui->nombreAlumno->clear();
    ui->uvClases->clear();
    ui->semestreClases->clear();
    ui->periodoClases->clear();
    ui->yearClases->clear();

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
    ui->tituloRegistro->setText("AGREGAR REGISTRO");

    ui->userRegistro->setEnabled(true);
    ui->nombreRegistro->clear();
    ui->userRegistro->clear();
    ui->passwordRegistro->clear();
}


void MainWindow::on_agregarAlumno_clicked()
{
    ui->formularioRegistro->setCurrentIndex(3);
    ui->tituloAlumnos->setText("AGREGAR ALUMNO");

    ui->cuentaAlumnos->setEnabled(true);
    ui->usuarioAlumnos->setEnabled(true);
    ui->cuentaAlumnos->clear();
    ui->nombreAlumno->clear();
    ui->carreraAlumnos->clear();
    ui->usuarioAlumnos->clear();
    ui->passwordAlumnos->clear();
}

void MainWindow::on_aceptarRegistro_clicked()
{
    if (ui->tituloRegistro->text()=="AGREGAR REGISTRO"){
        QString nombre= ui->nombreRegistro->text();
        QString user= ui->userRegistro->text();
        QString password=ui->passwordRegistro->text();

        if (nombre.isEmpty() || user.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        UsuarioRegistro usernuevo(true, nombre, user, password);

        if (manejo->usuarioRegistroExiste(usernuevo)) {
            QMessageBox::warning(this, "Error", "El usuario ya existen en el sistema.");
            return;
        }

        manejo->agregarRegistro(usernuevo);
        QMessageBox::information(this, "Éxito", "Registro fue agregado correctamente.");

        ui->nombreRegistro->clear();
        ui->passwordRegistro->clear();
        ui->userRegistro->clear();

    }else if(ui->tituloRegistro->text()=="MODIFICAR REGISTRO"){
        std::vector<UsuarioRegistro>& registroLista = manejo->getRegistros();
        QString nombre= ui->nombreRegistro->text();
        QString user= ui->userRegistro->text();
        QString password=ui->passwordRegistro->text();

        if (nombre.isEmpty() || user.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        for (std::vector<UsuarioRegistro>::size_type i = 0; i < registroLista.size(); ++i) {
            if (registroLista[i].getUser() == user) {
                registroLista[i].setNombre(nombre);
                registroLista[i].setPassword(password);

                QMessageBox::information(this, "Éxito", "Registro fue modificado correctamente.");
                break;
            }
        }

        ui->nombreRegistro->clear();
        ui->passwordRegistro->clear();
        ui->userRegistro->clear();
    }
}


void MainWindow::on_modificarRegistro_clicked()
{
    QList<UsuarioRegistro> registroLista = manejo->obtenerListaRegistros();
    QStringList nombresRegistro;
    for (int i = 0; i < registroLista.size(); ++i) {
        nombresRegistro.append(registroLista[i].getNombre());
    }

    bool ok;
    QString registroSelec = QInputDialog::getItem(nullptr, "Seleccionar Registro",
                                                            "Eliga el registro que desea modificar:",
                                                            nombresRegistro, 0, false, &ok);

    for (int i = 0; i < registroLista.size(); ++i) {
        if (registroLista[i].getNombre() == registroSelec) {
            ui->formularioRegistro->setCurrentIndex(2);
            ui->tituloRegistro->setText("MODIFICAR REGISTRO");
            ui->nombreRegistro->setText(registroLista[i].getNombre());
            ui->userRegistro->setText(registroLista[i].getUser());
            ui->passwordRegistro->setText(registroLista[i].getPassword());

            ui->userRegistro->setEnabled(false);
            break;
        }


    }
}


void MainWindow::on_eliminarRegistro_clicked()
{
    std::vector<UsuarioRegistro>& registroLista = manejo->getRegistros();
    QStringList nombresRegistros;
    for (const auto& registro : registroLista) {
        nombresRegistros.append(registro.getNombre());
    }

    bool ok;
    QString registroSelec = QInputDialog::getItem(nullptr, "Seleccionar Registro",
                                                            "Eliga el registro que desea eliminar:",
                                                            nombresRegistros, 0, false, &ok);

    if (ok && !registroSelec.isEmpty()) {
        for (auto it = registroLista.begin(); it != registroLista.end(); ++it) {
            if (it->getNombre() == registroSelec) {
                registroLista.erase(it);
                QMessageBox::information(this, "Éxito", "Registro eliminado correctamente.");
                return;
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "No se ha seleccionado un registro.");
    }

    ui->nombreRegistro->clear();
    ui->passwordRegistro->clear();
    ui->userRegistro->clear();
}


void MainWindow::on_modificarAlumno_clicked()
{
    QList<usuarioAlumno> alumnolista = manejo->obtenerListaAlumnos();
    QStringList nombresLista;
    for (int i = 0; i < alumnolista.size(); ++i) {
        nombresLista.append(alumnolista[i].getNombre());
    }

    bool ok;
    QString alumnoSeleccionado = QInputDialog::getItem(nullptr, "Seleccionar Alumno",
                                                            "Eliga el alumno que desea modificar:",
                                                            nombresLista, 0, false, &ok);

    for (int i = 0; i < alumnolista.size(); ++i) {
        if (alumnolista[i].getNombre() == alumnoSeleccionado) {
            ui->formularioRegistro->setCurrentIndex(3);
            ui->tituloAlumnos->setText("MODIFICAR ALUMNO");

            ui->cuentaAlumnos->setText(alumnolista[i].getCuenta());
            ui->rolAlumnos->setText(alumnolista[i].getRol());
            ui->nombreAlumno->setText(alumnolista[i].getNombre());
            ui->carreraAlumnos->setText(alumnolista[i].getCarrera());
            ui->clasesAlumnos->setText(alumnolista[i].getClases());
            ui->usuarioAlumnos->setText(alumnolista[i].getUser());
            ui->passwordAlumnos->setText(alumnolista[i].getPassword());
            ui->cuentaAlumnos->setEnabled(false);
            ui->usuarioAlumnos->setEnabled(false);
            break;
        }
    }
}


void MainWindow::on_eliminarAlumno_clicked()
{
    std::vector<usuarioAlumno>& alumnoLista = manejo->getAlumnos();
    QStringList nombresAlumnos;
    for (const auto& alumno : alumnoLista) {
        nombresAlumnos.append(alumno.getNombre());
    }

    bool ok;
    QString alumnoSelec = QInputDialog::getItem(nullptr, "Seleccionar Alumno",
                                                            "Eliga el alumno que desea eliminar:",
                                                            nombresAlumnos, 0, false, &ok);

    if (ok && !alumnoSelec.isEmpty()) {
        for (auto it = alumnoLista.begin(); it != alumnoLista.end(); ++it) {
            if (it->getNombre() == alumnoSelec) {
                alumnoLista.erase(it);
                QMessageBox::information(this, "Éxito", "Alumno eliminado correctamente.");
                return;
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "No se ha seleccionado un alumno.");
    }

    ui->cuentaAlumnos->clear();
    ui->nombreAlumno->clear();
    ui->carreraAlumnos->clear();
    ui->usuarioAlumnos->clear();
    ui->passwordAlumnos->clear();
}


void MainWindow::on_aceptarAlumnos_clicked()
{
    if (ui->tituloAlumnos->text()=="AGREGAR ALUMNO"){
        QString cuenta= ui->cuentaAlumnos->text();
        QString nombre= ui->nombreAlumno->text();
        QString carrera= ui->carreraAlumnos->text();
        QString user= ui->usuarioAlumnos->text();
        QString password=ui->passwordAlumnos->text();
        QString rol= ui->rolAlumnos->text();
        QString clases = ui->clasesAlumnos->text();

        if (cuenta.isEmpty() || nombre.isEmpty() || carrera.isEmpty() || user.isEmpty() ||
            password.isEmpty() || rol.isEmpty() || clases.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        usuarioAlumno usernuevo(true, cuenta, nombre, carrera, clases, user, password, rol);

        if (manejo->usuarioAlumnoExiste(usernuevo)) {
            QMessageBox::warning(this, "Error", "El usuario o cuenta ya existen en el sistema.");
            return;
        }

        manejo->agregarAlumno(usernuevo);
        QMessageBox::information(this, "Éxito", "Alumno agregado correctamente.");

        ui->cuentaAlumnos->clear();
        ui->nombreAlumno->clear();
        ui->carreraAlumnos->clear();
        ui->usuarioAlumnos->clear();
        ui->passwordAlumnos->clear();

    }else if(ui->tituloAlumnos->text()=="MODIFICAR ALUMNO"){
        std::vector<usuarioAlumno>& alumnoLista = manejo->getAlumnos();
        QString cuenta= ui->cuentaAlumnos->text();
        QString nombre= ui->nombreAlumno->text();
        QString carrera= ui->carreraAlumnos->text();
        QString user= ui->usuarioAlumnos->text();
        QString password=ui->passwordAlumnos->text();
        QString rol= ui->rolAlumnos->text();
        QString clases = ui->clasesAlumnos->text();

        if (cuenta.isEmpty() || nombre.isEmpty() || carrera.isEmpty() || user.isEmpty() ||
            password.isEmpty() || rol.isEmpty() || clases.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        for (std::vector<usuarioAlumno>::size_type i = 0; i < alumnoLista.size(); ++i) {
            if (alumnoLista[i].getCuenta() == cuenta) {
                alumnoLista[i].setNombre(nombre);
                alumnoLista[i].setCarrera(carrera);
                alumnoLista[i].setClases(clases);
                alumnoLista[i].setPassword(password);
                alumnoLista[i].setRol(rol);

                QMessageBox::information(this, "Éxito", "Alumno modificado correctamente.");
                break;
            }
        }

        ui->cuentaAlumnos->clear();
        ui->nombreAlumno->clear();
        ui->carreraAlumnos->clear();
        ui->usuarioAlumnos->clear();
        ui->passwordAlumnos->clear();
    }
}


void MainWindow::on_modificarClase_clicked()
{
    QList<clasesPlantilla> claseLista = manejo->obtenerListaClases();
    QStringList nombresClases;
    for (int i = 0; i < claseLista.size(); ++i) {
        nombresClases.append(claseLista[i].getNombre());
    }

    bool ok;
    QString claseSelec = QInputDialog::getItem(nullptr, "Seleccionar Clase",
                                                            "Eliga la clase que desea modificar:",
                                                            nombresClases, 0, false, &ok);

    for (int i = 0; i < claseLista.size(); ++i) {
        if (claseLista[i].getNombre() == claseSelec) {
            ui->formularioRegistro->setCurrentIndex(4);
            ui->tituloClases->setText("MODIFICAR CLASE");

            ui->idClases->setText(claseLista[i].getID());
            ui->horaComboBox->setCurrentText(claseLista[i].getHora());
            ui->nombreClases->setText(claseLista[i].getNombre());
            ui->uvClases->setText(QString::number(claseLista[i].getUV()));
            ui->periodoClases->setText(QString::number(claseLista[i].getPeriodo()));
            ui->yearClases->setText(QString::number(claseLista[i].getYear()));
            ui->semestreClases->setText(QString::number(claseLista[i].getSemestre()));
            ui->idClases->setEnabled(false);
            ui->nombreClases->setEnabled(false);
            break;
        }
    }
}


void MainWindow::on_eliminarClase_clicked()
{
    std::vector<clasesPlantilla>& clasesLista = manejo->getClases();
    QStringList nombreClases;
    for (const auto& clase : clasesLista) {
        nombreClases.append(clase.getNombre());
    }

    bool ok;
    QString claseSelec = QInputDialog::getItem(nullptr, "Seleccionar Clase",
                                                            "Eliga la clase que desea eliminar:",
                                                            nombreClases, 0, false, &ok);

    if (ok && !claseSelec.isEmpty()) {
        for (auto it = clasesLista.begin(); it != clasesLista.end(); ++it) {
            if (it->getNombre() == claseSelec) {
                QString rutaClase = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + it->getID();
                QDir dir(rutaClase);
                if (dir.exists()) {
                    if (!dir.removeRecursively()) {
                        QMessageBox::warning(this, "Error", "No se pudo eliminar la carpeta de la clase.");
                        return;
                    }
                }
                clasesLista.erase(it);
                QMessageBox::information(this, "Éxito", "Clase eliminado correctamente.");
                return;
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "No se ha seleccionado una clase.");
    }

    ui->idClases->clear();
    ui->nombreClases->clear();
    ui->uvClases->clear();
    ui->periodoClases->clear();
    ui->yearClases->clear();
    ui->semestreClases->clear();

}


void MainWindow::on_aceptarClases_clicked()
{
    if (ui->tituloClases->text()=="AGREGAR CLASE"){
        QString id= ui->idClases->text();
        QString nombre= ui->nombreClases->text();
        QString hora= ui->horaComboBox->currentText();
        QString uv= ui->uvClases->text();
        QString semestre=ui->semestreClases->text();
        QString year= ui->yearClases->text();
        QString periodo = ui->periodoClases->text();

        if (id.isEmpty() || nombre.isEmpty() || hora.isEmpty() || uv.isEmpty() ||
            semestre.isEmpty() || year.isEmpty() || periodo.isEmpty()) {
            QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
            return;
        }

        bool ok1, ok2, ok3, ok4;
        int uvInt = uv.toInt(&ok1);
        int semestreInt = semestre.toInt(&ok2);
        int yearInt = year.toInt(&ok3);
        int periodoInt = periodo.toInt(&ok4);

        if (!ok1 || !ok2 || !ok3 || !ok4) {
            QMessageBox::warning(this, "Error", "Uno o más valores ingresados no son números válidos.");
            return;
        }

        clasesPlantilla claseNueva(true, id, nombre, hora, uvInt, semestreInt, periodoInt, yearInt);

        if (manejo->ClaseExiste(claseNueva)) {
            QMessageBox::warning(this, "Error", "La clase ya existe en el sistema.");
            return;
        }

        manejo->agregarClases(claseNueva);
        manejo->crearClase(id);

        QMessageBox::information(this, "Éxito", "Clase agregada correctamente.");

        ui->idClases->clear();
        ui->nombreClases->clear();
        ui->uvClases->clear();
        ui->periodoClases->clear();
        ui->yearClases->clear();
        ui->semestreClases->clear();

    }else if(ui->tituloClases->text()=="MODIFICAR CLASE"){
        std::vector<clasesPlantilla>& claseLista = manejo->getClases();
        QString id= ui->idClases->text();
        QString nombre= ui->nombreClases->text();
        QString hora= ui->horaComboBox->currentText();
        QString uv= ui->uvClases->text();
        QString semestre=ui->semestreClases->text();
        QString year= ui->yearClases->text();
        QString periodo = ui->periodoClases->text();

        bool ok1, ok2, ok3, ok4;
        int uvInt = uv.toInt(&ok1);
        int semestreInt = semestre.toInt(&ok2);
        int yearInt = year.toInt(&ok3);
        int periodoInt = periodo.toInt(&ok4);

        if (!ok1 || !ok2 || !ok3 || !ok4) {
            QMessageBox::warning(this, "Error", "Uno o más valores ingresados no son números válidos.");
            return;
        }

        for (std::vector<clasesPlantilla>::size_type i = 0; i < claseLista.size(); ++i) {
            if (claseLista[i].getID() == id) {
                claseLista[i].setSemestre(semestreInt);
                claseLista[i].setYear(yearInt);
                claseLista[i].setPeriodo(periodoInt);
                claseLista[i].setUV(uvInt);
                claseLista[i].setHora(hora);

                QMessageBox::information(this, "Éxito", "Clase modificado correctamente.");
                break;
            }
        }

        ui->idClases->clear();
        ui->nombreClases->clear();
        ui->uvClases->clear();
        ui->periodoClases->clear();
        ui->yearClases->clear();
        ui->semestreClases->clear();
    }
}


void MainWindow::on_AsignarMaestro_clicked()
{
    ui->formularioRegistro->setCurrentIndex(6);
    ui->tituloAsignar->setText("ASIGNAR MAESTROS");
    ui->TituloMatricula->setText("");

    ui->claseComboBox->clear();
    ui->maestroComboBox->clear();
    QList<clasesPlantilla> claseLista = manejo->obtenerListaClases();
    QList<usuarioMaestro> maestrosLista = manejo->obtenerListaMaestros();
    for (auto it = claseLista.begin(); it != claseLista.end(); ++it) {
        ui->claseComboBox->addItem(it->getNombre());
    }

    for (auto it = maestrosLista.begin(); it != maestrosLista.end(); ++it) {
        ui->maestroComboBox->addItem(it->getNombre());
    }
}


void MainWindow::on_matricularAlumnos_clicked()
{
    ui->formularioRegistro->setCurrentIndex(5);
    ui->TituloMatricula->setText("MATRICULAR ALUMNO");
    ui->tituloAsignar->setText("");

    ui->claseMatricularCombo->clear();
    ui->alumnoCombobox->clear();
    QList<clasesPlantilla> claseLista = manejo->obtenerListaClases();
    QList<usuarioAlumno> alumnoLista = manejo->obtenerListaAlumnos();

    for (auto it = claseLista.begin(); it != claseLista.end(); ++it) {
        ui->claseMatricularCombo->addItem(it->getNombre());
    }

    for (auto it = alumnoLista.begin(); it != alumnoLista.end(); ++it) {
        ui->alumnoCombobox->addItem(it->getNombre());
    }
}


void MainWindow::on_aceptarAsignacion_clicked()
{
    QString nombre = ui->claseComboBox->currentText();
    QString user= ui->maestroComboBox->currentText();

    QString id= manejo->obtenerIDClaseXNombre(nombre);

    if (!manejo->matricularUsuarioEnClase(id, user, true)) {
        QMessageBox::warning(nullptr, "Error", "Ya está asignado un maestro en esta clase.");
    } else {
        QMessageBox::information(nullptr, "Éxito", "El maestro ha sido asignado correctamente.");
    }
}

void MainWindow::on_registrarAsignar_2_clicked()
{
    ui->submenuRegistro->setCurrentIndex(4);
    ui->formularioRegistro->setCurrentIndex(0);
}



void MainWindow::on_aceptarMatricula_clicked()
{
    QString nombre = ui->claseMatricularCombo->currentText();
    QString user= ui->alumnoCombobox->currentText();

    QString id= manejo->obtenerIDClaseXNombre(nombre);
    if (!manejo->matricularUsuarioEnClase(id, user, false)) {
        QMessageBox::warning(nullptr, "Error", "El usuario ya está matriculado en esta clase.");
    } else {
        QMessageBox::information(nullptr, "Éxito", "El usuario ha sido matriculado correctamente.");
    }
}


void MainWindow::on_examenesMaestro_clicked()
{
    ui->submenuMaestro->setCurrentIndex(1);
}


void MainWindow::on_tareasMaestro_clicked()
{
    ui->submenuMaestro->setCurrentIndex(2);
}


void MainWindow::on_crearExamen_clicked()
{
    if(ui->tituloMaestroStacked->text()=="NUEVO EXAMEN"){
        QString clase= ui->claseCombo->currentText();
        QString idClase= manejo->obtenerIDClaseXNombre(clase);
        QDateTime tiempo= ui->horaInicio->dateTime();
        int duracion = ui->comboBoxDuracion->currentText().toInt();
        int puntaje = ui->valorExamen->currentText().toInt();
        QString nombreExamen = tiempo.toString("yyyyMMdd_HHmm");
        QString titulo = ui->tituloExamen->text();
        qDebug() << "Duración seleccionada antes de guardar: " << duracion;
        manejo->registrarExamen(titulo, idClase, tiempo, duracion, puntaje, preguntas);
        preguntas.clear();
        ui->preguntas->clear();
        QMessageBox::information(this, "Éxito", "Examen guardado correctamente.");

    }else if(ui->tituloMaestroStacked->text()== "MODIFICAR EXAMEN"){
        QString clase = ui->claseCombo->currentText();
        QString idClase = manejo->obtenerIDClaseXNombre(clase);
        QDateTime tiempo = ui->horaInicio->dateTime();
        int duracion = ui->horaComboBox->currentText().toInt();
        int puntaje = ui->valorExamen->currentText().toInt();
        QString titulo = ui->tituloExamen->text();

        QString examenSelec = ui->claseCombo->currentData().toString();
        QString archivoRuta = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase + "/" + examenSelec;

        QFile archivo(archivoRuta);
        if (archivo.open(QIODevice::ReadWrite)) {
            QDataStream out(&archivo);
            out << tiempo << duracion << puntaje;

            archivo.close();
            QMessageBox::information(this, "Éxito", "Examen modificado correctamente.");
        } else {
            QMessageBox::warning(this, "Error", "No se pudo modificar el examen.");
        }
    }
}


void MainWindow::on_agregarPregunta_clicked()
{
    QString txt = ui->pregunta->text();
    QString tipo = ui->tipoPreguntaCombo->currentText();

    int tipoInt;
    if (tipo== "Verdadero o Falso"){
        tipoInt=0;
    }else if(tipo == "Selección Múltiple"){
        tipoInt=1;
    }else{
        tipoInt=2;
    }

    QString respuestaCorr= ui->respuestaCorrecta->text();
    QString respuestaInco=ui->respuestasIncorrectas->text();

    Pregunta nuevaPregunta(txt, respuestaCorr, respuestaInco, tipoInt);
    preguntas.append(nuevaPregunta);

    QString preguntasTxt;
    for (int i = 0; i < preguntas.size(); i++) {
        preguntasTxt += "Pregunta: "+ preguntas[i].obtenerTexto() +
                "\nRespuesta Correcta: " + preguntas[i].obtenerRespuestaCorrecta() +
                "\nRespuestas Incorrectas: "+ preguntas[i].obtenerRespuestaIncorrecta()+ "\n\n";
    }
    ui->preguntas->setText(preguntasTxt);
}


void MainWindow::on_nuevaTarea_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->tituloTareasMaestro->setText("CREAR TAREA");
    QList<QString> maestroLista = manejo->obtenerClasesDeMaestro(maestro);

    ui->comboClasetarea->clear();
    for (int i = 0; i < maestroLista.size(); ++i) {
        ui->comboClasetarea->addItem(maestroLista[i]);
    }
}


void MainWindow::on_nuevoExamen_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tituloMaestroStacked->setText("NUEVO EXAMEN");
    QList<QString> maestroLista = manejo->obtenerClasesDeMaestro(maestro);

    ui->claseCombo->clear();
    for (int i = 0; i < maestroLista.size(); ++i) {
        ui->claseCombo->addItem(maestroLista[i]);
    }
}


void MainWindow::on_modificarExamen_clicked()
{
    QList<QString> examenLista = manejo->obtenerExamenesDeMaestro(maestro);
    QStringList nombresExamenes;

    for (const QString& examen : examenLista) {
        nombresExamenes.append(examen);
    }

    if (nombresExamenes.isEmpty()) {
        QMessageBox::warning(this, "Sin exámenes", "No hay exámenes disponibles para modificar.");
        return;
    }

    bool ok;
    QString examenSelec = QInputDialog::getItem(this, "Seleccionar Examen",
                                                "Elija el examen que desea modificar:",
                                                nombresExamenes, 0, false, &ok);

    if (!ok || examenSelec.isEmpty()) {
        return;
    }

    QStringList datosExamen = examenSelec.split(" - ");
    if (datosExamen.size() < 3) {
        qDebug() << "Error: El formato del examen seleccionado no es válido.";
        return;
    }

    QString idClase = datosExamen[0];
    QString nombreClase = datosExamen[1];
    QString nombre = datosExamen[2];

    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tituloMaestroStacked->setText("MODIFICAR EXAMEN");
    ui->claseCombo->setCurrentText(nombreClase);

    QFile archivo("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase + "/" + nombre+".exam");
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        QDateTime fechaHora;
        int duracion, puntaje, numPreguntas;
        QString titulo;

        in >> titulo >> idClase >> fechaHora >> duracion >> puntaje >> numPreguntas;
        ui->horaInicio->setDateTime(fechaHora);
        ui->comboBoxDuracion->setCurrentText(QString::number(duracion));
        ui->valorExamen->setCurrentText(QString::number(puntaje));
        ui->periodoClases->setText(QString::number(duracion));
        ui->tituloExamen->setText(titulo);
        QVector<Pregunta> preguntas;
        for (int i = 0; i < numPreguntas; ++i) {
            Pregunta pregunta;
            pregunta.cargar(in);
            preguntas.append(pregunta);
        }
        QString preguntasTexto;
        for (const Pregunta& pregunta : preguntas) {
            preguntasTexto += pregunta.obtenerTexto() + "\n\n";
        }
        ui->preguntas->setText(preguntasTexto);

        archivo.close();
    }
}


void MainWindow::on_eliminarExamen_clicked()
{
    QList<QString> examenLista = manejo->obtenerExamenesDeMaestro(maestro);
    QStringList nombresExamenes;

    for (const QString& examen : examenLista) {
        nombresExamenes.append(examen);
    }

    if (nombresExamenes.isEmpty()) {
        QMessageBox::warning(this, "Sin exámenes", "No hay exámenes disponibles para modificar.");
        return;
    }

    bool ok;
    QString examenSelec = QInputDialog::getItem(this, "Seleccionar Examen",
                                                "Elija el examen que desea modificar:",
                                                nombresExamenes, 0, false, &ok);

    if (!ok || examenSelec.isEmpty()) {
        return;
    }

    QMessageBox::StandardButton confirmacion;
    confirmacion = QMessageBox::question(this, "Confirmar Eliminación",
                                         "¿Estás seguro de que deseas eliminar este examen?",
                                         QMessageBox::Yes | QMessageBox::No);

    if (confirmacion == QMessageBox::No) {
        return;
    }

    for (int i = 0; i < examenLista.size(); ++i) {
        QStringList datosExamen = examenLista[i].split(" - ");
        if (examenLista[i] == examenSelec) {
            QString idClase = manejo->obtenerIDClaseXNombre(datosExamen[1]);
            QString rutaArchivo = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/clases/" + idClase + "/" + datosExamen[2]+".exam";

            QFile archivo(rutaArchivo);
            if (archivo.exists()) {
                if (!archivo.remove()) {
                    QMessageBox::warning(this, "Error", "No se pudo eliminar el archivo del examen.");
                    return;
                }
            }
            manejo->eliminarExamen(datosExamen[2]);

            QMessageBox::information(this, "Éxito", "Examen eliminado correctamente.");
            return;
        }
    }

}


void MainWindow::on_crearTarea_clicked()
{
    QString clase= ui->comboClasetarea->currentText();
    QString titulo = ui->tituloTarea->text();
    QString descripcion = ui->descripciontarea->toPlainText();
    int prioridad = ui->comboPrioridad->currentText().toInt();
    QDateTime tiempoInicio = ui->tiempoInicio->dateTime();
    QDateTime tiempoFinal = ui->tiempoFinalizacion->dateTime();
    int tiempoEstimado = tiempoInicio.msecsTo(tiempoFinal) / 60000;
    QString estado = "Incompleto";
    QString tipoArchivo = ui->comboBox_2->currentText();
    QString recursostexto =ui->textorecursos->toPlainText();
    QStringList recursos = recursostexto.split("\n", QString::SkipEmptyParts);


    manejo->agregarTarea(clase, titulo, descripcion, prioridad, tiempoEstimado, estado, tipoArchivo, recursos);
    QMessageBox::information(this, "Éxito", "Tarea creada correctamente.");


}


void MainWindow::on_agregarRecursos_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Seleccionar archivo"), "", tr("Archivos (*.*)"));

    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString saveFolder = "C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/";
        QDir dir(saveFolder);
        if (!dir.exists()) {
            dir.mkpath(saveFolder);
        }
        QString newFilePath = saveFolder + fileName;
        QFile::copy(filePath, newFilePath);

        QStringList recursos = ui->textorecursos->toPlainText().split("\n", QString::SkipEmptyParts);
        recursos.append(newFilePath);
        ui->textorecursos->clear();
        ui->textorecursos->setPlainText(recursos.join("\n"));
    }
}

void MainWindow::on_tareasPendientes_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->boton1Tareas->hide();
    ui->boton2Listas->hide();
    ui->tituloDeListaTarea->setText("LISTADO DE TAREAS PENDIENTES");
    QList<QString> clasesMaestro = manejo->obtenerClasesDeMaestro(maestro);
    if (clasesMaestro.isEmpty()) {
        ui->textEditPendiente->setPlainText("Este maestro no tiene clases asignadas.");
        return;
    }

    ui->textEditPendiente->clear();
    QString texto;

    for (const tarea& t : manejo->getTareas()) {
        if (clasesMaestro.contains(t.getClase()) && t.getEstado() == "Incompleto") {
            texto += "Clase: " + t.getClase() + "\n";
            texto += "Título: " + t.getTitulo() + "\n";
            texto += "Descripción: " + t.getDescripcion() + "\n";
            texto += "Prioridad: " + QString::number(t.getPrioridad()) + "\n";
            texto += "Tiempo Estimado: " + QString::number(t.getTiempoEstimado()) + " min\n\n";
        }
    }

    if (texto.isEmpty()) {
        texto = "No hay tareas incompletas para este maestro.";
    }

    ui->textEditPendiente->setPlainText(texto);
}


void MainWindow::on_eliminarTareas_clicked()
{
    ui->boton1Tareas->show();
    ui->boton2Listas->show();
    ui->boton2Listas->setText("ELIMINAR PERMANENTEMENTE");
    ui->boton1Tareas->setText("RESTAURAR");
    ui->tituloDeListaTarea->setText("ELIMINAR TAREAS COMPLETADAS");
    ui->textEditPendiente->clear();
}


void MainWindow::on_ordenarTareas_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->tituloDeListaTarea->setText("ORDENAR TAREAS");
    ui->boton1Tareas->show();
    ui->boton2Listas->show();
    ui->boton2Listas->setText("POR TIEMPO ESTIMADO DE FINALIZACION");
    ui->boton1Tareas->setText("POR PRIORIDAD");
}


void MainWindow::on_ejecutarTareas_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->tituloDeListaTarea->setText("EJECUTAR TAREAS INCOMPLETAS");
    ui->boton1Tareas->show();
    ui->boton2Listas->show();
    ui->boton1Tareas->setText("POR FIFO");
    ui->boton2Listas->setText("POR PRIORIDAD");


}

void MainWindow::on_boton1Tareas_clicked()
{
    if(ui->tituloDeListaTarea->text() == "EJECUTAR TAREAS INCOMPLETAS") {
        ui->textEditPendiente->clear();
        if (manejo->getTareas().empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas para ejecutar.");
            return;
        }

        std::queue<tarea> colaTareas;
        for (size_t i = 0; i < manejo->getTareas().size(); ++i) {
            if (manejo->getTareas()[i].getEstado() == "Incompleto") {
                colaTareas.push(manejo->getTareas()[i]);
            }
        }

        if (colaTareas.empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas incompletas.");
            return;
        }

        while (!colaTareas.empty()) {
            tarea t = colaTareas.front();
            colaTareas.pop();

            ui->textEditPendiente->append("Ejecutando tarea: " + t.getTitulo());
            ui->textEditPendiente->append("Tarea completada: " + t.getTitulo());

            manejo->marcarTareaComoCompletada(t.getTitulo());
        }

        ui->textEditPendiente->append("Todas las tareas han sido completadas.");
        manejo->guardarTareas();
    }
    else if(ui->tituloDeListaTarea->text() == "ORDENAR TAREAS") {
        std::vector<tarea>& tareas = manejo->getTareas();

        if (tareas.empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas para ordenar.");
            return;
        }
        bool intercambiado;
        for (size_t i = 0; i < tareas.size(); ++i) {
            intercambiado = false;
            for (size_t j = 0; j < tareas.size() - 1 - i; ++j) {
                if (tareas[j].getTiempoEstimado() > tareas[j + 1].getTiempoEstimado()) {
                    std::swap(tareas[j], tareas[j + 1]);
                    intercambiado = true;
                }
            }
            if (!intercambiado){
                break;
            }
        }

        ui->textEditPendiente->clear();
        for (size_t i = 0; i < tareas.size(); ++i) {
            ui->textEditPendiente->append("Tarea: " + tareas[i].getTitulo() + " - Tiempo estimado: " + QString::number(tareas[i].getTiempoEstimado()) + " horas - Estado: " + tareas[i].getEstado());
        }
    }
    else if(ui->tituloDeListaTarea->text() == "ELIMINAR TAREAS COMPLETADAS") {
        std::vector<tarea>& tareas = manejo->getTareas();

        if (tareas.empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas para restaurar.");
            return;
        }
        for (size_t i = 0; i < tareas.size(); ++i) {
            if (tareas[i].getEstado() == "Completada") {
                tareas[i].setEstado("Incompleto");
            }
        }

        ui->textEditPendiente->append("Todas las tareas completadas han sido restauradas.");
        manejo->guardarTareas();
    }
}

void MainWindow::on_boton2Listas_clicked()
{
    if(ui->tituloDeListaTarea->text() == "EJECUTAR TAREAS INCOMPLETAS") {
        ui->textEditPendiente->clear();
        if (manejo->getTareas().empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas para ejecutar.");
            return;
        }

        auto comparador = [](const tarea& a, const tarea& b) {
            return a.getPrioridad() < b.getPrioridad();
        };

        std::priority_queue<tarea, std::vector<tarea>, decltype(comparador)> colaTareas(comparador);

        // Colocamos las tareas incompletas en la cola
        for (size_t i = 0; i < manejo->getTareas().size(); ++i) {
            if (manejo->getTareas()[i].getEstado() == "Incompleto") {
                colaTareas.push(manejo->getTareas()[i]);
            }
        }

        if (colaTareas.empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas incompletas.");
            return;
        }

        // Ejecutar las tareas en la cola por prioridad
        while (!colaTareas.empty()) {
            tarea t = colaTareas.top();
            colaTareas.pop();

            ui->textEditPendiente->append("Ejecutando tarea: " + t.getTitulo());
            ui->textEditPendiente->append("Tarea completada: " + t.getTitulo());

            manejo->marcarTareaComoCompletada(t.getTitulo());
        }

        ui->textEditPendiente->append("Todas las tareas han sido completadas.");
        manejo->guardarTareas();
    }
    else if(ui->tituloDeListaTarea->text() == "ORDENAR TAREAS") {
        std::vector<tarea>& tareas = manejo->getTareas();

        if (tareas.empty()) {
            ui->textEditPendiente->setPlainText("No hay tareas para ordenar.");
            return;
        }

        // Ordenamiento por prioridad usando for normal
        bool intercambiado;
        for (size_t i = 0; i < tareas.size(); ++i) {
            intercambiado = false;
            for (size_t j = 0; j < tareas.size() - 1 - i; ++j) {
                if (tareas[j].getPrioridad() > tareas[j + 1].getPrioridad()) {
                    std::swap(tareas[j], tareas[j + 1]);
                    intercambiado = true;
                }
            }
            if (!intercambiado) {
                break;
            }
        }

        ui->textEditPendiente->clear();
        for (size_t i = 0; i < tareas.size(); ++i) {
            ui->textEditPendiente->append("Tarea: " + tareas[i].getTitulo() + " - Prioridad: " + QString::number(tareas[i].getPrioridad()) + " - Estado: " + tareas[i].getEstado());
        }
    }
    else if(ui->tituloDeListaTarea->text() == "ELIMINAR TAREAS COMPLETADAS") {
        std::vector<tarea>& tareas = manejo->getTareas();

        if (tareas.empty()) {
            ui->textEditPendiente->append("No hay tareas para eliminar permanentemente.");
            return;
        }

        for (size_t i = 0; i < tareas.size(); ++i) {
            if (tareas[i].getEstado() == "Completada") {
                tareas.erase(tareas.begin() + i);
                --i;
            }
        }

        ui->textEditPendiente->append("Las tareas completadas han sido eliminadas permanentemente.");
        manejo->guardarTareas();
    }
}

void MainWindow::on_examenesAlumnos_clicked()
{
    QList<QString> examenesDelAlumno = manejo->obtenerExamenesDeAlumno(alumnoRegistrado);
    QScrollArea *scrollArea = findChild<QScrollArea*>("scrollArea");
    if (!scrollArea) {
        qDebug() << "No se encontró el QScrollArea en la UI.";
        return;
    }

    QWidget *contenedor = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(contenedor);

    for (const QString &examen : examenesDelAlumno) {
        QPushButton *boton = new QPushButton(examen);
        boton->setStyleSheet("background-color: rgb(6, 6, 92);"
                             "color: white;"
                             "font: 75 10pt 'Segoe UI Bold';"
                             "border-radius: 10px;"
                             "padding: 8px;"
                             "margin: 5px;");
        connect(boton, &QPushButton::clicked, this, [this, examen]() {
            mostrarExamen(examen);
        });

        layout->addWidget(boton);
    }

    contenedor->setLayout(layout);
    scrollArea->setWidget(contenedor);
    scrollArea->setWidgetResizable(true);
}

void MainWindow::mostrarExamen(const QString& datosExamen) {
    Examen examen = manejo->obtenerExamenDesdeArchivo(datosExamen);

    if (examen.getTitulo().isEmpty()) {
        qDebug() << "No se pudo cargar el examen.";
        return;
    }
    ui->stackedWidget_3->setCurrentIndex(1);

    ui->labelTitulo->setText(examen.getTitulo());
    ui->labelValor->setText(QString::number(examen.getPuntaje()));
    ui->labelDuracion->setText(QString::number(examen.getDuracion()));
    ui->labelClase->setText(examen.getIdClase());
    ui->dateTimeExamen->setDateTime(examen.getFechaHora());

    if(!examenYaRealizado(examen.getIdClase(), examen.getFechaHora().toString("yyyyMMdd_HHmm"), alumnoRegistrado)){
        QWidget *contenedorTodasLasPreguntas = new QWidget();
        QVBoxLayout *layoutPreguntas = new QVBoxLayout(contenedorTodasLasPreguntas);
        layoutPreguntas->setAlignment(Qt::AlignTop);

        for (const Pregunta &pregunta : examen.getPreguntas()) {
            QWidget *contenedorPregunta = mostrarPregunta(pregunta);
            layoutPreguntas->addWidget(contenedorPregunta);
        }
        layoutPreguntas->addStretch();

        ui->scrollAreaPreguntas->setWidget(contenedorTodasLasPreguntas);
        ui->scrollAreaPreguntas->setWidgetResizable(true);
    }else{
        QMessageBox::warning(this, "Error", "Ya realizaste este examen.");
    }
}

QWidget* MainWindow::mostrarPregunta(const Pregunta &pregunta) {
    QWidget *contenedorPregunta = new QWidget();
    QVBoxLayout *layoutPregunta = new QVBoxLayout(contenedorPregunta);

    layoutPregunta->setAlignment(Qt::AlignTop);

    QLabel *labelPregunta = new QLabel(pregunta.obtenerTexto(), contenedorPregunta);
    labelPregunta->setStyleSheet("font-size: 18px; font-weight: bold;"); // Aumentar tamaño de pregunta
    layoutPregunta->addWidget(labelPregunta);

    switch (pregunta.obtenerTipo()) {
        case 0: {  // Verdadero/Falso
            QComboBox *comboBox = new QComboBox(contenedorPregunta);
            comboBox->addItem("Verdadero");
            comboBox->addItem("Falso");
            comboBox->setFixedWidth(300);
            comboBox->setStyleSheet("font-size: 16px;"); // Aumentar tamaño de texto
            layoutPregunta->addWidget(comboBox);
            break;
        }
        case 1: {  // Selección Múltiple
            QVBoxLayout *opcionesLayout = new QVBoxLayout();

            QRadioButton *radioBtnCorrecto = new QRadioButton(pregunta.obtenerRespuestaCorrecta(), contenedorPregunta);
            radioBtnCorrecto->setStyleSheet("font-size: 16px;"); // Aumentar tamaño de respuesta
            opcionesLayout->addWidget(radioBtnCorrecto);

            QStringList opcionesIncorrectas = pregunta.obtenerRespuestaIncorrecta().split(",");
            for (const QString &opcion : opcionesIncorrectas) {
                QRadioButton *radioBtnIncorrecto = new QRadioButton(opcion.trimmed(), contenedorPregunta);
                radioBtnIncorrecto->setStyleSheet("font-size: 16px;"); // Aumentar tamaño de respuesta
                opcionesLayout->addWidget(radioBtnIncorrecto);
            }

            layoutPregunta->addLayout(opcionesLayout);
            break;
        }
        case 2: {  // Enumeradas
            QLineEdit *lineEdit = new QLineEdit(contenedorPregunta);
            lineEdit->setFixedWidth(300);
            lineEdit->setStyleSheet("font-size: 16px;"); // Aumentar tamaño de texto en input
            layoutPregunta->addWidget(lineEdit);
            break;
        }
        default:
            qDebug() << "Tipo de pregunta no reconocido.";
    }

    contenedorPregunta->setMinimumSize(400, 100);
    return contenedorPregunta;
}

bool MainWindow::examenYaRealizado(const QString& idClase, const QString& nombreFile, const QString& usuario) {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/examenes_realizados.gen");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList datos = linea.split("|");
            if (datos.size() == 3 && datos[0] == idClase && datos[1] == nombreFile && datos[2] == usuario) {
                file.close();
                return true; // El usuario ya hizo este examen
            }
        }
        file.close();
    }
    return false;
}

void MainWindow::registrarExamenRealizado(const QString& idClase, const QString& nombreFile, const QString& usuario) {
    QFile file("C:/Users/avril/Desktop/Proyectos/ProyectoEstruCanvas/archivos/examenes_realizados.gen");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << idClase << "|" << nombreFile << "|" << usuario << "\n";
        file.close();
    } else {
        qDebug() << "Error al abrir el archivo de exámenes realizados.";
    }
}

void MainWindow::on_responderExamen_clicked() {
    QString idClase = ui->labelClase->text();
    QString nombreFile = ui->dateTimeExamen->dateTime().toString("yyyyMMdd_HHmm");
    QString usuario = alumnoRegistrado;

    if (examenYaRealizado(idClase, nombreFile, usuario)) {
        QMessageBox::warning(this, "Error", "Ya realizaste este examen.");
        return;
    }

    Examen examen = manejo->obtenerExamenDesdeArchivo(nombreFile);
    if (examen.getTitulo().isEmpty()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar el examen.");
        return;
    }

    int puntajeTotal = examen.getPuntaje();
    int puntajeObtenido = 0;
    int totalPreguntas = examen.getPreguntas().size();

    QWidget *contenedorPreguntas = ui->scrollAreaPreguntas->widget();
    QList<QWidget*> preguntasWidgets = contenedorPreguntas->findChildren<QWidget*>();

    int index = 0;
    for (const Pregunta &pregunta : examen.getPreguntas()) {
        if (index >= preguntasWidgets.size()) break;

        QWidget *preguntaWidget = preguntasWidgets[index];
        index++;

        switch (pregunta.obtenerTipo()) {
            case 0: { // Verdadero/Falso
                QComboBox *comboBox = preguntaWidget->findChild<QComboBox*>();
                if (comboBox && comboBox->currentText() == pregunta.obtenerRespuestaCorrecta()) {
                    puntajeObtenido++;
                }
                break;
            }
            case 1: { // Selección Múltiple
                QList<QRadioButton*> radios = preguntaWidget->findChildren<QRadioButton*>();
                for (QRadioButton *radio : radios) {
                    if (radio->isChecked() && radio->text() == pregunta.obtenerRespuestaCorrecta()) {
                        puntajeObtenido++;
                        break;
                    }
                }
                break;
            }
            case 2: { // Enumeradas (respuesta escrita)
                QLineEdit *lineEdit = preguntaWidget->findChild<QLineEdit*>();
                if (lineEdit && lineEdit->text().trimmed().toLower() == pregunta.obtenerRespuestaCorrecta().trimmed().toLower()) {
                    puntajeObtenido++;
                }
                break;
            }
        }
    }
    double notaFinal = (static_cast<double>(puntajeObtenido) / totalPreguntas) * puntajeTotal;
    registrarExamenRealizado(idClase, nombreFile, usuario);
    manejo->actualizarNotas(idClase, usuario, notaFinal);

    QMessageBox::information(this, "Examen Finalizado", "Tu calificación es: " + QString::number(notaFinal, 'f', 2));
}



void MainWindow::on_verResultadosExamen_clicked()
{

}

