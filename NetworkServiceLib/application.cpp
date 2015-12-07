#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief Application::isIPBusy checks if this IP is used by server or client
 * \param addr IP to check
 * \return true if IP is used, false otherwise
 */
bool Application::isIPBusy(ulong addr) const {
    auto pos = std::find_if(usedIPs.begin(),usedIPs.end(),[addr](ulong _addr){
        return _addr==addr;
    });
    if(pos == usedIPs.end())
        return false;
    else
        return true;
}

/*!
 * \brief Application::addServer adds new server to table
 * \param addr server IP
 * \param name server name
 * \param costpermin cost of 1 minute of link
 * \param costpermb cost of 1MB of transmitted data
 * \throws invalid_argument if IP is invalid
 * \throws logic_error if IP is busy
 */
void Application::addServer(ulong addr, std::__cxx11::string &name, ulong costpermin, ulong costpermb) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Cannot use this IP "+std::to_string(addr));
    if(isIPBusy(addr))
        throw std::logic_error("IP "+std::to_string(addr)+" is already used");
    usedIPs.push_back(addr);
    Server newserv(addr);
    newserv.setName(name);
    newserv.setCostPerMB(costpermb);
    newserv.setCostPerMin(costpermin);
    servers.push_back(newserv);
}

/*!
 * \brief Application::delServer removes server with given address from table
 * \param addr IP of removable server
 * \throws invalid_argument if IP is invalid or not used
 */
void Application::delServer(ulong addr) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(addr));
    auto pos = std::find_if(servers.begin(),servers.end(),[addr](indexT &srv){
        return srv.getAddress()==addr;
    });
    if (pos==servers.end())
        throw std::invalid_argument("Server with IP "+std::to_string(addr)+" not found");
    else
        servers.erase(pos);
    usedIPs.erase(std::find_if(usedIPs.begin(),usedIPs.end(),[addr](ulong _addr){ return _addr==addr; }));
}

/*!
 * \brief Application::getServer finds server with given IP
 * \param addr IP address of needed server
 * \return reference to Server object
 * \throws invalid_argument if IP is invalid or not used
 */
