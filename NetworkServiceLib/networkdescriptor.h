#ifndef NETWORKDESCRIPTOR
#define NETWORKDESCRIPTOR
namespace NetworkService {
    class NetworkDescriptor : public ServiceDescriptor {
    private:
        unsigned long intraffic,outtraffic;
        NetworkDescriptor();
    public:
        NetworkDescriptor(unsigned long intraffic,
                       unsigned long outtraffic,
                       unsigned long address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        unsigned long getInTraffic() const;
        unsigned long getOutTraffic() const;
        std::string getType() const;
        const ftimepoint & getLinkTime() const;
        const fduration & getLinkDuration() const;
        unsigned int calculatePrice() const;
    };
}
#endif // NETWORKDESCRIPTOR

