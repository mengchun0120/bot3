#include <cassert>
#include <iostream>
#include <sstream>
#include <regex>
#define ENABLE_LOG
#include <commonlib_log.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

class LogTester {
public:
    LogTester();

    std::ostringstream os_;
};

LogTester::LogTester()
{
    Logger::initInstance(os_, Logger::LEVEL_DEBUG);
}

static LogTester k_logTester;

void testLog_TestOutput()
{
    using namespace std;

    k_logTester.os_.clear();

    LOG_INFO << "Hello world! " << 100 << LOG_END;
    cout << k_logTester.os_.str();

    regex r("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3} \\S+:\\d+ " \
            "INFO Hello world! 100\n");
    assert(regex_match(k_logTester.os_.str(), r));
}

void testLog()
{
    testLog_TestOutput();
}

} // end of namespace commonlib
} // end of namespce mcdane

