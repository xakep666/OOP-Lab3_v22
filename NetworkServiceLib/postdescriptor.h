#ifndef POSTDESCRIPTOR
#define POSTDESCRIPTOR
namespace NetworkService {
    class PostDescriptor : public ServiceDescriptor {
    private:
        ulong traffic;
        Direction direction;
        PostDescriptor();
    public:
        PostDescriptor(ulong traffic,
                       Direction direction,
                       ulong address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        Direction getDirection() const;
        ulong getTraffic() const;
        std::string getType() const;
        const ftimepoint & getLinkTime() const;
        const fduration & getLinkDuration() const;
        virtual unsigned int calculatePrice() const;
        virtual ~PostDescriptor();
    };
}
#endif // POSTDESCRIPTOR

