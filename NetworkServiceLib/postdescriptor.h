#ifndef POSTDESCRIPTOR
#define POSTDESCRIPTOR
namespace NetworkService {
    class PostDescriptor : public ServiceDescriptor {
    private:
        unsigned long traffic;
        Direction direction;
        PostDescriptor();
    public:
        PostDescriptor(unsigned long traffic,
                       Direction direction,
                       unsigned long address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        Direction getDirection() const;
        unsigned long getTraffic() const;
        std::string getType() const;
        const ftimepoint & getLinkTime() const;
        const fduration & getLinkDuration() const;
        unsigned int calculatePrice() const;
    };
}
#endif // POSTDESCRIPTOR

