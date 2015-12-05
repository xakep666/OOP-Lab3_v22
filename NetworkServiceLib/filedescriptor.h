#ifndef FILEDESCRIPTOR
#define FILEDESCRIPTOR
namespace NetworkService {
    class FileDescriptor : public PostDescriptor {
    private:
        fduration linkduration;
        FileDescriptor ();
    public:
        FileDescriptor(ulong traffic,
                       Direction direction,
                       ulong address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        const fduration & getDuration() const;
        std::string getType() const;
        ulong calculatePrice() const;
        virtual ~FileDescriptor();
    };
}
#endif // FILEDESCRIPTOR

