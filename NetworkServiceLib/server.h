#ifndef SERVER
#define SERVER
namespace NetworkService {
class Application;
class Server: public LinkTable {
private:
    ulong address;
    std::string name;
    ulong costpermin,costpermb;
public:
    /*!
     * Needed for changing address
     */
    friend class Application;
    explicit Server(ulong address);
    ulong getAddress() const;
    const std::string & getName() const;
    void setName(std::string & name);
    ulong getCostPerMin() const;
    ulong getCostPerMB() const;
    void setCostPerMin(ulong cost);
    void setCostPerMB(ulong cost);
    virtual ~Server();
};
}
#endif // SERVER

