#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief LongIPtoString converts ulong IP representation to string
 * \param ip
 * \return human readable ip as string
 * \throws logic_error if convertation fails
 */
std::string LongIPtoString(ulong &ip) {
    char ipstr [INET_ADDRSTRLEN];
    struct in_addr inaddr;
    inaddr.s_addr = ip;
    auto checkptr = inet_ntop(AF_INET,&inaddr,ipstr,INET_ADDRSTRLEN);
    if (!checkptr)
        throw std::logic_error("Cannot convert "+std::to_string(ip)+" to string IP");
    return std::string(ipstr);
}

/*!
 * \brief stringToLongIP converts string to long int IP representation
 * \param src
 * \return long int IP representation
 * \throws logic_error if conversion fails
 */
ulong stringToLongIP(std::string &src) {
    struct in_addr tmp;
    int code = inet_pton(AF_INET,src.c_str(),&tmp);
    if (code<=0)
        throw std::invalid_argument("Cannot convert "+src+" to IP address");
    ulong ip = tmp.s_addr;
    if (isValidIP(ip))
        throw std::invalid_argument("Invalid ip address ("+src+") given");
    return ip;
}

/*!
 * \brief checks if input IP is valid
 * \param ip
 * \return true if valid, false otherwise
 * IP is valid if it doesn`t starts or ends at 0
 * and does not starts or ends at 255
 */
bool isValidIP(ulong &ip) {
    const ulong IPSize = 32;
    if ( (ip&0xFF)==0 || (ip&0xFF)==0xFF)
        return false;
    if (((ip>>(IPSize-2))&0xFF)==0 || ((ip>>(IPSize-2))&0xFF)==0xFF)
        return false;
    return true;
}
