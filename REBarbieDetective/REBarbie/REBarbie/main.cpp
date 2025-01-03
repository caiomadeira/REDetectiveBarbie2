#include "framework.h"
#include "REBarbie.h"
#include <mmsystem.h> // timeGetTime()(WInMM.dll)
#include <ddraw.h> // DirectDrawCreate()(DDRAW.dll)
#include <dsound.h> // IDirectSound
#include <new>
#include <iostream>
#include <stdint.h>


#pragma comment(lib, "WinMM.lib") // A diretiva informa ao compilador pra automaticamente linkar a lib
#pragma comment(lib, "ddraw.lib")

#define MAX_LOADSTRING 100

// Variáveis Globais:
HINSTANCE hInst;                                // instância atual
WCHAR szTitle[MAX_LOADSTRING];                  // O texto da barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // o nome da classe da janela principal

// Declarações de encaminhamento de funções incluídas nesse módulo de código:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int MainGameWindow(HINSTANCE param_1, int nCmdShow, int param_2);


int __cdecl directDrawFailedInit(HWND windowIdentifier)

{
    //CHAR s[256];

    // FUN_0047e1e1
    // FUN_0047e1e1(s, (byte*)"DirectDraw initialization failed!!\nLocation Code: %u");
    DWORD errorCode = GetLastError();
    wchar_t errorMessage[256];
    swprintf(errorMessage, 256, L"Failed to register window class. Error code: %lu", errorCode);
    MessageBox(nullptr, errorMessage, L"Detective Barbie 2: Error", MB_OK | MB_ICONERROR);
    DestroyWindow(windowIdentifier);
    return 0;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    MSG msg;
    int result;
    //BOOL feedback;

    result = MainGameWindow(hInstance, nCmdShow, 0); // MAINGAMEWINDOW(HINSTANCE param_1,int param_2,int param_3)

    if (result != 0)
    {
        while (GetMessage(&msg, nullptr, 0, 0)) // Retorna 0 ao receber WM_QUIT
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return static_cast<int>(msg.wParam); // static_cast eh mais seguro que apenas usar (int)
    }

    return 0;
}

//
//  FUNÇÃO: MainGameWindow()
//
//  FINALIDADE: Game Main Window
//
int MainGameWindow(HINSTANCE hInstance, int param_2, int param_3)
{

    ATOM classRegister; // AVar1 Register the class
    HWND windowIdentifier; // The data of type HWND Represents THE WINDOW Identifier
    //int feedback1; // undefined4 uVar2; - Maybe for feedback
    //HDC hDC;
    //int directResult; // int uVar6;
    WNDCLASS wc = { 0 }; // WINDCLASSA wc
    //ZeroMemory(&wc, sizeof(WNDCLASS)); // Garante que todos os campos de wc sejam inicializados

    //UINT feedback2; // uint uVar4

    // Look for active instance of the window (if the window is already open)
      windowIdentifier = FindWindow(L"Detective Barbie(R) II", L"Detective Barbie(R) II");
    // if the window is not open yet, then create a new window
    // almost all the function runs inside this verification
    if (windowIdentifier == NULL)
    {
        if (param_2 == 0) // Checks if the param_2 come from another function.
        {
            wc.hCursor = LoadCursor(NULL, IDC_ARROW); // (LPCSTR)0x7f00 = IDSC_ARROW
            wc.hIcon = LoadCursor(hInstance, IDI_APPLICATION); // (LPCSTR)0x7f00 = IDI_APPLICATION
            wc.lpszMenuName = L"Detective Barbie(R) II";
            wc.lpszClassName = L"Detective Barbie(R) II";
            wc.hbrBackground = (HBRUSH)GetStockObject(4);
            wc.hInstance = hInstance; // param_1
            wc.style = 0x100b;
            wc.lpfnWndProc = WndProc; // FUN_00474600; -> renamed to WndProc in Ghidra
            wc.cbWndExtra = 0;
            wc.cbClsExtra = 0;

            classRegister = RegisterClass(&wc);
            if (classRegister == 0)
            {
                // Error mensagens more detaileds
                DWORD errorCode = GetLastError();
                wchar_t errorMessage[256];
                swprintf(errorMessage, 256, L"Failed to register window class. Error code: %lu", errorCode);
                MessageBox(nullptr, errorMessage, L"Error", MB_OK | MB_ICONERROR);
                return 0;
            }
        }

        // DAT_004a602c (global var maybe) = HWND hWnd 
        HWND hWnd = CreateWindowEx(0, wc.lpszClassName, L"Detective Barbie(R) II", WS_OVERLAPPEDWINDOW,
            0, 0, 0x280, 0x1e0, NULL, NULL, hInstance, NULL); 
        ShowWindow(hWnd, param_2); // Exibe a janela
        UpdateWindow(hWnd);
        if (hWnd == NULL)
        {
            //feedback1 = 0;
            MessageBox(nullptr, L"Failed to create main window.", L"Detective Barbie 2: Error",  MB_OK | MB_ICONERROR);
            return 0;
        }
        else
        {
            printf("Init game. Loading DirectDraw...");
            //feedback1 = 1;
        }
    }
    else
    {
        //feedback1 = 0;
        MessageBox(nullptr, L"Another window is already open.", L"Detective Barbie 2: Error", MB_OK | MB_ICONERROR);
    }

    //return feedback1;
    return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analise as seleções do menu:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Adicione qualquer código de desenho que use hdc aqui...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Manipulador de mensagem para a caixa 'sobre'.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
