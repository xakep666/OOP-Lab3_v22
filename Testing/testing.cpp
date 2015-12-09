#include <QtTest>
#include "testhelpers.h"
#include "testserver.h"
#include "testpostdescriptor.h"
#include "testfiledescriptor.h"
#include "testnetworkdescriptor.h"
#include <random>
#include <time.h>
int main(int argc, char** argv)
{
   int status = 0;
   auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
     status |= QTest::qExec(obj, argc, argv);
     delete obj;
   };
   srand(time(nullptr));
   ASSERT_TEST(new testHelpers());
   ASSERT_TEST(new testServer());
   ASSERT_TEST(new testPostDescriptor());
   ASSERT_TEST(new testFileDescriptor());
   ASSERT_TEST(new testNetworkDescriptor());
   return status;
}
