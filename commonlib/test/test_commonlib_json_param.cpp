#include <gtest/gtest.h>
#include <commonlib_json_param.h>

using namespace mcdane::commonlib;
using namespace rapidjson;

TEST(TestParseJson, ParseSimplePathSuccess)
{
    const char* json = "{\"count\": 1}";
    Document doc;
    doc.Parse(json);

    int i;
    JsonParamPtr param = jsonParam(i, {"count"});
    ASSERT_NO_THROW(param->parse(doc));
    ASSERT_EQ(i, 1);
}

TEST(TestParseJson, ParseComplexPathSuccess)
{
    const char* json = "{\"content\": {\"summary\": {\"amount\": 2.0}}}";
    Document doc;
    doc.Parse(json);

    double d;
    JsonParamPtr param = jsonParam(d, {"content", "summary", "amount"});
    ASSERT_NO_THROW(param->parse(doc));
    ASSERT_EQ(d, 2.0);
}

TEST(TestParseJson, ParseArraySuccess)
{
    const char* json1 = "[\"fish\", \"meat\"]";
    Document doc1;
    doc1.Parse(json1);

    std::vector<std::string> strArr;
    JsonParamPtr param1 = jsonParam(strArr, {});
    ASSERT_NO_THROW(param1->parse(doc1));
    ASSERT_EQ(strArr[0], "fish");
    ASSERT_EQ(strArr[1], "meat");

    const char* json2 = "{\"list\": [1, 2]}";
    Document doc2;
    doc2.Parse(json2);

    std::vector<int> intArr;
    JsonParamPtr param2 = jsonParam(intArr, {"list"});
    ASSERT_NO_THROW(param2->parse(doc2));
    ASSERT_EQ(intArr[0], 1);
    ASSERT_EQ(intArr[1], 2);
}

TEST(TestParseJson, WrongPathThrowException)
{
    const char* json = "{\"store\": {\"name\": \"Steak\"}}";
    Document doc;
    doc.Parse(json);

    std::string store;
    JsonParamPtr param = jsonParam(store, {"store", "brand"});
    ASSERT_THROW(param->parse(doc), MyException);
}

TEST(TestParseJson, ValidationFailThrowException)
{
    const char* json = "{\"hose\": 1}";
    Document doc;
    doc.Parse(json);

    int i;
    JsonParamPtr param = jsonParam(i, {"hose"}, true, gt(i, 1));
    ASSERT_THROW(param->parse(doc), MyException);
}

TEST(TestParseJson, UnrequiedThrowNoException)
{
    const char* json = "{}";
    Document doc;
    doc.Parse(json);

    int i;
    JsonParamPtr param = jsonParam(i, {"hose"}, false);
    ASSERT_NO_THROW(param->parse(doc));
}

TEST(TestParseJson, ParseComplexJsonSuccess)
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
        jsonParam(id, {"identity", "id"}, true, gt(id, 0)),
        jsonParam(name, {"identity", "name"}),
        jsonParam(age, {"identity", "age"}, false, gt(age, 0)),
        jsonParam(books, {"books"})
    };

    ASSERT_NO_THROW(parse(params, doc));
    ASSERT_EQ(id, 12345);
    ASSERT_EQ(name, "Mary");
    ASSERT_EQ(books[0], "Shoot");
    ASSERT_EQ(books[1], "Zero");
}
