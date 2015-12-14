#include "editservicedialog.h"
#include "networkservice.h"
#include "ui_addservicedialog.h"
EditServiceDialog::EditServiceDialog(QWidget *parent,ulong serveraddr,uint index):
    AddServiceDialog(parent,serveraddr),
    index(index)
{
    setWindowTitle("Изменение записи об услуге");
    //initialize fields
    _rewrite();
}

void EditServiceDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //reset button
    if (ui->buttonBox->standardButton(button)==QDialogButtonBox::Reset) {
        //first we clear all
        AddServiceDialog::on_buttonBox_clicked(button);
        //second we reinitialize needed fields,switches
        _rewrite();
    }
}

void EditServiceDialog::_rewrite()
{
    NetworkService::Server::indexT ltrecord = NetworkService::Application::getInstance().getServer(serveraddr)[0];
    if(auto postdesc = dynamic_cast<NetworkService::PostDescriptor *>(ltrecord.first)) {
        ui->addPost->setChecked(true);
        if(postdesc->getDirection()==NetworkService::RECV) {
            ui->recvToggle_post->setChecked(true);
            on_recvToggle_post_clicked();
        }
        if(postdesc->getDirection()==NetworkService::SEND) {
            ui->sendToggle_post->setChecked(true);
            on_sendToggle_post_clicked();
        }
        ui->sendrecvEdit_post->setText(NetworkService::LongIPtoString(postdesc->getDestinationAddress()).c_str());
        ui->sendrecvDataEdit_post->setText(QString::number(postdesc->getTraffic()));
        ui->dateTimeEdit_post->setDateTime(QDateTime::fromTime_t(Time::to_time_t(postdesc->getLinkTime())));
    }
    if(auto filedesc = dynamic_cast<NetworkService::FileDescriptor *>(ltrecord.first)) {
        ui->addFiles->setChecked(true);
        if(filedesc->getDirection()==NetworkService::RECV) {
            ui->recvToggle_files->setChecked(true);
            on_recvToggle_files_clicked();
        }
        if(filedesc->getDirection()==NetworkService::SEND) {
            ui->sendToggle_files->setChecked(true);
            on_sendToggle_post_clicked();
        }
        ui->sendrecvEdit_post->setText(NetworkService::LongIPtoString(filedesc->getDestinationAddress()).c_str());
        ui->sendrecvDataEdit_post->setText(QString::number(filedesc->getTraffic()));
        ui->dateTimeEdit_post->setDateTime(QDateTime::fromTime_t(Time::to_time_t(filedesc->getLinkTime())));
        ui->durationEdit_files->setText(QString::number(filedesc->getLinkDuration().count()/minute_k));
    }
    if(auto netdesc = dynamic_cast<NetworkService::NetworkDescriptor *>(ltrecord.first)) {
        ui->addNet->setChecked(true);
        ui->destEdit_net->setText(NetworkService::LongIPtoString(netdesc->getDestinationAddress()).c_str());
        ui->sendEdit_net->setText(QString::number(netdesc->getOutTraffic()));
        ui->recvEdit_net->setText(QString::number(netdesc->getInTraffic()));
        ui->dateTimeEdit_network->setDateTime(QDateTime::fromTime_t(Time::to_time_t(netdesc->getLinkTime())));
    }
    ui->abonentEdit->setText(NetworkService::LongIPtoString(ltrecord.second).c_str());
}

