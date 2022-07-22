#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_constants.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

void initVertexArray(VertexArray& va,
                     const rapidjson::Value& v,
                     const std::string& dataDir)
{
    std::vector<std::string> files;
    std::vector<JsonParamPtr> params{
        jsonParam(files, "data_files")
    };

    parse(params, v);

    if (files.empty())
    {
        THROW_EXCEPT(ParseException, "Empty data for VertexArray");
    }

    std::vector<std::vector<Vector2>> data;
    std::vector<BufferBlock> blocks;

    data.resize(files.size());
    blocks.resize(files.size());
    for (unsigned int i = 0; i < files.size(); ++i)
    {
        readList(data[i], constructPath({dataDir, files[i]}));
        blocks[i].data_ = data[i].data();
        blocks[i].numVertices_ = data[i].size();
        blocks[i].vertexSize_ = Constants::POS_SIZE;
        blocks[i].stride_ = 0;
    }

    va.load(blocks.begin(), blocks.end());
}

} // end of unnamed namespace

void GameLib::load(const AppConfig& cfg)
{
    initTextureLib(cfg.textureLibFile(), cfg.picDir());
    initVertexArrayLib(cfg.vertexArrayLibFile(), cfg.vertexArrayDataDir());
    initRectLib(cfg.rectLibFile());
    initComponentTemplateLib(cfg.componentTemplateLibFile());
    initTileTemplateLib(cfg.tileTemplateLibFile());
    initGoodieTemplateLib(cfg.goodieTemplateLibFile());
    initParticleEffectTemplateLib(cfg.particleEffectTemplateLibFile(),
                                  cfg.particleEffectDataDir());
    initProgressPieTemplateLib(cfg.progressPieTemplateLibFile());
    initMissileTemplateLib(cfg.missileTemplateLibFile());
    initAIRobotTemplateLib(cfg.aiRobotTemplateLibFile());
    playerTemplate_.init(cfg.playerTemplateFile(),
                         missileTemplateLib_,
                         componentTemplateLib_);
    aiLib_.init(cfg.chaseShootAIParamLibFile());

    calculateMaxObjSpan();
    calculateMaxCollideBreath();

    LOG_DEBUG << "maxObjSpan=" << maxObjSpan_
              << "maxCollideBreath=" << maxCollideBreath_
              << LOG_END;

    LOG_INFO << "GameLib loaded successfull" << LOG_END;
}

void GameLib::initTextureLib(const std::string& textureLibFile,
                             const std::string& picDir)
{
    auto parser = [&](Texture& texture,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        texture.init(v, picDir);
    };

    textureLib_.init(textureLibFile, parser);

    LOG_DEBUG << "textureLib loaded successfully" << LOG_END;
}

void GameLib::initVertexArrayLib(const std::string& vertexArrayLibFile,
                                 const std::string& dataDir)
{
    auto parser = [&](VertexArray& va,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        initVertexArray(va, v, dataDir);
    };

    vertexArrayLib_.init(vertexArrayLibFile, parser);

    LOG_DEBUG << "vertexArrayLib loaded successfully" << LOG_END;
}

void GameLib::initRectLib(const std::string& rectLibFile)
{
    auto parser = [&](Rectangle& rect,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        rect.init(v, true);
    };

    rectLib_.init(rectLibFile, parser);

    LOG_DEBUG << "rectLib loaded successfully" << LOG_END;
}

void GameLib::initComponentTemplateLib(
                    const std::string& componentTemplateLibFile)
{
    auto parser = [&](ComponentTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, textureLib_, rectLib_);
    };

    componentTemplateLib_.init(componentTemplateLibFile, parser);

    LOG_DEBUG << "componentTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initTileTemplateLib(const std::string& tileTemplateLibFile)
{
    auto parser = [&](TileTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, componentTemplateLib_);
    };

    tileTemplateLib_.init(tileTemplateLibFile, parser);

    LOG_DEBUG << "tileTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initGoodieTemplateLib(const std::string& goodieTemplateLibFile)
{
    auto parser = [&](GoodieTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        GoodieType type = toGoodieType(name);
        t.init(type, v, componentTemplateLib_);
    };

    goodieTemplateLib_.init(goodieTemplateLibFile, parser);

    LOG_DEBUG << "goodieTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initParticleEffectTemplateLib(
    const std::string& particleEffectTemplateLibFile,
    const std::string& dataDir)
{
    auto parser = [&](ParticleEffectTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, textureLib_, dataDir);
    };

    particleEffectTemplateLib_.init(particleEffectTemplateLibFile, parser);

    LOG_DEBUG << "particleEffectTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initProgressPieTemplateLib(
                            const std::string& progressPieTemplateLibFile)
{
    auto parser = [&](ProgressPieTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, vertexArrayLib_);
    };

    progressPieTemplateLib_.init(progressPieTemplateLibFile, parser);

    LOG_DEBUG << "progressPieTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initMissileTemplateLib(const std::string& missileTemplateLibFile)
{
    auto parser = [&](MissileTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, particleEffectTemplateLib_, componentTemplateLib_);
    };

    missileTemplateLib_.init(missileTemplateLibFile, parser);

    LOG_DEBUG << "missileTemplateLib loaded successfully" << LOG_END;
}

void GameLib::initAIRobotTemplateLib(const std::string& aiRobotTemplateLibFile)
{
    auto parser = [&](AIRobotTemplate& t,
                      const std::string& name,
                      const rapidjson::Value& v)
    {
        t.init(v, missileTemplateLib_, componentTemplateLib_);
    };

    aiRobotTemplateLib_.init(aiRobotTemplateLibFile, parser);

    LOG_DEBUG << "aiRobotTemplateLib loaded successfully" << LOG_END;
}

void GameLib::calculateMaxObjSpan()
{
    maxObjSpan_ = playerTemplate_.span();

    auto accessor = [this](const GameObjectTemplate& t)->bool
    {
        if (t.span() > maxObjSpan_)
        {
            maxObjSpan_ = t.span();
        }

        return true;
    };

    tileTemplateLib_.traverse(accessor);
    missileTemplateLib_.traverse(accessor);
    aiRobotTemplateLib_.traverse(accessor);
    particleEffectTemplateLib_.traverse(accessor);

    LOG_INFO << "maxObjSpan=" << maxObjSpan_ << LOG_END;
}

void GameLib::calculateMaxCollideBreath()
{
    maxCollideBreath_ = playerTemplate_.collideBreath();

    auto accessor = [this](const GameObjectTemplate& t)->bool
    {
        if (t.collideBreath() > maxCollideBreath_)
        {
            maxCollideBreath_ = t.collideBreath();
        }

        return true;
    };

    tileTemplateLib_.traverse(accessor);
    missileTemplateLib_.traverse(accessor);
    aiRobotTemplateLib_.traverse(accessor);

    LOG_INFO << "maxCollideBreath=" << maxCollideBreath_ << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

