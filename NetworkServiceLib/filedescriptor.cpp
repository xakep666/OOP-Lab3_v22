#include "networkservice.h"
/*!
 * \file
 * \brief Файл, содержащий реализацию класса FileDescriptor
 */
using namespace NetworkService;

/*!
 * \brief Создает запись об оказанной услуге, основываясь на параметрах
 * \param traffic Количество переданной информации в MB
 * \param direction Направление передачи
 * \param address Адрес назначения
 * \param linktime Время связи
 * \param linkduration Продолжительность связи
 * \param server Указатель на сервер (объект Server), оказывающий услугу
 */
FileDescriptor::FileDescriptor(ulong traffic,
                               Direction direction,
                               ulong address,
                               ftimepoint &linktime,
                               fduration &linkduration,
                               Server *server) {
    setTraffic(traffic);
    setDirection(direction);
    setDestinationAddress(address);
    setLinkTime(linktime);
    this->linkduration=linkduration;
    setServer(server);
}

/*!
 * \brief Получение продолжительности связи
 * \return Ссылка на объект fduration
 */
const fduration & FileDescriptor::getLinkDuration() const {
    return linkduration;
}

/*!
 * \brief Получение названия типа услуги
 * \return Название типа услуги (строка "File")
 */
std::string FileDescriptor::getType() const {
    return std::string("File");
}

/*!
 * \brief Рассчет стоимости оказанных услуг
 * \return Стоимость оказанных услуг
 * Рассчет стоимости оказанных услуг, на основании стоимости 1 минуты и 1MB, установленной сервером
 */
ulong FileDescriptor::calculatePrice() const {
    return getTraffic()*getServer()->getCostPerMB() + linkduration.count()*minute_k*getServer()->getCostPerMin();
}
