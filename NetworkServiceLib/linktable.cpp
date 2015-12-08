#include "networkservice.h"
/*!
 * \file
 * Файл, содержащий реализацию класса LinkTable
 */
using namespace NetworkService;

/*!
 * \brief Добавление записи об оказанной услуге в таблицу
 * \param sdesc Указатель на описатель сервиса (полиморфный ServiceDescriptor)
 * \param abonentaddr Адрес абонента, воспользовавшегося услугой
 * \throws invalid_argument если адрес абонента неверен или в качестве указателя передан nullptr
 */
void LinkTable::addService(ServiceDescriptor *sdesc, ulong abonentaddr) {
    if (sdesc==nullptr)
        throw std::invalid_argument("Service descriptor cannot be nullptr");
    if (!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP "+std::to_string(abonentaddr));
    linktable.push_back(std::make_pair(sdesc,abonentaddr));
}

/*!
 * \brief Получение информации об оказанных услугах для абонента
 * \param abonentaddr IP абонента
 * \return vector из указателей на описатели сервисов (полиморфный ServiceDescriptor)
 * \throws invalid_argument если IP абонента неверен
 * Метод обходит всю "таблицу связи" (используется итератор), добавляя нужные описатель к результату
 */
std::vector<ServiceDescriptor *> LinkTable::getServices(ulong abonentaddr) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    std::vector<ServiceDescriptor *> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT item){
        if (item.second==abonentaddr)
            result.push_back(item.first);
    });
    return result;
}

/*!
 * \brief Получение информации об оказанных услугах для абонента
 * \param abonentaddr IP абонента
 * \param linktime Время оказателей услуги
 * \return vector из указателей на описатели сервисов (полиморфный ServiceDescriptor)
 * \throws invalid_argument если IP абонента неверен
 * Метод обходит всю "таблицу связи" (используется итератор), добавляя нужные описатель к результату
 */
std::vector<ServiceDescriptor *> LinkTable::getServices(ulong abonentaddr, ftimepoint &linktime) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    std::vector<ServiceDescriptor *> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT item){
        if (item.second==abonentaddr && item.first->getLinkTime()==linktime)
            result.push_back(item.first);
    });
    return result;
}
/*!
 * \brief Удаление записи из таблицы
 * \param index Индекс записи
 * \throws invalid_argument если индекс больше, чем размер таблицы
 */
void LinkTable::delService(uint index) {
    if(index>=linktable.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then size of table ("+std::to_string(linktable.size())+")");
    linktable.erase(linktable.begin()+index);
}

/*!
 * \brief Создать текстовое представление таблицы
 * \return vector из string с описанием
 * Метод обходит всю "таблицу связи" (используется итератор), создавая для каждого элемента
 * описывающюю его строку и добавляя её к результату
 */
std::vector<std::string> LinkTable::showTable() const {
    std::vector<std::string> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT pair){
        std::string tmp("Type:"+pair.first->getType()+"\t"+
                        "Destination address:"+std::to_string(pair.first->getDestinationAddress())+"\t"+
                        "Price:"+std::to_string(pair.first->calculatePrice())+"\t");
        if(typeid(*pair.first)==typeid(PostDescriptor)) {
            auto tmpdesc = dynamic_cast<PostDescriptor *>(pair.first);
            switch (tmpdesc->getDirection()) {
                case SEND:
                    tmp += "Send\t";
                case RECV:
                    tmp += "Recive\t";
            }
            tmp+=std::to_string(tmpdesc->getTraffic())+"MB\t";
        }
        if(typeid(*pair.first)==typeid(FileDescriptor)) {
            auto tmpdesc = dynamic_cast<FileDescriptor *>(pair.first);
            switch (tmpdesc->getDirection()) {
                case SEND:
                    tmp += "Send\t";
                case RECV:
                    tmp += "Recive\t";
            }
            tmp+=std::to_string(tmpdesc->getTraffic())+"MB\t";
            tmp+=std::to_string(tmpdesc->getLinkDuration().count())+"Min\t";
        }
        if(typeid(*pair.first)==typeid(NetworkDescriptor)) {
            auto tmpdesc = dynamic_cast<NetworkDescriptor *>(pair.first);
            tmp += "Send: "+std::to_string(tmpdesc->getOutTraffic())+"MB\t";
            tmp += "Recived: "+std::to_string(tmpdesc->getInTraffic())+"MB\t";
        }
        result.push_back(tmp);
    });
    return result;
}

/*!
 * \brief Оператор индексирования
 * \param index Индекс
 * \return Ссылка на пару из указателя на описатель сервиса (полиморфный ServiceDescriptor) и адреса абонента
 * \throws invalid_argument if index is greater then table size
 */
NetworkService::LinkTable::indexT &LinkTable::operator [](uint index) {
    if(index>=linktable.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then size of table ("+std::to_string(linktable.size())+")");
    return linktable[index];
}

/*!
 * \brief Итератор для первого элемента
 * \return Объект Iterator
 */
LinkTable::Iterator LinkTable::begin(){
    return LinkTable::Iterator(this,0);
}

/*!
 * \brief Константный итератор для первого элемента
 * \return Объект ConstIterator
 */
LinkTable::ConstIterator LinkTable::begin() const{
    return LinkTable::ConstIterator(this,0);
}

/*!
 * \brief Итератор, указывающий на конец таблицы (индекс, равный размеру)
 * \return объект Iterator
 */
LinkTable::Iterator LinkTable::end() const{
    return LinkTable::Iterator(this,linktable.size());
}

/*!
 * \brief Константный итератор, указывающий на конец таблицы (индекс, равный размеру)
 * \return объект ConstIterator
 */
LinkTable::ConstIterator LinkTable::end() const{
    return LinkTable::ConstIterator(this,linktable.size());
}

/*!
 * \brief Деструктор
 * Применяет к указателям на ServiceDescriptor оператор delete;
 */
LinkTable::~LinkTable() {
    std::for_each(linktable.begin(),linktable.end(),[](LinkTable::indexT pair) {
        delete pair.first;
    });
}
