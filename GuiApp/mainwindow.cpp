#include "servertable.h"
#include "mainwindow.h"
#include "filemenu.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "networkservice.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Exit_triggered()
{
    close();
}

void MainWindow::on_OpenFile_triggered()
{
    std::string path = QFileDialog::getOpenFileName(this,"Открыть файл",
                                             "..",
                                             "База данных сетевого сервиса (*.txtdb)").toUtf8().data();
    if (path=="") return;
    try {
        NetworkService::Application::getInstance().readFromFile(path);
        emit ui->filemenu->UpdateTableSignal();
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void MainWindow::on_SaveFile_triggered()
{
    std::string path = QFileDialog::getSaveFileName(this,"Сохранить файл",
                                             "..",
                                             "База данных сетевого сервиса (*.txtdb)").toUtf8().data();
    if (path=="") return;
    try {
        NetworkService::Application::getInstance().saveToFile(path);
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}
