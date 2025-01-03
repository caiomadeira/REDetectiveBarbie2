// ReconstructScratch.cpp : Define o ponto de entrada para o aplicativo.
//

#include "framework.h"
#include "ReconstructScratch.h"
#include<ddraw.h>

#pragma comment(lib, "ddraw.lib")

// Variáveis Globais:
HINSTANCE hInst;                                // instância atual

// FROM BARBIE DECOMPILED //

HWND hWnd; // DAT_004a602c
LPDIRECTDRAW lplpDD; // Direct Draw Var
LPDIRECTDRAWSURFACE g_pPrimarySurface = nullptr; // Superfície primária
LPDIRECTDRAWSURFACE g_pSecondarySurface = nullptr; // Superfície secundária (backbuffer)

DWORD screenWidth = 0x280;   // Largura (1280)
DWORD screenHeight = 0x1e0;  // Altura (720)
DWORD someFlag = 0x6c;       // Valor desconhecido
DWORD globalState = 1;       // DAT_0049370c

// Declarações de encaminhamento de funções incluídas nesse módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL MainGameWindow(HINSTANCE hInstance, int nCmdShow, int param_3);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void debugError(HRESULT result, const wchar_t* txt)
{
    wchar_t errorMsg[256];
    swprintf(errorMsg, sizeof(errorMsg) / sizeof(errorMsg[0]), txt, result);
    MessageBox(hWnd, errorMsg, L"Erro", MB_OK);
}

// FUN_00473ce0
BOOL directError(HWND hwnd, LPCWSTR txt)
{
    MessageBox(hwnd, txt, L"Detective Barbie 2: Error", MB_OK | MB_ICONERROR);
    DestroyWindow(hwnd);
    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,  _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    BOOL result = MainGameWindow(hInstance, nCmdShow, 0);

    // Realize a inicialização do aplicativo:
    if (!result)
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RECONSTRUCTSCRATCH));

    // Loop de mensagem principal:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

