#include <androidlib_android_out.h>

namespace mcdane {
namespace androidlib {

AndroidOut androidOut("AO");
std::ostream aout(&androidOut);

} // end of namespace androidlib
} // end of namespace mcdane
