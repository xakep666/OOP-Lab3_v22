#ifndef MENUS
#define MENUS
#define MENU_SIZE(_x) sizeof(_x)/sizeof(_x[0])
typedef void (*menufunc)(NetworkService::Application &);
const menufunc mainmenufuncs [] = {
    Exit,
    AddServer,
    ShowServers,
    SaveToFile,
};
const std::string mainmenutext [] = {
    "Выход",
    "Добавить сервер",
    "Показать сервера",
    "Сохранить в файл"
};
void PrintMenu(const std::string text[],size_t size) {
    for(size_t i=0;i<size;i++) {
        cout << i << ": " <<text[i]<<endl;
    }
}

int getMenuPt(size_t size) {
    uint num;
    do{
        cout << "Введите номер пункта меню: ";
        cin >> num;
        cin.clear();
        cin.ignore();
    }while(!cin.good() || (uint)num>=size);
    return num;
}
#endif // MENUS

