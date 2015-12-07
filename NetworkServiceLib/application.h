#ifndef APPLICATION
#define APPLICATION
namespace NetworkService {
class Application {
public:
    typedef Server indexT;
private:
    std::vector<indexT> servers;
    std::vector<ulong> usedIPs;
    bool isIPBusy(ulong addr) const;
public:
    const uint ServicesNum = 3; ///currently we have 3 services: post,files,network
    Application();
    void addServer(ulong addr,std::string name,ulong costpermin,ulong costpermb);
    void delServer(ulong addr);
    Server & getServer(ulong addr);
    void SetServerAddress(Server &srv, ulong newaddr);
    void addService(ulong serveraddr,ulong abonentaddr,ServiceDescriptor *sdesc);
    std::vector<std::string> abonentInfo(ulong abonentaddr) const;
    ulong abonentTotalPrice(ulong abonentaddr) const;
    std::pair<ulong,ulong> countIOTraffic() const;
    void saveToFile(std::string &path);
    void readFromFile(std::string &path);
    typedef MyIterator<Application> Iterator;
    typedef MyConstIterator<Application> ConstIterator;
    friend class MyIterator<Application>;
    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;
    Server & operator [](uint index);
    virtual ~Application();
};
}
#endif // APPLICATION

