#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#include <dirent.h>
using namespace std;

string spacePID(int p){
if((p<10))        return"       ";
if((p>=10)&&(p<100))return"      ";
if((p>=100)&&(p<1000))return"     ";
if((p>=1000)&&(p<10000))return"    ";
return "   ";
}
string spaceM(float p){
if((p>=0.0)&&(p<10))return"             ";
else if(p>9.9)return"            ";
else return"              ";
}
string spaceSWAP(int p){
if((p<10))        return"         ";
if((p>=10)&&(p<100))return"        ";
if((p>=100)&&(p<1000))return"       ";
if((p>=1000)&&(p<10000))return"      ";
return "     ";
}
string spaceMIN(int p){
if((p<10))        return"                   ";
if((p>=10)&&(p<100))return"                  ";
if((p>=100)&&(p<1000))return"                 ";
if((p>=1000)&&(p<10000))return"                ";
if((p>=10000)&&(p<100000))return"               ";
if((p>=100000)&&(p<1000000))return"              ";
return "            ";
}
