#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief FileDescriptor::FileDescriptor initialises record with given information about service
 * \param traffic
 * \param direction
 * \param address
 * \param linktime
 * \param linkduration
 * \param server
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
 * \brief FileDescriptor::getLinkDuration get duration of file transfer
 * \return reference to duration
 */
const fduration & FileDescriptor::getLinkDuration() const {
    return linkduration;
}

std::string FileDescriptor::getType() const {
    return std::string("File");
}

ulong FileDescriptor::calculatePrice() const {
    return getTraffic()*getServer()->getCostPerMB() + linkduration.count()*minute_k*getServer()->getCostPerMin();
}