Server & Application::getServer(ulong addr) {
    if(!isValidIP(addr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(addr));
    auto pos = std::find_if(servers.begin(),servers.end(),[addr](Server &srv){
        return srv.getAddress()==addr;
    });
    if (pos==servers.end())
        throw std::invalid_argument("Server with IP "+std::to_string(addr)+" not found");
    else
        return *pos;
}

/*!
 * \brief Application::SetServerAddress changes server IP to given
 * \param srv reference to Server object
 * \param newaddr address to set
 * \throw invalid_argument if IP is invalid or busy
 */
void Application::SetServerAddress(Server &srv, ulong newaddr) {
    if(!isValidIP(newaddr))
        throw std::invalid_argument("Invalid IP given "+std::to_string(newaddr));
    if(isIPBusy(newaddr))
        throw std::invalid_argument("New IP "+std::to_string(newaddr)+" is already used");
    auto pos = std::find_if(usedIPs.begin(),usedIPs.end(),[&srv](ulong _addr){
            return srv.getAddress()==_addr;
    });
    *pos=newaddr;
    srv.address=newaddr;
}

/*!
 * \brief Application::addService adds information about given service to server link table
 * \param serveraddr IP of server
 * \param abonentaddr IP of client
 * \param sdesc Descriptor of given service
 * Method also adds IP of client to table of used IPs if it was not found in table;
 */
void Application::addService(ulong serveraddr, ulong abonentaddr, ServiceDescriptor *sdesc) {
    if(!isValidIP(serveraddr))
        throw std::invalid_argument("Invalid server IP given: "+std::to_string(serveraddr));
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given "+std::to_string(abonentaddr));
    if(sdesc==nullptr)
        throw std::invalid_argument("Cannot use nullptr as service descriptor");
    if(!isIPBusy(abonentaddr))
        usedIPs.push_back(abonentaddr);
    getServer(serveraddr).addService(sdesc,abonentaddr);
}

/*!
 * \brief Application::operator [] Servers indexing operator
 * \param index
 * \return reference to Server object
 * \throw invalid_argument if index greater then size of table of servers
 */
Server & Application::operator [](uint index) {
    if(index>=servers.size())
        throw std::invalid_argument("Index ("+std::to_string(index)+
                                    ") is greater then table size ("+std::to_string(servers.size()));
    return servers[index];
}

/*!
 * \brief Application::begin Iterator to first item of servers table
 * \return Iterator object
 */
Application::Iterator Application::begin() {
    return Application::Iterator(this,0);
}

Application::ConstIterator Application::begin() const{
    return Application::ConstIterator(this,0);
}


/*!
 * \brief Application::end Iterator to end of servers table
 * \return Iterator object
 */
Application::Iterator Application::end(){
    return Application::Iterator(this,servers.size());
}

Application::ConstIterator Application::end() const{
    return Application::ConstIterator(this,0);
}

/*!
 * \brief Application::abonentInfo gather information about abonent`s total traffic and links duration
 * \param abonentaddr IP of abonent
 * \return vector of string with description
 * Method iterates over all servers, calculates summary traffic (both send and recieve) and total links
 * duration and moves results to temporary vector like this
 * \snippet application.cpp countervec
 * where first item in pair - total traffic for service,
 * second - total links duration for service (optional)
 */
std::vector<std::string> Application::abonentInfo(ulong abonentaddr) const{
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given:"+std::to_string(abonentaddr));
    if(!isIPBusy(abonentaddr))
        throw std::invalid_argument("Abonent with IP "+std::to_string(abonentaddr)+" not found");
    std::vector<std::string> result;
    //! [countervec]
    std::vector<std::pair<ulong,ulong>> counter;
    counter.reserve(ServicesNum);
    //! [countervec]
    std::for_each(begin(),end(),[&](const indexT &srv){
        std::for_each(srv.begin(),srv.end(),[&](const LinkTable::indexT &p){
            if(p.second==abonentaddr) {
                if(typeid(*p.first)==typeid(PostDescriptor)) {
                    counter[0].first+=dynamic_cast<PostDescriptor *>(p.first)->getTraffic();
                }
                if(typeid(*p.first)==typeid(FileDescriptor)) {
                    auto fptr = dynamic_cast<FileDescriptor *>(p.first);
                    counter[1].first+=fptr->getTraffic();
                    counter[1].second+=fptr->getLinkDuration().count();
                }
                if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                    auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                    counter[2].first+=nptr->getInTraffic()+nptr->getOutTraffic();
                    counter[2].second+=nptr->getLinkDuration().count();
                }
            }
        });
    });

    //WHERE CONVERSION OPERATORS?!!!!
    struct in_addr iaddr;
    iaddr.s_addr=abonentaddr;
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&iaddr,ipstr,INET_ADDRSTRLEN);

    result.push_back("User IP: "+std::string(ipstr));
    result.push_back("Post: Total traffic: "+std::to_string(counter[0].first)+" MB");
    result.push_back("Files: Total traffic: "+std::to_string(counter[1].first)+" MB , "+
                     "Total time: "+std::to_string(counter[1].second)+" Min");
    result.push_back("Network: Total traffic: "+std::to_string(counter[2].first)+" MB , "+
                     "Total time: "+std::to_string(counter[2].second)+" Min");
    return result;
}

/*!
 * \brief Application::abonentTotalPrice calculates total price for abonent with given IP
 * \param abonentaddr IP of abonent
 * \return total price
 * Method iterates over all servers and over all service records, calls virtual calculatePrice() method
 * and adds it to result
 */
ulong Application::abonentTotalPrice(ulong abonentaddr) const {
    if(!isValidIP(abonentaddr))
        throw std::invalid_argument("Invalid abonent IP given:"+std::to_string(abonentaddr));
    if(!isIPBusy(abonentaddr))
        throw std::invalid_argument("Abonent with IP "+std::to_string(abonentaddr)+" not found");
    ulong result=0;
    std::for_each(begin(),end(),[&](const indexT &s){
        std::for_each(s.begin(),s.end(),[&](const indexT::indexT &p){
            if(p.second == abonentaddr)
                result+= p.first->calculatePrice();
        });
    });
    return result;
}

