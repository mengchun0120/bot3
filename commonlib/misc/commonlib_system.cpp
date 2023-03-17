#include <commonlib_system.h>

namespace mcdane {
namespace commonlib {

#ifdef __ANDROID__
static AAssetManager *k_assetManager;

void setAssetManager(AAssetManager *mgr)
{
    k_assetManager = mgr;
}

AAssetManager *assetManager()
{
    return k_assetManager;
}
#endif

} // end of namespace commonlib
} // end of namespace mcdane
