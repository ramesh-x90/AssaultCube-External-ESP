#include "pch.h"
#include "OverlayWindow.h"
#include "Esp.h"



Graphics* graphics = nullptr;
Esp *esp;

void render();
void DrawCrossHair(Graphics*);
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM );


OverlayWindow::OverlayWindow(std::wstring name, WindowManager gWm ) : overlayWindowName(name) , gameWindowManager(gWm)
{

    if (!registerClass()) 
        throw std::exception("dx_overlay::create_overlay: failed to register wndclassex");

    createWindow();



}



void OverlayWindow::adjestWindow()
{
    RECT gameWindowRect = gameWindowManager.getWindowRect();

    int x = gameWindowRect.left;
    int y = gameWindowRect.top;
    int wWidth = gameWindowRect.right - gameWindowRect.left;
    int wHeight = gameWindowRect.bottom - gameWindowRect.top;

    MoveWindow(cWinHandle, x, y, wWidth, wHeight, true);
}


ATOM OverlayWindow::registerClass()
{

    WNDCLASSEX wincl;
    wincl.cbSize = sizeof(wincl);          // size of structure 
    wincl.style = CS_HREDRAW | CS_VREDRAW;               // redraw if size changes 
    wincl.lpfnWndProc = WndProc;    // points to window procedure 
    wincl.cbClsExtra = 0;                // no extra class memory 
    wincl.cbWndExtra = 0;                // no extra window memory 
    wincl.hInstance = hInstance;         // handle to instance 
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);              // predefined app. icon 
    wincl.hCursor = LoadCursor(NULL, IDC_CROSS);                    // predefined arrow 
    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    wincl.lpszMenuName = overlayWindowName.c_str();    // name of menu resource 
    wincl.lpszClassName = overlayWindowName.c_str();  // name of window class 
    wincl.hIconSm = NULL;

    return RegisterClassEx(&wincl);




}

void OverlayWindow::createWindow()
{


    int x = getWindowAttribute().x;
    int y = getWindowAttribute().y;
    int wWidth = getWindowAttribute().width;
    int wHeight = getWindowAttribute().height;

    cWinHandle = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, overlayWindowName.c_str(), overlayWindowName.c_str(), WS_POPUP,
        x, y, wWidth, wHeight, nullptr, nullptr, hInstance, nullptr
    );

    RECT abc = gameWindowManager.getWindowRect();

    AdjustWindowRect(&abc, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT , false);

    SetLayeredWindowAttributes(cWinHandle, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(cWinHandle, SW_SHOW);

    graphics = new Graphics(cWinHandle , getWindowAttribute().width , getWindowAttribute().height);
    esp = new Esp(EntityList::getInstance(), graphics);
}


void OverlayWindow::runEventLoop()
{
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        adjestWindow();

    }
}



OverlayWindow::~OverlayWindow()
{
    UnregisterClass(overlayWindowName.c_str() , hInstance);
    delete graphics;
    delete esp;
}


HWND OverlayWindow::getOverlayHandle()
{
    return cWinHandle;
}






WINDOW OverlayWindow::getWindowAttribute()
{
    WINDOW windowAtt;

    RECT gameWindowRect = gameWindowManager.getWindowRect();
    windowAtt.x = gameWindowRect.left;
    windowAtt.y = gameWindowRect.top;
    windowAtt.width = gameWindowRect.right - gameWindowRect.left;
    windowAtt.height = gameWindowRect.bottom - gameWindowRect.top - 26;
    return windowAtt;
}





LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message) {
    case WM_PAINT:
        render();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void render()
{
    graphics->BeginScene();
    DrawCrossHair(graphics);
    
    if(esp != nullptr)
        esp->drawPlayers(true,true, true, true);
    graphics->EndScene();

    //Sleep(1000);


}


void DrawCrossHair(Graphics* g)
{
    int lineLen = 3.0f;
    int x = g->overlayWindowWidth / 2;
    int y = g->overlayWindowHeight / 2;
    g->DrawLine(x - lineLen, y, x + lineLen, y, WHITE ,  2);
    g->DrawLine(x , y - lineLen, x , y + lineLen, WHITE, 2);

}