#include"parser.h"
int SearchStringInArray(char* array,int size,int startindex,const char* search,int count)
{
    int len = strlen(search);
    int c = 0;
    
   
        for (int i = startindex; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                if (array[j] == search[j - i])
                {
                    if (j - i == len - 1)
                    {
                        c++;
                        if (c == count)
                            return i;
                    }
                }
                else
                {
                    i += j - i;
                    break;
                }
            }
        }
        return -1;
    
}
char* GetStringBySign(char* array,int size,int startindex,char sign){
    int index = 0;
    for (int i = startindex; i < size; i++)
    {
        if (array[i] == sign)
        {
            index = i;
            break;
        }
    }
    char* text = NULL;
    if (index != 0) {
        int stringsize = index - startindex;
        text = (char*)malloc(stringsize + 1);
        memcpy(text, array + startindex, size);
        text[size] = '\0';
    }
    return text;
}
char* GetValueParam(char* string,int sizestring,const char* name_param,int*sizeres){
    char param[100];
    strcpy(param,name_param);
    int length=strlen(param);
    strcpy(&param[length],":");
    int start=SearchStringInArray(string,sizestring,0,param,1);
    if(start==-1)
        return NULL;
    start=SearchStringInArray(string,sizestring,start,":",1);
    if(start==-1)
        return NULL;
    start++;
    int end=SearchStringInArray(string,sizestring,start,"\r",1);
    if(end==-1)
        return NULL;
    int sizearr=end-start+1;
    *sizeres=sizearr;
    char* arrstr=(char*)malloc(sizearr);
    memcpy(arrstr,&string[start],sizearr-1);
    arrstr[sizearr-1]='\0';
    return arrstr;
}
void StringAddString(char* string,const char* str){
    int length=strlen(string);
    strcpy(&string[length],str);
}
void StringAddInt(char* string,int number){
    int length=strlen(string);
    char buffint[12];
    sprintf(buffint, "%d", number);
    strcpy(&string[length],buffint);
}
int GetLengthInt(int number){
    char buffint[12];
    sprintf(buffint, "%d", number);
    return strlen(buffint);
}