#include <cmath>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_math_utils.h>
#include <commonlib_collide.h>
#include <botlib_context.h>
#include <botlib_game_object_presenter.h>
#include <botlib_player.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

static int k_objTypeLayerMap[] = {
    0,     // tile
    1,     // robot
    2,     // missile
    3      // effect
};


inline int getLayer(GameObjectType type)
{
    return k_objTypeLayerMap[static_cast<int>(type)];
}

inline bool isPlayer(GameObject* obj)
{
    return obj->type() == GameObjectType::ROBOT &&
           static_cast<Robot*>(obj)->side() == Side::PLAYER;
}

} // end of unnamed namespace

void GameMap::init(unsigned int rows,
                   unsigned int cols,
                   float viewportWidth,
                   float viewportHeight,
                   float maxObjSpan,
                   float maxCollideBreath)
{
    maxObjSpan_ = maxObjSpan;
    maxCollideBreath_ = maxCollideBreath;
    extraCell_ = static_cast<int>(ceil(maxObjSpan_ / k_cellBreath));
    initMapCells(rows, cols);
    setBoundary(rows, cols);
    setViewportSize(viewportWidth, viewportHeight);
    setViewportOrigin(minViewportOrigin_[0], minViewportOrigin_[1]);
}

void GameMap::present()
{
    presentObjs();
    presentParticleEffects();
}

void GameMap::addObj(GameObject* obj)
{
    if (!obj)
    {
        THROW_EXCEPT(InvalidArgumentException, "obj is null");
    }

    int rowIdx = getCellIdx(obj->y());
    int colIdx = getCellIdx(obj->x());
    int layer = getLayer(obj->type());

    cells_[rowIdx][colIdx][layer].pushFront(obj);
    obj->setMapPos(rowIdx, colIdx);

    if (isPlayer(obj))
    {
        player_ = static_cast<Player*>(obj);
        setViewportOrigin(player_->x(), player_->y());
    }

    LOG_DEBUG << "addObj " << *obj << LOG_END;
}

void GameMap::repositionObj(GameObject* obj)
{
    if (!obj)
    {
        THROW_EXCEPT(InvalidArgumentException, "obj is null");
    }

    unsigned int rowIdx = getCellIdx(obj->y());
    unsigned int colIdx = getCellIdx(obj->x());
    int layer = getLayer(obj->type());

    if (rowIdx == obj->row() && colIdx == obj->col())
    {
        return;
    }

    cells_[obj->row()][obj->col()][layer].unlink(obj);
    cells_[rowIdx][colIdx][layer].pushFront(obj);
    obj->setMapPos(rowIdx, colIdx);
}

void GameMap::setViewportOrigin(float x,
                                float y)
{
    viewportOrigin_[0] = clamp(x, minViewportOrigin_[0], maxViewportOrigin_[0]);
    viewportOrigin_[1] = clamp(y, minViewportOrigin_[1], maxViewportOrigin_[1]);
    viewportAnchor_ = viewportOrigin_ - viewportHalfSize_;
    resetViewableRegion();
    resetPresentArea();
}

Region<int> GameMap::getCollideArea(const Region<float>& r,
                                    float deltaX,
                                    float deltaY) const
{
    float startX, endX, startY, endY;

    if (std::signbit(deltaX))
    {
        startX = r.left() + deltaX - maxCollideBreath_;
        endX = r.right() + maxCollideBreath_;
    }
    else
    {
        startX = r.left() - maxCollideBreath_;
        endX = r.right() + deltaX + maxCollideBreath_;
    }

    if (std::signbit(deltaY))
    {
        startY = r.bottom() + deltaY - maxCollideBreath_;
        endY = r.top() + maxCollideBreath_;
    }
    else
    {
        startY = r.bottom() - maxCollideBreath_;
        endY = r.top() + deltaY + maxCollideBreath_;
    }

    int bottom = clamp(getCellIdx(startY), 0, rowCount()-1);
    int top = clamp(getCellIdx(endY), 0, rowCount()-1);
    int left = clamp(getCellIdx(startX), 0, colCount()-1);
    int right = clamp(getCellIdx(endX), 0, colCount()-1);

    return Region<int>(left, right, bottom, top);
}

Region<int> GameMap::getCollideArea(const Region<float>& r) const
{
    float startX = r.left() - maxCollideBreath_;
    float endX = r.right() + maxCollideBreath_;
    float startY = r.bottom() - maxCollideBreath_;
    float endY = r.top() + maxCollideBreath_;

    int bottom = clamp(getCellIdx(startY), 0, rowCount()-1);
    int top = clamp(getCellIdx(endY), 0, rowCount()-1);
    int left = clamp(getCellIdx(startX), 0, colCount()-1);
    int right = clamp(getCellIdx(endX), 0, colCount()-1);

    return Region<int>(left, right, bottom, top);
}

