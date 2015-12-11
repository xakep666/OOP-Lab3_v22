#include "networkservice.h"
/*!
 * \file
 * \brief Файл, содержащий реализацию класса Application
 */
using namespace NetworkService;


/*!
 * \brief Проверка, занят ли адрес
 * \param addr Проверяемый адрес
 * \return true, если занят, false, если свободен
 *
 * Метод ищет проверяемый адрес в таблице используемых адресов
 */
bool Application::isIPBusy(ulong addr) const {
    auto pos = std::find_if(usedIPs.cbegin(),usedIPs.cend(),[addr](ulong _addr){
        return _addr==addr;
    });
    if(pos == usedIPs.cend())
        return false;
    else
        return true;
}

/*!
 * \brief Добавление нового сервера в таблицу
 * \param addr IP адрес сервера
 * \param name Имя сервера
 * \param costpermin Стоимость 1 минуты связи
 * \param costpermb Стоимость 1MB переданных данных
 * \throws invalid_argument если IP адрес сервера неверный
 * \throws logic_error если IP адрес занят(используется)
 *
 * Метод добавляет новый сервер в таблицу, в случае успешного добавления сервера
 * IP адрес добавляется в таблицу используемых адресов
 */
void Application::addServer(ulong addr, std::string name, ulong costpermin, ulong costpermb) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Cannot use this IP "+std::to_string(addr));
    if(isIPBusy(addr))
        throw std::logic_error("IP "+std::to_string(addr)+" is already used");
    usedIPs.push_back(addr);
    Server newserv(addr);
    newserv.setName(name);
    newserv.setCostPerMB(costpermb);
    newserv.setCostPerMin(costpermin);
    servers.push_back(newserv);
}

/*!
 * \brief Удаление сервера из таблицы
 * \param addr IP адрес удаляемого сервера
 * \throws invalid_argument если IP неверный или сервер с таким адресом не был наиден
 *
 * Метод удаляет сервер из таблицы серверов, также IP адрес удаляется из таблицы использованных адресов
 */
void Application::delServer(ulong addr) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(addr));
    auto pos = std::find_if(servers.begin(),servers.end(),[addr](indexT &srv){
        return srv.getAddress()==addr;
    });
    if (pos==servers.end())
        throw std::invalid_argument("Server with IP "+std::to_string(addr)+" not found");
    else
        servers.erase(pos);
    usedIPs.erase(std::find_if(usedIPs.begin(),usedIPs.end(),[addr](ulong _addr){ return _addr==addr; }));
}

/*!
 * \brief Находит сервер в таблице по адресу
 * \param addr IP адрес предполагаемого сервера
 * \return ссылка на объект Server
 * \throws invalid_argument если IP адрес неверный или сервера с таким адресом не найдено
 */
Server & Application::getServer(ulong addr) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(addr));
    auto pos = std::find_if(servers.begin(),servers.end(),[addr](Server &srv){
        return srv.getAddress()==addr;
    });
    if (pos==servers.end())
        throw std::invalid_argument("Server with IP "+std::to_string(addr)+" not found");
    else
        return *pos;
}

/*!
 * \brief Изменение IP адреса сервера
 * \param srv Ссылка на объект Server
 * \param newaddr Новый адрес
 * \throw invalid_argument если адрес неверный или занят
 *
 * Метод меняет своиство address у объекта Server, проверяя новый адрес на занятость
 * по таблице занятых адресов и на правильность
 */
