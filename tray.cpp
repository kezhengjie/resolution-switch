#include <windows.h>
#include <shellapi.h>

#define ID_TRAY_ICON 1001
#define ID_TRAY_EXIT 1002
#define WM_TRAYICON (WM_USER + 1)

// 全局变量
HINSTANCE hInst;
NOTIFYICONDATA nid;
HMENU hMenu;

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateTrayIcon(HWND hwnd);
void ShowContextMenu(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("TrayDemo");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    hInst = hInstance;

    // 注册窗口类
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("程序需要Windows NT！"), 
                   szAppName, MB_ICONERROR);
        return 0;
    }

    // 创建窗口（隐藏）
    hwnd = CreateWindow(szAppName, 
                        TEXT("系统托盘演示"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    // 创建系统托盘图标
    CreateTrayIcon(hwnd);

    // 创建右键菜单
    hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, TEXT("退出"));

    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// 创建系统托盘图标
void CreateTrayIcon(HWND hwnd)
{
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAY_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 使用默认图标
    
    // 设置提示文本
    lstrcpy(nid.szTip, TEXT("系统托盘演示程序"));
    
    Shell_NotifyIcon(NIM_ADD, &nid);
}

// 显示上下文菜单
void ShowContextMenu(HWND hwnd)
{
    POINT pt;
    GetCursorPos(&pt);
    
    SetForegroundWindow(hwnd);
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
    PostMessage(hwnd, WM_NULL, 0, 0);
}

// 窗口过程
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
                         WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_TRAYICON:
            {
                if (lParam == WM_RBUTTONUP)
                {
                    ShowContextMenu(hwnd);
                }
                else if (lParam == WM_LBUTTONDBLCLK)
                {
                    MessageBox(hwnd, 
                              TEXT("这是系统托盘演示程序！"), 
                              TEXT("信息"),
                              MB_OK | MB_ICONINFORMATION);
                }
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case ID_TRAY_EXIT:
                    // 移除托盘图标并退出
                    Shell_NotifyIcon(NIM_DELETE, &nid);
                    DestroyMenu(hMenu);
                    PostQuitMessage(0);
                    break;
            }
            break;

        case WM_DESTROY:
            Shell_NotifyIcon(NIM_DELETE, &nid);
            DestroyMenu(hMenu);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}