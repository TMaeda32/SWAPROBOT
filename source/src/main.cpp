#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#include "./Scene/CGame.h"
#include "Library/Library.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height


////  グローバル変数宣言

LPD3DXSPRITE lpSprite;	// スプライト
LPD3DXFONT lpFont;		// フォント

bool gameFullScreen;	// フルスクリーン（true,false)

D3DLIGHT9 Light;		// ライト

//単位行列
D3DXMATRIX IdenMat;

// 構造体
POINT BasePt;	// X.Yが入っている

// 初期化関数
void Init(HWND a_hwnd)
{
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(a_hwnd, &BasePt); // クライアント座標　→　スクリーン座標へ
	SetCursorPos(BasePt.x, BasePt.y);
	// カーソルを消す
	ShowCursor(FALSE);

	// 単位行列の生成
	D3DXMatrixIdentity(&IdenMat);

	//---------------------- ライト ----------------------//

	// ライトの設定
	Light.Type = D3DLIGHT_DIRECTIONAL;	// ディレクショナルライト (平行ライト) = 太陽のようなもの

	// スペキュラを有効にする
	cdg.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// ライトの色指定 (基本は白)
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	// スペキュラの色指定
	Light.Specular.r = 1.0f;
	Light.Specular.g = 1.0f;
	Light.Specular.b = 1.0f;

	Light.Attenuation0 = 0.0f;
	Light.Attenuation1 = 0.2f;
	Light.Attenuation2 = 0.0f;

	// ライトの方向 (光の進行方向 = 光の方向ベクトル)
	Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// 座標ではなく方向ベクトル！

	// ライトをセットする
	cdg.GetDevice()->SetLight(0, &Light);

	// ライトを有効にする
	//cdg.GetDevice->LightEnable(0, TRUE);	// Enable = 有効

	csm.Init();
}

// 終了処理関数
void end()
{
	// カーソル表示を元に戻す
	ShowCursor(TRUE);
}


// 更新処理
void Update(void)
{
	csm.Update();
}

// 3D描画
void Render3D(void)
{
	csm.Render3D();
}

// 2D描画
void Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	csm.Render2D();

	// 描画終了
	lpSprite->End();
}

void GameFrame(void)
{
	// バックバッファと Z バッファをクリア
	cdg.GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);


	// 更新処理
	Update();


	// 描画開始
	cdg.GetDevice()->BeginScene();

	//カメラ
	csm.Camera();

	// 3D描画
	Render3D();

	// 2D描画
	Render2D();



	// 描画終了
	cdg.GetDevice()->EndScene();

	// バックバッファをプライマリバッファにコピー
	cdg.GetDevice()->Present(NULL, NULL, NULL, NULL);
}

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdParam, int nCmdshow)
{
	MSG msg;

	HWND hwnd;
	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(
		0,
		szAppName,
		"SWAP ROBOT",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, hInst,
		NULL);

	if (!hwnd)return FALSE;

	ShowWindow(hwnd, nCmdshow);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

	gameFullScreen = false;	// ウィンドウモード

	if (gameFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics関連-----------------------
	cdg.Init(hwnd, SCRW, SCRH, gameFullScreen);

	timeBeginPeriod(1);

	// ゲームに関する初期化処理 ---------------------------
	Init(hwnd);

	// スプライト作成
	D3DXCreateSprite(cdg.GetDevice(), &lpSprite);
	lpSprite->OnResetDevice();

	// フォント作成
	D3DXCreateFont(cdg.GetDevice(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &lpFont);

	lpFont->OnResetDevice();

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			GameFrame();
		}
	}

	// ゲームに関する終了処理 ---------------------------
	end();
	cdg.Release();


	lpSprite->Release();	// スプライト
	lpFont->Release();		// フォント


	timeEndPeriod(1);



	return (int)msg.wParam;
}