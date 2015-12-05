#ifndef APPLICATION
#define APPLICATION
namespace NetworkService {
class Application {
private:
    std::vector<Server> servers;
public:
    Application();
    void addServer(ulong addr,std::string &name,unsigned int costpermin,unsigned int costpermb);
    void delServer(ulong addr);
    Server & getServer(ulong addr);
    void addService(ulong serveraddr,ulong abonentaddr,ServiceDescriptor *sdesc);
    std::vector<std::string> abonentInfo(ulong abonentaddr) const;
    unsigned int abonentTotalCost(ulong abonentaddr) const;
    std::vector<ulong> countIOTraffic() const;
    void saveToFile(std::string &path);
    void readFromFile(std::string &path);
    virtual ~Application();
};
}
#endif // APPLICATION

