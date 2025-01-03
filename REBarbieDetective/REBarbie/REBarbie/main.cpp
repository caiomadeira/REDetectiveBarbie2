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

// ::::::::::::::::::::::::::::::
// DAT_XXXXXXX GLOBALS

LPDIRECTDRAW DAT_004a6030 = NULL;
LPDIRECTDRAWSURFACE primarySurface = NULL; //  &DAT_004a5a78 -> endereco do local onde o ponteiro pra superficie criada sera armazenado
LPDIRECTDRAWSURFACE secondarySurface = NULL;

// CreatePallete Parameters
LPPALETTEENTRY DAT_004a5b98 = NULL; // Tabela de cores
LPDIRECTDRAWPALETTE DAT_004a600c = NULL; // Ponteiro para a paleta

// CreateThread
LPTHREAD_START_ROUTINE  DAT_0000a164 = NULL;

// ::::::::::::::::::::::::::::::


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

/*
* FUN_00442a30
A função FUN_00442a30 parece estar relacionada ao
carregamento e manipulação de paletas ou dados gráficos, 
como o nome do arquivo de paleta mencionado (s_Method_LoadPalette). 
Aqui está o que acontece, passo a passo:
*/
//unsigned int __cdecl FUN_00442a30(undefined4 param_1, int param_2)
//
//{
//    FILE* pFVar1;
//    unsigned int uVar2;
//    undefined* puVar3;
//    char* pcVar4;
//    int iVar5;
//    char local_50c[12];
//    CHAR local_500[256];
//    char local_400[1024];
//
//    pFVar1 = (FILE*)FUN_0047d5d3(param_1, &DAT_0048f954);
//    if (pFVar1 == (FILE*)0x0) {
//        FUN_0047e1e1(local_500, (byte*)s_Method_LoadPalette(> _ % s_ < )_Faile_004933c0);
//        uVar2 = MessageBoxA((HWND)0x0, local_500, s_Fatal_ERROR_004933b4, 0x10);
//        return uVar2 & 0xffffff00;
//    }
//    FUN_0047d3ff(local_50c, 1, 0xc, (int*)pFVar1);
//    FUN_0047d3ff(local_400, 4, 0x100, (int*)pFVar1);
//    FUN_0047d382(pFVar1);
//    puVar3 = (undefined*)(param_2 + 1);
//    iVar5 = 0x100;
//    pcVar4 = local_400;
//    do {
//        puVar3[1] = puVar3[(int)(local_400 + (1 - param_2))];
//        *puVar3 = puVar3[(int)(local_400 + -param_2)];
//        puVar3[-1] = *pcVar4;
//        puVar3[2] = 5;
//        puVar3 = puVar3 + 4;
//        iVar5 = iVar5 + -1;
//        pcVar4 = pcVar4 + 4;
//    } while (iVar5 != 0);
//    puVar3 = (undefined*)(param_2 + 3);
//    iVar5 = 10;
//    do {
//        puVar3[0x3d8] = 2;
//        *puVar3 = 2;
//        puVar3 = puVar3 + 4;
//        iVar5 = iVar5 + -1;
//    } while (iVar5 != 0);
//    return CONCAT31((int3)((uint)puVar3 >> 8), 1);
//}

// VERSAO SIMPLIFICADA DA FUN_00442a30
// TODO: Revisar

unsigned int FUN_00442a30(const char* filename, int base_offset) {
    FILE* file;
    char header[12];
    char buffer[1024];
    uint8_t* data_pointer;
    int i;

    // 1. Abrir o arquivo
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 0xFFFFFF00; // Código de erro simplificado
    }

    // 2. Ler os dados do arquivo
    fread(header, 1, sizeof(header), file);
    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    // 3. Configurar os dados processados
    data_pointer = (uint8_t*)(base_offset + 1); // Ajuste inicial do ponteiro
    for (i = 0; i < 256; i++) {
        data_pointer[1] = buffer[i];  // Simulação do processamento
        data_pointer[0] = buffer[255 - i];
        data_pointer[-1] = buffer[i];
        data_pointer[2] = 5;
        data_pointer += 4; // Avança 4 bytes por iteração
    }

    // 4. Inicializar valores adicionais
    data_pointer = (uint8_t*)(base_offset + 3);
    for (i = 0; i < 10; i++) {
        data_pointer[0x3D8] = 2;
        data_pointer[0] = 2;
        data_pointer += 4; // Avança 4 bytes por iteração
    }

    // 5. Retornar sucesso com um valor específico
    return 0x01; // Valor simplificado (sem CONCAT31)
}


