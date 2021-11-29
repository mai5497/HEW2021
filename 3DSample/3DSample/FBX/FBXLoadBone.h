#ifndef __FBX_LOAD_BONE_H__
#define __FBX_LOAD_BONE_H__

#include "FBXLoader.h"

namespace ggfbx {

void CleanupBone(BoneListInfo &boneListInfo);
void GetBone(FbxScene *pScene, BoneListInfo &boneListInfo);

}; // fbx

#endif // __FBX_LOAD_BONE_H__