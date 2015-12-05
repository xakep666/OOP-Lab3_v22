#ifndef SERVICEDESCRIPTOR
#define SERVICEDESCRIPTOR
namespace NetworkService {
    class Server;
    class ServiceDescriptor {
    private:
        ulong addr;
        ftimepoint linktime;
        Server * server;
    public:
        ServiceDescriptor();
        virtual std::string getType() const = 0;
        virtual const ftimepoint & getLinkTime() const = 0;
        virtual unsigned int calculatePrice() const = 0;
        ulong getDestinationAddress() const;
        const Server * getServer() const;
        virtual ~ServiceDescriptor();
    protected:
        void setDestinationAddress(ulong addr);
        void setLinkTime(ftimepoint & time);
        void setServer(Server * srv);
    };
}
#endif // SERVICEDESCRIPTOR

