#include "servertable.h"
#include "networkservice.h"

ServerTable::ServerTable(QWidget *parent) : QTableWidget(parent)
{
    //disable editing by default
    setEditTriggers(QTableWidget::NoEditTriggers);

}

void ServerTable::UpdateTable() {
    int Yindex=0;
    //clear table
    setRowCount(0);
    std::for_each(NetworkService::Application::getInstance().cbegin(),
                  NetworkService::Application::getInstance().cend(),
                  [this,&Yindex](const NetworkService::Server &srv){
                insertRow(Yindex);

                auto IP = new QTableWidgetItem();
                IP->setData(Qt::EditRole,QVariant(NetworkService::LongIPtoString(srv.getAddress()).c_str()));
                setItem(Yindex,0,IP);

                auto Name = new QTableWidgetItem();
                Name->setData(Qt::EditRole,QVariant(srv.getName().c_str()));
                setItem(Yindex,1,Name);

                auto CostPerMin = new QTableWidgetItem();
                CostPerMin->setData(Qt::EditRole,QVariant((uint)srv.getCostPerMin()));
                setItem(Yindex,2,CostPerMin);

                auto CostPerMB = new QTableWidgetItem();
                CostPerMB->setData(Qt::EditRole,QVariant((uint)srv.getCostPerMB()));
                setItem(Yindex,3,CostPerMB);

                Yindex++;
    });
    sortByColumn(0);
}
