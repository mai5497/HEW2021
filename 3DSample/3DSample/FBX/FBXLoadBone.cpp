#include "FBXLoadBone.h"
#include <assert.h>

namespace ggfbx {

int GetRootBone(FbxNode *pNode, BoneList &list);

//-----------------------------------------------------
//
/// @brief データクリア
//
//-----------------------------------------------------
void CleanupBone(BoneListInfo &boneListInfo)
{
	BoneList::iterator it = boneListInfo.list.begin();
	while (it != boneListInfo.list.end())
	{
		it->name.clear();
		it->translate.x = it->translate.y = it->translate.z = 0.0f;
		it->rotation.x = it->rotation.y = it->translate.z = 0.0f;
		it->scale.x = it->scale.y = it->scale.z = 0.0f;
		it->preRotate.x = it->preRotate.y = it->preRotate.z = 0.0f;
		it->order = ROTATE_XYZ;
		it->children.clear();
		++it;
	}
	boneListInfo.list.clear();
}

//-----------------------------------------------------
//
/// @brief データ取得
//
//-----------------------------------------------------
void GetBone(FbxScene *pScene, BoneListInfo &boneListInfo)
{
	CleanupBone(boneListInfo);
	boneListInfo.list.resize(pScene->GetMemberCount<FbxSkeleton>());
	BoneList::iterator it = boneListInfo.list.begin();
	while (it != boneListInfo.list.end())
	{
		FbxNode *pNode = pScene->GetMember<FbxSkeleton>(static_cast<int>(it - boneListInfo.list.begin()))->GetNode();
		BoneInfo &info = *it;

		// ボーン情報取得
		info.name = pNode->GetInitialName();
		FbxDouble3 trans = pNode->LclTranslation.Get();
		FbxDouble3 rotate = pNode->LclRotation.Get();
		FbxDouble3 scale = pNode->LclScaling.Get();
		FbxDouble3 preRotate = pNode->PreRotation.Get();
		info.translate.x = static_cast<float>(trans[0]);
		info.translate.y = static_cast<float>(trans[1]);
		info.translate.z = static_cast<float>(trans[2]);
		info.rotation.x = static_cast<float>(rotate[0]);
		info.rotation.y = static_cast<float>(rotate[1]);
		info.rotation.z = static_cast<float>(rotate[2]);
		info.scale.x = static_cast<float>(scale[0]);
		info.scale.y = static_cast<float>(scale[1]);
		info.scale.z = static_cast<float>(scale[2]);
		info.preRotate.x = static_cast<float>(preRotate[0]);
		info.preRotate.y = static_cast<float>(preRotate[1]);
		info.preRotate.z = static_cast<float>(preRotate[2]);

		FbxEuler::EOrder order;
		pNode->GetRotationOrder(FbxNode::eSourcePivot, order);
		switch (order)
		{
		case FbxEuler::EOrder::eOrderXYZ: info.order = ROTATE_XYZ; break;
		case FbxEuler::EOrder::eOrderZXY: info.order = ROTATE_ZXY; break;
		default: assert(""); break;
		}

		++it;
	}

	// 子要素の構築
	LogOutput("BoneNum : %d\n", boneListInfo.list.size());
	it = boneListInfo.list.begin();
	while (it != boneListInfo.list.end())
	{
		FbxNode *pNode = pScene->GetMember<FbxSkeleton>(static_cast<int>(it - boneListInfo.list.begin()))->GetNode();
		BoneInfo &info = *it;

		// データ出力
		LogOutput("========== BoneData[No.%d/Name:%s] ==========\n", it - boneListInfo.list.begin(), info.name.c_str());
		LogOutput("Translate(x/y/z) : %.3f/%.3f/%.3f\n", info.translate.x, info.translate.y, info.translate.z);
		LogOutput("Rotation (x/y/z) : %.3f/%.3f/%.3f\n", info.rotation.x, info.rotation.y, info.rotation.z);
		LogOutput("Scale    (x/y/z) : %.3f/%.3f/%.3f\n", info.scale.x, info.scale.y, info.scale.z);
		LogOutput("PreRotate(x/y/z) : %.3f/%.3f/%.3f\n", info.preRotate.x, info.preRotate.y, info.preRotate.z);
		LogOutput("Children(name(index)) :");

		// 構築
		for (int i = 0; i < pNode->GetChildCount(); ++i)
		{
			BoneList::iterator find = boneListInfo.list.begin();
			while (find != boneListInfo.list.end())
			{
				if (find->name == pNode->GetChild(i)->GetInitialName())
				{
					info.children.push_back(static_cast<int>(find - boneListInfo.list.begin()));
					LogOutput(" %s(%d)", find->name.c_str(), info.children.back());
					break;
				}
				++find;
			}
		}

		LogOutput("\n\n");
		++it;
	}

	// ルートボーン
	boneListInfo.root = GetRootBone(pScene->GetRootNode(), boneListInfo.list);
}


int GetRootBone(FbxNode *pNode, BoneList &list)
{
	int attrCnt = pNode->GetNodeAttributeCount();
	for (int i = 0; i < attrCnt; ++i)
	{
		FbxNodeAttribute* attr = pNode->GetNodeAttributeByIndex(i);
		if (attr->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			FbxNode *pBone = attr->GetNode();
			if (pBone != NULL)
			{
				const char *nodeName = pBone->GetInitialName();
				BoneList::iterator it = list.begin();
				while (it != list.end())
				{
					if (nodeName == it->name)
					{
						FbxNode *pP = pBone->GetParent();
						nodeName = pP->GetInitialName();
						return static_cast<int>(it - list.begin());
					}
					++it;
				}
			}
		}
	}

	int root = -1;
	for (int i = 0; i < pNode->GetChildCount() && root < 0; ++i)
	{
		root = GetRootBone(pNode->GetChild(i), list);
	}
	return root;
}

}; // fbx