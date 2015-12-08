#include "networkservice.h"
/*!
 * \file
 * \brief Файл, содержащий реализацию класса Server
 */
using namespace NetworkService;

/*!
 * \brief Создание описателя сервиса
 * \param address IP адрес сервера
 * \warning Проверка на правильность и свободность адреса не выполняется
 */
Server::Server(ulong address) {
    this->address = address;
}

/*!
 * \brief Получение IP сервера
 * \return IP сервера в ulong-представлении
 */
ulong Server::getAddress() const{
    return address;
}

/*!
 * \brief Получение имени сервера
 * \return Строка, содержащая имя серера
 */
const std::string & Server::getName() const {
    return name;
}

/*!
 * \brief Установка имени сервера
 * \param name Строка, содержащая новое имя
 */
void Server::setName(std::__cxx11::string &name) {
    this->name=name;
}

/*!
 * \brief Получение стоимости передачи 1MB данных
 * \return Стоимость передачи 1MB
 */
ulong Server::getCostPerMB() const {
    return costpermb;
}

/*!
 * \brief Установка стоимости передачи 1MB данных
 * \param cost Новая стоимость
 */
void Server::setCostPerMB(ulong cost) {
    costpermb=cost;
}

/*!
 * \brief Получение стоимости 1 минуты связи
 * \return Стоимость 1 минуты
 */
ulong Server::getCostPerMin() const {
    return costpermin;
}

/*!
 * \brief Установка стоимости 1 минуты связи
 * \param cost Новая стоимость
 */
void Server::setCostPerMin(ulong cost) {
    costpermin=cost;
}
