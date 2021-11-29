#include "FBXLoadMaterial.h"

namespace ggfbx {
	
//-----------------------------------------------------
//
/// @brief データクリア
//
//-----------------------------------------------------
void CleanupMaterial(MaterialList &materialList)
{
	MaterialList::iterator it = materialList.begin();
	while (it != materialList.end())
	{
		it->name.clear();
		it->textureList.clear();
		if (it->pLambert != NULL)
		{
			delete it->pLambert;
		}
		if (it->pPhong != NULL)
		{
			delete it->pPhong;
		}
		++it;
	}
	materialList.clear();
}

//-----------------------------------------------------
//
/// @brief データ取得
//
//-----------------------------------------------------
void GetMaterial(FbxScene *pScene, MaterialList &materialList)
{
	CleanupMaterial(materialList);
	materialList.resize(pScene->GetMaterialCount());
	MaterialList::iterator it = materialList.begin();
	LogOutput("MaterialNum : %d\n", materialList.size());
	while (it != materialList.end())
	{
		MaterialInfo &info = *it;
		FbxSurfaceMaterial *pMaterial = pScene->GetMaterial(static_cast<int>(it - materialList.begin()));
		it->name = pMaterial->GetInitialName();
		LogOutput("========== MaterialData[No.%d/Name:%s] ==========\n", it - materialList.begin(), it->name.c_str());

		// cgfxチェック
		const FbxImplementation *pImplementation = GetImplementation(pMaterial, FBXSDK_IMPLEMENTATION_CGFX);
		if (pImplementation != NULL) {
			// 未対応
			LogOutput("Unimplemented cgfx\n");
		}
		
		// Lambert
		if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
		{
			FbxSurfaceLambert *pLambert = static_cast<FbxSurfaceLambert*>(pMaterial);
			info.pLambert = new MaterialInfo::Lambert();
			MaterialInfo::Lambert *lambert = info.pLambert;
			// アンビエント
			lambert->ambient.r = static_cast<float>(pLambert->Ambient.Get()[0]);
			lambert->ambient.g = static_cast<float>(pLambert->Ambient.Get()[1]);
			lambert->ambient.b = static_cast<float>(pLambert->Ambient.Get()[2]);
			lambert->ambient.a = static_cast<float>(pLambert->AmbientFactor.Get());
			LogOutput("Ambient : %.2f, %.2f, %.2f, %.2f\n", lambert->ambient.r, lambert->ambient.g, lambert->ambient.b, lambert->ambient.a);
			// ディフューズ
			lambert->diffuse.r = static_cast<float>(pLambert->Diffuse.Get()[0]);
			lambert->diffuse.g = static_cast<float>(pLambert->Diffuse.Get()[1]);
			lambert->diffuse.b = static_cast<float>(pLambert->Diffuse.Get()[2]);
			lambert->diffuse.a = static_cast<float>(pLambert->DiffuseFactor.Get());
			LogOutput("Diffuse : %.2f, %.2f, %.2f, %.2f\n", lambert->diffuse.r, lambert->diffuse.g, lambert->diffuse.b, lambert->diffuse.a);
			// エミッシブ
			lambert->emissive.r = static_cast<float>(pLambert->Emissive.Get()[0]);
			lambert->emissive.g = static_cast<float>(pLambert->Emissive.Get()[1]);
			lambert->emissive.b = static_cast<float>(pLambert->Emissive.Get()[2]);
			lambert->emissive.a = static_cast<float>(pLambert->EmissiveFactor.Get());
			LogOutput("Emissive : %.2f, %.2f, %.2f, %.2f\n", lambert->emissive.r, lambert->emissive.g, lambert->emissive.b, lambert->emissive.a);
			// バンプ
			lambert->bump.x = static_cast<float>(pLambert->Bump.Get()[0]);
			lambert->bump.y = static_cast<float>(pLambert->Bump.Get()[1]);
			lambert->bump.z = static_cast<float>(pLambert->Bump.Get()[2]);
			LogOutput("Bump : %.3f, %.3f, %.3f\n", lambert->bump.x, lambert->bump.y, lambert->bump.z);
			// 透過度
			lambert->transparency = static_cast<float>(pLambert->TransparencyFactor.Get());
			LogOutput("Transparency : %.2f\n", lambert->transparency);
		}
		else
		{
			info.pLambert = NULL;
		}
		// Phong
		if (pMaterial->GetClassId().Is(FbxSurfacePhong::ClassId)) {
			FbxSurfacePhong* pPhong = static_cast<FbxSurfacePhong*>(pMaterial);
			info.pPhong = new MaterialInfo::Phong();
			MaterialInfo::Phong *phong = info.pPhong;
			// スペキュラ
			phong->specular.r = static_cast<float>(pPhong->Specular.Get()[0]);
			phong->specular.g = static_cast<float>(pPhong->Specular.Get()[1]);
			phong->specular.b = static_cast<float>(pPhong->Specular.Get()[2]);
			phong->specular.a = static_cast<float>(pPhong->SpecularFactor.Get());
			LogOutput("Specular : %.2f, %.2f, %.2f, %.2f\n", phong->specular.r, phong->specular.g, phong->specular.b, phong->specular.a);
			// 光沢
			phong->shininess = static_cast<float>(pPhong->Shininess.Get());
			LogOutput("Shininess : %.2f\n", phong->shininess);
			// 反射
			phong->reflectivity = static_cast<float>(pPhong->ReflectionFactor.Get());
			LogOutput("Reflectivity : %.2f\n", phong->reflectivity);
		}
		else
		{
			info.pPhong = NULL;
		}

		// テクスチャデータ取得
		FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
		if (fileTextureCount > 0)
		{
			for (int i = 0; i < fileTextureCount; ++i)
			{
				FbxFileTexture *texture = prop.GetSrcObject<FbxFileTexture>(i);
				if (texture)
				{
					it->textureList.push_back(texture->GetFileName());
					LogOutput("TextureName : %s\n",
						it->textureList[it->textureList.size() - 1].c_str());
				}
			}
		}

		LogOutput("\n");
		++it;
	}
}

}; // fbx