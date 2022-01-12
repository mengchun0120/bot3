#include <cassert>
#include <iostream>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

struct TestNamedMapParser {
    TestNamedMapParser();

    std::string* operator()(const rapidjson::Value& v);

    std::vector<JsonParamPtr> params_;
    std::string value_;
};


TestNamedMapParser::TestNamedMapParser()
    : params_{jsonParam(value_, {"value"})}
{
}

std::string* TestNamedMapParser::operator()(const rapidjson::Value& v)
{
    parse(params_, v);
    return new std::string(value_);
}

void testNamedMap_LoadWrongFileThrowException()
{
    bool exceptionHappened = false;

    try
    {
        TestNamedMapParser parser;
        NamedMap<std::string> map;
        map.load("unittest/commonlib/data/wrong_named_map.json", parser);
    }
    catch (const ParseException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testNamedMap_SearchCorrectFile()
{
    bool exceptionHappened = false;

    try
    {
        TestNamedMapParser parser;
        NamedMap<std::string> map;
        map.load("unittest/commonlib/data/correct_named_map.json", parser);

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
}

} // end of namespace commonlib
} // end of namespace mcdane

