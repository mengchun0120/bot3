#include <cmath>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_math_utils.h>
#include <commonlib_collide.h>
#include <botlib_context.h>
#include <botlib_game_object_jsonizer.h>
#include <botlib_place_in_map_checker.h>
#include <botlib_player.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

class NonpassthroughCollideChecker {
public:
    NonpassthroughCollideChecker(const GameObject* obj, Vector2& delta1);

    inline bool collide() const;

    inline const Vector2& delta() const;

    bool operator()(GameObject* obj);

private:
    const GameObject* obj_;
    bool collide_;
    commonlib::Vector2 delta_;
};

NonpassthroughCollideChecker::NonpassthroughCollideChecker(const GameObject* obj,
                                                           Vector2& delta1)
    : obj_(obj)
    , collide_(false)
    , delta_(delta1)
{
}

bool NonpassthroughCollideChecker::collide() const
{
    return collide_;
}

const Vector2& NonpassthroughCollideChecker::delta() const
{
    return delta_;
}

bool NonpassthroughCollideChecker::operator()(GameObject* o)
{
    bool check = o != obj_ &&
                 o->state() == GameObjectState::ALIVE &&
                 (o->type() == GameObjectType::ROBOT ||
                  o->type() == GameObjectType::TILE);

    if (!check)
    {
        return true;
    }

    bool collide = checkRectCollideRect(delta_,
                                        obj_->collideRegion(),
                                        o->collideRegion(),
                                        delta_);

    if (collide)
    {
        collide_ = true;
    }

    return true;
}


bool presentObj(GameObject* obj)
{
    if (obj->state() == GameObjectState::DEAD)
    {
        return true;
    }

    obj->present();

    return true;
}

int GameMap::getLayer(GameObjectType t)
{
    switch(t)
    {
        case GameObjectType::TILE:
        case GameObjectType::GOODIE:
            return 0;
        case GameObjectType::ROBOT:
            return 1;
        case GameObjectType::MISSILE:
            return 2;
        case GameObjectType::EFFECT:
            return 3;
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid GameObjectType");
    }
}

void GameMap::init(unsigned int rows,
                   unsigned int cols,
                   float viewportWidth,
                   float viewportHeight,
                   float maxObjSpan,
                   float maxCollideBreath)
{
    using namespace std::placeholders;

    maxObjSpan_ = maxObjSpan;
    maxCollideBreath_ = maxCollideBreath;
    extraCell_ = static_cast<int>(ceil(maxObjSpan_ / k_cellBreath));
    initMapCells(rows, cols);
    setBoundary(rows, cols);
    setViewportSize(viewportWidth, viewportHeight);
    setViewportOrigin(minViewportOrigin_[0], minViewportOrigin_[1]);
    aiRobotCount_ = 0;
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

    if (obj->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(obj);
        if (robot->side() == Side::PLAYER)
        {
            player_ = static_cast<Player*>(obj);
            setViewportOrigin(player_->x(), player_->y());
        }
        else
        {
            ++aiRobotCount_;
        }
    }

    LOG_DEBUG << "added " << obj->type() << " " << obj->id() << LOG_END;
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

void GameMap::removeObj(GameObject* obj)
{
    if (obj->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(obj);
        if (robot->side() == Side::PLAYER)
        {
            player_ = nullptr;
        }
    }

    int layer = getLayer(obj->type());

    cells_[obj->row()][obj->col()][layer].remove(obj);
}

void GameMap::setViewportOrigin(float x, float y)
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
        startX = r.left() - maxCollideBreath_;
        endX = r.right() + deltaX + maxCollideBreath_;
    }
    else
    {
        startX = r.left() + deltaX - maxCollideBreath_;
        endX = r.right() + maxCollideBreath_;
    }

    if (std::signbit(deltaY))
    {
        startY = r.bottom() - maxCollideBreath_;
        endY = r.top() + deltaY + maxCollideBreath_;
    }
    else
    {
        startY = r.bottom() + deltaY - maxCollideBreath_;
        endY = r.top() + maxCollideBreath_;
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
                           int startLayer,
                           int layerCount)
{
    int endLayer = startLayer + layerCount - 1;

    for (int layer = startLayer; layer <= endLayer; ++layer)
    {
        for (int rowIdx = r.bottom(); rowIdx <= r.top(); ++rowIdx)
        {
            auto& row = cells_[rowIdx];
            for (int colIdx = r.left(); colIdx <= r.right(); ++colIdx)
            {
                GameObjectList& objs = row[colIdx][layer];
                GameObject* next;
                for (GameObject* obj = objs.first(); obj; obj = next)
                {
                    next = obj->next();
                    if (!accessor.run(obj))
                    {
                        return;
                    }
                }
            }
        }
    }
}