void Application::SetServerAddress(Server &srv, ulong newaddr) {
    if(!isValidIP(newaddr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(newaddr));
    if(isIPBusy(newaddr))
        throw std::invalid_argument("New IP "+std::to_string(newaddr)+" is already used");
    auto pos = std::find_if(usedIPs.begin(),usedIPs.end(),[&srv](ulong _addr){
            return srv.getAddress()==_addr;
    });
    *pos=newaddr;
    srv.address=newaddr;
}

/*!
 * \brief Добавление записи об оказанной услуге в "таблицу связи" сервера
 * \param serveraddr IP адрес сервера
 * \param abonentaddr IP адрес клиента
 * \param sdesc Указатель на описатель сервиса (полиморфный ServiceDescriptor)
 * \throw invalid_argument Если:
 * - Неверный IP сервера
 * - Неверный IP клиента
 * - В качестве указателя на ServiceDescriptor передан нулевой указатель
 *
 * Метод ищет сервер в таблице серверов и добавляет в его "таблицу связи" информацию об оказанной услуге.
 * Также метод добавляет IP адрес клиента в таблицу занятых адресов, если такого адреса там еще нет
 */
void Application::addService(ulong serveraddr, ulong abonentaddr, ServiceDescriptor *sdesc) {
    if(!isValidIP(serveraddr))
        throw std::invalid_argument("Invalid server IP given: "+std::to_string(serveraddr));
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    if(sdesc==nullptr)
        throw std::invalid_argument("Cannot use nullptr as service descriptor");
    if(!isIPBusy(abonentaddr))
        usedIPs.push_back(abonentaddr);
    getServer(serveraddr).addService(sdesc,abonentaddr);
}

/*!
 * \brief Оператор индексирования таблицы серверов
 * \param index Индекс
 * \return Ссылка на объект Server
 * \throw invalid_argument если index больше, чем размер таблицы
 *
 * Метод использует перегруженный оператор для [] для таблицы серверов.
 * Метод необходим для работы итератора
 */
Server & Application::operator [](uint index) {
    if(index>=servers.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then table size ("+std::to_string(servers.size()));
    return servers[index];
}

/*!
 * \brief Оператор индексирования таблицы серверов
 * \param index Индекс
 * \return Константная ссылка на объект Server
 * \throw invalid_argument если index больше, чем размер таблицы
 *
 * Метод использует перегруженный оператор для [] для таблицы серверов.
 * Метод необходим для работы константного итератора
 */
const Server &Application::operator [](uint index) const
{
    if(index>=servers.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then table size ("+std::to_string(servers.size()));
    return servers[index];
}

/*!
 * \brief Итератор, указывающий на первый элемент таблицы
 * \return объект Iterator
 */
Application::Iterator Application::begin() {
    return Application::Iterator(this,0);
}

/*!
 * \brief Константный итератор, указывающий на первый элемент таблицы
 * \return объект ConstIterator
 */
Application::ConstIterator Application::cbegin() const{
    return Application::ConstIterator(this,0);
}


/*!
 * \brief Итератор, указывающий на конец таблицы (индекс, равный размеру)
 * \return объект Iterator
 */
Application::Iterator Application::end(){
    return Application::Iterator(this,servers.size());
}

/*!
 * \brief Константный итератор, указывающий на конец таблицы (индекс, равный размеру)
 * \return объект ConstIterator
 */
Application::ConstIterator Application::cend() const{
    return Application::ConstIterator(this,0);
}

/*!
 * \brief Cбор информации о количестве переданных данных и длительности связи для абонента
 * \param abonentaddr IP адрес абонента
 * \return vector из string - текстовое представление собранной информации
 * \throw invalid_argument если адрес абонента неверен или не найден
 *
 * Метод проходит по всем серверам и их таблицам связи, используя итераторы, собирая информацию во "временную"
 * коллекцию следующего вида
 * \snippet application.cpp countervec
 * Первый элемент пары - суммарный траффик для сервиса (передано+получено),
 * Второй - Общая длительность связи для сервиса (не для всех сервисов)
 * Вектор result резервируется для 3-х сервисов
 */
MyVector<std::string> Application::abonentInfo(ulong abonentaddr) const{
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given:"+std::to_string(abonentaddr));
    if(!isIPBusy(abonentaddr))
        throw std::invalid_argument("Abonent with IP "+std::to_string(abonentaddr)+" not found");
    MyVector<std::string> result;
    //! [countervec]
    MyVector<std::pair<ulong,ulong>> counter;
    counter.reserve(ServicesNum);
    //! [countervec]
    std::for_each(cbegin(),cend(),[&](const indexT &srv){
        std::for_each(srv.cbegin(),srv.cend(),[&](const LinkTable::indexT &p){
            if(p.second==abonentaddr) {
                if(typeid(*p.first)==typeid(PostDescriptor)) {
                    counter[0].first+=dynamic_cast<PostDescriptor *>(p.first)->getTraffic();
                }
                if(typeid(*p.first)==typeid(FileDescriptor)) {
                    auto fptr = dynamic_cast<FileDescriptor *>(p.first);
                    counter[1].first+=fptr->getTraffic();
                    counter[1].second+=fptr->getLinkDuration().count();
                }
                if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                    auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                    counter[2].first+=nptr->getInTraffic()+nptr->getOutTraffic();
                    counter[2].second+=nptr->getLinkDuration().count();
                }
            }
        });
    });

    result.push_back("User IP: "+LongIPtoString(abonentaddr));
    result.push_back("Post: Total traffic: "+std::to_string(counter[0].first)+" MB");
    result.push_back("Files: Total traffic: "+std::to_string(counter[1].first)+" MB , "+
                     "Total time: "+std::to_string(counter[1].second)+" Min");
    result.push_back("Network: Total traffic: "+std::to_string(counter[2].first)+" MB , "+
                     "Total time: "+std::to_string(counter[2].second)+" Min");
    return result;
}

/*!
 * \brief Считает итоговую стоимость оказанных услуг абонента
 * \param abonentaddr IP адрес абонента
 * \return Итоговая стоимость
 *
 * Метод проходит по всем серверам и их "таблицам связи" (используются итераторы), вызывая для каждой записи виртуальную
 * функцию calculatePrice() и прибавляя ее результат к итоговому
 */
ulong Application::abonentTotalPrice(ulong abonentaddr) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given:"+std::to_string(abonentaddr));
    if(!isIPBusy(abonentaddr))
        throw std::invalid_argument("Abonent with IP "+std::to_string(abonentaddr)+" not found");
    ulong result=0;
    std::for_each(cbegin(),cend(),[&](const indexT &s){
        std::for_each(s.cbegin(),s.cend(),[&](const indexT::indexT &p){
            if(p.second == abonentaddr)
                result+= p.first->calculatePrice();
        });
    });
    return result;
}

/*!
 * \brief Считает количество переданных данных и количество полученных данных
 * \return пара значений: первое - количество переданных данных, второе - количество полученных
 *
 * Метод проходит по всем серверам и их "таблицам связи" (используются итераторы), считывает количество данных
 * и направление их передачи, добавляя к результату
 */
std::pair<ulong,ulong> Application::countIOTraffic() const {
    std::pair<ulong,ulong> result(0,0);
    std::for_each(cbegin(),cend(),[&](const indexT &s){
        std::for_each(s.cbegin(),s.cend(),[&](const indexT::indexT &p){
            if(typeid(*p.first)==typeid(PostDescriptor) ||
               typeid(*p.first)==typeid(FileDescriptor)) {
                auto pptr = dynamic_cast<PostDescriptor *>(p.first);
                switch (pptr->getDirection()) {
                    case SEND:
                        result.second+=pptr->getTraffic();
                    case RECV:
                        result.first+=pptr->getTraffic();
                }
            }
            if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                result.first+=nptr->getInTraffic();
                result.second+=nptr->getOutTraffic();
            }
        });
    });
    return result;
}

/*!
 * \brief Сохраняет записи в JSON формате в текстовый файл
 * \param path Путь к файлу назначения
 * \throws logic_error в случае ошибки открытия файла на запись
 *
 * Метод проходит по всем серверам и их "таблицам связи" (используются итераторы), сохраняя информацию в
 * JSON формате в текстовый файл
 */
void Application::saveToFile(std::string &path) {
    std::ofstream destfile (path);
    if(!destfile.is_open())
        throw std::logic_error("Cannot open file \""+path+"\" for writing");
    using namespace rapidjson;
    Document doc;
    doc.SetArray();
    std::for_each(begin(),end(),[&](const indexT &s){
        using namespace rapidjson;
        Value server;
        server.SetObject();
        server.AddMember("address",StringRef(LongIPtoString(s.getAddress()).c_str()),doc.GetAllocator());
        server.AddMember("name",StringRef(s.getName().c_str()),doc.GetAllocator());
        server.AddMember("mbcost",s.getCostPerMB(),doc.GetAllocator());
        server.AddMember("mincost",s.getCostPerMin(),doc.GetAllocator());
        Value services;
        services.SetArray();
        std::for_each(s.cbegin(),s.cend(),[&](const indexT::indexT &p) {
            Value service;
            service.SetObject();
            service.AddMember("type",StringRef(p.first->getType().c_str()),doc.GetAllocator());
            if(typeid(*p.first)==typeid(PostDescriptor)) {
                auto pptr = dynamic_cast<PostDescriptor *>(p.first);
                service.AddMember("traffic",pptr->getTraffic(),doc.GetAllocator());
                switch (pptr->getDirection()) {
                case SEND:
                    service.AddMember("direction","send",doc.GetAllocator());
                case RECV:
                    service.AddMember("direciton","recv",doc.GetAllocator());
                }
            }
            if(typeid(*p.first)==typeid(FileDescriptor)) {
                auto fptr = dynamic_cast<FileDescriptor *>(p.first);
                service.AddMember("traffic",fptr->getTraffic(),doc.GetAllocator());
                service.AddMember("duration",fptr->getLinkDuration().count(),doc.GetAllocator());
                switch (fptr->getDirection()) {
                case SEND:
                    service.AddMember("direction","send",doc.GetAllocator());
                case RECV:
                    service.AddMember("direciton","recv",doc.GetAllocator());
                }
            }
            if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                service.AddMember("intraffic",nptr->getInTraffic(),doc.GetAllocator());
                service.AddMember("outtraffic",nptr->getOutTraffic(),doc.GetAllocator());
                service.AddMember("duration",nptr->getLinkDuration().count(),doc.GetAllocator());
            }
            service.AddMember("source",StringRef(LongIPtoString(p.second).c_str()),doc.GetAllocator());
            service.AddMember("destination",StringRef(LongIPtoString(p.first->getDestinationAddress()).c_str()),doc.GetAllocator());
            service.AddMember("linktime",Time::to_time_t(p.first->getLinkTime()),doc.GetAllocator());
            services.PushBack(service,doc.GetAllocator());
        });
        server.AddMember("linktable",services,doc.GetAllocator());
        doc.PushBack(server,doc.GetAllocator());
    });
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    doc.Accept(writer);
    destfile << strbuf.GetString();
    destfile.close();
}

/*!
 * \brief Считывает информацию о серверах и оказанных услугах из текстового файла, содержащего JSON представление
 * \param path Путь к исходному файлу
 * \throws invalid_argument если не удалось открыть файл на чтение
 * \throws logic_error в случае ошибки разбора
 *
 * Метод разбирает JSON представление, взятое из файла, восстанавливая информацию о серверах и оказанных услугах
 */
void Application::readFromFile(std::string &path) {
    std::ifstream srcfile(path);
    if (!srcfile.is_open())
        throw std::invalid_argument("Cannot open file \""+path+"\"for reading");
    std::string docstr;
    srcfile.seekg(0,std::ios::end);
    docstr.reserve(srcfile.tellg());
    srcfile.seekg(0,std::ios::beg);
    docstr.assign((std::istreambuf_iterator<char>(srcfile)),
                  std::istreambuf_iterator<char>());
    using namespace rapidjson;
    Document doc;
    doc.Parse(docstr.c_str());
    if(!doc.IsArray())
        throw std::logic_error("Source file is not JSON array");
    std::for_each(doc.Begin(),doc.End(),[&](Value &server){
        if(!server.IsObject())
            throw std::logic_error("JSON Array contains corrupted server object");
        if(!server["address"].IsString() || isValidIP(stringToLongIP(server["address"].GetString())))
            throw std::logic_error("Server object contains invalid IP");
        ulong srvip = stringToLongIP(server["address"].GetString());
        if(!server["name"].IsString())
            throw std::logic_error("Server name must be string");
        if(!server["mbcost"].IsUint())
            throw std::logic_error("Cost per MB must be unsigned number");
        if(!server["mincost"].IsUint())
            throw std::logic_error("Cost per minute must be unsigned number");
        if(!server["linktable"].IsArray())
            throw std::logic_error("Linktable array is corrupted");
        addServer(srvip,server["name"].GetString(),server["mbcost"].GetUint(),server["mincost"].GetUint());
        Server * cur_server = &servers.back();
        std::for_each(server["linktable"].Begin(),server["linktable"].End(),[&](Value &service){
            if(!service.IsObject())
                throw std::logic_error("Service record is not object");
            if(!service["type"].IsString())
                throw std::logic_error("Service type must be string");
            std::string servicetype = service["type"].GetString();
            if(servicetype!="Post" || servicetype!="Network" || servicetype!="File")
                throw std::logic_error("Service type must be \"Post\", \"File\" or \"Network\"");
            if(!service["source"].IsUint() || !isValidIP(stringToLongIP(service["source"].GetString())))
                throw std::logic_error("Source address is invalid");
            ulong srcip = stringToLongIP(service["source"].GetString());
            if(!service["destination"].IsUint() || !isValidIP(stringToLongIP(service["destination"].GetString())))
                throw std::logic_error("Destination address is invalid");
            ulong dstip = stringToLongIP(service["destination"].GetString());
            if(!service["linktime"].IsUint())
                throw std::logic_error("Linktime must be unsigned number");
            auto linktime = Time::from_time_t(service["linktime"].GetUint());
            if(servicetype=="Post") {
                if(!service["traffic"].IsUint())
                    throw std::logic_error("Traffic must be unsigned number");
                ulong traffic = service["traffic"].GetUint();
                if(!service["direction"].IsString())
                    throw std::logic_error("Direction must be string");
                std::string directionstr = service["direction"].GetString();
                if(directionstr=="send") {
                    ServiceDescriptor *postdesc = new PostDescriptor(traffic,SEND,dstip,linktime,cur_server);
                    addService(srvip,srcip,postdesc);
                } else if (directionstr=="recv") {
                    ServiceDescriptor *postdesc = new PostDescriptor(traffic,RECV,dstip,linktime,cur_server);
                    addService(srvip,srcip,postdesc);
                } else {
                    throw std::logic_error("Direction must be \"send\" or \"recv\"");
                }
            }
            if(servicetype=="File") {
                if(!service["traffic"].IsUint())
                    throw std::logic_error("Traffic must be unsigned number");
                ulong traffic = service["traffic"].GetUint();
                if(!service["direction"].IsString())
                    throw std::logic_error("Direction must be string");
                std::string directionstr = service["direction"].GetString();
                if(!service["duration"].IsUint())
                    throw std::logic_error("Duration must be unsigned number");
                fduration duration(service["duration"].GetUint());
                if(directionstr=="send") {
                    ServiceDescriptor *postdesc = new FileDescriptor(traffic,SEND,dstip,linktime,duration,cur_server);
                    addService(srvip,srcip,postdesc);
                } else if (directionstr=="recv") {
                    ServiceDescriptor *postdesc = new FileDescriptor(traffic,RECV,dstip,linktime,duration,cur_server);
                    addService(srvip,srcip,postdesc);
                } else {
                    throw std::logic_error("Direction must be \"send\" or \"recv\"");
                }
            }
            if(servicetype=="Network") {
                if(!service["intraffic"].IsUint())
                    throw std::logic_error("Input Traffic must be unsigned number");
                ulong intraffic = service["intraffic"].GetUint();
                if(!service["outtraffic"].IsUint())
                    throw std::logic_error("Output Traffic must be unsigned number");
                ulong outtraffic = service["outtraffic"].GetUint();
                if(!service["duration"].IsUint())
                    throw std::logic_error("Duration must be unsigned number");
                fduration duration(service["duration"].GetUint());
                addService(srvip,srcip,new NetworkDescriptor(intraffic,outtraffic,dstip,linktime,duration,cur_server));
            }
        });
    });
    srcfile.close();
}

Application::Application() {
}

Application::~Application() {
}
