#ifndef NETWORKSERVICE
#define NETWORKSERVICE
#include <chrono>
#include <string>
#include <vector>
#include <utility>
typedef std::chrono::system_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::time_point<float> ftimepoint;
typedef std::chrono::duration<float> fduration;
namespace NetworkService {
    typedef enum {
        SEND,
        RECV
    } Direction;
}
#include "servicedescriptor.h"
#include "postdescriptor.h"
#include "filedescriptor.h"
#include "networkdescriptor.h"
#include "myiterator.h"
#include "linktable.h"
#include "server.h"
#include "application.h"
#endif // NETWORKSERVICE

