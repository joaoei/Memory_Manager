#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*Variáveis*/
FILE *memInfo;
FILE *swaps;
char s[7], kb[2];
char s1[9], s2[4], s3[4], s4[4], s5[9];
int n,s_total, s_used, s_priority;

void rotina_memInfo(){

	memInfo = fopen("/proc/meminfo", "r");
	if(memInfo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		fscanf(memInfo,"%s %d %s\n",s,&n,kb);
		int total = n;
		fscanf(memInfo,"%s %d %s\n",s,&n,kb);
		int livre = n;
		int mem_usada = (100 * (total - livre)) / total;
		cout << "Memória total: " << total << " kB \n";
		cout << "Memoria usada: " << mem_usada << "% \n";
		fscanf(memInfo,"%s %d %s\n",s,&n,kb);
		fscanf(memInfo,"%s %d %s\n",s,&n,kb);
		fscanf(memInfo,"%s %d %s\n",s,&n,kb);
		int cache_usada = n;
		cout << "Cache usada:   " << cache_usada << " kB \n";
	}
	fclose(memInfo);	
}
void rotina_swaps(){
   	
	swaps = fopen("/proc/swaps", "r");
	if(swaps == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		fscanf(swaps,"%s %s %s %s %s\n",s1,s2,s3,s4,s5);
		fscanf(swaps,"%s %s %d %d %d\n",s1,s5, &s_total, &s_used, &s_priority);
		int swap_usado = (100 * s_used) / s_total;
		cout << "Swap total:    " <<  s_total << " kB \n";
		cout << "Swap usado:    " <<  swap_usado << "% \n";
	}
	fclose(swaps);	
}
int main(int argc, char *argv[]){
	
	while(true){
		system("ps -eo pid,min_flt,maj_flt,comm | awk '$2!=0'");
		rotina_memInfo();
		rotina_swaps();
		sleep(2);
		system("clear");
	}
	
return 0;
}
