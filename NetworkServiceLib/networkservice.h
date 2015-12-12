#ifndef NETWORKSERVICE
#define NETWORKSERVICE
/*!
 * \file
 * \brief Файл, содержаший все необходимые определения и включения для работы библиотеки
 *
 * В приложении используйте его.
 */
#ifdef TESTING
#define private public
#define protected public
#endif
#include <chrono>
#include <string>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <stdexcept>
#include <new>
#include <fstream>
typedef std::chrono::system_clock Time; ///<Системные часы
typedef std::chrono::milliseconds ms; ///<Милисекунда
typedef std::chrono::time_point<Time> ftimepoint; ///<Специализация time_point для системных часов
typedef std::chrono::duration<float> fduration; ///<Специализация duration для типа float
static const ulong minute_k = std::chrono::minutes::period::num / std::chrono::minutes::period::den; ///<Коэфиициент для получения количества минут из объекта duration
namespace NetworkService {
    ///Направление передачи данных
    typedef enum {
        SEND, ///<Передача
        RECV, ///<Прием
    } Direction;
}
#include "helpers.h"
#include "servicedescriptor.h"
#include "postdescriptor.h"
#include "filedescriptor.h"
#include "networkdescriptor.h"
#include "myiterator.h"
#include "myvector.h"
#include "linktable.h"
#include "server.h"
#include "application.h"
#endif // NETWORKSERVICE

