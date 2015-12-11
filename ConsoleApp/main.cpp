#include <iostream>
#include <networkservice.h>
#include <string>
#include <algorithm>

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

void AddServer(NetworkService::Application &app) {
    cout << "Введите IP сервера: ";
    string ip = getCin<string>();
    cout << "Введите имя сервера: ";
    string name = getCin<string>();
    cout << "Введите стоимость минуты: ";
    ulong cpmin = getCin<ulong>();
    cout << "Введите стоимость MB: ";
    ulong cpmb = getCin<ulong>();
    app.addServer(NetworkService::stringToLongIP(ip),name,cpmin,cpmb);
}

void ShowServers(NetworkService::Application &app) {
    for_each(app.begin(),app.end(),[](NetworkService::Server &srv){
        cout <<"---------------------------------------------\n";
        cout << "IP: "<<NetworkService::LongIPtoString(srv.getAddress())<<endl<<
                "Имя: "<<srv.getName()<<endl<<
                "Стоимость минуты: "<<srv.getCostPerMin()<<endl<<
                "Стоимость MB: "<<srv.getCostPerMB()<<endl;
    });
}

void SaveToFile(NetworkService::Application &app) {
    cout << "Введите имя файла: ";
    std::string path = getCin<std::string>();
    app.saveToFile(path);
}

void Exit(NetworkService::Application &){
    exit(0);
}

#include "menus.h"
int main()
{
    NetworkService::Application app;
    for(;;) {
        try {
            PrintMenu(mainmenutext,MENU_SIZE(mainmenufuncs));
            int pt = getMenuPt(MENU_SIZE(mainmenufuncs));
            mainmenufuncs[pt](app);
        } catch (std::exception &exc) {
            cout << "Исключение: "<<exc.what()<<endl;
        }
    }
    return 0;
}

