#ifndef SERVER
#define SERVER
namespace NetworkService {
class Server {
private:
    unsigned long address;
    std::string name;
    unsigned int costpermin,costpermb;
    LinkTable linktable;
public:
    Server();
    unsigned long getAddress() const;
    void setAddress(unsigned int setAddress);
    const std::string & getName() const;
    void setName(std::string & name);
    unsigned int getCostPerMin() const;
    void setCostPerMin(unsigned int cost);
    unsigned int setCostPerMB(unsigned int cost);
    void addService(ServiceDescriptor *servdesc,unsigned long abonaddr);
    ServiceDescripor * getService(unsigned long abonaddr,ftimepoint &linktime);
    std::vector<std::string> showTable() const;
    friend class MyIterator<Server>;
    MyIterator<Server> begin();
    MyIterator<Server> end();
    std::pair<ServiceDescriptor *,unsigned long> & operator [](int index);
    virtual ~Server();
};
}
#endif // SERVER

