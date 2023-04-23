#include <commonlib_log.h>
#include <botlib_game_object.h>
#include <botlib_game_obj_flag_resetter.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameObjFlagResetter::init(GameObjFlag flag)
{
    flag_ = flag;
}

bool GameObjFlagResetter::operator()(GameObject *obj)
{
    obj->setFlag(flag_, false);

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
