#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief empty constructor
 */
ServiceDescriptor::ServiceDescriptor() {
    addr = 0;
    linktime = Time::now();
    server = nullptr;
}

/*!
 * \brief ServiceDescriptor::getDestinationAddress
 * \return destination address
 */
ulong ServiceDescriptor::getDestinationAddress() const{
    return addr;
}

/*!
 * \brief ServiceDescriptor::getServer
 * \return pointer to associated server
 */
const Server * ServiceDescriptor::getServer() const {
    return server;
}

/*!
 * \brief ServiceDescriptor::setDestinationAddress
 * \param addr
 * \throw invalid_argument if given invalid representation
 */
void ServiceDescriptor::setDestinationAddress(ulong addr) {
    if(!isValidIP(addr))
        throw std::logic_error("Cannot use "+std::to_string(addr)+ "as destination IP");
    this->addr = addr;
}

/*!
 * \brief ServiceDescriptor::setLinkTime changes link time to given
 * \param time
 */
void ServiceDescriptor::setLinkTime(ftimepoint &time) {
    linktime = time;
}

/*!
 * \brief ServiceDescriptor::setServer changes associated server to given
 * \param srv
 * \throws invalid_argument if nullptr given
 */
void ServiceDescriptor::setServer(Server *srv) {
    if(srv==nullptr)
        throw std::invalid_argument("Cannot set associated server to nullptr");
    server=srv;
}

/*!
 * \brief ServiceDescriptor::getLinkTime gets time when service was given
 * \return reference to ftimepoint object
 */
const ftimepoint & ServiceDescriptor::getLinkTime() const {
    return linktime;
}
