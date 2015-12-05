#ifndef SERVER
#define SERVER
namespace NetworkService {
class Server {
private:
    ulong address;
    std::string name;
    ulong costpermin,costpermb;
    LinkTable linktable;
public:
    Server();
    ulong getAddress() const;
    void setAddress(ulong setAddress);
    const std::string & getName() const;
    void setName(std::string & name);
    ulong getCostPerMin() const;
    ulong getCostPerMB() const;
    void setCostPerMin(ulong cost);
    void setCostPerMB(ulong cost);
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

