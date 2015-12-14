#include "addservicedialog.h"
#include "ui_addservicedialog.h"
#include "linktabledialog.h"
#include <QRegExpValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QPushButton>
#include "networkservice.h"
AddServiceDialog::AddServiceDialog(QWidget *parent, ulong serveraddr) :
    QDialog(parent),
    ui(new Ui::AddServiceDialog),
    serveraddr(serveraddr)
{
    ui->setupUi(this);
    //set validators
    //IP
    QRegExp rx( "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])."
                                      "(   |[0-9]  | [0-9] |  [0-9]|[0-9][0-9] | [0-9][0-9]|[0-1][0-9][0-9]|2[0-4][0-9]|25[0-5])" );
    ui->abonentEdit->setValidator(new QRegExpValidator(rx,ui->abonentEdit));
    ui->sendrecvEdit_files->setValidator(new QRegExpValidator(rx,ui->sendrecvEdit_files));
    ui->sendrecvEdit_post->setValidator(new QRegExpValidator(rx,ui->sendrecvEdit_post));
    ui->destEdit_net->setValidator(new QRegExpValidator(rx,ui->destEdit_net));
    //numbers
    ui->sendEdit_net->setValidator(new QIntValidator(0,INT_MAX,ui->sendEdit_net));
    ui->recvEdit_net->setValidator(new QIntValidator(0,INT_MAX,ui->recvEdit_net));
    ui->durationEdit_net->setValidator(new QIntValidator(0,INT_MAX,ui->durationEdit_net));
    ui->durationEdit_files->setValidator(new QIntValidator(0,INT_MAX,ui->durationEdit_files));
    ui->sendrecvDataEdit_files->setValidator(new QIntValidator(0,INT_MAX,ui->sendrecvDataEdit_files));
    ui->sendrecvDataEdit_post->setValidator(new QIntValidator(0,INT_MAX,ui->sendrecvDataEdit_post));
    //disable OK button until we enter valid IP
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    //set all times to now
    ui->dateTimeEdit_post->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_network->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_files->setDateTime(QDateTime::currentDateTime());
    //setup radio-buttons
    ui->recvToggle_post->setChecked(true);
    ui->recvToggle_files->setChecked(true);
}

AddServiceDialog::~AddServiceDialog()
{
    delete ui;
}

void AddServiceDialog::on_recvToggle_post_clicked()
{
    ui->srcdestLabel_post->setText("Отправитель");
    ui->sendrecvDataLabel_post->setText("Получено (MB)");
}

void AddServiceDialog::on_sendToggle_post_clicked()
{
    ui->srcdestLabel_post->setText("Получатель");
    ui->sendrecvDataLabel_post->setText("Отправлено (MB)");
}

void AddServiceDialog::on_recvToggle_files_clicked()
{
    ui->srcdestLabel_files->setText("Отправитель");
    ui->sendrecvDataLabel_files->setText("Получено (MB)");
}

void AddServiceDialog::on_sendToggle_files_clicked()
{
     ui->srcdestLabel_files->setText("Получатель");
     ui->sendrecvDataLabel_files->setText("Отправлено (MB)");
}

void AddServiceDialog::on_buttonBox_rejected()
{
    close();
}

void AddServiceDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //reset button
    if (ui->buttonBox->standardButton(button)==QDialogButtonBox::Reset) {
        //reset only current tab
        auto tabindex = ui->services->currentIndex();
        switch (tabindex) {
        case 0: //post
        {
            ui->addPost->setChecked(false);
            ui->sendrecvEdit_post->setText("");
            ui->srcdestLabel_post->setText("Отправитель");
            ui->sendrecvDataLabel_post->setText("Получено (MB)");
            ui->sendrecvDataEdit_post->setText("");
            ui->recvToggle_post->setChecked(true);
            break;
        }
        case 1: //files
        {
            ui->addFiles->setChecked(false);
            ui->sendrecvEdit_files->setText("");
            ui->srcdestLabel_files->setText("Отправитель");
            ui->sendrecvDataLabel_files->setText("Получено (MB)");
            ui->sendrecvDataEdit_files->setText("");
            ui->recvToggle_files->setChecked(false);
            ui->durationEdit_files->setText("");
            break;
        }
        case 2: //net
        {
            ui->addNet->setChecked("false");
            ui->sendEdit_net->setText("");
            ui->recvEdit_net->setText("");
            ui->destEdit_net->setText("");
            ui->durationEdit_net->setText("");
            break;
        }
        }
    }
}

