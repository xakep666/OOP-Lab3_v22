#include "servertable.h"
#include "networkservice.h"
#include <QMessageBox>
ServerTable::ServerTable(QWidget *parent) : QTableWidget(parent)
{
    //disable editing by default
    setEditTriggers(QTableWidget::NoEditTriggers);
    //highlight all row
    setSelectionBehavior(QAbstractItemView::SelectRows);
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

void ServerTable::AddLastItem() {
    int Yindex = rowCount();
    insertRow(Yindex);
    auto srv = NetworkService::Application::getInstance().back();
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

}

void ServerTable::UpdateItem(uint index, ulong newip, QString &newname, uint newcostpermin, uint newcostpermb)
{
    try {
        if(NetworkService::Application::getInstance()[index].getAddress()!=newip)
        NetworkService::Application::getInstance().SetServerAddress(
                    NetworkService::Application::getInstance()[index],newip);
        std::string _newname(newname.toUtf8().data());
        NetworkService::Application::getInstance()[index].setName(_newname);
        NetworkService::Application::getInstance()[index].setCostPerMB(newcostpermb);
        NetworkService::Application::getInstance()[index].setCostPerMin(newcostpermin);
    } catch (std::exception &e) {
        QMessageBox::critical(this,"Ошибка",e.what(),QMessageBox::Ok);
        return;
    }
    //update information in table
    item(index,0)->setText(NetworkService::LongIPtoString(newip).c_str());
    item(index,1)->setText(newname);
    item(index,2)->setText(QString::number(newcostpermin));
    item(index,3)->setText(QString::number(newcostpermb));
}
