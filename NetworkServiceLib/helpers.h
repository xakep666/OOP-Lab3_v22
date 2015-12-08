#ifndef HELPERS
#define HELPERS
/*!
 * \file
 * \brief Файл, содержащий реализацию функций-помощников, не принадлежащих какому-либо объекту
 */
namespace NetworkService {
    bool isValidIP (ulong);
    std::string LongIPtoString(ulong);
    ulong stringToLongIP(std::string);
}
#endif // HELPERS

