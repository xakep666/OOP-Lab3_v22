#include "editserverdialog.h"
#include "ui_addserverdialog.h"
#include "networkservice.h"
#include <QMessageBox>
EditServerDialog::EditServerDialog(QWidget *parent, uint index):
    AddServerDialog(parent),
    index(index)
{
    //change title and setup fields
    setWindowTitle("Редактирование сервера");
    try {
        ui->ipEdit->setText(NetworkService::LongIPtoString(NetworkService::Application::getInstance()[index].getAddress()).c_str());
        ui->nameEdit->setText(NetworkService::Application::getInstance()[index].getName().c_str());
        ui->costmbEdit->setText(QString::number(NetworkService::Application::getInstance()[index].getCostPerMB()));
        ui->costminEdit->setText(QString::number(NetworkService::Application::getInstance()[index].getCostPerMin()));
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
        close();
    }
}

void EditServerDialog::on_buttonBox_accepted() {
    try {
        std::string ipstr(ui->ipEdit->text().toUtf8().data());
        auto newIP = NetworkService::stringToLongIP(ipstr);
        auto newName = ui->nameEdit->text();
        emit UpdateItemSignal(index,newIP,newName,ui->costminEdit->text().toULong(),ui->costmbEdit->text().toULong());
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void EditServerDialog::on_buttonBox_clicked(QAbstractButton *button) {
    //reset button
    if (ui->buttonBox->standardButton(button)==QDialogButtonBox::Reset) {
        //restore original values
        ui->ipEdit->setText(NetworkService::LongIPtoString(NetworkService::Application::getInstance()[index].getAddress()).c_str());
        ui->nameEdit->setText(NetworkService::Application::getInstance()[index].getName().c_str());
        ui->costmbEdit->setText(QString::number(NetworkService::Application::getInstance()[index].getCostPerMB()));
        ui->costminEdit->setText(QString::number(NetworkService::Application::getInstance()[index].getCostPerMin()));
    }
}