void GameMap::accessRegion(const Region<int>& r,
                           GameMapAccessor& accessor,
                           bool deleteDeadObj)
{
    for (int layer = 0; layer < LAYER_COUNT; ++layer)
    {
        for (int rowIdx = r.bottom(); rowIdx <= r.top(); ++rowIdx)
        {
            auto& row = cells_[rowIdx];
            for (int colIdx = r.left(); colIdx <= r.right(); ++colIdx)
            {
                GameObjectList& objs = row[colIdx][layer];
                for (GameObject* obj = objs.first(); obj; obj = obj->next())
                {
                    accessor.run(objs, obj);
                }
            }
        }
    }
}

rapidjson::Value GameMap::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "GameMap", allocator);
    v.AddMember("maxObjSpan", maxObjSpan_, allocator);
    v.AddMember("maxCollideBreath", maxCollideBreath_, allocator);
    v.AddMember("extraCell", extraCell_, allocator);
    v.AddMember("viewportSize", jsonVal(viewportSize_, allocator), allocator);
    v.AddMember("minViewportOrigin", jsonVal(minViewportOrigin_, allocator),
                allocator);
    v.AddMember("maxViewportOrigin", jsonVal(maxViewportOrigin_, allocator),
                allocator);
    v.AddMember("viewportAnchor", jsonVal(viewportAnchor_, allocator), allocator);
    v.AddMember("boundary", boundary_.toJson(allocator), allocator);
    v.AddMember("viewableRegion", viewableRegion_.toJson(allocator), allocator);
    v.AddMember("presentArea", presentArea_.toJson(allocator), allocator);
    v.AddMember("rowCount", rowCount(), allocator);
    v.AddMember("colCount", colCount(), allocator);
    v.AddMember("cells", cellsToJson(allocator), allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

void GameMap::initMapCells(unsigned int rows,
                           unsigned int cols)
{
    unsigned int rowCount = rows + extraCell_*2;
    unsigned int colCount = cols + extraCell_*2;

    cells_.resize(rowCount);
    for (auto it = cells_.begin(); it != cells_.end(); ++it)
    {
        it->resize(colCount);
    }
}

void GameMap::setBoundary(unsigned int rows,
                          unsigned int cols)
{
    if (rows < k_minRows)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid rows " + std::to_string(rows));
    }

    if (cols < k_minCols)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid cols " + std::to_string(cols));
    }

    boundary_.init(0.0f, rows * k_cellBreath, 0.0f, cols * k_cellBreath);
}

void GameMap::setViewportSize(float viewportWidth,
                              float viewportHeight)
{
    if (viewportWidth <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportWidth " + std::to_string(viewportWidth));
    }

    if (viewportHeight <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportHeight " + std::to_string(viewportHeight));
    }

    viewportSize_.init({viewportWidth, viewportHeight});
    viewportHalfSize_ = viewportSize_ / 2.0f;
    minViewportOrigin_ = viewportHalfSize_;
    maxViewportOrigin_.init({width() - viewportHalfSize_[0],
                             height() - viewportHalfSize_[1]});

}

void GameMap::resetViewableRegion()
{
    viewableRegion_.init(viewportAnchor_[0] - maxObjSpan_,
                         viewportAnchor_[0] + viewportSize_[0] + maxObjSpan_,
                         viewportAnchor_[1] - maxObjSpan_,
                         viewportAnchor_[1] + viewportSize_[1] + maxObjSpan_);
}

void GameMap::resetPresentArea()
{
    int startRow = clamp(getCellIdx(viewableRegion_.bottom()), 0, rowCount()-1);
    int endRow = clamp(getCellIdx(viewableRegion_.top()), 0, rowCount()-1);
    int startCol = clamp(getCellIdx(viewableRegion_.left()), 0, colCount()-1);
    int endCol = clamp(getCellIdx(viewableRegion_.right()), 0, colCount()-1);

    presentArea_.init(startCol, endCol, startRow, endRow);
}

void GameMap::presentObjs()
{
    static GameObjectType presentOrder[] = {
        GameObjectType::TILE,
        GameObjectType::ROBOT,
        GameObjectType::MISSILE
    };
    constexpr int presentTypeCount = 3;

    SimpleShaderProgram& program = Context::graphics().simpleShader();
    program.use();
    program.setViewportSize(viewportSize_);
    program.setViewportOrigin(viewportOrigin_);

    for (unsigned int i = 0; i < presentTypeCount; ++i)
    {
        presenter_.reset(presentOrder[i]);
        accessRegion(presentArea_, presenter_, false);
    }
}

void GameMap::presentParticleEffects()
{
    ParticleShaderProgram& program = Context::graphics().particleShader();
    program.use();
    program.setViewportSize(viewportSize_);
    program.setViewportOrigin(viewportOrigin_);

    presenter_.reset(GameObjectType::EFFECT);
    accessRegion(presentArea_, presenter_, false);
}

rapidjson::Value GameMap::cellsToJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (unsigned int rowIdx = 0; rowIdx < cells_.size(); ++rowIdx)
    {
        const auto& row = cells_[rowIdx];
        for (unsigned int colIdx = 0; colIdx < row.size(); ++colIdx)
        {
            const Cell& cell = row[colIdx];
            for (int layer = 0; layer < GameMap::LAYER_COUNT; ++layer)
            {
                if (!cell[layer].empty())
                {
                    v.PushBack(jsonVal(cell[layer], allocator), allocator);
                }
            }
        }
    }

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

