#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>
#include <locale>
#include <wchar.h>


int main()
{
	setlocale(LC_CTYPE,"");
	wchar_t c1 = L'а';
	wchar_t c2 = L'a';
	wchar_t c3 = L'А';
	wchar_t c4 = L'я';
	wchar_t c5 = L'Я';
	wchar_t c6 = L'ё';
	wchar_t c7 = L'Ё';
	
	
	wprintf(L"рус а - %lc = %d\n", c1,c1);
	wprintf(L"англ а - %lc = %d\n", c2, c2);
	wprintf(L"А - %lc = %d\n", c3, c3);
	wprintf(L"я - %lc = %d\n", c4, c4);
	wprintf(L"Я - %lc = %d\n", c5, c5);
	wprintf(L"ё - %lc = %d\n", c6, c6);
	wprintf(L"Ё - %lc = %d\n", c7, c7);

	wprintf(L"size = %d\n", sizeof(wchar_t));
	return 0;
}