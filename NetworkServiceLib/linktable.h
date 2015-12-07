#ifndef LINKTABLE
#define LINKTABLE
namespace NetworkService {
    class LinkTable {
    public:
        typedef std::pair<ServiceDescriptor *,ulong> indexT;
    private:
        std::vector<indexT> linktable;
    public:
        LinkTable();
        void addService(ServiceDescriptor * sdesc, ulong abonentaddr);
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr) const;
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr,ftimepoint &linktime) const;
        void delService(uint index);
        std::vector<std::string> showTable() const;
        indexT & operator [] (uint index);
        friend class MyIterator<LinkTable>;
        typedef MyIterator<LinkTable> Iterator;
        typedef MyConstIterator<LinkTable> ConstIterator;
        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;
        virtual ~LinkTable();
    };
}
#endif // LINKTABLE

