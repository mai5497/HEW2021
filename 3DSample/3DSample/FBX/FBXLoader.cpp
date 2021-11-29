#include "FBXLoader.h"
#include "FBXLoadMesh.h"
#include "FBXLoadBone.h"
#include "FBXLoadMaterial.h"
#include "FBXLoadAnimation.h"

namespace ggfbx
{

FbxManager *g_pManager = NULL;
LogCallbackFunc g_LogFunc = NULL;

//-----------------------------------------------------
//
/// @brief 初期化
//
//-----------------------------------------------------
void Initialize()
{
	g_pManager = FbxManager::Create();

	FbxIOSettings *pIO = FbxIOSettings::Create(g_pManager, IOSROOT);
	g_pManager->SetIOSettings(pIO);
	LogOutput("[FBXLoadInitialize]\nstart\n");
}

//-----------------------------------------------------
//
/// @brief 終了処理
//
//-----------------------------------------------------
void Terminate()
{
	g_pManager->Destroy();
	LogOutput("[FBXLoadInitialize]\nend\n");
}

//-----------------------------------------------------
//
/// @brief FBX読み込み
/// @param [in] fileName ファイル名
/// @param [out] meshList メッシュ読み込み先
/// @param [out] boneListInfo ボーン読み込み先
/// @param [out] materialList マテリアル読み込み先
/// @param [out] anime アニメーション読み込み先
/// @param [in] isMirror モデル反転
/// @return 読み込み結果
//
//-----------------------------------------------------
bool Load(const char* pFileName, MeshList* pMeshList, BoneListInfo* pBoneListInfo, MaterialList* pMaterialList, AnimationInfo* pAnime)
{
	LogOutput("[FBXLoad]\n");
	LogOutput("FileName: %s\n", pFileName);

	// 読み込み初期化
	FbxImporter *pImporter = FbxImporter::Create(g_pManager, "");
	if (!pImporter->Initialize(pFileName, -1, g_pManager->GetIOSettings()))
	{
		LogOutput("\nfailed...\n");
		return false;
	}

	// 読み込み
	FbxScene *pScene = FbxScene::Create(g_pManager, "originalScene");
	pImporter->Import(pScene);
	// 三角化
	FbxGeometryConverter geometryConverter(g_pManager);
	geometryConverter.Triangulate(pScene, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(pScene);
	// マテリアルで分割
	geometryConverter.SplitMeshesPerMaterial(pScene, true);

	// メッシュデータ取得
	if (pMeshList != nullptr)
	{
		GetMesh(pScene, *pMeshList);
	}

	// マテリアルデータ取得
	if (pMaterialList != nullptr)
	{
		GetMaterial(pScene, *pMaterialList);
	}

	// ボーンデータ取得
	if (pBoneListInfo != nullptr)
	{
		GetBone(pScene, *pBoneListInfo);
	}

	// アニメーションデータ取得
	if (pAnime != nullptr)
	{
		GetAnimation(pScene, *pAnime);
	}

	pImporter->Destroy();
	LogOutput("\nsucsess!\n");
	return true;
}

//-----------------------------------------------------
//
/// @brief 解放処理
/// @param [out] meshList メッシュ
/// @param [out] boneList ボーン
/// @param [out] materiaList マテリアル
/// @param [out] anime アニメーション
//
//-----------------------------------------------------
void Cleanup(MeshList* pMeshList, BoneListInfo* pBoneListInfo, MaterialList* pMaterialList, AnimationInfo* pAnime)
{
	if (pMeshList != nullptr) { CleanupMesh(*pMeshList); }
	if (pBoneListInfo != nullptr) { CleanupBone(*pBoneListInfo); }
	if (pMaterialList != nullptr) { CleanupMaterial(*pMaterialList); }
	if (pAnime != nullptr) { CleanupAnimation(*pAnime); }
}

//-----------------------------------------------------
//
/// @brief ログ処理関数の設定
/// @param [in] func コールバック関数
//
//-----------------------------------------------------
void SetLogCallbackFunc(LogCallbackFunc func)
{
	g_LogFunc = func;
}

//-----------------------------------------------------
//
/// @brief ログ出力
/// @param[in] format 出力フォーマット
/// @param[in] ... 可変個引数
//
//-----------------------------------------------------
void LogOutput(const char *format, ...)
{
	if (g_LogFunc != NULL){
		va_list args;
		char buf[1024];
		va_start(args, format);
		vsprintf_s(buf, sizeof(buf), format, args);
		g_LogFunc(buf);
		va_end(args);
	}
}

}; // fbx

// EOF