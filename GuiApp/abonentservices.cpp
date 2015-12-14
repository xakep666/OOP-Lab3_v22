#include "abonentservices.h"
#include "ui_abonentservices.h"
#include "networkservice.h"
#include "QMessageBox"
AbonentServices::AbonentServices(QWidget *parent, ulong abonentIP) :
    QDialog(parent),
    ui(new Ui::AbonentServices),
    abonentIP(abonentIP)
{
    ui->setupUi(this);
    setWindowTitle(tr("Услуги, полученные абонентом ")+
                   tr(NetworkService::LongIPtoString(abonentIP).c_str()));
    try {
        std::for_each(NetworkService::Application::getInstance().cbegin(),
                      NetworkService::Application::getInstance().cend(),
                      [this,abonentIP](const NetworkService::Server &srv){
            std::string tmp;
            tmp+="------------------------------------------------------------------------------\n";
            auto services = srv.getServices(abonentIP);
            std::for_each(services.cbegin(),
                          services.cend(),
                          [&tmp](NetworkService::ServiceDescriptor *sd){
                time_t linktime = Time::to_time_t(sd->getLinkTime());
                tmp+=sd->getType()+'\n'+
                                "Time: "+std::string(std::ctime(&linktime))+
                                "Destination address:"+NetworkService::LongIPtoString(sd->getDestinationAddress())+"\n"+
                                "Price:"+std::to_string(sd->calculatePrice())+"\n";
                if(typeid(*sd)==typeid(NetworkService::PostDescriptor)) {
                    auto tmpdesc = dynamic_cast<const NetworkService::PostDescriptor *>(sd);
                    switch (tmpdesc->getDirection()) {
                    case NetworkService::SEND:
                    {
                        tmp += "Send: ";
                        break;
                    }
                    case NetworkService::RECV:
                    {
                        tmp += "Recive: ";
                        break;
                    }
                    }
                    tmp+=std::to_string(tmpdesc->getTraffic())+"MB\n";
                }
                if(typeid(*sd)==typeid(NetworkService::FileDescriptor)) {
                    auto tmpdesc = dynamic_cast<const NetworkService::FileDescriptor *>(sd);
                    switch (tmpdesc->getDirection()) {
                    case NetworkService::SEND:
                    {
                        tmp += "Send: ";
                        break;
                    }
                    case NetworkService::RECV:
                    {
                        tmp += "Recive: ";
                        break;
                    }
                    }
                    tmp+=std::to_string(tmpdesc->getTraffic())+"MB\n";
                    tmp+="Duration: "+std::to_string(tmpdesc->getLinkDuration().count()/minute_k)+"Min\n";
                }
                if(typeid(*sd)==typeid(NetworkService::NetworkDescriptor)) {
                    auto tmpdesc = dynamic_cast<const NetworkService::NetworkDescriptor *>(sd);
                    tmp += "Send: "+std::to_string(tmpdesc->getOutTraffic())+"MB\n";
                    tmp += "Recived: "+std::to_string(tmpdesc->getInTraffic())+"MB\n";
                    tmp+="Duration: "+std::to_string(tmpdesc->getLinkDuration().count()/minute_k)+"Min\n";
                }
                tmp+="------------------------------------------------------------------------------\n";
            });
            ui->servicesTable->addItem(new QListWidgetItem(tmp.c_str()));
        });
    }catch(std::exception &e) {
        close();
        QMessageBox::critical(this,"Ошибка",e.what(),QMessageBox::Ok);
    }
}

AbonentServices::~AbonentServices()
{
    delete ui;
}

void AbonentServices::on_closeButton_clicked()
{
    close();
}