BOOL MainGameWindow(HINSTANCE hInstance, int nCmdShow, int param_3)
{
   hInst = hInstance; // Armazenar o identificador de instância em nossa variável global

   ATOM classRegister;
   HWND windowId;
   HRESULT directResult;
   HDC hdc;
   HRESULT result;

   windowId = FindWindowW(L"Detective Barbie II", L"Detective Barbie II");

   classRegister = MyRegisterClass(hInstance);

   if (windowId == NULL)
   {
       HWND hWnd = CreateWindowW(L"Detective Barbie II", L"Detective Barbie II", WS_OVERLAPPEDWINDOW,
           0, 0, 0x280, 0x1e0, nullptr, nullptr, hInstance, nullptr);

       if (!hWnd)
       {
           MessageBox(nullptr, L"Failed to create main window.", L"Detective Barbie 2: Error", MB_OK | MB_ICONERROR);
           return FALSE; // feedback1 = 0
       }
       else
       {
           //ReleaseDC(hWnd, hdc); // libera o hdc
           // Init DirectDraw
           directResult = DirectDrawCreate(NULL, &lplpDD, NULL);
           if (SUCCEEDED(directResult))
           {
               directResult = lplpDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
               if (SUCCEEDED(directResult))
               {
                   DWORD directBufferParameters[27]; // DWORD aDStack_17c[27];
                   int uStack_110;                  
                   DWORD DAT_0049370c = 8; // EXEMPLO DE VALOR

                   // surface
                   DDSURFACEDESC surfaceDesc = {};
                   LPDIRECTDRAWSURFACE lpDDSPrimary = nullptr;
                   LPDIRECTDRAWSURFACE lpDDSBack = nullptr;

                   lplpDD->SetDisplayMode(0x280, 0x1e0, DAT_0049370c);// (int)DAT_0049370c << 3: Profundidade de cor (bits por pixel). Isso parece ser calculado dinamicamente no programa.
                   if (SUCCEEDED(directResult))
                   {
                           // 4. Criar a superfície primária
                       DDSURFACEDESC ddsd = {};

                       ddsd.dwSize = sizeof(ddsd);
                       ddsd.dwFlags = DDSD_CAPS;
                       ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

                       result = lplpDD->CreateSurface(&ddsd, &g_pPrimarySurface, nullptr);
                       if (FAILED(result)) {
                           MessageBox(hWnd, L"Falha ao criar a superfície primária.", L"Erro", MB_OK);
                       }

                       // 5. Criar a superfície secundária (backbuffer)
                       ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
                       ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
                       ddsd.dwWidth = 640; // Largura
                       ddsd.dwHeight = 480; // Altura

                       result = lplpDD->CreateSurface(&ddsd, &g_pSecondarySurface, nullptr);
                       if (FAILED(result)) {
                           MessageBox(hWnd, L"Falha ao criar a superfície secundária.", L"Erro", MB_OK);
                       }
                       else
                       {
                           // Continuando

    // Caso exista um erro, chamar FUN_00473ce0
                           auto handleError = [&](HWND hWnd) {
                               directError(hWnd, L"Generic Error"); // FUN_00473ce0(hWnd);
                               return DDERR_GENERIC;
                               };

                           // Atualizar algumas variáveis globais
                           DWORD _DAT_004a5b90 = screenWidth;
                           DWORD _DAT_004a5b8c = 0;
                           DWORD _DAT_004a5b94 = screenHeight;
                           DWORD _DAT_004a5fa0 = someFlag;

                           // Mostrar cursor
                           ShowCursor(TRUE);


                           int globalState = 1; // globalState
                           if (globalState == 1)
                           {
                               // Detecta a paleta de cores
                               // auto feedback2 = FUN_00442a30("DATA\\detect.pal", 0x4a5b98); // 0x4a5b98 deve ser um endereco
                               auto feedback2 = 1;
                               if (feedback2 == 0)
                               {
                                   MessageBox(hWnd, L"Erro ao carregar detect.pal", L"feedback2 == 0", MB_OK);
                                   return FALSE;
                               }
                               // Configurar a paleta com DirectDraw
                               PALETTEENTRY paletteData[256]; // Array com 256 entradas (tamanho da paleta de 8 bits)
                               for (int i = 0; i < 256; ++i) {
                                   paletteData[i].peRed = i;       // Exemplo: Gradiente de vermelho
                                   paletteData[i].peGreen = 0;     // Sem verde
                                   paletteData[i].peBlue = 255 - i; // Gradiente inverso de azul
                                   paletteData[i].peFlags = 0;     // Sem flags adicionais
                               }
                               LPDIRECTDRAWPALETTE pPalette = nullptr;

                               result = lplpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, paletteData, &pPalette, nullptr);
                               if (FAILED(result)) {
                                   //return directError(hWnd, L"Create Pallete.");  //FUN_00473ce0(hWnd); // Handle error
                                   debugError(result, L"Erro em CreatetPalette: 0x%08X");
                               }

                               // Aplicar a paleta às superfícies (surfaceA e surfaceB)
                               result = g_pPrimarySurface->SetPalette(pPalette);
                               if (FAILED(result)) {
                                   // return directError(hWnd, L"Set Pallete primary."); //FUN_00473ce0(hWnd); // Handle error
                                   debugError(result, L"Erro em SetPalette: 0x%08X");
                               }

                               result = g_pSecondarySurface->SetPalette(pPalette);
                               if (FAILED(result)) {
                                   // return directError(hWnd, L"Set Pallete secondary."); //FUN_00473ce0(hWnd); // Handle error 
                                   debugError(result, L"Erro em SettPalette2: 0x%08X");
                               }
                           }
                           else
                           {
                               //FUN_00442f30();
                               MessageBox(hWnd, L"_Another_instance_is_already_active", L"FUN_00442f30() (instanceError)", MB_OK);

                               return FALSE;
                           }
                       }
                   }
               }
           }
       }

       ShowWindow(hWnd, nCmdShow);
       UpdateWindow(hWnd);
   }

   return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RECONSTRUCTSCRATCH));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(4);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RECONSTRUCTSCRATCH);
    wcex.lpszClassName = L"Detective Barbie II";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
