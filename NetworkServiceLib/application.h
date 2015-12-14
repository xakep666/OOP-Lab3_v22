#ifndef APPLICATION
#define APPLICATION
/*!
 * \file
 * \brief Файл, содержащий объявление класса Application
 */
namespace NetworkService {
/*!
 * \brief Класс, реализующий работу приложения
 * \note Класс является одиночкой, обращение осуществлять через метод getInstance()
 *
 * Отвечает за взаимодействия прикладной программы с библиотекой 
 */
class Application {
public:
    typedef Server indexT; ///<Определение типа для работы итератора
private:
    MyVector<indexT> servers; ///<Таблица серверов
    MyVector<std::pair<ulong,bool>> usedIPs; ///<Таблица использованных адресов. Второй элемент пары - метка о том, занят ли адрес сервером
    bool isIPBusy(ulong addr) const;
    Application() {}
    Application(const Application &);
    Application &operator=(const Application&);
    ~Application() {}
public:
    static Application &getInstance() { ///<Статический метод, возвращающий объект
        static Application instance;
        return instance;
    }
    const uint ServicesNum = 3; ///<Количество возможных вариантов сервиса (почта,файлы,сеть)
    void addServer(ulong addr,std::string name,ulong costpermin,ulong costpermb);
    void delServer(ulong addr);
    void delServerIndex(uint index);
    Server & getServer(ulong addr);
    void SetServerAddress(Server &srv, ulong newaddr);
    void addService(ulong abonentaddr,ServiceDescriptor *sdesc);
    MyVector<std::string> abonentInfo(ulong abonentaddr) const;
    ulong abonentTotalPrice(ulong abonentaddr) const;
    std::pair<ulong,ulong> countIOTraffic() const;
    const MyVector<std::pair<ulong, bool> > &getUsedIPs() const;
    void saveToFile(std::string &path);
    void readFromFile(std::string &path);
    typedef MyIterator<Application> Iterator; ///<Специализация шаблонного типа MyIterator
    typedef MyConstIterator<Application> ConstIterator; ///<Специализация шаблонного типа MyConstIterator
    friend class MyIterator<Application>;
    friend class MyConstIterator<Application>;
    Iterator begin();
    ConstIterator cbegin() const;
    Iterator end();
    ConstIterator cend() const;
    Server & back();
    const Server & back() const;
    Server & operator [](uint index);
    const Server & operator [](uint index) const;
};
}
#endif // APPLICATION

