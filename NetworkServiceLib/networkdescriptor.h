#ifndef NETWORKDESCRIPTOR
#define NETWORKDESCRIPTOR
namespace NetworkService {
    class NetworkDescriptor : public ServiceDescriptor {
    private:
        ulong intraffic,outtraffic;
        fduration linkduration;
        NetworkDescriptor();
    public:
        NetworkDescriptor(ulong intraffic,
                       ulong outtraffic,
                       ulong address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        ulong getInTraffic() const;
        ulong getOutTraffic() const;
        std::string getType() const;
        const ftimepoint & getLinkTime() const;
        const fduration & getLinkDuration() const;
        void setDuration(fduration & linkduration);
        unsigned int calculatePrice() const;
    };
}
#endif // NETWORKDESCRIPTOR