bool GameMap::checkCollision(Vector2& delta,
                             const GameObject* obj)
{
    bool collideBoundary = checkRectCollideBoundary(delta,
                                                    obj->collideRegion(),
                                                    boundary(),
                                                    delta);

    bool collideObjs = checkNonpassthroughCollide(delta, obj);

    return collideBoundary || collideObjs;
}

void GameMap::decreaseAIRobotCount()
{
    if (aiRobotCount_ <= 0)
    {
        LOG_WARN << "Something is wrong. No AI robot left!" << LOG_END;
        return;
    }

    --aiRobotCount_;
}

bool GameMap::canBePlaced(const commonlib::Vector2& pos,
                          float collideBreath)
{
    Region<float> region{pos[0]-collideBreath, pos[0]+collideBreath,
                         pos[1]-collideBreath, pos[1]+collideBreath};

    if (checkRectCollideBoundary(region, boundary()))
    {
        return false;
    }

    PlaceInMapChecker checker(region);
    accessRegion(getCollideArea(region), checker, 0, 2);

    return !checker.collide();
}

void GameMap::toJson(rapidjson::Document& doc)
{
    using namespace rapidjson;

    auto& allocator = doc.GetAllocator();

    doc.SetObject();
    doc.AddMember("rows", absRowCount(), allocator);
    doc.AddMember("cols", absColCount(), allocator);

    Value objects(kArrayType);

    GameObjectJsonizer jsonizer(objects, allocator);
    accessRegion(wholeArea(), jsonizer);

    doc.AddMember("objects", objects, allocator);
}

void GameMap::initMapCells(unsigned int rows, unsigned int cols)
{
    unsigned int rowCount = rows + extraCell_*2;
    unsigned int colCount = cols + extraCell_*2;
    auto objDeleter = [](GameObject* obj)
    {
        LOG_DEBUG << "deleted " << obj->type() << " " << obj->id() << LOG_END;
        delete obj;
    };

    cells_.resize(rowCount);
    for (auto rowIt = cells_.begin(); rowIt != cells_.end(); ++rowIt)
    {
        rowIt->resize(colCount);

        for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt)
        {
            for (auto listIt = colIt->begin(); listIt != colIt->end(); ++listIt)
            {
                listIt->setDeleter(objDeleter);
            }
        }
    }
}

void GameMap::setBoundary(unsigned int rows, unsigned int cols)
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
    SimpleShaderProgram& program = Context::graphics().simpleShader();
    program.use();
    program.setViewportSize(viewportSize_);
    program.setViewportOrigin(viewportOrigin_);
    traverse(presentArea_, presentObj, 0, 3);
}

void GameMap::presentParticleEffects()
{
    ParticleShaderProgram& program = Context::graphics().particleShader();
    program.use();
    program.setViewportSize(viewportSize_);
    program.setViewportOrigin(viewportOrigin_);
    traverse(presentArea_, presentObj, 3, 1);
}

bool GameMap::checkNonpassthroughCollide(commonlib::Vector2& delta,
                                         const GameObject* obj)
{
    NonpassthroughCollideChecker checker(obj, delta);
    Region<int> area = getCollideArea(obj->collideRegion(), delta[0], delta[1]);

    traverse(area, checker, 0, 2);

    delta = checker.delta();

    return checker.collide();
}

std::string GameMap::detail()
{
    std::ostringstream oss;
    for (int r = 0; r < rowCount(); ++r)
    {
        for (int c = 0; c < colCount(); ++c)
        {
            for (int i = 0; i < 4; ++i)
            {
                auto& q = cells_[r][c][i];
                if (q.empty())
                {
                    continue;
                }

                oss << r << ":" << c << ":" << i << " ";
                for (GameObject* o = q.first(); o; o = o->next())
                {
                    oss << o->type() << ":" << o->id();
                }
                oss << std::endl;
            }
        }
    }
    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane

