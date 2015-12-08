#ifndef LINKTABLE
#define LINKTABLE
/*!
 * \file
 * Файл, содержащий объявление класса LinkTable
 */
namespace NetworkService {
    /*!
     * \brief Класс, реализующий "таблицу связи"
     */
    class LinkTable {
    public:
        typedef std::pair<ServiceDescriptor *,ulong> indexT; ///<Определение типа для работы итератора
    private:
        std::vector<indexT> linktable; ///<"Таблица связи"
    public:
        LinkTable();
        void addService(ServiceDescriptor * sdesc, ulong abonentaddr);
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr) const;
        std::vector<ServiceDescriptor *> getServices(ulong abonentaddr,ftimepoint &linktime) const;
        void delService(uint index);
        std::vector<std::string> showTable() const;
        indexT & operator [] (uint index);
        friend class MyIterator<LinkTable>;
        typedef MyIterator<LinkTable> Iterator; ///<Специализация шаблонного типа MyIterator
        typedef MyConstIterator<LinkTable> ConstIterator; ///<Специализация шаблонного типа MyConstIterator
        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;
        virtual ~LinkTable();
    };
}
#endif // LINKTABLE

