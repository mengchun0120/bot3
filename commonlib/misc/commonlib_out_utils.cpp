#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <commonlib_out_utils.h>

namespace std {

std::ostream &operator<<(std::ostream& os,
                         const rapidjson::Value &v)
{
    using namespace rapidjson;

    OStreamWrapper ows(os);
    Writer<OStreamWrapper> writer(ows);

    v.Accept(writer);

    return os;
}

} // end of namespace std
