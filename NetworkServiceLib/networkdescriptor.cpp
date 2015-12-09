#include "networkservice.h"
/*!
 * \file
 * \brief Файл, содержащий реализацию класса NetworkDescriptor
 */
using namespace NetworkService;

/*!
 * \brief Создает запись об оказанной услуге, основываясь на параметрах
 * \param intraffic Количество полученной информации (в MB)
 * \param outtraffic Количество переданной информации (в MB)
 * \param address IP адрес назначения
 * \param linktime Время оказания услуги
 * \param linkduration Продолжительность связи
 * \param server Указатель на сервер (объект Server), оказывающий услугу
 */
NetworkDescriptor::NetworkDescriptor(ulong intraffic,
                                     ulong outtraffic,
                                     ulong address,
                                     ftimepoint &linktime,
                                     fduration &linkduration,
                                     Server *server) {
    this->intraffic=intraffic;
    this->outtraffic=outtraffic;
    setDestinationAddress(address);
    setLinkTime(linktime);
    this->linkduration=linkduration;
    setServer(server);
}

/*!
 * \brief Получение количества полученных данных
 * \return Количество полученных данных (в MB)
 */
ulong NetworkDescriptor::getInTraffic() const {
    return intraffic;
}

/*!
 * \brief Получение количества отправленных данных
 * \return Количество отправленных данных MB
 */
ulong NetworkDescriptor::getOutTraffic() const {
    return outtraffic;
}
/*!
 * \brief Получение названия типа услуги
 * \return Название типа услуги (строка "Network")
 */
std::string NetworkDescriptor::getType() const {
    return std::string("Network");
}

/*!
 * \brief Рассчет стоимости оказанных услуг
 * \return Стоимость оказанных услуг
 *
 * Рассчет стоимости оказанных услуг, на основании стоимости 1 минуты и 1MB, установленной сервером
 */
ulong NetworkDescriptor::calculatePrice() const {
    return getServer()->getCostPerMB()*(intraffic+outtraffic)+getServer()->getCostPerMin()*linkduration.count()*minute_k;
}

/*!
 * \brief Получение продолжительности связи
 * \return Ссылка на объект fduration
 */
const fduration & NetworkDescriptor::getLinkDuration() const {
    return linkduration;
}

NetworkDescriptor::NetworkDescriptor() {
}

NetworkDescriptor::~NetworkDescriptor() {
}

/*!
 * \brief Установка количества полученных данных
 * \param intraffic Количество полученных данных
 */
void NetworkDescriptor::setInTraffic(ulong intraffic) {
    this->intraffic=intraffic;
}

/*!
 * \brief Установка количества отправленных данных
 * \param outtraffic Количество отправленных данных
 */
void NetworkDescriptor::setOutTraffic(ulong outtraffic) {
    this->outtraffic=outtraffic;
}

/*!
 * \brief Установка продолжительности связи
 * \param ld Ссылка на объект fduration, содержащий информацию о продолжительности связи
 */
void NetworkDescriptor::setLinkDuration(fduration &ld) {
    linkduration=ld;
}
