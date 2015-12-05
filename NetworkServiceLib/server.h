#ifndef SERVER
#define SERVER
namespace NetworkService {
class Server {
private:
    ulong address;
    std::string name;
    unsigned int costpermin,costpermb;
    LinkTable linktable;
public:
    Server();
    ulong getAddress() const;
    void setAddress(unsigned int setAddress);
    const std::string & getName() const;
    void setName(std::string & name);
    unsigned int getCostPerMin() const;
    void setCostPerMin(unsigned int cost);
    unsigned int setCostPerMB(unsigned int cost);
    void addService(ServiceDescriptor *servdesc,ulong abonaddr);
    ServiceDescriptor * getService(ulong abonaddr,ftimepoint &linktime);
    std::vector<std::string> showTable() const;
    friend class MyIterator<Server>;
    typedef MyIterator<Server> Iterator;
    Iterator begin();
    Iterator end();
    std::pair<ServiceDescriptor *,ulong> & operator [](int index);
    virtual ~Server();
};
}
#endif // SERVER

