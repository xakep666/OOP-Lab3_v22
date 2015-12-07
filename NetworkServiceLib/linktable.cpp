#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief LinkTable::addService adds record about service to link table
 * \param sdesc Descriptor of service
 * \param abonentaddr Address of abonent
 * \throws invalid_argument if abonentaddr is invalid or sdesc is nullptr
 */
void LinkTable::addService(ServiceDescriptor *sdesc, ulong abonentaddr) {
    if (sdesc==nullptr)
        throw std::invalid_argument("Service descriptor cannot be nullptr");
    if (!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP "+std::to_string(abonentaddr));
    linktable.push_back(std::make_pair(sdesc,abonentaddr));
}

/*!
 * \brief LinkTable::getServices gets given services for given abonent
 * \param abonentaddr IP of abonent
 * \return vector of service descriptors
 * \throws invalid_argument if given abonent address is invalid
 */
std::vector<ServiceDescriptor *> LinkTable::getServices(ulong abonentaddr) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    std::vector<ServiceDescriptor *> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT item){
        if (item.second==abonentaddr)
            result.push_back(item.first);
    });
    return result;
}

/*!
 * \brief LinkTable::getServices gets given servies for given abonent and time
 * \param abonentaddr IP of abonent
 * \param linktime time of given service
 * \return vector of service descriptors
 * \throws invalid_argument if given abonent address is invalid
 */
std::vector<ServiceDescriptor *> LinkTable::getServices(ulong abonentaddr, ftimepoint &linktime) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    std::vector<ServiceDescriptor *> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT item){
        if (item.second==abonentaddr && item.first->getLinkTime()==linktime)
            result.push_back(item.first);
    });
    return result;
}
/*!
 * \brief LinkTable::delService removes record from table
 * \param index index of record
 * \throws invalid_argument if index greater then size of table
 */
void LinkTable::delService(uint index) {
    if(index>=linktable.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then size of table ("+std::to_string(linktable.size())+")");
    linktable.erase(linktable.begin()+index);
}

/*!
 * \brief LinkTable::showTable creates string representation of link table
 * \return vector of string
 */
std::vector<std::string> LinkTable::showTable() const {
    std::vector<std::string> result;
    std::for_each(linktable.begin(),linktable.end(),[&](LinkTable::indexT pair){
        std::string tmp("Type:"+pair.first->getType()+"\t"+
                        "Destination address:"+std::to_string(pair.first->getDestinationAddress())+"\t"+
                        "Price:"+std::to_string(pair.first->calculatePrice())+"\t");
        if(typeid(*pair.first)==typeid(PostDescriptor)) {
            auto tmpdesc = dynamic_cast<PostDescriptor *>(pair.first);
            switch (tmpdesc->getDirection()) {
                case SEND:
                    tmp += "Send\t";
                case RECV:
                    tmp += "Recive\t";
            }
            tmp+=std::to_string(tmpdesc->getTraffic())+"MB\t";
        }
        if(typeid(*pair.first)==typeid(FileDescriptor)) {
            auto tmpdesc = dynamic_cast<FileDescriptor *>(pair.first);
            switch (tmpdesc->getDirection()) {
                case SEND:
                    tmp += "Send\t";
                case RECV:
                    tmp += "Recive\t";
            }
            tmp+=std::to_string(tmpdesc->getTraffic())+"MB\t";
            tmp+=std::to_string(tmpdesc->getLinkDuration().count())+"Min\t";
        }
        if(typeid(*pair.first)==typeid(NetworkDescriptor)) {
            auto tmpdesc = dynamic_cast<NetworkDescriptor *>(pair.first);
            tmp += "Send: "+std::to_string(tmpdesc->getOutTraffic())+"MB\t";
            tmp += "Recived: "+std::to_string(tmpdesc->getInTraffic())+"MB\t";
        }
        result.push_back(tmp);
    });
    return result;
}

/*!
 * \brief LinkTable::operator [] returns constant reference to record
 * \param index
 * \return reference to pair of descriptor and abonent address
 * \throws invalid_argument if index is greater then table size
 */
NetworkService::LinkTable::indexT &LinkTable::operator [](uint index) {
    if(index>=linktable.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then size of table ("+std::to_string(linktable.size())+")");
    return linktable[index];
}

/*!
 * \brief LinkTable::begin returns iterator for first item
 * \return iterator
 */
LinkTable::Iterator LinkTable::begin(){
    return LinkTable::Iterator(this,0);
}

LinkTable::ConstIterator LinkTable::begin() const{
    return LinkTable::ConstIterator(this,0);
}


/*!
 * \brief LinkTable::end returns iterator for end of table
 * \return iterator
 */
LinkTable::ConstIterator LinkTable::end() const{
    return LinkTable::ConstIterator(this,linktable.size());
}

LinkTable::~LinkTable() {
    std::for_each(linktable.begin(),linktable.end(),[](LinkTable::indexT pair) {
        delete pair.first;
    });
}
