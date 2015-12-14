#include "abonentlist.h"
#include "networkservice.h"
AbonentList::AbonentList(QWidget *parent) : QComboBox(parent)
{

}

void AbonentList::Update()
{
    clear();
    std::for_each(NetworkService::Application::getInstance().getUsedIPs().cbegin(),NetworkService::Application::getInstance().getUsedIPs().cend(),[&](const std::pair<ulong,bool> &p){
        if(!p.second) addItem(NetworkService::LongIPtoString(p.first).c_str(),QVariant((qulonglong)p.first));
    });
}

