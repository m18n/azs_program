#pragma once
#include <iostream>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include<string.h>
#include <fstream>
#include <sys/types.h>
#include <signal.h>
using std::cout; using std::cin;
using std::endl; using std::vector;
struct PID{
    int pid;
    std::string pwddir;
    std::string nameprogram;
    std::string pwd;
};
std::vector<PID> GetAllProc();
void ShowPid(PID* pid);
std::string GetStringG(char* arr,int startindex,int size);
void ReverChar(const char* arr,char* out);
int SearchWordIndex(char* arr,int startindex,int size,int count,const char* search);
void StartProgram();
std::vector<PID> FindProc();
std::string GetPwdProc(const char* path);
int main();