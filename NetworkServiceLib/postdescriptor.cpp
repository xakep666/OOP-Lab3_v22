#include "networkservice.h"
/*!
 * \file
 * \brief Файл, содержащий реализацию класса PostDescriptor
 */
using namespace NetworkService;

/*!
 * \brief Создает запись об оказанной услуге, основываясь на параметрах
 * \param traffic Количество переданных данных в MB
 * \param direction Направление передачи
 * \param address Адрес назначения
 * \param linktime Времи оказания услуги
 * \param server Указатель на сервер (объект Server), оказывающий услугу
 */
PostDescriptor::PostDescriptor(ulong traffic,
                               Direction direction,
                               ulong address,
                               ftimepoint &linktime,
                               Server *server) {
    this->traffic = traffic;
    this->direction = direction;
    setDestinationAddress(address);
    setLinkTime(linktime);
    setServer(server);
}

/*!
 * \brief Получить направление передачи данных
 * \return Направление передачи данных
 */
Direction PostDescriptor::getDirection() const{
    return direction;
}

/*!
 * \brief Получить количество переданных данных
 * \return Количество переданных данных в MB
 */
ulong PostDescriptor::getTraffic() const {
    return traffic;
}

/*!
 * \brief Получение названия типа услуги
 * \return Название типа услуги (строка "Post")
 */
std::string PostDescriptor::getType() const {
    return std::string("Post");
}

/*!
 * \brief Рассчет стоимости оказанных услуг
 * \return Стоимость оказанных услуг
 *
 * Рассчет стоимости оказанных услуг, на основании стоимости 1MB, установленной сервером
 */
ulong PostDescriptor::calculatePrice() const {
    return traffic*getServer()->getCostPerMB();
}

/*!
 * \brief Изменения направления передачи данных
 * \param d Направление передачи
 */
void PostDescriptor::setDirection(Direction d) {
    direction = d;
}

/*!
 * \brief Изменения количество переданной информации
 * \param t Количество переданной информации (в MB)
 */
void PostDescriptor::setTraffic(ulong t) {
    traffic = t;
}

PostDescriptor::PostDescriptor() {
}

PostDescriptor::~PostDescriptor() {
}
