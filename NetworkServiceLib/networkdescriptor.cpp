#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief NetworkDescriptor::NetworkDescriptor initialises record with information about given service
 * \param intraffic
 * \param outtraffic
 * \param address
 * \param linktime
 * \param linkduration
 * \param server
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
 * \brief NetworkDescriptor::getInTraffic gets input traffic in MB
 * \return input traffic in MB
 */
ulong NetworkDescriptor::getInTraffic() const {
    return intraffic;
}

/*!
 * \brief NetworkDescriptor::getOutTraffic gets output traffic in MB
 * \return output traffic in MB
 */
ulong NetworkDescriptor::getOutTraffic() const {
    return outtraffic;
}

std::string NetworkDescriptor::getType() const {
    return std::string("Network");
}

ulong NetworkDescriptor::calculatePrice() const {
    return getServer()->getCostPerMB()*(intraffic+outtraffic)+getServer()->getCostPerMin()*linkduration.count();
}

/*!
 * \brief NetworkDescriptor::getLinkDuration gets link duration
 * \return reference to fduration object
 */
const fduration & NetworkDescriptor::getLinkDuration() const {
    return linkduration;
}
