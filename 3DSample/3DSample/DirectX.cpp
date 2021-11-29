#include "DirectX.h"

//--- グローバル変数
ID3D11Device *g_pDevice;
ID3D11DeviceContext *g_pContext;
IDXGISwapChain *g_pSwapChain;

//画面への出力
ID3D11RenderTargetView	*g_pRenderTarget;
//深度バッファ(Zバッファ、デプスバッファ
//2Dの描画は画面の後に描画されたものが画面の手前に来る
//3Dでそのまま描画を行うと、2Dと
//同じような表示になってしまう
//(前後関係がおかしくなる
//そこで、既に描画されたオブジェクト
//が画面から見てどの程度離れているか
//(深さ、深度値)を判断して、カメラの
//手前に来るオブジェクトが優先的に
//描画されるように制御を行う必要がある。
ID3D11DepthStencilView* g_pDepthStencil;

ID3D11BlendState* g_pBlendState[BLEND_MAX];
ID3D11RasterizerState* g_pRasterizer[2];


HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen)
{
	HRESULT	hr = E_FAIL;

	// スワップチェインの設定
	// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
	// マルチサンプリング、リフレッシュレートが設定できる
	// 複数のバックバッファが作成できる
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));					// ゼロクリア
	sd.BufferDesc.Width = width;						// バックバッファの幅
	sd.BufferDesc.Height = height;						// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
	sd.SampleDesc.Count = 1;		// マルチサンプルの数
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用方法
	sd.BufferCount = 1;									// バックバッファの数
	sd.OutputWindow = hWnd;			// 関連付けるウインドウ
	sd.Windowed = fullscreen ? FALSE : TRUE;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	
	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	UINT createDeviceFlags = 0;
	// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	// 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// ディスプレイデバイスのアダプタ（ＮＵＬＬの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&sd,					// スワップチェインの設定
			&g_pSwapChain,			// IDXGIDwapChainインタフェース	
			&g_pDevice,				// ID3D11Deviceインタフェース
			&featureLevel,		// サポートされている機能レベル
			&g_pContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//--- レンダリングターゲット
	// バックバッファのポインタを取得
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) { return hr; }
	// バックバッファへのポインタを指定してレンダーターゲットビューを作成
	hr = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTarget);
	SAFE_RELEASE(pBackBuffer);
	if (FAILED(hr)) { return hr; }

	//---深度バッファの作成
	//深度バッファとして使用する
	//テクスチャの作成
	ID3D11Texture2D* pDepthTexture = NULL;
	D3D11_TEXTURE2D_DESC depthTexDesc = {};
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.SampleDesc = sd.SampleDesc;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	//テクスチャの利用方法
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//テクスチャのフォーマット
	//本来の画像フォーマットはRGBA
	//各8bitのデータになる。深度値を
	//8bitで表そうとすると、256段階で
	//しか奥行きを表現できない
	//より詳細に奥行きを表現するために
	//深度バッファでは24bit、または32bit
	//使用して奥行きを表す画像フォーマットがある
	//注意点として、カメラの写す奥行きが
	//遠すぎると、微妙な前後関係が
	//データの丸め誤差として表現できなくなる
	//例えば、1m間隔の前後関係がある時
	//カメラの奥行きが10mだと奥行きの
	//差は0.1になる。奥行きが1000mだと
	//差が0.001となり、丸め誤差で差が
	//ないものとして扱われることがある
	//差がないと2つのオブジェクトが
	//同一の場所にあるものとして判断され
	//お互いに画面に映ろうとして、結果
	//その一部がちらつくことがある（Zファイティングってやつ）
	
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	hr = g_pDevice->CreateTexture2D(
		&depthTexDesc, NULL,
		&pDepthTexture);
	if (FAILED(hr)) { return E_FAIL; }

	//作成したテクスチャを使用して
	//深度バッファの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthTexDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = g_pDevice->CreateDepthStencilView(
		pDepthTexture, &dsvDesc,
		&g_pDepthStencil);
	if (FAILED(hr)) { return E_FAIL; }

	// 設定
	//2Dの描画を行うときは
	//Zバッファを設定しない(無効にする
	//3D描画では
	//Zバッファを設定する(有効にする
	g_pContext->OMSetRenderTargets(1, &g_pRenderTarget, g_pDepthStencil);

	//--- アルファブレンド
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND blendSetting[][4] = {
		{
			D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_ONE, D3D11_BLEND_ZERO
		},{
			D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE,
			D3D11_BLEND_ONE, D3D11_BLEND_ZERO
		},
	};
	D3D11_BLEND_OP blendOp[][2] = {
		{ D3D11_BLEND_OP_ADD, D3D11_BLEND_OP_ADD },
		{ D3D11_BLEND_OP_ADD, D3D11_BLEND_OP_ADD },
	};
	for (int i = 0; i < BLEND_MAX; ++i)
	{
		blendDesc.RenderTarget[0].SrcBlend = blendSetting[i][0];
		blendDesc.RenderTarget[0].DestBlend = blendSetting[i][1];
		blendDesc.RenderTarget[0].BlendOp = blendOp[i][0];
		blendDesc.RenderTarget[0].SrcBlendAlpha = blendSetting[i][2];
		blendDesc.RenderTarget[0].DestBlendAlpha = blendSetting[i][3];
		blendDesc.RenderTarget[0].BlendOpAlpha = blendOp[i][1];
		hr = g_pDevice->CreateBlendState(&blendDesc, &g_pBlendState[i]);
		if (FAILED(hr)) { return hr; }
	}
	SetBlendMode(BLEND_ALPHA);

	//ラスタライザ
	D3D11_RASTERIZER_DESC rrDesc = {};
	//カリング対象の面を設定
	rrDesc.CullMode = D3D11_CULL_BACK;
	//表示方法の設定
	rrDesc.FillMode = D3D11_FILL_SOLID;

	//通常設定
	hr = g_pDevice->CreateRasterizerState(
		&rrDesc, &g_pRasterizer[0]);
	if (FAILED(hr)) { return hr; }
	//カリング無効
	rrDesc.CullMode = D3D11_CULL_NONE;
	hr = g_pDevice->CreateRasterizerState(
		&rrDesc, &g_pRasterizer[1]);
	if (FAILED(hr)) { return hr; }


	D3D11_SAMPLER_DESC smpDesc;
	ID3D11SamplerState *pSampler;
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	// 拡大縮小時の色の取得方法
	// D3D11_FILTER_MIN_MAG_MIP_LINER;
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	// テクスチャの繰り返し方法
	// MIRROR
	// CLAMP
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = g_pDevice->CreateSamplerState(&smpDesc, &pSampler);
	if (FAILED(hr))
		return hr;
	g_pContext->PSSetSamplers(0, 1, &pSampler);
	SAFE_RELEASE(pSampler);


	// ビューポートを設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pContext->RSSetViewports(1, &vp);

	return S_OK;
}

