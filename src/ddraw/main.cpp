#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>

typedef HRESULT(WINAPI* DirectDrawCreate_t)(GUID*, void**, void*);
typedef HRESULT(WINAPI* SetCooperativeLevel_t)(void*, HWND, DWORD);
typedef HRESULT(WINAPI* SetDisplayMode_t)(void*, DWORD, DWORD, DWORD);

DirectDrawCreate_t r_DirectDrawCreate = NULL;
SetCooperativeLevel_t r_SetCooperativeLevel = NULL;
SetDisplayMode_t r_SetDisplayMode = NULL;

HMODULE hSystemDDraw = NULL;

int hwnd_selectedMode = 0;
HMODULE g_hModule = NULL;

#define ID_COMBOBOX 101
#define ID_BUTTON 102

void GetDesktopResolution(int* horizontal, int* vertical) {
    *horizontal = GetSystemMetrics(SM_CXSCREEN);
    *vertical = GetSystemMetrics(SM_CYSCREEN);
}

LRESULT CALLBACK launcherWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hComboBox, hBtn;
    HFONT hFont;
    int h = 0;
    int v = 0;
    GetDesktopResolution(&h, &v);
    switch (msg) {
    case WM_CREATE:
        hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        CreateWindowA("STATIC", "Select the game mode", WS_VISIBLE | WS_CHILD, 
        20, 20, 200, 20, hWnd, NULL, g_hModule, NULL);

        hComboBox = CreateWindowA("COMBOBOX", NULL,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
            20, 50, 240, 200, hWnd, (HMENU)ID_COMBOBOX, g_hModule, NULL);

            SendMessageA(hComboBox, WM_SETFONT, (WPARAM)hFont, TRUE);
            // SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Window Mode (Recommended)");
            // SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Fullscreen (Can freeze)");
            SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"640x480 (Original)");
            SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"1280X720");
            char szDesktopRes[64];
            snprintf(szDesktopRes, sizeof(szDesktopRes), "%dx%d (Your resolution)", h, v);
            SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)szDesktopRes);
            SendMessageA(hComboBox, CB_SETCURSEL, 0, 0);

            hBtn = CreateWindowA("BUTTON", "Play",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                80, 100, 120, 30, hWnd, (HMENU)ID_BUTTON, g_hModule, NULL);
            SendMessageA(hBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON) {
            hwnd_selectedMode = SendMessageA(hComboBox, CB_GETCURSEL, 0, 0);
            PostQuitMessage(0);
        }
        break;

    case WM_CLOSE:
        ExitProcess(0);
        break;
    default:
        return DefWindowProcA(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void SelectResultionMode() {
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = launcherWndProc;
    wc.hInstance = g_hModule;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "D2Launcher";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    int scrW = GetSystemMetrics(SM_CXSCREEN);
    int srcH = GetSystemMetrics(SM_CYSCREEN);
    int w = 300, h = 200;
    int x = (scrW - w) / 2;
    int y = (srcH - h) / 2;

    HWND hWnd = CreateWindowA("D2Launcher", "Configuration = Detective Barbie II", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        x, y, w, h, NULL, NULL, g_hModule, NULL);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg),
        DispatchMessageA(&msg);
    }
}

HRESULT WINAPI fake_SetCooperativeLevel(void* self, HWND hWnd, DWORD dwFlags) {
    int h = 0;
    int v = 0;
    GetDesktopResolution(&h, &v);
    // 0x00000008 = DDSCL_NORMAL 
    if (hWnd) {
        LONG estilo = GetWindowLong(hWnd, GWL_STYLE);
        estilo &= ~WS_POPUP;
        estilo |= (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        SetWindowLong(hWnd, GWL_STYLE, estilo);
        if (hwnd_selectedMode == 0) {
            SetWindowPos(hWnd, NULL, 0, 0, 640, 480, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }
        else if (hwnd_selectedMode == 1) {
            SetWindowPos(hWnd, NULL, 0, 0, 1280, 720, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }
        else if (hwnd_selectedMode == 2) {
            SetWindowPos(hWnd, NULL, 0, 0, h, v, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }
        else {
            SetWindowPos(hWnd, NULL, 0, 0, 640, 480, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }
    }
    return r_SetCooperativeLevel(self, hWnd, 0x00000008);
}

HRESULT WINAPI fake_SetDisplayMode(void* self, DWORD width, DWORD height, DWORD bpp) {

    if (hwnd_selectedMode == 0)
        return 0;
    return r_SetDisplayMode(self, width, height, bpp);
}

void hookVTable(void* lpDD) {
    void** vtable = *(void***)lpDD;
    DWORD protect;

    int indexCoop = 20;
    r_SetCooperativeLevel = (SetCooperativeLevel_t)vtable[indexCoop];

    VirtualProtect(&vtable[indexCoop], sizeof(void*), PAGE_READWRITE, &protect);
    vtable[indexCoop] = (void*)fake_SetCooperativeLevel;
    VirtualProtect(&vtable[indexCoop], sizeof(void*), protect, &protect);

    int indexDisp = 21;
    r_SetDisplayMode = (SetDisplayMode_t)vtable[indexDisp];

    VirtualProtect(&vtable[indexDisp], sizeof(void*), PAGE_READWRITE, &protect);
    vtable[indexDisp] = (void*)fake_SetDisplayMode;
    VirtualProtect(&vtable[indexDisp], sizeof(void*), protect, &protect);
}

HRESULT WINAPI DirectDrawCreate(GUID* lpGUID, void** lplpDD, void* pUnkOuter) {
    if (!hSystemDDraw) {
    if (g_hModule == NULL) g_hModule = GetModuleHandle(NULL);
        SelectResultionMode();
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        strcat(path, "\\ddraw.dll");

        hSystemDDraw = LoadLibraryA(path);
        if (!hSystemDDraw) {
            MessageBoxA(NULL, "Erro Fatal: Nao achei ddraw.dll no System32", "Wrapper Error", MB_OK | MB_ICONERROR);
            return -1;
        }

        r_DirectDrawCreate = (DirectDrawCreate_t)GetProcAddress(hSystemDDraw, "DirectDrawCreate");
        if (!r_DirectDrawCreate) {
            MessageBoxA(NULL, "Erro: DDraw original invalido", "Wrapper Error", MB_OK | MB_ICONERROR);
            return -1;
        }
    }

    HRESULT hr = r_DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);

    if (hr == 0 && lplpDD && *lplpDD) {
        hookVTable(*lplpDD);
    }

    return hr;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);
    }
    return TRUE;
}