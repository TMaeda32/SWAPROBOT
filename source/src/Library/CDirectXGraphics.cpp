#include "CDirectXGraphics.h"



CDirectXGraphics::CDirectXGraphics()
{
}

bool CDirectXGraphics::Init(HWND hwnd, int SCRW, int SCRH, bool FullScreen)
{
	// Direct3D オブジェクトを作成
	mpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!mpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
		// 終了する
		return 0;
	}
	int adapter;

	// 使用するアダプタ番号
	adapter = D3DADAPTER_DEFAULT;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (FullScreen)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		mpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!FullScreen)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// デバイスの作成 - T&L HAL
	if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mpD3DDevice)))
	{
		// 失敗したので HAL で試行
		if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mpD3DDevice)))
		{
			// 失敗したので REF で試行
			if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mpD3DDevice)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);
				mpD3D->Release();
				// 終了する
				return 0;
			}
		}
	}

	// レンダリング・ステートを設定
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	mpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	mpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファブレンディング有効化
	mpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// アルファブレンディング方法を設定
	mpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// レンダリング時のアルファ値の計算方法の設定
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// テクスチャの色を使用
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// レンダリング時の色の計算方法の設定
	mpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//裏面カリング
	mpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// フィルタ設定
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ライト
	mpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		// TRUEにすると影が生まれる (LIGHTING = 光に関する計算)

	mpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// 頂点フォーマットの設定
	mpD3DDevice->SetFVF(FVF_VERTEX);

	// スプライト作成
	D3DXCreateSprite(mpD3DDevice, &mpSprite);
	mpSprite->OnResetDevice();

	// フォント作成
	D3DXCreateFont(mpD3DDevice, 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &mpFont);

	mpFont->OnResetDevice();

	return 1;
}

void CDirectXGraphics::Release()
{
	// Direct3D オブジェクトを解放
	mpD3DDevice->Release();
	mpD3D->Release();
}