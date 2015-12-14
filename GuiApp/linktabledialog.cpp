#include "linktabledialog.h"
#include "ui_linktabledialog.h"
#include "networkservice.h"
#include "addservicedialog.h"
#include "editservicedialog.h"
#include <QMessageBox>
LinkTableDialog::LinkTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkTableDialog)
{
    ui->setupUi(this);
}

LinkTableDialog::LinkTableDialog(QWidget *parent, uint _index) :
    QDialog(parent),
    ui(new Ui::LinkTableDialog),
    index(_index)
{
    ui->setupUi(this);
    auto servername = NetworkService::Application::getInstance()[index].getName();
    auto serveraddr = NetworkService::Application::getInstance()[index].getAddress();
    setWindowTitle(tr("Таблица связи для сервера: ")+
                   tr(servername.c_str())+
                   tr(" (")+
                   tr(NetworkService::LongIPtoString(serveraddr).c_str())+
                   tr(")"));
}

uint LinkTableDialog::getIndex() const
{
    return index;
}

LinkTableDialog::~LinkTableDialog()
{
    delete ui;
}

void LinkTableDialog::on_addService_clicked()
{
    auto asd = new AddServiceDialog(this,NetworkService::Application::getInstance()[index].getAddress());
    connect(asd,SIGNAL(UpdateLinkTableSignal()),ui->linktableWidget,SLOT(UpdateLinkTable()));
    asd->show();
}

void LinkTableDialog::on_editService_clicked()
{
    QModelIndexList selected = ui->linktableWidget->selectionModel()->selectedIndexes();
    if(selected.size()==0)
        QMessageBox::warning(this,"Информация","Выберете хотя бы одну запись",QMessageBox::Ok);
    foreach (QModelIndex index,selected){
        auto editd = new EditServiceDialog(this,NetworkService::Application::getInstance()[this->index].getAddress(),index.row());
        connect(editd,SIGNAL(UpdateLinkTableSignal()),ui->linktableWidget,SLOT(UpdateLinkTable()));
        editd->show();
    }
}

void LinkTableDialog::on_pushButton_clicked()
{
    close();
}

void LinkTableDialog::on_removeService_clicked()
{
    QModelIndexList selected = ui->linktableWidget->selectionModel()->selectedIndexes();
    if(selected.size()==0)
        QMessageBox::warning(this,"Информация","Выберете хотя бы одну запись",QMessageBox::Ok);
    try {
        foreach (QModelIndex index,selected){
            NetworkService::Application::getInstance()[this->index].delService(index.row());
        }
        ui->linktableWidget->UpdateLinkTable();
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Ошибка",e.what(),QMessageBox::Ok);
    }
}
