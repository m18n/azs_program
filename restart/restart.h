#pragma once
#include <iostream>
#include <vector>
#include<string.h>
#include <fstream>
#ifdef _WIN32
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include<string>
#include<string.h>

#else
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>
#endif
using std::cout; using std::cin;
using std::endl; using std::vector;
struct PID{
    int pid;
    std::string pwddir;
    std::string nameprogram;
    std::string pwd;
};
#ifdef __linux__ 
std::string GetPwdProc(std::string path);
std::vector<PID> GetAllProc();
#endif

void ShowPid(PID* pid);
std::string GetStringG(char* arr,int startindex,int size);
void ReverChar(const char* arr,char* out);
int SearchWordIndex(char* arr,int startindex,int size,int count,const char* search);
void StartProgram();
std::vector<PID> FindProc();
void KillProc(int pid);
int main();