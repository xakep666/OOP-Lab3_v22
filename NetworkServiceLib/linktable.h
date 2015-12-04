#ifndef LINKTABLE
#define LINKTABLE
namespace NetworkService {
    class LinkTable {
    private:
        std::vector<std::pair<ServiceDescriptor *,unsigned long>> linktable;
    public:
        LinkTable();
        void addService(ServiceDescriptor * sdesc, unsigned long abonentaddr);
        std::vector<ServiceDescriptor *> getServices(unsigned long abonentaddr) const;
        std::vector<ServiceDescriptor *> getServices(unsigned long abonentaddr,ftimepoint &linktime) const;
        void delService(unsigned long abonentaddr, ftimepoint &linktime);
        template <class T> delService(unsigned long abonentaddr);
        void delService(ServiceDescriptor *sdesc);
        std::vector<std::string> showTable() const;
        std::pair<ServiceDescriptor *,unsigned long> & operator [] (int index);
        friend class MyIterator<LinkTable>;
        MyIterator<LinkTable> begin();
        MyIterator<LinkTable> end();
        virtual ~LinkTable();
    };
}
#endif // LINKTABLE

