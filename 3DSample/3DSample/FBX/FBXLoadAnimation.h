#ifndef __FBX_LOAD_ANIMATION_H__
#define __FBX_LOAD_ANIMATION_H__

#include "FBXLoader.h"

namespace ggfbx {

void CleanupAnimation(AnimationInfo &anime);
void GetAnimation(FbxScene *pScene, AnimationInfo &anime);

}; // fbx

#endif // __FBX_LOAD_ANIMATION_H__