#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    this->move(screenGeometry.center() - this->rect().center());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    if (!ui->usuario->text().isEmpty() && !ui->password->text().isEmpty()){
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::warning(this, "Advertencia", "Se debe de ingresar ambos datos.");
    }

}

