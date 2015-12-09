#ifndef POSTDESCRIPTOR
#define POSTDESCRIPTOR
/*!
 * \file
 * \brief Файл, содержащий объявление класса PostDescriptor
 */
namespace NetworkService {
    /*!
     * \brief Описатель сервиса "почта", наследуемый от ServiceDescriptor
     */
    class PostDescriptor : public ServiceDescriptor {
    private:
        ulong traffic; ///<Количество отправленных/полученных данных в MB
        Direction direction; ///<Направление передачи данных
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
        virtual ulong calculatePrice() const;
        virtual ~PostDescriptor();
    protected:
        void setTraffic(ulong);
        void setDirection(Direction);
    };
}
#endif // POSTDESCRIPTOR

