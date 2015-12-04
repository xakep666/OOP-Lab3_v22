#ifndef SERVICEDESCRIPTOR
#define SERVICEDESCRIPTOR
namespace NetworkService {

    class ServiceDescriptor {
    private:
        unsigned long addr;
        ftimepoint linktime;
        fduration linkduration;
        Server * server;
    public:
        ServiceDescriptor();
        virtual std::string getType() const = 0;
        virtual const ftimepoint & getLinkTime() const = 0;
        virtual const fduration & getLinkDuration() const = 0;
        virtual unsigned int calculatePrice() const = 0;
        unsigned long getDestinationAddress() const;
        Server * getServer() const;
        virtual ~ServiceDescriptor();
    protected:
        void setAddress(unsigned long addr);
        void setLinkTime(ftimepoint & time);
        void setLinkDuration(fduration & linkduration);
        void setServer(Server * srv);
    };
}
#endif // SERVICEDESCRIPTOR