int __cdecl directDrawFailedInit(HWND windowIdentifier)

{
    CHAR s[256];

    // FUN_0047e1e1
    // FUN_0047e1e1(s, (byte*)"DirectDraw initialization failed!!\nLocation Code: %u");
    MessageBoxA(windowIdentifier, s, "Detectibe Barbie 2 by Caio M", 0);
    DestroyWindow(windowIdentifier);
    return 0;
}


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


/*
* __ftol() 
A função __ftol() realiza a conversão de um número de ponto flutuante 
(armazenado no registrador ST0 da FPU - Unidade de Ponto Flutuante) para
um inteiro de 64 bits (longlong) usando arredondamento (ROUND).

Isso significa que, para qualquer número em ST0 no momento da chamada,
ele será arredondado ao inteiro mais próximo e retornado.

Talvez mudar o retorno pra int ou float (mas c/ ressalvas);
*/
long long __ftol(void)
{
    float in_ST0; // ST0 é um registrador da FPU (Unidade de Ponto flutuante) p/ um inteiro de 64 bits(long long)
    return (long long)std::round(in_ST0); //  return (long long)ROUND(in_ST0);
}


/*
* FUN_00473d30
Analisando a função FUN_00473d30, parece que ela está implementando
uma espera ativa que dura até 2 segundos ou até um certo limite de iterações,
com algumas peculiaridades.
Essa função parece ser um tipo de temporizador baseado em polling, 
verificando continuamente o tempo até atingir um limite de 2 segundos.
O valor retornado depende da implementação interna de __ftol().
*/
long long FUN_00473d30(void)

{
    DWORD DVar1;
    DWORD DVar2;
    long long lVar3;
    int local_8;

    DVar1 = timeGetTime();
    local_8 = 0;
    do {
        DVar2 = timeGetTime();
        if (DVar1 + 2000 <= DVar2) {
            lVar3 = __ftol();
            return (int)lVar3;
        }
        local_8 = local_8 + 1;
    } while (local_8 != -1);
    return 300;
}

// FUN_00442f30
void FUN_00442f30(void)

