#ifndef INCLUDED_ANDROIDLIB_ANDROID_OUT_H
#define INCLUDED_ANDROIDLIB_ANDROID_OUT_H

#include <android/log.h>
#include <sstream>

namespace mcdane {
namespace androidlib {

extern std::ostream aout;

class AndroidOut: public std::stringbuf {
public:
    inline AndroidOut(const char* kLogTag)
        : logTag_(kLogTag)
    {}

protected:
    virtual int sync() override
    {
        __android_log_print(ANDROID_LOG_DEBUG, logTag_, "%s", str().c_str());
        str("");
        return 0;
    }

private:
    const char* logTag_;
};

} // end of namespace androidlib
} // end of namespace mcdane

#endif
