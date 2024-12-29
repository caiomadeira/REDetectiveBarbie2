#include "framework.h"
#include "REBarbie.h"
#include <mmsystem.h> // timeGetTime()(WInMM.dll)
#include <ddraw.h> // DirectDrawCreate()(DDRAW.dll)
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


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializar cadeias de caracteres globais
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_REBARBIE, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);
    
    MSG msg;
    int result;
    BOOL feedback;

    result = MainGameWindow(hInstance, nCmdShow, 0);

    if (result != 0)
    {
        while (true)
        {
            while (feedback = PeekMessageA(&msg, nullptr, 0, 0, 1), feedback == 0) {
                WaitMessage();
            }
            //if (GetMessage(&msg, nullptr, 0, 0) == 0x12) break;
            if (msg.message == 0x12) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // FUN_00474310();
        return (int)msg.wParam;
    }

    return 0;
}

//
//  FUNÇÃO: MainGameWindow()
//
//  FINALIDADE: Game Main Window
//
int MainGameWindow(HINSTANCE param_1, int nCmdShow, int param_2)
{

    ATOM AVar1; // AVar1 Register the class
    HWND windowIdentifier; // The data of type HWND Represents THE WINDOW Identifier
    int uVar2; // undefined4 uVar2; - Maybe for feedback
    HDC hDC;
    DWORD DVar3;
    DWORD DVar4;
    UINT uVar5;
    int directResult; // int uVar6;

    //void* pvStack_c;

    WNDCLASS wc = { 0 }; // WINDCLASSA wc

    // ==============================================
    //uStack_4 = 0xffffffff;
    //puStack_8 = &LAB_0048a5ec;
    //pvStack_c = ExceptionList;
    //ExceptionList = &pvStack_c;
    //DAT_004a5a7c = FUN_00473d30();
    // ==============================================

    // Look for active instance of the window (if the window is already open)
    windowIdentifier = FindWindow(L"Detective Barbie(R) II", L"Detective Barbie(R) II");
    // if the window is not open yet, then create a new window
    // almost all the function runs inside this verification
    if (windowIdentifier == NULL)
    {
        if (param_2 == 0) // Checks if the param_2 come from another function.
        {
            wc.hCursor = LoadCursorA(NULL, (LPCSTR)0x7f00);
            wc.hIcon = LoadCursorA(param_1, (LPCSTR)0x7f00);
            wc.lpszMenuName = L"Detective Barbie(R) II";
            wc.lpszClassName = L"Detective Barbie(R) II";
            wc.hbrBackground = (HBRUSH)GetStockObject(4);
            wc.hInstance = param_1; // param_1
            wc.style = 0x100b;
            wc.lpfnWndProc = WndProc; // FUN_00474600; -> renamed to WndProc in Ghidra
            wc.cbWndExtra = 0;
            wc.cbClsExtra = 0;

            AVar1 = RegisterClass(&wc);
            if (AVar1 == 0)
            {
                MessageBox(nullptr, L"Failed to register window class.", L"Error", MB_OK | MB_ICONERROR); // ExceptionList = pvStack_c;
                //ExceptionList = pvStack_c;
                return 0;
            }
        }

        // DAT_004a602c (global var maybe) = HWND hWnd 
        HWND hWnd = CreateWindowEx(0, wc.lpszClassName, L"Detective Barbie(R) II", 0xcf000,
            0, 0, 0x280, 0x1e0, NULL, NULL, param_1, NULL); // talvez o param_1 seja hInstance

        if (hWnd == NULL)
        {
            uVar2 = 0;
            MessageBox(nullptr, L"Failed to create main window.", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }
        else {
            hDC = GetDC(hWnd);
            DVar3 = timeGetTime();
            DVar4 = timeGetTime();
            uVar5 = DVar4 - DVar3;

            while (uVar5 < 1000) {
                // TODO: Revise this FindWindowExA call. The difference between FindWindow, FindWindowExA, etc...
                windowIdentifier = FindWindowExA(NULL, NULL, "Detective Barbie(R) II", "Detective Barbie(R) II");
                if ((windowIdentifier != hWnd) ||
                    (windowIdentifier = FindWindowExA(NULL, windowIdentifier, "Detective Barbie(R) II", "Detective Barbie(R) II"), windowIdentifier != NULL))
                {
                    break; // TODO: temporary break instruction. not equal to decompiled code.
                }
                // goto LAB_00473dda;
                DVar4 = timeGetTime();
                uVar5 = DVar4 - DVar3;
                
            }
            ReleaseDC(hWnd, hDC);
            directResult = DirectDrawCreate(0, &DAT_004a6030, 0);
            if (directResult == 0) 
            {
                int graphicRenderWidth = 0x280; // 640
                int graphicRenderHeight = 0x1e0; // 480
                directResult = (**(code**)(*DAT_004a6030 + 0x54))
                    (DAT_004a6030, graphicRenderWidth, graphicRenderHeight, (int)DAT_0049370c << 3); //directResult = (**(code**)(*DAT_004a6030 + 0x54)) (DAT_004a6030, 0x280, 0x1e0, (int)DAT_0049370c << 3);
               
                if (directResult == 0)
                {
                    aDStack_17c[1] = 0x6c;
                    aDStack_17c[2] = 1;
                    uStack_110 = 0x200;
                    directResult = (**(code**)(*DAT_004a6030 + 0x18))
                        (DAT_004a6030, aDStack_17c + 1, &DAT_004a5a78, 0);
                    if (directResult == 0)
                    {
                        aDStack_17c[2] = 7;
                        uStack_110 = 0x800;
                        aDStack_17c[4] = 0x280; // This is about Width resolution of render
                        aDStack_17c[3] = 0x1e0; // This is about Height resolution of render
                        directResult = (**(code**)(*DAT_004a6030 + 0x18))
                            (DAT_004a6030, aDStack_17c + 1, &DAT_004a6010, 0);
                    }

                    if (directResult != 0) {
                        FUN_00473ce0(hWnd);
                    }
                    _DAT_004a5b88 = 0;
                    _DAT_004a5b90 = 0x280;
                    _DAT_004a5b8c = 0;
                    _DAT_004a5b94 = 0x1e0;
                    _DAT_004a5fa0 = 0x6c;
                    ShowCursor(0);

                    if (direc)

                }
            
            
            }
        }

        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);
    }


    return 1;
}


//
//  FUNÇÃO: MyRegisterClass()
//
//  FINALIDADE: Registra a classe de janela.
//
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REBARBIE));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REBARBIE);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

//
//   FUNÇÃO: InitInstance(HINSTANCE, int)
//
//   FINALIDADE: Salva o identificador de instância e cria a janela principal
//
//   COMENTÁRIOS:
//
//        Nesta função, o identificador de instâncias é salvo em uma variável global e
//        crie e exiba a janela do programa principal.
//
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // Armazenar o identificador de instância em nossa variável global
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}

//
//  FUNÇÃO: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  FINALIDADE: Processa as mensagens para a janela principal.
//
//  WM_COMMAND  - processar o menu do aplicativo
//  WM_PAINT    - Pintar a janela principal
//  WM_DESTROY  - postar uma mensagem de saída e retornar
//
//
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
