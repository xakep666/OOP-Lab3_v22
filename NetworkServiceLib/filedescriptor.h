#ifndef FILEDESCRIPTOR
#define FILEDESCRIPTOR
/*!
 * \file
 * \brief Файл, содержащий объявление класса FileDescriptor
 */
namespace NetworkService {
    /*!
     * \brief Класс, описывающий сервис "файл"
     * Наследуется от PostDescriptor в связи с большим количеством общих полей
     */
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
        const fduration & getLinkDuration() const;
        std::string getType() const;
        ulong calculatePrice() const;
        virtual ~FileDescriptor();
    };
}
#endif // FILEDESCRIPTOR

