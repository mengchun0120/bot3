#include <cassert>
#include <iostream>
#include <stdexcept>
#include <commonlib_json_param.h>
#include <test_commonlib.h>

using namespace rapidjson;

namespace mcdane {
namespace commonlib {

void testJsonParam_ParseSimplePathSuccess()
{
    const char* json = "{\"count\": 1}";
    Document doc;
    doc.Parse(json);

    int i;
    JsonParamPtr param = jsonParam(i, {"count"});

    try
    {
        param->parse(doc);
        assert(i == 1);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testJsonParam_ParseComplexPathSuccess()
{
    const char* json = "{\"content\": {\"summary\": {\"amount\": 2.0}}}";
    Document doc;
    doc.Parse(json);

    double d;
    JsonParamPtr param = jsonParam(d, {"content", "summary", "amount"});

    try
    {
        param->parse(doc);
        assert(d == 2.0);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testJsonParam_ParseArraySuccess()
{
    try
    {
        const char* json1 = "[\"fish\", \"meat\"]";
        Document doc1;
        doc1.Parse(json1);

        std::vector<std::string> strArr;
        JsonParamPtr param1 = jsonParam(strArr, {});
        param1->parse(doc1);
        assert(strArr[0] == "fish");
        assert(strArr[1] == "meat");

        const char* json2 = "{\"list\": [1, 2]}";
        Document doc2;
        doc2.Parse(json2);

        std::vector<int> intArr;
        JsonParamPtr param2 = jsonParam(intArr, {"list"});
        param2->parse(doc2);
        assert(intArr[0] == 1);
        assert(intArr[1] == 2);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testJsonParam_WrongPathThrowException()
{
    bool exceptionHappened = false;

    try
    {
        const char* json = "{\"store\": {\"name\": \"Steak\"}}";
        Document doc;
        doc.Parse(json);

        std::string store;
        JsonParamPtr param = jsonParam(store, {"store", "brand"});
        param->parse(doc);
    }
    catch (const MyException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testJsonParam_ValidationFailThrowException()
{
    bool exceptionHappened = false;

    try
    {
        const char* json = "{\"hose\": 1}";
        Document doc;
        doc.Parse(json);

        int i;
        JsonParamPtr param = jsonParam(i, {"hose"}, true, gt(1));
        param->parse(doc);
    }
    catch (const MyException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testJsonParam_UnrequiedThrowNoException()
{
    try
    {
        const char* json = "{}";
        Document doc;
        doc.Parse(json);

        int i;
        JsonParamPtr param = jsonParam(i, {"hose"}, false);
        param->parse(doc);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testJsonParam_ParseComplexJsonSuccess()
{
    try
    {
        const char* json = "{" \
                           "    \"identity\": {" \
                           "        \"id\": 12345," \
                           "        \"name\": \"Mary\"" \
                           "    }," \
                           "    \"books\": [\"Shoot\", \"Zero\"]" \
                           "}";
        Document doc;
        doc.Parse(json);

        int id;
        std::string name;
        int age;
        std::vector<std::string> books;
        std::vector<JsonParamPtr> params{
            jsonParam(id, {"identity", "id"}, true, gt(0)),
            jsonParam(name, {"identity", "name"}),
            jsonParam(age, {"identity", "age"}, false, gt(0)),
            jsonParam(books, {"books"})
        };

        parse(params, doc);
        assert(id == 12345);
        assert(name == "Mary");
        assert(books[0] == "Shoot");
        assert(books[1] == "Zero");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testJsonParam()
{
    testJsonParam_ParseSimplePathSuccess();
    testJsonParam_ParseComplexPathSuccess();
    testJsonParam_ParseArraySuccess();
    testJsonParam_WrongPathThrowException();
    testJsonParam_ValidationFailThrowException();
    testJsonParam_UnrequiedThrowNoException();
    testJsonParam_ParseComplexJsonSuccess();
}

} // end of namespace commonlib
} // end of namespace mcdane