void UninitDX()
{
	SAFE_RELEASE(g_pRasterizer[1]);
	SAFE_RELEASE(g_pRasterizer[0]);
	for (int i = 0; i < BLEND_MAX; ++i)
	{
		SAFE_RELEASE(g_pBlendState[i]);
	}

	SAFE_RELEASE(g_pDepthStencil);
	SAFE_RELEASE(g_pRenderTarget);

	g_pContext->ClearState();
	SAFE_RELEASE(g_pContext);

	g_pSwapChain->SetFullscreenState(false, NULL);
	SAFE_RELEASE(g_pSwapChain);

	SAFE_RELEASE(g_pDevice);
}


/**
* @brief 描画クリア
* @param[in] color 描画色
*/
void BeginDrawDX()
{
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	g_pContext->ClearRenderTargetView(g_pRenderTarget, color);
	g_pContext->ClearDepthStencilView(
		//初期化する深度バッファ
		g_pDepthStencil,
		//初期化する対象
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		//深度値を初期化したときの値
		//(カメラが映せる範囲は最終的に
		//0～1の範囲に丸められる。そのため、
		//1が一番奥になる
		1.0f,
		0);
}
void EndDrawDX()
{
	g_pSwapChain->Present(0, 0);
}


ID3D11Device *GetDevice()
{
	return g_pDevice;
}

ID3D11DeviceContext *GetContext()
{
	return g_pContext;
}


void SetBlendMode(BlendMode blend)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	g_pContext->OMSetBlendState(g_pBlendState[blend], blendFactor, 0xffffffff);
}

void EnableCulling(bool enable)
{
	g_pContext->RSSetState(
		g_pRasterizer[enable ? 0 : 1]
	);
}