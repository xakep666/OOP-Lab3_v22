#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief PostDescriptor::PostDescriptor initialises record with information about given service
 * \param traffic
 * \param direction
 * \param address
 * \param linktime
 * \param server
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
 * \brief PostDescriptor::getDirection
 * \return direction of data transfer
 */
Direction PostDescriptor::getDirection() const{
    return direction;
}

/*!
 * \brief PostDescriptor::getTraffic
 * \return traffic in MB
 */
ulong PostDescriptor::getTraffic() const {
    return traffic;
}

std::string PostDescriptor::getType() const {
    return std::string("Post");
}

ulong PostDescriptor::calculatePrice() const {
    return traffic*getServer()->getCostPerMB();
}

/*!
 * \brief PostDescriptor::setDirection changes direction to given
 * \param d
 */
void PostDescriptor::setDirection(Direction d) {
    direction = d;
}

/*!
 * \brief PostDescriptor::setTraffic changes traffic to given
 * \param t
 */
void PostDescriptor::setTraffic(ulong t) {
    traffic = t;
}