void AddServiceDialog::on_buttonBox_accepted()
{
    try {
        std::string abonentStr(ui->abonentEdit->text().toUtf8().data());
        ulong abonentIP = NetworkService::stringToLongIP(abonentStr);
        NetworkService::Server *srv = &NetworkService::Application::getInstance().getServer(serveraddr);
        //add post descriptor
        if(ui->addPost->isChecked()) {
            //extract needed data
            NetworkService::Direction direction;
            ulong dstIP = NetworkService::stringToLongIP(std::string(ui->sendrecvEdit_post->text().toUtf8().data()));
            if(ui->recvToggle_post->isChecked()) //reciving post
                direction = NetworkService::RECV;
            if(ui->sendToggle_post->isChecked()) //sending post
                direction = NetworkService::SEND;
            ulong traffic = ui->sendrecvDataEdit_post->text().toULong();
            ftimepoint timeofservice(Time::from_time_t(ui->dateTimeEdit_post->dateTime().toTime_t()));
            NetworkService::ServiceDescriptor *pd =
                    new NetworkService::PostDescriptor(traffic,direction,dstIP,timeofservice,srv);
            NetworkService::Application::getInstance().addService(abonentIP,pd);
        }
        if(ui->addFiles->isChecked()) {
            //extract needed data
            NetworkService::Direction direction;
            ulong dstIP = NetworkService::stringToLongIP(std::string(ui->sendrecvEdit_post->text().toUtf8().data()));
            if(ui->recvToggle_post->isChecked()) //reciving post
                direction = NetworkService::RECV;
            if(ui->sendToggle_post->isChecked()) //sending post
                direction = NetworkService::SEND;
            fduration duration (ui->durationEdit_files->text().toUInt()*minute_k);
            ulong traffic = ui->sendrecvDataEdit_post->text().toULong();
            ftimepoint timeofservice(Time::from_time_t(ui->dateTimeEdit_files->dateTime().toTime_t()));
            NetworkService::ServiceDescriptor *fd =
                    new NetworkService::FileDescriptor(traffic,direction,dstIP,timeofservice,duration,srv);
            NetworkService::Application::getInstance().addService(abonentIP,fd);
        }
        if(ui->addNet->isChecked()) {
            //extract needed data
            ulong dstIP = NetworkService::stringToLongIP(std::string(ui->destEdit_net->text().toUtf8().data()));
            fduration duration (ui->durationEdit_net->text().toUInt()*minute_k);
            ulong intraffic = ui->recvEdit_net->text().toULong();
            ulong outtraffic = ui->sendEdit_net->text().toULong();
            ftimepoint timeofservice(Time::from_time_t(ui->dateTimeEdit_network->dateTime().toTime_t()));
            NetworkService::ServiceDescriptor *nd =
                    new NetworkService::NetworkDescriptor(intraffic,outtraffic,dstIP,timeofservice,duration,srv);
            NetworkService::Application::getInstance().addService(abonentIP,nd);
        }
        emit UpdateLinkTableSignal();
        if (auto linktabledialog = dynamic_cast<LinkTableDialog *>(parentWidget())) {
            emit linktabledialog->UpdateAbonentListSignal();
        }
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Error",e.what(),QMessageBox::Ok);
    }
}

void AddServiceDialog::on_abonentEdit_textChanged(const QString &arg1)
{
    //try to convert text to IP
    try {
        NetworkService::stringToLongIP(std::string(arg1.toUtf8().data()));
    } catch (std::invalid_argument) {
        //if fails, disable OK button
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        return;
    }
    //if not fails, enable OK button
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void AddServiceDialog::on_sendrecvEdit_post_textChanged(const QString &arg1)
{
    //only if checked
    if(ui->addPost->isChecked()){
        //try to convert text to IP
        try {
            NetworkService::stringToLongIP(std::string(arg1.toUtf8().data()));
        } catch (std::invalid_argument) {
            //if fails, disable OK button
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            return;
        }
        //if not fails, enable OK button
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void AddServiceDialog::on_sendrecvEdit_files_textChanged(const QString &arg1)
{
    //only if checked
    if(ui->addFiles->isChecked()){
        //try to convert text to IP
        try {
            NetworkService::stringToLongIP(std::string(arg1.toUtf8().data()));
        } catch (std::invalid_argument) {
            //if fails, disable OK button
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            return;
        }
        //if not fails, enable OK button
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void AddServiceDialog::on_destEdit_net_textChanged(const QString &arg1)
{
    //only if checked
    if(ui->addNet->isChecked()){
        //try to convert text to IP
        try {
            NetworkService::stringToLongIP(std::string(arg1.toUtf8().data()));
        } catch (std::invalid_argument) {
            //if fails, disable OK button
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            return;
        }
        //if not fails, enable OK button
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void AddServiceDialog::on_addPost_toggled(bool checked)
{
    //initiate validity check
    if(checked)
        on_sendrecvEdit_post_textChanged(ui->sendrecvEdit_post->text());
}

void AddServiceDialog::on_addFiles_toggled(bool checked)
{
    //initiate validity check
    if(checked)
        on_sendrecvEdit_files_textChanged(ui->sendrecvEdit_files->text());
}

void AddServiceDialog::on_addNet_toggled(bool checked)
{
    //initiate validity check
    if(checked)
        on_destEdit_net_textChanged(ui->destEdit_net->text());
}
