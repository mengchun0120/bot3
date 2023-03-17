#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <time.h>
#endif

#include <cstdio>
#include <commonlib_exception.h>
#include <commonlib_log.h>

namespace mcdane {
namespace commonlib {

std::string Logger::k_levelStr[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};

std::shared_ptr<Logger> Logger::k_logger;

void Logger::initInstance(std::ostream &os,
                          LogLevel minLevel)
{
#ifdef ENABLE_LOG
    if (!k_logger)
    {
        k_logger.reset(new Logger(os, minLevel));
    }
#endif
}

Logger::LogLevel Logger::strToLevel(const std::string &levelStr)
{
    for (int i = 0; i < static_cast<int>(LEVEL_COUNT); ++i)
    {
        if (levelStr == k_levelStr[i])
        {
            return static_cast<LogLevel>(i);
        }
    }

    THROW_EXCEPT(InvalidArgumentException, "Invalid log level " + levelStr);
}

Logger::Logger(std::ostream &os,
               LogLevel minLevel)
    : os_(os)
    , enabled_(true)
    , minLevel_(minLevel)
{
}

void Logger::setMinLevel(LogLevel level)
{
    minLevel_ = level;
}

void Logger::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

Logger &Logger::logTime()
{
#ifdef ENABLE_LOG
    static char buffer[200];

#ifdef _WIN32
    SYSTEMTIME t;
    GetLocalTime(&t);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            t.wYear, t.wMonth, t.wDay, t.wHour,
            t.wMinute, t.wSecond, t.wMilliseconds);
    os_ << buffer;
#elif __linux__
    struct timespec tp;
    if (clock_gettime(CLOCK_REALTIME, &tp) == -1)
    {
        return *this;
    }

    struct tm t;
    if (localtime_r(&tp.tv_sec, &t) == NULL)
    {
        return *this;
    }

    int ms = tp.tv_nsec / 1e6;
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            (t.tm_year + 1900), t.tm_mon, t.tm_mday, t.tm_hour,
            t.tm_min, t.tm_sec, ms);
    os_ << buffer;
#endif

#endif
    return *this;
}

void Logger::flush()
{
#ifdef ENABLE_LOG
    os_.flush();
#endif
}

} // end of namespace commonlib
} // end of namespace mcdane
