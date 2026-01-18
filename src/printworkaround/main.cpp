#define _CTR_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>

#define DirectDrawCreate DirectDrawCreate_Original
#include <ddraw.h>
#undef DirectDrawCreate

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "user32.lib")

typedef HRESULT(WINAPI* DirectDrawCreate_t)(GUID*, void**, void*);
DirectDrawCreate_t r_DirectDrawCreate = NULL;

const char