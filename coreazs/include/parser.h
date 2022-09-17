#pragma once
#ifdef _WIN32

#ifdef CORE_EXPORTS

#define CORE_API __declspec(dllimport)

#else
#define CORE_API __declspec(dllexport)
#endif
#else
#define CORE_API
#endif
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
CORE_API int SearchStringInArray(char* array,int size,int startindex,const char* search,int count);
char* GetStringBySign(char* array,int size,int startindex,char sign);
CORE_API char* GetValueParam(char* string,int sizestring,const char* name_param,int*sizeres);