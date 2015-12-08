#ifndef APPLICATION
#define APPLICATION
/*!
 * \file
 * \brief Файл, содержащий объявление класса Application
 */
namespace NetworkService {
/*!
 * \brief Класс, реализующий работу приложения
 *
 * Отвечает за взаимодействия прикладной программы с библиотекой
 */
class Application {
public:
    typedef Server indexT; ///<Определение типа для работы итератора
private:
    std::vector<indexT> servers; ///<Таблица серверов
    std::vector<ulong> usedIPs; ///<Таблица использованных адресов
    bool isIPBusy(ulong addr) const;
public:
    const uint ServicesNum = 3; ///<Количество возможных вариантов сервиса (почта,файлы,сеть)
    Application();
    void addServer(ulong addr,std::string name,ulong costpermin,ulong costpermb);
    void delServer(ulong addr);
    Server & getServer(ulong addr);
    void SetServerAddress(Server &srv, ulong newaddr);
    void addService(ulong serveraddr,ulong abonentaddr,ServiceDescriptor *sdesc);
    std::vector<std::string> abonentInfo(ulong abonentaddr) const;
    ulong abonentTotalPrice(ulong abonentaddr) const;
    std::pair<ulong,ulong> countIOTraffic() const;
    void saveToFile(std::string &path);
    void readFromFile(std::string &path);
    typedef MyIterator<Application> Iterator; ///<Специализация шаблонного типа MyIterator
    typedef MyConstIterator<Application> ConstIterator; ///<Специализация шаблонного типа MyConstIterator
    friend class MyIterator<Application>;
    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;
    Server & operator [](uint index);
    virtual ~Application();
};
}
#endif // APPLICATION

