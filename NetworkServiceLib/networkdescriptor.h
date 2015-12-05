#ifndef NETWORKDESCRIPTOR
#define NETWORKDESCRIPTOR
namespace NetworkService {
    class NetworkDescriptor : public ServiceDescriptor {
    private:
        ulong intraffic,outtraffic;
        fduration linkduration;
    public:
        NetworkDescriptor();
        NetworkDescriptor(ulong intraffic,
                       ulong outtraffic,
                       ulong address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        ulong getInTraffic() const;
        ulong getOutTraffic() const;
        std::string getType() const;
        const fduration & getLinkDuration() const;
        ulong calculatePrice() const;
    };
}
#endif // NETWORKDESCRIPTOR

