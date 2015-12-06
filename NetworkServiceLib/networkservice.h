#ifndef NETWORKSERVICE
#define NETWORKSERVICE
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
typedef std::chrono::system_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::time_point<Time> ftimepoint;
typedef std::chrono::duration<float> fduration;
namespace NetworkService {
    ///Direction of data transfer
    typedef enum {
        SEND, ///<sending
        RECV, ///<reciving
    } Direction;
}
#include "helpers.h"
#include "servicedescriptor.h"
#include "postdescriptor.h"
#include "filedescriptor.h"
#include "networkdescriptor.h"
#include "myiterator.h"
#include "linktable.h"
#include "server.h"
#include "application.h"
#endif // NETWORKSERVICE

