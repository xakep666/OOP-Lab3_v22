/*!
  * \file
  * Файл, содержащий реализацию функций-помощников, не принадлежащих какому-либо объекту
  */
#include "networkservice.h"
using namespace NetworkService;

/*!
 * \brief Преобразование IP адреса из ulong-представления в строковое
 * \param ip IP в ulong-представлении
 * \return Строковое представление адреса
 * \throws logic_error в случае ошибки преобразования
 * Функция преобразует IP адрес в строковое представления, используя C функцию inet_ntop()
 */
std::string LongIPtoString(ulong ip) {
    char ipstr [INET_ADDRSTRLEN];
    struct in_addr inaddr;
    inaddr.s_addr = ip;
    auto checkptr = inet_ntop(AF_INET,&inaddr,ipstr,INET_ADDRSTRLEN);
    if (!checkptr)
        throw std::logic_error("Cannot convert "+std::to_string(ip)+" to string IP");
    return std::string(ipstr);
}

/*!
 * \brief Преобразование IP адреса из строкового представления в ulong-представление
 * \param src исходная строка
 * \return ulong-представление адреса
 * \throws logic_error в случае ошибки преобразования
 * Функция преобразует IP адрес из строкового представления в ulong, исползуя C функцию inet_pton()
 */
ulong stringToLongIP(std::string src) {
    struct in_addr tmp;
    int code = inet_pton(AF_INET,src.c_str(),&tmp);
    if (code<=0)
        throw std::invalid_argument("Cannot convert "+src+" to IP address");
    ulong ip = tmp.s_addr;
    if (isValidIP(ip))
        throw std::invalid_argument("Invalid ip address ("+src+") given");
    return ip;
}

/*!
 * \brief Проверка, является ли IP адрес верным
 * \param ip IP адрес в ulong-представлении
 * \return true если IP верный, false в противном случае
 * IP адрес считается верным, если он не начинается и не заканчивается на 0 или 255.
 * Проверка происходит с использованием битовых сдвигов, побитовых "и" и сравнений.
 * Пример реализации проверки
 * \snippet helpers.cpp ipcode
 */
bool isValidIP(ulong ip) {
    const ulong IPSize = 32;
    ///[!ipcode]
    if ( (ip&0xFF)==0 || (ip&0xFF)==0xFF)
        return false;
    if (((ip>>(IPSize-8))&0xFF)==0 || ((ip>>(IPSize-8))&0xFF)==0xFF)
        return false;
    return true;
    ///[!ipcode]
}
