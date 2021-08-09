#include <commonlib_json_param.h>
#include <commonlib_app_config.h>

namespace mcdane {
namespace commonlib {

void AppConfig::load(const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::vector<JsonParamPtr> params{
        jsonParam(width_, {"window", "width"}, true, gt(width_, 400)),
        jsonParam(height_, {"window", "height"}, true, gt(height_, 400)),
        jsonParam(title_, {"window", "title"}, true, nonempty(title_)),
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true,
                  gt(inputQueueCapacity_, 0))
    };

    parse(params, doc);
}

} // end of namespace commonlib
} // end of namespace mcdane

