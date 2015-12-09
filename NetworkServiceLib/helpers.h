#ifndef HELPERS
#define HELPERS
/*!
 * \file
 * \brief Файл, содержащий объявление функций-помощников, не принадлежащих какому-либо объекту
 */
namespace NetworkService {
    std::string LongIPtoString(ulong);
    ulong stringToLongIP(std::string);
    bool isValidIP (ulong);
}
#endif // HELPERS