/*!
 * \brief Application::countIOTraffic calculates total input and output traffic
 * \return pair of values: first - input traffic, second - output traffic
 * Method iterates over all servers and over all service records, gets information about direction of data transfer and adds it to result
 */
std::pair<ulong,ulong> Application::countIOTraffic() const {
    std::pair<ulong,ulong> result(0,0);
    std::for_each(begin(),end(),[&](const indexT &s){
        std::for_each(s.begin(),s.end(),[&](const indexT::indexT &p){
            if(typeid(*p.first)==typeid(PostDescriptor) ||
               typeid(*p.first)==typeid(FileDescriptor)) {
                auto pptr = dynamic_cast<PostDescriptor *>(p.first);
                switch (pptr->getDirection()) {
                    case SEND:
                        result.second+=pptr->getTraffic();
                    case RECV:
                        result.first+=pptr->getTraffic();
                }
            }
            if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                result.first+=nptr->getInTraffic();
                result.second+=nptr->getOutTraffic();
            }
        });
    });
    return result;
}

/*!
 * \brief Application::saveToFile saves all data to file in JSON format
 * \param path Path to destination file
 * \throws logic_error in case of errors when opening file for writing
 * Method iterates over all records and saves all data to text(JSON) file using rapidjson library
 */
void Application::saveToFile(std::__cxx11::string &path) {
    std::ofstream destfile (path);
    if(!destfile.is_open())
        throw std::logic_error("Cannot open file \""+path+"\" for writing");
    using namespace rapidjson;
    Document doc;
    doc.SetArray();
    std::for_each(begin(),end(),[&](const indexT &s){
        using namespace rapidjson;
        Value server;
        server.SetObject();
        server.AddMember("address",s.getAddress(),doc.GetAllocator());
        server.AddMember("name",StringRef(s.getName().c_str()),doc.GetAllocator());
        server.AddMember("mbcost",s.getCostPerMB(),doc.GetAllocator());
        server.AddMember("mincost",s.getCostPerMin(),doc.GetAllocator());
        Value services;
        services.SetArray();
        std::for_each(s.begin(),s.end(),[&](const indexT::indexT &p) {
            Value service;
            service.SetObject();
            service.AddMember("type",StringRef(p.first->getType().c_str()),doc.GetAllocator());
            if(typeid(*p.first)==typeid(PostDescriptor)) {
                auto pptr = dynamic_cast<PostDescriptor *>(p.first);
                service.AddMember("traffic",pptr->getTraffic(),doc.GetAllocator());
                switch (pptr->getDirection()) {
                case SEND:
                    service.AddMember("direction","send",doc.GetAllocator());
                case RECV:
                    service.AddMember("direciton","recv",doc.GetAllocator());
                }
            }
            if(typeid(*p.first)==typeid(FileDescriptor)) {
                auto fptr = dynamic_cast<FileDescriptor *>(p.first);
                service.AddMember("traffic",fptr->getTraffic(),doc.GetAllocator());
                service.AddMember("duration",fptr->getLinkDuration().count(),doc.GetAllocator());
                switch (fptr->getDirection()) {
                case SEND:
                    service.AddMember("direction","send",doc.GetAllocator());
                case RECV:
                    service.AddMember("direciton","recv",doc.GetAllocator());
                }
            }
            if(typeid(*p.first)==typeid(NetworkDescriptor)) {
                auto nptr = dynamic_cast<NetworkDescriptor *>(p.first);
                service.AddMember("intraffic",nptr->getInTraffic(),doc.GetAllocator());
                service.AddMember("outtraffic",nptr->getOutTraffic(),doc.GetAllocator());
                service.AddMember("duration",nptr->getLinkDuration().count(),doc.GetAllocator());
            }
            service.AddMember("source",p.second,doc.GetAllocator());
            service.AddMember("destination",p.first->getDestinationAddress(),doc.GetAllocator());
            service.AddMember("linktime",std::chrono::system_clock::to_time_t(p.first->getLinkTime()),doc.GetAllocator());
            services.PushBack(service,doc.GetAllocator());
        });
        server.AddMember("linktable",services,doc.GetAllocator());
        doc.PushBack(server,doc.GetAllocator());
    });
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    doc.Accept(writer);
    destfile << strbuf.GetString();
    destfile.close();
}
