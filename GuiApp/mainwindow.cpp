#include "servertable.h"
#include "mainwindow.h"
#include "addserverdialog.h"
#include "linktabledialog.h"
#include "ui_mainwindow.h"
#include "abonentlist.h"
#include "editserverdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include "networkservice.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add key combos for menu
    (void)new QShortcut(tr("Ctrl+O"),this,SLOT(on_OpenFile_triggered()));
    (void)new QShortcut(tr("Ctrl+S"),this,SLOT(on_SaveFile_triggered()));
    (void)new QShortcut(tr("Ctrl+Q"),this,SLOT(on_Exit_triggered()));
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
        ui->servertable->UpdateTable();
        ui->abonentList->Update();
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void MainWindow::on_SaveFile_triggered()
{
    QString filter = "База данных сетевого сервиса (*.txtdb)";
    QString _path = QFileDialog::getSaveFileName(this,"Сохранить файл",
                                             "..",filter,&filter);
    if (QFileInfo(_path).suffix().isEmpty())
        _path+=".txtdb";
    auto path=std::string(_path.toUtf8().data());
    if (path=="") return;

    try {
        NetworkService::Application::getInstance().saveToFile(path);
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void MainWindow::on_addserver_clicked()
{
    auto *asdialog = new AddServerDialog;
    connect(asdialog,SIGNAL(AddLastItemSignal()),ui->servertable,SLOT(AddLastItem()));
    connect(asdialog,SIGNAL(AddLastItemSignal()),ui->abonentList,SLOT(Update()));
    asdialog->show();
}

void MainWindow::on_removeServer_clicked()
{
    QModelIndexList selected = ui->servertable->selectionModel()->selectedRows();
    foreach (QModelIndex index,selected) {
        try {
            NetworkService::Application::getInstance().delServerIndex(index.row());
            ui->servertable->removeRow(index.row());
            ui->abonentList->Update();
        } catch (std::exception &e) {
            QMessageBox::critical(this,"Ошибка",e.what(),QMessageBox::Ok);
        }
    }
}

void MainWindow::on_linktableShow_clicked()
{
    QModelIndexList selected = ui->servertable->selectionModel()->selectedRows();
    if(selected.size()==0)
        QMessageBox::warning(this,"Информация","Выберете хотя бы один сервер",QMessageBox::Ok);
    foreach (QModelIndex index,selected) {
        auto ltf = new LinkTableDialog(this,index.row());
        connect(ltf,SIGNAL(UpdateAbonentListSignal()),ui->abonentList,SLOT(Update()));
        ltf->show();
    }
}


void MainWindow::on_abonentInfo_clicked()
{
    if(ui->abonentList->currentData().isNull()) {
        QMessageBox::critical(this,"Ошибка","Список абонентов пуст",QMessageBox::Ok);
        return;
    }
    try {
        auto abinfo = NetworkService::Application::getInstance().abonentInfo((ulong)ui->abonentList->currentData().toULongLong());
        QString message;
        std::for_each(abinfo.cbegin(),abinfo.cend(),[&](const std::string &s){
            message+=s.c_str();
            message+='\n';
        });
        message.remove(message.size()-1,1);
        QMessageBox::information(this,"Информация об абоненте",message,QMessageBox::Ok);
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Ошибка",e.what(),QMessageBox::Ok);
    }
}

void MainWindow::on_editServer_clicked()
{
    QModelIndexList selected = ui->servertable->selectionModel()->selectedRows();
    if(selected.size()==0)
        QMessageBox::warning(this,"Информация","Выберете хотя бы один сервер",QMessageBox::Ok);
    foreach (QModelIndex index,selected) {
        auto editd = new EditServerDialog(this,index.row());
        //connect UpdateItem slot
        connect(editd,SIGNAL(UpdateItemSignal(uint,ulong,QString &,uint,uint)),ui->servertable,SLOT(UpdateItem(uint,ulong,QString&,uint,uint)));
        editd->show();
    }
}
