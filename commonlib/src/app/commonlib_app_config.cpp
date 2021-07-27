#include <commonlib_json_param.h>
#include <commonlib_app_config.h>

namespace mcdane {
namespace commonlib {

std::shared_ptr<AppConfig> AppConfig::k_config;

void AppConfig::initInstance(const std::string& fileName)
{
    k_config.reset(new AppConfig(fileName));
}

AppConfig::AppConfig(const std::string& fileName)
{
    load(fileName);
}

AppConfig::~AppConfig()
{
}

void AppConfig::load(const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::vector<JsonParamPtr> params{
        jsonParam(logFile_, {"logFile"}, true, nonempty(logFile_)),
        jsonParam(width_, {"window", "width"}, true, gt(width_, 400)),
        jsonParam(height_, {"window", "height"}, true, gt(height_, 400)),
        jsonParam(title_, {"window", "title"}, true, nonempty(title_))
    };

    parse(params, doc);
}

} // end of namespace commonlib
} // end of namespace mcdane

