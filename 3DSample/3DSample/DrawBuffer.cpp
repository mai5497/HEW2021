#include "DrawBuffer.h"

DrawBuffer::DrawBuffer()
	:m_pVertexBuffer(NULL)
	,m_vtxSize(0)
	,m_vtxCount(0)
	,m_pIndexBuffer(NULL)
	,m_idxCount(0)
{

}

DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}

HRESULT DrawBuffer::CreateVertexBuffer(void* pVtx,UINT size,UINT count,bool isWrite/* = true*/)
{
	//作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	//バッファの大きさ
	bufDesc.ByteWidth = size * count;
	//バッファの使用方法
	if (isWrite){
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	
	//バッファの利用先
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	//初期化に使うデータのアドレスの指定
	subResource.pSysMem = pVtx;

	//頂点バッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pVertexBuffer
	);

	//そのほかの情報を設定
	if (SUCCEEDED(hr)){
		m_vtxSize = size;
		m_vtxCount = count;
	}
	return hr;
}

HRESULT DrawBuffer::CreateIndexBuffer(
	const long* pIdx, UINT count)
{
	//バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = sizeof(long)* count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	//インデックスバッファ生成
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pIndexBuffer);
	if (SUCCEEDED(hr)){
		m_idxCount = count;
	}
	return hr;
}

//バッファの書き込み
void DrawBuffer::Write(void* pData)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(
		m_pVertexBuffer,0,
		D3D11_MAP_WRITE_DISCARD,
		0,&mapResource);
	//Msp関数で書き込み出来OKであれば実行
	if (SUCCEEDED(hr)){
		memcpy_s(
			mapResource.pData,
			m_vtxSize * m_vtxCount,
			pData,
			m_vtxSize * m_vtxCount);
	}

	//書き込み完了
	pContext->Unmap(m_pVertexBuffer, 0);
}

void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext =
		GetContext();
	//頂点一つ当たりの大きさ
	UINT stride = m_vtxSize;
	//頂点データの読み取り開始位置
	UINT offset = 0;

	//プリミティブの設定
	//TriangleList...頂点を3つずつに区切って描画
	//TriangleStrip...参照場所を一つずつずらしながら描画
	pContext->IASetPrimitiveTopology(primitive);

	//描画に使用するバッファの設定
	pContext->IASetVertexBuffers(
		0,		//GPUへの割り当て先
		1,		//頂点バッファの数
		&m_pVertexBuffer,	//頂点バッファ
		&stride,	//頂点のサイズ
		&offset		//読み取り開始位置
	);

	//描画
	//インデクスバッファの有無で
	//描画処理が若干異なる
	if (m_idxCount > 0){
		//描画に使用するインデックスバッファ
		//バッファを設定
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			//インデックス一つ当たりの大きさ
			//4byte = 32bit
			//2byte = 16bit
			DXGI_FORMAT_R32_UINT,
			0);

		//インデックスバッファを使用して描画
		pContext->DrawIndexed(
			m_idxCount, 0, 0);
	}
	else{
		//頂点バッファのみで描画
		pContext->Draw(m_vtxCount, 0);
	}
	
}
