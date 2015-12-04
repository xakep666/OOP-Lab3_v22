#ifndef APPLICATION
#define APPLICATION
namespace NetworkService {
class Application {
private:
    std::vector<Server> servers;
public:
    Application();
    void addServer(unsigned long addr,std::string &name,unsigned int costpermin,unsigned int costpermb);
    void delServer(unsigned long addr);
    Server & getServer(unsigned long addr);
    void addService(unsigned long serveraddr,unsigned long abonentaddr,ServiceDescriptor *sdesc);
    std::vector<std::string> abonentInfo(unsigned long abonentaddr) const;
    unsigned int abonentTotalCost(unsigned long abonentaddr) const;
    std::vector<unsigned long> countIOTraffic() const;
    void saveToFile(std::string &path);
    void readFromFile(std::string &path);
    virtual ~Application();
};
}
#endif // APPLICATION

