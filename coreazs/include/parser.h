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
#ifdef __cplusplus
extern "C" {
#endif
CORE_API int SearchStringInArray(char* array,int size,int startindex,const char* search,int count);
CORE_API char* GetStringBySign(char* array,int size,int startindex,char sign);
char* CORE_API  GetValueParam(char* string,int sizestring,const char* name_param,int*sizeres);
CORE_API void StringAddString(char* string,const char* str);
CORE_API void StringAddInt(char* string,int number);
CORE_API int GetLengthInt(int number);
#ifdef __cplusplus
}
#endif
