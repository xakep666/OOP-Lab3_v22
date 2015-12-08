#ifndef HELPERS
#define HELPERS
/*!
 * \file
 * \brief Файл, содержащий объявление функций-помощников, не принадлежащих не одному объекту
 */
namespace NetworkService {
    bool isValidIP (ulong);
    std::string LongIPtoString(ulong);
    ulong stringToLongIP(std::string);
}
#endif // HELPERS