{
    undefined4 local_20[2];
    uint uStack_18;
    uint uStack_14;
    uint uStack_10;

    local_20[0] = 0x20;
    (**(code**)(*primarySurface + 0x54))(primarySurface, local_20);
    DAT_004a55d4 = uStack_18;
    FUN_00442f00(uStack_18, &DAT_004a55b8);
    DAT_004a55d0 = uStack_14;
    FUN_00442f00(uStack_14, &DAT_004a55b4);
    DAT_004a55cc = uStack_10;
    FUN_00442f00(uStack_10, &DAT_004a55b0);
    DAT_004a55c0 = DAT_004a55b8 + -7;
    DAT_004a51ac = 0xf - DAT_004a55b4;
    DAT_004a55c8 = 0x17 - DAT_004a55b0;
    DAT_004a55c4 = 0x17 - DAT_004a55b8;
    DAT_004a55bc = 7 - DAT_004a55b0;
    return;
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
    unsigned int uVar5;
    int directResult; // int uVar6;
    void* pvVar6;
    void* puVar7; // undefined4* puVar7; type *void, *int or *unsigned int, or a struct
    unsigned long uVar8; // ulong uVar8;
    unsigned long uVar9; // ulong uVar9;
    unsigned long uVar10; // ulong uVar10;
    unsigned long uVar11; // ulong uVar11;
    // DDRAW Pointers
    IDirectSound* pIVar12;
    IDirectDraw *pIVar13;
    IDirectDrawSurface *pIVar14;
    IDirectDrawSurface* pIVar15;

    BYTE* pBVar16;
    WNDCLASS wc = { 0 }; // WINDCLASSA wc
    DWORD aDStack_17c[27];
    int uStack_110; // undefined4 uStack_110;
    BYTE BStack_10c;
    undefined4 uStack_10b; // é passado seu endereco para o puVar7. Talvez seja do mesmo tipo?
    void* pvStack_c;
    // undefined* puStack_8; Deixar pra depois pois so eh referenciada em mais um lugar do codigo.
    int uStack_4; // undefined4 uStack_4; // vou assumir como int pelo contexto do codigo


    //void* pvStack_c;
    int uStack_4; // undefined4 uStack_4;

    // ==============================================
    uStack_4 = -1; //uStack_4 = 0xffffffff;
    // puStack_8 = &LAB_0048a5ec; Deixar pra depois pois so eh referenciada em mais um lugar do codigo.
    //pvStack_c = ExceptionList;
    //ExceptionList = &pvStack_c;
    long long DAT_004a5a7c;
    DAT_004a5a7c = FUN_00473d30(); // DAT_004a5a7c = FUN_00473d30();  DAT_004a5a7c tavez seja uma variavel global long long talvez
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
            // &DAT_004a6030 is probably the address of pointer of  LPDIRECTDRAW *lplpDD
            directResult = DirectDrawCreate(0, &DAT_004a6030, 0);
            if (directResult == 0)
            {
                //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                //::::::::::::::::::::::::::: V TABLE 1 ::::::::::::::::::::::::::::::::::::::::::::::
                //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // Linha: directResult = (**(code**)(*DAT_004a6030 + 0x50))(DAT_004a6030, hWnd, 0x13);
                directResult = DAT_004a6030->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
                //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                if (directResult == 0) {
                    int graphicRenderWidth = 0x280; // 640
                    int graphicRenderHeight = 0x1e0; // 480
                    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    //::::::::::::::::::::::::::: V TABLE 2 ::::::::::::::::::::::::::::::::::::::::::::::
                    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // Linha: directResult = (**(code**)(*DAT_004a6030 + 0x54))(DAT_004a6030, graphicRenderWidth, graphicRenderHeight, (int)DAT_0049370c << 3); //directResult = (**(code**)(*DAT_004a6030 + 0x54)) (DAT_004a6030, 0x280, 0x1e0, (int)DAT_0049370c << 3);
                    // Utiliza o offset passado (0x54) para procurar a funcao no vtable.
                    
                    typedef HRESULT(*SetDisplayModeFunc)(LPDIRECTDRAW, DWORD, DWORD, DWORD);
                    SetDisplayModeFunc SetDisplayMode = *(SetDisplayModeFunc*)((uintptr_t)(*(void**)DAT_004a6030) + 0x54);
                    if (SetDisplayMode == NULL) { printf("Erro: função SetDisplayMode não encontrada no vtable.\n"); return -1; }
                    
                    // Configurando o modo de exibição para 640x480 com 16 bits de cor
                    directResult = SetDisplayMode(DAT_004a6030, 640, 480, 16);
                    if (directResult != DD_OK) { printf("Erro ao configurar o modo de exibição: 0x%x\n", directResult); return -1; }
                    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                    if (directResult == 0)
                    {
                        aDStack_17c[1] = 0x6c;
                        aDStack_17c[2] = 1;
                        uStack_110 = 0x200;
                       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                       //::::::::::::::::::::::::::: V TABLE 3 ::::::::::::::::::::::::::::::::::::::::::::::
                       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                       // Linha: directResult = (**(code**)(*DAT_004a6030 + 0x18))(DAT_004a6030, aDStack_17c + 1,, 0);
                       // Utiliza o offset passado (0x18) para procurar a funcao no vtable.
                       // 
                       // Definindo o tipo do método CreateSurface
                        typedef HRESULT(*CreateSurfaceFunc)(
                            LPDIRECTDRAW,
                            LPDDSURFACEDESC,
                            LPDIRECTDRAWSURFACE*,
                            IUnknown*
                            );

                        // Obtemos o ponteiro para o método CreateSurface da vtable
                        CreateSurfaceFunc CreateSurface = *(CreateSurfaceFunc*)((uintptr_t)(*(void**)DAT_004a6030) + 0x18);

                        if (CreateSurface != NULL) {
                            DDSURFACEDESC surfaceDesc = { 0 };
                            surfaceDesc.dwSize = sizeof(DDSURFACEDESC);
                            surfaceDesc.dwFlags = DDSD_CAPS;
                            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

                            // Criando a superfície
                            HRESULT directResult = CreateSurface(DAT_004a6030, &surfaceDesc, &primarySurface, NULL);
                            if (directResult != DD_OK) {
                                printf("Erro ao criar superfície: 0x%x\n", directResult);
                            }
                        }
                        else {
                            printf("Erro: método CreateSurface não encontrado na vtable.\n");
                        }

                       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                       //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        if (directResult == 0)
                        {
                            aDStack_17c[2] = 7;
                            uStack_110 = 0x800;
                            aDStack_17c[4] = 0x280; // This is about Width resolution of render
                            aDStack_17c[3] = 0x1e0; // This is about Height resolution of render
                            //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                            //::::::::::::::::::::::::::: V TABLE 4 (MESMA DO VTABLE 3) ::::::::::::::::::::::::::::::::::::::::::::::
                            //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                            // Linha: directResult = (**(code**)(*DAT_004a6030 + 0x18))(DAT_004a6030, aDStack_17c + 1,, 0);
                            // Utiliza o offset passado (0x18) para procurar a funcao no vtable.
                            // 
                            // Definindo o tipo do método CreateSurface
                            typedef HRESULT(*CreateSurfaceFunc)(
                                LPDIRECTDRAW,
                                LPDDSURFACEDESC,
                                LPDIRECTDRAWSURFACE*,
                                IUnknown*
                                );

                            // Obtemos o ponteiro para o método CreateSurface da vtable
                            CreateSurfaceFunc CreateSurface = *(CreateSurfaceFunc*)((uintptr_t)(*(void**)DAT_004a6030) + 0x18);

                            if (CreateSurface != NULL) {
                                DDSURFACEDESC surfaceDesc = { 0 };
                                surfaceDesc.dwSize = sizeof(DDSURFACEDESC);
                                surfaceDesc.dwFlags = DDSD_CAPS;
                                surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

                                // Criando a superfície
                                LPDIRECTDRAWSURFACE secondarySurface = NULL; 
                                HRESULT directResult = CreateSurface(DAT_004a6030, &surfaceDesc, &secondarySurface, NULL);
                                if (directResult != DD_OK) {
                                    printf("Erro ao criar superfície: 0x%x\n", directResult);
                                }
                            }
                            else {
                                printf("Erro: método CreateSurface não encontrado na vtable.\n");
                            }

                            //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                            //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        }

                        if (directResult != 0) {
                            directDrawFailedInit(hWnd);
                        }
                        int _DAT_004a5b88;
                        int _DAT_004a5b90;
                        int _DAT_004a5b8c;
                        int _DAT_004a5b94;
                        int _DAT_004a5fa0;

                        _DAT_004a5b88 = 0;
                        _DAT_004a5b90 = 0x280;
                        _DAT_004a5b8c = 0;
                        _DAT_004a5b94 = 0x1e0;
                        _DAT_004a5fa0 = 0x6c;
                        ShowCursor(TRUE); // ShowCursor(0); // Nao mostra o cursor

                        /*
                        * DAT_0049370c
                        Quando é igual a 1, um fluxo específico é ativado, o que 
                        provavelmente afeta como as superfícies gráficas ou paletas 
                        são configuradas. Observe que, dentro do if, há uma chamada
                        para FUN_00442a30, que parece carregar um arquivo de paleta 
                        (s_data\detect.pal_00493158) e configurar algum recurso gráfico
                        relacionado a cores.
                        Dado o segundo contexto, provavelmente é um tipo inteiro (e.g., int, uint, ou BYTE):
                        */
                        int DAT_0049370c;
                        if (DAT_0049370c == 1) // (DAT_0049370c == '\x01') 
                        {
                            // TODO VERIFICAR ESSES DADOS MOCKADOS DE DAT_004A5B98
                            uVar5 = FUN_00442a30(
                                "C:\\Users\\caiom\\OneDrive\\Área de Trabalho\\REDetectiveBarbie2\\REBarbieDetective\\DATA\\detect.pal",
                                0x4a5b98); // uVar5 = FUN_00442a30(s_data\detect.pal_00493158,0x4a5b98);
                            if ((char)uVar5 == '\0') // se o caractere for nulo
                            {
                                // ExceptionList = pvStack_c;
                                MessageBox(nullptr, L"uVar5 == NULL TERMINATOR", L"Error", MB_OK | MB_ICONERROR);
                                return 0;
                            }

                            // VTABLE 5
                            // linha: directResult = (**(code**)(*DAT_004a6030 + 0x14))(DAT_004a6030, 0x44, &DAT_004a5b98, &DAT_004a600c, 0);
                            // TODO: Voltar aqui pois o DAT_004a5b98 NAO  parece certo.
                            //DAT_004a5b98: provavelmente faz parte de uma estrutura de bytes;  00431658 8a 41 ff        MOV        AL,byte ptr [ECX + -0x1]=>DAT_004a5b98

                            directResult = DAT_004a6030->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256, DAT_004a5b98, &DAT_004a600c, NULL);
                            if (directResult != 0) {
                                directDrawFailedInit(hWnd);
                            }
                            // VTABLE 6 - BltFast probably
                            // linha: directResult = (**(code**)(*primarySurface + 0x7c))(primarySurface, DAT_004a600c);
                            RECT srcRect = { 0, 0, 50, 50 };
                            directResult = primarySurface->BltFast(100, 100, secondarySurface, &srcRect, DDBLTFAST_NOCOLORKEY);

                            if (directResult != 0) {
                                directDrawFailedInit(hWnd);
                            }

                            LPDIRECTDRAWSURFACE DAT_004a6010 = NULL; // Superfície alvo
                            // VTABLE 7 - Same as vtable 6 - BlitFast
                            // linha: directResult = (**(code**)(*DAT_004a6010 + 0x7c))(DAT_004a6010, DAT_004a600c);
                            directResult = DAT_004a6010->BltFast(
                                150, 150, // Posição no destino (DAT_004a6010)
                                primarySurface, // Superfície de origem
                                &srcRect, // Retângulo de origem
                                DDBLTFAST_NOCOLORKEY // Sem transparência
                            );

                            if (directResult != 0) {
                                directDrawFailedInit(hWnd);
                            }
                        }
                        else {
                            FUN_00442f30();
                        }
                        pvVar6 = operator new(0x1010, std::nothrow);  // pvVar6 = operator_new(0x1010); // Probably, operator_new = malloc; UPDATE: No, operator new is like malloc but for C++ objects
                        uStack_4 = 0;
                        if (pvVar6 == (void*)0x0) // Maybe, i should put pvVar6 == NULL or nullptr
                        {
                            DAT_004a5f98 = nullptr; // DAT_004a5f98 = (undefined4*)0x0;
                        }
                        else {
                            DAT_004a5f98 = FUN_00474c60(pvVar6, hWnd, 1);
                        }
                        uStack_4 = -1;// uStack_4 = 0xffffffff; 
                        puVar7 = operator new(0x210, std::nothrow); // puVar7 = (undefined4*)operator_new(0x210);
                        if (puVar7 == nullptr) // if (puVar7 == (undefined4*)0x0) 
                        {
                            puVar7 = nullptr; // puVar7 = (undefined4*)0x0;
                        }
                        else {
                            *puVar7 = &PTR_LAB_0048b4a8;
                            puVar7[1] = 1; // maybe its a int array
                            puVar7[0x82] = 0;
                        }
                        FUN_00474da0(DAT_004a5f98, (int)puVar7); // or not because here we convert puVar7 to int
                        pvVar6 = operator new(8, std::nothrow); // pvVar6 = operator_new(8);
                        uStack_4 = 1;
                        if (pvVar6 == nullptr) // if (pvVar6 == (void*)0x0) 
                        {
                            DAT_004a5a70 = nullptr; // DAT_004a5a70 = (undefined4*)0x0;
                        }
                        else {
                            DAT_004a5a70 = FUN_0043bd80(
                                pvVar6,
                                "C:\\Users\\caiom\\OneDrive\\Área de Trabalho\\REDetectiveBarbie2\\REBarbieDetective\\DATA\\pinames.hix",
                                "C:\\Users\\caiom\\OneDrive\\Área de Trabalho\\REDetectiveBarbie2\\REBarbieDetective\\DATA\\pinames.hug"
                            ); // DAT_004a5a70 = FUN_0043bd80(pvVar6, s_data\pinames.hix_004937e0, s_data\pinames.hug_004937f4);
                        }
                        DAT_004a41c0 = 0;
                        uStack_4 = -1; // uStack_4 = 0xffffffff;
                        DAT_004a41c4 = 0;
                        puVar7 = &DAT_004a47fc;
                        _DAT_004a41c8 = 0;
                        _DAT_004a41cc = 0;
                        _DAT_004a41d0 = 0;
                        do {
                            *puVar7 = 0;
                            puVar7 = puVar7 + 2;
                        } while ((int)puVar7 < DAT_004a484c); // DAT_004a484c is in 0x4a484c address
                        FUN_00431860();
                        DVar3 = timeGetTime();
                        FUN_0047e516(DVar3);
                        ShowWindow(hWnd, nCmdShow); // ShowWindow(hWnd,param_3); maybe, param_3 = nCmdShow
                        // UpdateWindow(hWnd); // Eu adicionei essa linha
                        FUN_00417d90();
                        FUN_00431200();
                        DAT_004a6018 = CreateThread(NULL, 0,
                            (LPTHREAD_START_ROUTINE)&DAT_0000a164, // 0043dae0 is the address. Maybe DAT_000a164.
                            (LPVOID)0x0, 0, aDStack_17c);
                        BStack_10c = DAT_004a6038;
                        puVar7 = &uStack_10b;

                        for (directResult = 0x3f; directResult != 0; directResult = directResult + -1) {
                            *puVar7 = 0;
                            puVar7 = puVar7 + 1;
                        }
                        *(undefined2*)puVar7 = 0;
                        *(undefined*)((int)puVar7 + 2) = 0;
                        FUN_00473bf0(&BStack_10c);
                        // :::::::::::::::::::::::::::::::::::::::::::
                        // Gus.dll calls
                        // TODO: Como tenho apenas as GUS.DLL e GUSD.DLL (sem os arquivos .lib)
                        // vou tentar linkar dinamicamente ao final utilizando funcoes do windows pra carregar
                        // a funcao de RGBA propriarmente. 
                        // 
                        // Caso não der certo, vou tentar arranjar algum jeito de gerar um .lib.
                        // Como última opção, usarei outra função RGBA.
                        // 
                        // Há ainda a possibilidade remota de reconstruir essa DLL.
                        // :::::::::::::::::::::::::::::::::::::::::::
                        uVar8 = Gus::RGBA(0, 0, 0, 0xff);
                        uVar9 = Gus::RGBA(0xff, 0xff, 0xff, 0xff);
                        uVar10 = Gus::RGBA(0, 0, 0, 0xff);
                        uVar11 = Gus::RGBA(0x78, 0xdc, 0x78, 0xff);
                        pBVar16 = &BStack_10c;
                        directResult = 0x10;

                        pIVar13 = (IDirectDraw*)DAT_004a6030;
                        pIVar14 = (IDirectDrawSurface*)primarySurface;
                        pIVar15 = (IDirectDrawSurface*)DAT_004a6010;
                        pIVar12 = (IDirectSound*)FUN_00474d00(DAT_004a5f98);
                        // Another Gus function call
                        Gus::initialize(hWnd, pIVar12, pIVar13, pIVar14, pIVar15, directResult,
                            (char*)pBVar16, uVar11, uVar10, uVar9, uVar8);
                        uVar2 = 1;
                        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        // A lot of 'elses' stataments in original code. Caution here. Probably get some problems in future.
                        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                } else { uVar2 = directDrawFailedInit(hWnd); }
            } else { uVar2 = directDrawFailedInit(hWnd); }
 
      } else { uVar2 = directDrawFailedInit(hWnd); }
    } else {
        LAB_00473dda:
        uVar2 = FUN_00473ca0();
    }
    // ExceptionList = pvStack_c;
    
    return uVar2;
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
