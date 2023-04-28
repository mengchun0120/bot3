#ifndef INCLUDED_COMMONLIB_LOG_H
#define INCLUDED_COMMONLIB_LOG_H

#include <memory>
#include <string>
#include <ostream>

namespace mcdane {
namespace commonlib {

class Logger {
    template <typename T>
    friend Logger &operator<<(Logger& logger, const T& t);

public:
    enum LogLevel {
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARN,
        LEVEL_ERROR,
        LEVEL_COUNT
    };

    static std::string k_levelStr[LEVEL_COUNT];
    static std::shared_ptr<Logger> k_logger;

    static LogLevel strToLevel(const std::string &levelStr);

    static void initInstance(std::ostream &os,
                             LogLevel minLevel=LEVEL_DEBUG);

    ~Logger() = default;

    LogLevel getMinLevel() const
    {
        return minLevel_;
    }

    void setMinLevel(LogLevel level);

    bool getEnabled() const
    {
        return enabled_;
    }

    void setEnabled(bool enabled);

    Logger &logTime();

    void flush();

private:
    Logger(std::ostream &os,
           LogLevel minLevel);

private:
    std::ostream &os_;
    bool enabled_;
    LogLevel minLevel_;
};

template <typename T>
Logger &operator<<(Logger& logger, const T& t)
{
#ifdef ENABLE_LOG
    logger.os_ << t;
#endif
    return logger;
}

} // end of namespace commonlib
} // end of namespace mcdane

#define LOGGER (mcdane::commonlib::Logger::k_logger)

#ifdef ENABLE_LOG
#define LOG_START(level) \
    if (LOGGER && LOGGER->getEnabled() && LOGGER->getMinLevel() <= (level)) \
    { \
        LOGGER->logTime() << ' ' << __FILE__ << ':' << __LINE__ << ' ' \
                          << mcdane::commonlib::Logger::k_levelStr[(level)] \
                          << ' '

#define LOG_END \
        '\n'; \
        LOGGER->flush(); \
    }

#else
#define LOG_START(level) *LOGGER
#define LOG_END "";
#endif // ENABLE_LOG

#define LOG_DEBUG LOG_START(mcdane::commonlib::Logger::LEVEL_DEBUG)
#define LOG_INFO LOG_START(mcdane::commonlib::Logger::LEVEL_INFO)
#define LOG_WARN LOG_START(mcdane::commonlib::Logger::LEVEL_WARN)
#define LOG_ERROR LOG_START(mcdane::commonlib::Logger::LEVEL_ERROR)

#endif // INCLUDED_COMMONLIB_LOG_H
