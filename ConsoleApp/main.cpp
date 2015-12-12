#include <iostream>
#include <networkservice.h>
#include <string>
#include <algorithm>
#include "menus.h"
#include "menufuncs.h"
using namespace std;

template <typename T> T getCin() {
    T num;
    do{
        cin >> num;
        cin.clear();
        cin.sync();
    }while(!cin.good());
    cin.sync();
    return num;
}

void AddServer() {
    cout << "Введите IP сервера: ";
    string ip = getCin<string>();
    cout << "Введите имя сервера: ";
    string name = getCin<string>();
    cout << "Введите стоимость минуты: ";
    ulong cpmin = getCin<ulong>();
    cout << "Введите стоимость MB: ";
    ulong cpmb = getCin<ulong>();
    NetworkService::Application::getInstance().addServer(NetworkService::stringToLongIP(ip),name,cpmin,cpmb);
}

void ShowServers() {
    for_each(NetworkService::Application::getInstance().begin(),NetworkService::Application::getInstance().end(),[](NetworkService::Server &srv){
        cout <<"---------------------------------------------\n";
        cout << "IP: "<<NetworkService::LongIPtoString(srv.getAddress())<<endl<<
                "Имя: "<<srv.getName()<<endl<<
                "Стоимость минуты: "<<srv.getCostPerMin()<<endl<<
                "Стоимость MB: "<<srv.getCostPerMB()<<endl;
    });
}

void SaveToFile() {
    cout << "Введите имя файла: ";
    std::string path = getCin<std::string>();
    NetworkService::Application::getInstance().saveToFile(path);
}

void LoadFromFile() {
    cout << "Введите имя файла: ";
    std::string path = getCin<std::string>();
    NetworkService::Application::getInstance().readFromFile(path);
}

void ServerInfo() {
    cout << "Введите IP сервера: ";
    std::string ipstr = getCin<std::string>();
    auto srv = NetworkService::Application::getInstance().getServer(NetworkService::stringToLongIP(ipstr));
    cout <<"---------------------------------------------\n";
    cout << "IP: "<<NetworkService::LongIPtoString(srv.getAddress())<<endl<<
            "Имя: "<<srv.getName()<<endl<<
            "Стоимость минуты: "<<srv.getCostPerMin()<<endl<<
            "Стоимость MB: "<<srv.getCostPerMB()<<endl;
    cout << "Таблица связи:\n";
    auto table = srv.showTable();
    std::for_each(table.begin(),table.end(),[](std::string &info){
        cout<<info<<endl;
    });
}

void SetServerAddr() {
    cout << "Введите старый IP сервера: ";
    std::string oldipstr = getCin<std::string>();
    cout << "Введите новый IP сервера: ";
    std::string newipstr = getCin<std::string>();
    NetworkService::Application::getInstance().SetServerAddress(NetworkService::Application::getInstance().getServer(NetworkService::stringToLongIP(oldipstr)),NetworkService::stringToLongIP(newipstr));
}

void AddService() {
    cout << "Введите IP сервера: ";
    std::string srvipstr = getCin<std::string>();
    ulong srvip = NetworkService::stringToLongIP(srvipstr);
    cout << "Выберете сервис\n";
    PrintMenu(servicetext,MENU_SIZE(servicetext));
    int pt = getMenuPt(MENU_SIZE(servicetext));
    cout << "Введите адрес назначения: ";
    std::string dstipstr = getCin<std::string>();
    ulong dstip = NetworkService::stringToLongIP(dstipstr);
    cout << "Введите адрес источника: ";
    std::string srcipstr = getCin<std::string>();
    ulong srcip = NetworkService::stringToLongIP(srcipstr);
    NetworkService::ServiceDescriptor *sdesc = nullptr;
    switch (pt) {
    case 0:
    {
        cout << "Выберете направление\n";
        PrintMenu(directiontext,MENU_SIZE(directiontext));
        NetworkService::Direction direction = (NetworkService::Direction)getMenuPt(MENU_SIZE(directiontext));
        cout << "Введите количество MB: ";
        ulong traffic = getCin<ulong>();
        NetworkService::Server *sptr = & NetworkService::Application::getInstance().getServer(srvip);
        auto now = Time::now();
        sdesc = new NetworkService::PostDescriptor(traffic,direction,dstip,now,sptr);
        break;
    }
    case 1:
    {
        cout << "Выберете направление\n";
        PrintMenu(directiontext,MENU_SIZE(directiontext));
        NetworkService::Direction direction = (NetworkService::Direction)getMenuPt(MENU_SIZE(directiontext));
        cout << "Введите количество MB: ";
        ulong traffic = getCin<ulong>();
        cout << "Введите длительность связи в минутах: ";
        ulong linkduration = getCin<ulong>();
        fduration duration (linkduration*minute_k);
        NetworkService::Server *sptr = & NetworkService::Application::getInstance().getServer(srvip);
        auto now = Time::now();
        sdesc = new NetworkService::FileDescriptor(traffic,direction,dstip,now,duration,sptr);
        break;
    }
    case 2: {
        cout << "Введите количество отправленных MB: ";
        ulong outtraffic = getCin<ulong>();
        cout << "Введите количество полученных MB: ";
        ulong intraffic = getCin<ulong>();
        cout << "Введите длительность связи в минутах: ";
        ulong linkduration = getCin<ulong>();
        fduration duration (linkduration*minute_k);
        auto now = Time::now();
        NetworkService::Server *sptr = & NetworkService::Application::getInstance().getServer(srvip);
        sdesc = new NetworkService::NetworkDescriptor(intraffic,outtraffic,dstip,now,duration,sptr);
        break;
    }
    default:
        cout << "Ошибка выбора\n";
        return;
    }
    NetworkService::Application::getInstance().addService(srcip,sdesc);
}

void AbonentInfo() {
    cout << "Введите IP абонента: ";
    std::string ipstr = getCin<std::string>();
    ulong ip = NetworkService::stringToLongIP(ipstr);
    auto info = NetworkService::Application::getInstance().abonentInfo(ip);
    cout << "Информация-----------------------------\n";
    std::for_each(info.begin(),info.end(),[](std::string &info){
        cout<<info<<endl;
    });
    cout << "---------------------------------------\n";
}

void AbonentTotalPrice() {
    cout << "Введите IP абонента: ";
    std::string ipstr = getCin<std::string>();
    ulong ip = NetworkService::stringToLongIP(ipstr);
    cout << "Итоговая цена услуг абонента: "<<NetworkService::Application::getInstance().abonentTotalPrice(ip)<<endl;
}

void IOTraffic() {
    auto iotraffic = NetworkService::Application::getInstance().countIOTraffic();
    cout << "Входящий траффик: "<<std::to_string(iotraffic.first)<<" MB\n";
    cout << "Исходящиф траффик: "<<std::to_string(iotraffic.second)<<" MB\n";
}

void Exit(){
    exit(0);
}
#include "dependentmenus.h"
int main()
{
    for(;;) {
        try {
            PrintMenu(mainmenutext,MENU_SIZE(mainmenufuncs));
            int pt = getMenuPt(MENU_SIZE(mainmenufuncs));
            mainmenufuncs[pt]();
        } catch (std::exception &exc) {
            cout << "Исключение: "<<exc.what()<<endl;
        }
    }
    return 0;
}

