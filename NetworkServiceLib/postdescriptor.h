#ifndef POSTDESCRIPTOR
#define POSTDESCRIPTOR
namespace NetworkService {
    class PostDescriptor : public ServiceDescriptor {
    private:
        ulong traffic;
        Direction direction;
    public:
        PostDescriptor();
        PostDescriptor(ulong traffic,
                       Direction direction,
                       ulong address,
                       ftimepoint &linktime,
                       Server * server);
        Direction getDirection() const;
        ulong getTraffic() const;
        virtual std::string getType() const;
        const ftimepoint & getLinkTime() const;
        virtual ulong calculatePrice() const;
        virtual ~PostDescriptor();
    protected:
        void setTraffic(ulong);
        void setDirection(Direction);
    };
}
#endif // POSTDESCRIPTOR

