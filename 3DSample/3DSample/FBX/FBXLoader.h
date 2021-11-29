#ifndef __FBX_LOADER_H__
#define __FBX_LOADER_H__

#include <fbxsdk.h>
#include <vector>
#include <string>

#pragma comment(lib, "libfbxsdk-mt.lib")
#pragma comment(lib, "libxml2-mt.lib")
#pragma comment(lib, "zlib-mt.lib")

namespace ggfbx
{

//----- 定義
// 
struct Vector2
{
	float x, y;
};
struct Vector3
{
	float x, y, z;
};
union Matrix
{
	struct
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};
	float m[4][4];
	float a[16];
};
struct Color
{
	float r, g, b, a;
};


// 回転順序
enum RotateOrder
{
	ROTATE_XYZ,
	ROTATE_ZXY,
};
// マッピング情報
enum Mapping
{
	MAPPING_VERTEX,
	MAPPING_INDEX,
};


// メッシュ情報
struct MeshInfo
{
	// 法線情報
	struct NormalInfo
	{
		typedef std::vector<Vector3> List;
		Mapping	mapping;
		List	list;
	};
	// UV情報
	struct UVInfo
	{
		typedef std::vector<Vector2> List;
		Mapping	mapping;
		List	list;
	};
	typedef std::vector<UVInfo> UVList;
	// スキン
	struct SkinInfo
	{
		struct WeightInfo
		{
			struct WeightValue
			{
				long index;
				float weight;
			};
			static const long WEIGHT_NUM_MAX = 4;
			WeightValue value[WEIGHT_NUM_MAX];
		};
		struct BoneInfo
		{
			std::string name;
			float offset[4][4];
		};
		typedef std::vector<WeightInfo> WeightList;
		typedef std::vector<BoneInfo> BoneList;

		WeightList		weightList;
		BoneList		boneList;
	};

	typedef std::vector<long> IndexList;
	typedef std::vector<Vector3> VertexList;
	typedef std::string MaterialName;

	IndexList		indexList;		///< インデックス情報
	VertexList		vertexList;		///< 頂点情報
	NormalInfo		normalInfo;		///< 法線情報
	UVList			uvList;			///< UV情報
	MaterialName	materialName;	///< マテリアル名(マテリアルで分割してるので一つ
	SkinInfo		skinInfo;		///< スキン情報
	Matrix			transform;		///< 姿勢情報
};
typedef std::vector<MeshInfo> MeshList;

// ボーン情報
struct BoneInfo
{
	typedef std::vector<long> ChildList;

	std::string		name;		///< ボーン名
	Vector3			translate;	///< 移動値
	Vector3			rotation;	///< 回転値
	Vector3			scale;		///< 拡大縮小
	Vector3			preRotate;	///< 事前回転
	RotateOrder		order;		///< 回転順序
	ChildList		children;	///< 子要素
};
typedef std::vector<BoneInfo> BoneList;

// ボーン一覧
struct BoneListInfo
{
	int root;
	BoneList list;
};

// マテリアル情報
struct MaterialInfo
{
	struct Lambert
	{
		Color	ambient;
		Color	diffuse;
		Color	emissive;
		Vector3	bump;
		float	transparency;
	};
	struct Phong
	{
		Color	specular;
		float	shininess;
		float	reflectivity;
	};
	typedef std::vector<std::string> TextureList;

	std::string name;			///< マテリアル名
	TextureList textureList;	///< テクスチャ名
	Lambert		*pLambert;		///< ランバート情報
	Phong		*pPhong;		///< フォン情報
};
typedef std::vector<MaterialInfo> MaterialList;

// アニメーション情報
struct AnimationInfo
{
	struct CurveInfo
	{
		enum Channels
		{
			TRANSLATION_X,
			TRANSLATION_Y,
			TRANSLATION_Z,
			ROTATION_X,
			ROTATION_Y,
			ROTATION_Z,
			SCALING_X,
			SCALING_Y,
			SCALING_Z,
			CHANNEL_MAX
		};
		struct KeyInfo
		{
			long	frame;
			float	value;
		};
		typedef std::vector<KeyInfo> List;

		std::string		name;					///< 対応するボーン名
		List			keyList[CHANNEL_MAX];	///< チャンネルごとのキー情報
	};
	typedef std::vector<CurveInfo> List;

	long		totalFrame;		///< アニメーション時間
	List		curveList;		///< アニメ情報
};

/// ログ出力関数型定義
typedef void(*LogCallbackFunc)(const char *);


/// @brief 初期化
void Initialize();

/// @brief 終了処理
void Terminate();

/// @brief FBX読み込み
/// @param [in] fileName ファイル名
/// @param [out] meshList メッシュ読み込み先
/// @param [out] boneList ボーン読み込み先
/// @param [out] materiaList マテリアル読み込み先
/// @param [out] anime アニメーション読み込み先
/// @param [in] isMirror モデル反転
/// @return 読み込み結果
bool Load(const char* pFileName, MeshList* pMeshList, BoneListInfo* pBoneListInfo, MaterialList* pMaterialList, AnimationInfo* pAnime);

/// @brief 解放処理
/// @param [out] meshList メッシュ
/// @param [out] boneList ボーン
/// @param [out] materiaList マテリアル
/// @param [out] anime アニメーション
void Cleanup(MeshList* pMeshList, BoneListInfo* pBoneListInfo, MaterialList* pMaterialList, AnimationInfo* pAnime);


/// @brief ログ処理関数の設定
/// @param [in] func コールバック関数
void SetLogCallbackFunc(LogCallbackFunc func);

/// @brief ログ出力
/// @param[in] format 出力フォーマット
/// @param[in] ... 可変個引数
void LogOutput(const char *format, ...);

}; // fbx

#endif // __FBX_LOADER_H__