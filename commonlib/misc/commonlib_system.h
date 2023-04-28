#ifndef INCLUDED_COMMONLIB_SYSTEM_H
#define INCLUDED_COMMONLIB_SYSTEM_H

#ifdef __ANDROID__
#include <android/asset_manager.h>
#endif

namespace mcdane {
namespace commonlib {

#ifdef __ANDROID__
void setAssetManager(AAssetManager *mgr);

AAssetManager *assetManager();
#endif

} // end of namespace commonlib
} // end of namespace mcdane

#endif
