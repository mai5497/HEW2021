#ifndef __MODEL_H__
#define __MODEL_H__

#include "DrawBuffer.h"
#include "FBX/FBXPlayer.h"

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(const char* pFilePath);
	void Draw();

private:
	//ゲームのキャラクターは複数のパーツで成り立っている。
	//そのパーツ一つ一つをメッシュと呼ぶ。
	//基本的に一つのメッシュで一つの頂点バッファを持つ
	//モデルごとにメッシュの数が異なるため、
	//頂点バッファを動的に確保する
	DrawBuffer* m_pBuffer;

	FBXPlayer m_fbx;	//FBXファイル操作クラス
};

#endif	//__MODEL_H__