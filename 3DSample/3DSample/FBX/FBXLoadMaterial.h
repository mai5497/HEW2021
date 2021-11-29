#ifndef __FBX_LOAD_MATERIAL_H__
#define __FBX_LOAD_MATERIAL_H__

#include "FBXLoader.h"

namespace ggfbx {

void CleanupMaterial(MaterialList &materialList);
void GetMaterial(FbxScene *pScene, MaterialList &materialList);

}; // fbx

#endif // __FBX_LOAD_MATERIAL_H__