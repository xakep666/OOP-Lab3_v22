#include "networkservice.h"
/*!
 * \file
 * Файл, содержащий реализацию класса ServiceDescriptor
 */
using namespace NetworkService;

/*!
 * \brief Пустой конструктор
 */
ServiceDescriptor::ServiceDescriptor() {
    addr = 0;
    linktime = Time::now();
    server = nullptr;
}

/*!
 * \brief Получение адреса назначения
 * \return Адрес назначения
 */
ulong ServiceDescriptor::getDestinationAddress() const{
    return addr;
}

/*!
 * \brief Получение ассоциированного сервера
 * \return Указатель на ассоциированный сервер
 */
const Server * ServiceDescriptor::getServer() const {
    return server;
}

/*!
 * \brief Установка адреса назначения
 * \param addr Новый адрес назначения
 * \throw invalid_argument Если IP адрес не верный
 */
void ServiceDescriptor::setDestinationAddress(ulong addr) {
    if(!isValidIP(addr))
        throw std::logic_error("Cannot use "+std::to_string(addr)+ "as destination IP");
    this->addr = addr;
}

/*!
 * \brief Установка времени связи
 * \param time Время связи
 */
void ServiceDescriptor::setLinkTime(ftimepoint &time) {
    linktime = time;
}

/*!
 * \brief Установка ассоциированного сервера
 * \param srv Указатель на сервер
 * \throws invalid_argument Если передан nullptr
 */
void ServiceDescriptor::setServer(Server *srv) {
    if(srv==nullptr)
        throw std::invalid_argument("Cannot set associated server to nullptr");
    server=srv;
}

/*!
 * \brief Получение времени оказания услуги
 * \return Ссылка на объект ftimepoint
 */
const ftimepoint & ServiceDescriptor::getLinkTime() const {
    return linktime;
}
