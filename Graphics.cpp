
#include "pch.h"
#include "Graphics.h"




int Graphics::d3D9Init(HWND hWnd ) {

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dObject))) {
		exit(1);
	}

	ZeroMemory(&d3dparams, sizeof(d3dparams));

	d3dparams.BackBufferWidth = overlayWindowWidth;
	d3dparams.BackBufferHeight = overlayWindowHeight;
	d3dparams.Windowed = TRUE;
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = hWnd;
	d3dparams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dparams.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dparams.EnableAutoDepthStencil = TRUE;
	d3dparams.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT res = d3dObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dparams, 0, &d3dDevice);

	if (FAILED(res)) {
		std::wstring ws(DXGetErrorString(res));
		std::string str(ws.begin(), ws.end());
		std::wstring ws2(DXGetErrorDescription(res));
		std::string str2(ws2.begin(), ws2.end());
		std::string error = "Error: " + str + " error description: " + str2;
		

		exit(1);
	}

	D3DXCreateFont(d3dDevice, 12, 0, FW_LIGHT , 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial", &d3dFont);

	D3DXCreateLine(d3dDevice, &d3dLine);

	return 0;

}



Graphics::Graphics(HWND overLayhandle, int sWidth, int sHeight) : overlayWindowWidth(sWidth) , overlayWindowHeight(sHeight)
{
	d3D9Init(overLayhandle);
}

Graphics::~Graphics()
{
	if(d3dLine)
		d3dLine->Release();
	if(d3dFont)
			d3dFont->Release();
	if(d3dDevice)
		d3dDevice->Release();
	if(d3dObject)
		d3dObject->Release();

}


int Graphics::BeginScene()
{
	if (d3dDevice == nullptr)
		return 1;
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	d3dDevice->BeginScene();

	return 0;
}


int Graphics::EndScene()
{
	if (d3dDevice == nullptr)
		return 1;
	d3dDevice->EndScene();
	d3dDevice->PresentEx(0, 0, 0, 0, 0);

	return 0;
}


void Graphics::drawText(char* String, int x, int y, D3DCOLOR color)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y ;
	d3dFont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, color);
}


void Graphics::DrawLine(int x1, int y1, int x2, int y2, D3DCOLOR color, float px)
{
	D3DXVECTOR2 pionts[2];

	d3dLine->SetWidth(px);

	pionts[0].x = x1;
	pionts[0].y = y1 ;

	pionts[1].x = x2;
	pionts[1].y = y2;

	d3dLine->Draw(pionts, 2, color);

}


void Graphics::DrawBox(int x, float y, int width, int height, int px, D3DCOLOR color)
{
	D3DXVECTOR2 points[5];
	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width, y );
	points[2] = D3DXVECTOR2(x + width, y + height);
	points[3] = D3DXVECTOR2(x, y + height );
	points[4] = D3DXVECTOR2(x, y);
	d3dLine->SetWidth(px);
	d3dLine->Draw(points, 5, color);
}