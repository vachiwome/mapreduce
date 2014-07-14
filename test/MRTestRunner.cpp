#include <cppunit/ui/text/TestRunner.h>

#include "comms/include/SocketManagerTest.h"
#include "comms/include/PacketTest.h"

int main( int argc, char **argv) {
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(SocketManagerTest::suite());
  runner.addTest(PacketTest::suite());

  runner.run();

  return 0;
}
