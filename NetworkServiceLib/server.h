#ifndef SERVER
#define SERVER
/*!
 * \file
 * \brief Файл, содержащий объявление класса Server
 */
namespace NetworkService {
class Application;
/*!
 * \brief Описатель сервера
 *
 * Описатель сервера. Используется наследование от LinkTable вместо композиции для облегчения работы с итераторами
 */
class Server: public LinkTable {
private:
    ulong address; ///<IP адрес сервера
    std::string name; ///<Имя сервера
    ulong costpermin,costpermb; ///<Стоимость 1 минуты связи и 1MB переданных данных
public:
    Server();
    friend class Application; ///<Необходимо для изменения адреса
    explicit Server(ulong address);
    ulong getAddress() const;
    const std::string & getName() const;
    void setName(std::string & name);
    ulong getCostPerMin() const;
    ulong getCostPerMB() const;
    void setCostPerMin(ulong cost);
    void setCostPerMB(ulong cost);
};
}
#endif // SERVER

