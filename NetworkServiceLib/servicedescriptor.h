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
        /*!
         * \brief getType
         * \return human readable type name
         */
        virtual std::string getType() const = 0;
        /*!
         * \brief calculatePrice calculated price for service using associated server costs
         * \return price for given service
         */
        virtual ulong calculatePrice() const = 0;
        ulong getDestinationAddress() const;
        const ftimepoint & getLinkTime() const;
        const Server * getServer() const;
        virtual ~ServiceDescriptor();
    protected:
        void setDestinationAddress(ulong addr);
        void setLinkTime(ftimepoint & time);
        void setServer(Server * srv);
    };
}
#endif // SERVICEDESCRIPTOR

