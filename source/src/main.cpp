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

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight


////  �O���[�o���ϐ��錾

LPD3DXSPRITE lpSprite;	// �X�v���C�g
LPD3DXFONT lpFont;		// �t�H���g

bool gameFullScreen;	// �t���X�N���[���itrue,false)

D3DLIGHT9 Light;		// ���C�g

//�P�ʍs��
D3DXMATRIX IdenMat;

// �\����
POINT BasePt;	// X.Y�������Ă���

// �������֐�
void Init(HWND a_hwnd)
{
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(a_hwnd, &BasePt); // �N���C�A���g���W�@���@�X�N���[�����W��
	SetCursorPos(BasePt.x, BasePt.y);
	// �J�[�\��������
	ShowCursor(FALSE);

	// �P�ʍs��̐���
	D3DXMatrixIdentity(&IdenMat);

	//---------------------- ���C�g ----------------------//

	// ���C�g�̐ݒ�
	Light.Type = D3DLIGHT_DIRECTIONAL;	// �f�B���N�V���i�����C�g (���s���C�g) = ���z�̂悤�Ȃ���

	// �X�y�L������L���ɂ���
	cdg.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// ���C�g�̐F�w�� (��{�͔�)
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	// �X�y�L�����̐F�w��
	Light.Specular.r = 1.0f;
	Light.Specular.g = 1.0f;
	Light.Specular.b = 1.0f;

	Light.Attenuation0 = 0.0f;
	Light.Attenuation1 = 0.2f;
	Light.Attenuation2 = 0.0f;

	// ���C�g�̕��� (���̐i�s���� = ���̕����x�N�g��)
	Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// ���W�ł͂Ȃ������x�N�g���I

	// ���C�g���Z�b�g����
	cdg.GetDevice()->SetLight(0, &Light);

	// ���C�g��L���ɂ���
	//cdg.GetDevice->LightEnable(0, TRUE);	// Enable = �L��

	csm.Init();
}

// �I�������֐�
void end()
{
	// �J�[�\���\�������ɖ߂�
	ShowCursor(TRUE);
}


// �X�V����
void Update(void)
{
	csm.Update();
}

// 3D�`��
void Render3D(void)
{
	csm.Render3D();
}

// 2D�`��
void Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	csm.Render2D();

	// �`��I��
	lpSprite->End();
}

void GameFrame(void)
{
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	cdg.GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);


	// �X�V����
	Update();


	// �`��J�n
	cdg.GetDevice()->BeginScene();

	//�J����
	csm.Camera();

	// 3D�`��
	Render3D();

	// 2D�`��
	Render2D();



	// �`��I��
	cdg.GetDevice()->EndScene();

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
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

	gameFullScreen = false;	// �E�B���h�E���[�h

	if (gameFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics�֘A-----------------------
	cdg.Init(hwnd, SCRW, SCRH, gameFullScreen);

	timeBeginPeriod(1);

	// �Q�[���Ɋւ��鏉�������� ---------------------------
	Init(hwnd);

	// �X�v���C�g�쐬
	D3DXCreateSprite(cdg.GetDevice(), &lpSprite);
	lpSprite->OnResetDevice();

	// �t�H���g�쐬
	D3DXCreateFont(cdg.GetDevice(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &lpFont);

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

	// �Q�[���Ɋւ���I������ ---------------------------
	end();
	cdg.Release();


	lpSprite->Release();	// �X�v���C�g
	lpFont->Release();		// �t�H���g


	timeEndPeriod(1);



	return (int)msg.wParam;
}