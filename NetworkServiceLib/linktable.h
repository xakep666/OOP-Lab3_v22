#ifndef LINKTABLE
#define LINKTABLE
namespace NetworkService {
    class LinkTable {
    private:
        std::vector<std::pair<ServiceDescriptor *,ulong>> linktable;
    public:
        LinkTable();
        void addService(ServiceDescriptor * sdesc, ulong abonentaddr);
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr) const;
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr,ftimepoint &linktime) const;
        void delService(ulong abonentaddr, ftimepoint &linktime);
        template <class T> void delService(ulong abonentaddr);
        void delService(ServiceDescriptor *sdesc);
        std::vector<std::string> showTable() const;
        std::pair<ServiceDescriptor *,ulong> & operator [] (int index);
        friend class MyIterator<LinkTable>;
        typedef MyIterator<LinkTable> Iterator;
        Iterator begin();
        Iterator end();
        virtual ~LinkTable();
    };
}
#endif // LINKTABLE

