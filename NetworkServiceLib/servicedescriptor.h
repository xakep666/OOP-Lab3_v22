#ifndef SERVICEDESCRIPTOR
#define SERVICEDESCRIPTOR
/*!
 * \file
 * \brief Файл, содержащий объявление абстрактного класса ServiceDescriptor
 */
namespace NetworkService {
    class Server;
    /*!
     * \brief Описатель сервиса, абстрактный класс
     *
     * Описатели сервисов наследуются от данного класса.
     * Наследуемые классы должны реализовывать методы getType() и calculatePrice()
     */
    class ServiceDescriptor {
    private:
        ulong addr; ///<Адрес назначения
        ftimepoint linktime; ///<Время связи
        Server * server; ///<Указатель на ассоциированный сервер, нужен для рассчета стоимости
    public:
        ServiceDescriptor();
        /*!
         * \brief Получение название сервиса
         * \return Строка с названием
         */
        virtual std::string getType() const = 0;
        /*!
         * \brief Рассчет стоимости оказанных услуг
         * \return стоимость оказанных услуг
         */
        virtual ulong calculatePrice() const = 0;
        ulong getDestinationAddress() const;
        const ftimepoint & getLinkTime() const;
        const Server * getServer() const;
        virtual ~ServiceDescriptor();
    protected:
        void setDestinationAddress(ulong addr);
        void setLinkTime(ftimepoint & time);
        void setServer(Server * srv);
    };
}
#endif // SERVICEDESCRIPTOR

