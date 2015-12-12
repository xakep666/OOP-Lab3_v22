#ifndef DEPENDENTMENUS
#define DEPENDENTMENUS
typedef void (*menufunc)(void);
const menufunc mainmenufuncs [] = {
    Exit,
    AddServer,
    ShowServers,
    SaveToFile,
    LoadFromFile,
    ServerInfo,
    SetServerAddr,
    AddService,
    AbonentInfo,
    AbonentTotalPrice,
    IOTraffic,
};
const std::string mainmenutext [] = {
    "Выход",
    "Добавить сервер",
    "Показать сервера",
    "Сохранить в файл",
    "Загрузить из файла",
    "Информация о сервере",
    "Изменить адрес сервера",
    "Добавить запись об оказанной услуге",
    "Информация об абоненте",
    "Итоговая стоимость услуг абонента",
    "Входящий/исходящий траффик",
};
#endif // DEPENDENTMENUS

