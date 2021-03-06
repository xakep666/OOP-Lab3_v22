#ifndef NETWORKDESCRIPTOR
#define NETWORKDESCRIPTOR
/*!
 * \file
 * \brief Файл, содержащий объявление класса NetworkDescriptor
 */
namespace NetworkService {
    /*!
     * \brief Описатель сервиса "сеть", наследуется от ServiceDescriptor
     */
    class NetworkDescriptor : public ServiceDescriptor {
    private:
        ulong intraffic,outtraffic; ///<Количество переданной и отправленной информации
        fduration linkduration; ///<Продолжительность связи
    public:
        NetworkDescriptor();
        NetworkDescriptor(ulong intraffic,
                       ulong outtraffic,
                       ulong address,
                       ftimepoint &linktime,
                       fduration &linkduration,
                       Server * server);
        ulong getInTraffic() const;
        ulong getOutTraffic() const;
        std::string getType() const;
        const fduration & getLinkDuration() const;
        ulong calculatePrice() const;
        virtual ~NetworkDescriptor();
    protected:
        void setInTraffic(ulong intraffic);
        void setOutTraffic(ulong outtraffic);
        void setLinkDuration(fduration &ld);
    };
}
#endif // NETWORKDESCRIPTOR

