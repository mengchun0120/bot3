#include <cassert>
#include <iostream>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

auto stringParser =
[](
    std::string& s,
    const rapidjson::Value& v)
{
    std::vector<JsonParamPtr> params{
        jsonParam(
            s,
            "value"
        )
    };

    parse(params, v);
};

void
testNamedMap_LoadWrongFileThrowException()
{
    bool exceptionHappened = false;

    try
    {
        NamedMap<std::string> map;
        map.init(
            "unittest/commonlib/data/wrong_named_map.json",
            stringParser);
    }
    catch (const ParseException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void
testNamedMap_SearchCorrectFile()
{
    bool exceptionHappened = false;

    try
    {
        NamedMap<std::string> map;
        map.init(
            "unittest/commonlib/data/correct_named_map.json",
            stringParser);

        const std::string* s = map.search("top");
        assert(s && *s == "Top");
        s = map.search("list");
        assert(s && *s == "List");
        s = map.search("rect");
        assert(!s);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(!exceptionHappened);
}

void testNamedMap()
{
    testNamedMap_LoadWrongFileThrowException();
    testNamedMap_SearchCorrectFile();
}

} // end of namespace commonlib
} // end of namespace mcdane

