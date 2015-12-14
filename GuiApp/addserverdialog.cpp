#include "addserverdialog.h"
#include "ui_addserverdialog.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include "networkservice.h"
AddServerDialog::AddServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServerDialog)
{
    ui->setupUi(this);
    //regexp for ip validation, checks only 0-255.0-255.0-255.0-255
    QRegExp rx( "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])" );
    QRegExpValidator *validator = new QRegExpValidator(QRegExp(rx), ui->ipEdit);
    ui->ipEdit->setValidator(validator);
    ui->costmbEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}"),ui->costmbEdit));
    ui->costminEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}"),ui->costminEdit));
}

AddServerDialog::~AddServerDialog()
{
    delete ui;
}

void AddServerDialog::on_buttonBox_rejected()
{
    close();
}

void AddServerDialog::on_buttonBox_accepted()
{
    try {
        auto ipstr = std::string(ui->ipEdit->text().toUtf8().data());
        auto ip = NetworkService::stringToLongIP(ipstr);
        auto name = std::string(ui->nameEdit->text().toUtf8().data());
        auto costpermb = ui->costmbEdit->text().toULong();
        auto costpermin = ui->costminEdit->text().toULong();
        NetworkService::Application::getInstance().addServer(ip,name,costpermin,costpermb);
        emit AddLastItemSignal();
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void AddServerDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //reset button
    if (ui->buttonBox->standardButton(button)==QDialogButtonBox::Reset) {
        ui->ipEdit->setText("");
        ui->nameEdit->setText("");
        ui->costmbEdit->setText("");
        ui->costminEdit->setText("");
    }
}
