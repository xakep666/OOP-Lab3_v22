#include "networkservice.h"
using namespace NetworkService;

Server::Server(ulong address) {
    this->address = address;
}

/*!
 * \brief Server::getAddress gets server IP
 * \return IP in unsigned long representation
 */
ulong Server::getAddress() const{
    return address;
}

/*!
 * \brief Server::getName gets server name
 * \return reference to string, contains server name
 */
const std::string & Server::getName() const {
    return name;
}

/*!
 * \brief Server::setName changes server name to given
 * \param name new name
 */
void Server::setName(std::__cxx11::string &name) {
    this->name=name;
}

/*!
 * \brief Server::getCostPerMB returns cost of data transmission (per 1MB)
 * \return cost per 1MB
 */
ulong Server::getCostPerMB() const {
    return costpermb;
}

/*!
 * \brief Server::setCostPerMB changes cost per 1MB of transmitted data
 * \param cost new cost
 */
void Server::setCostPerMB(ulong cost) {
    costpermb=cost;
}

/*!
 * \brief Server::getCostPerMin returns cost of 1 minute of link
 * \return cost per 1 minute
 */
ulong Server::getCostPerMin() const {
    return costpermin;
}

/*!
 * \brief Server::setCostPerMin changes cost of 1 minute of link to given
 * \param cost new cost
 */
void Server::setCostPerMin(ulong cost) {
    costpermin=cost;
}
