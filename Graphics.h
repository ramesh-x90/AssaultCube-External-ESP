#pragma once

#include "OverlayWindow.h"

#define RED D3DCOLOR_RGBA(255,0,0,255)
#define GREEN D3DCOLOR_RGBA(0,255,0,255)
#define WHITE D3DCOLOR_RGBA(255,255,255,255)






class Graphics {
private:
	IDirect3D9Ex* d3dObject = NULL; //used to create device
	IDirect3DDevice9Ex* d3dDevice = NULL; //contains functions like begin and end scene 
	D3DPRESENT_PARAMETERS d3dparams; //parameters for creating device
	ID3DXFont* d3dFont = nullptr; // font used when displaying text
	ID3DXLine* d3dLine = nullptr; // font used when displaying text

	
private:
	int d3D9Init(HWND hWnd);



public:
	int overlayWindowWidth, overlayWindowHeight = 0;


public:
	Graphics(HWND overLayhandle , int sWidth , int sHeight);
	~Graphics();
	int BeginScene();

	void drawText(char* String, int x, int y, D3DCOLOR color);
	void DrawLine(int x1, int y1, int x2, int y2, D3DCOLOR color, float px);
	void DrawBox(int x, float y, int width, int height, int px, D3DCOLOR color);

	int EndScene();
};

/*


void GradientFunc(int x, int y, int w, int h, int r, int g, int b, int a);
//void DrawCenterLine(float x, float y, int r, int g, int b, int a);
void DrawLine(float x, float y, float xx, float yy, int r, int g, int b, int a);
void DrawFilled(float x, float y, float w, float h, int r, int g, int b, int a);
void DrawBox(float x, float y, float width, float height, float px, int r, int g, int b, int a);
void DrawGUIBox(float x, float y, float w, float h, int r, int g, int b, int a, int rr, int gg, int bb, int aa);
void DrawHealthBar(float x, float y, float w, float h, int r, int g, int b, int a);
void DrawHealthBarBack(float x, float y, float w, float h, int a);

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);
int DrawShadowString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);

*/

