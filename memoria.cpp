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
# include <dirent.h>
using namespace std;

/*Variáveis*/
char caminho[256],cmd[256],s1[9], s2[9], s3[9], s4[9];

void swap(string pid, int *p_swap) {
	FILE *swaps;
	strcpy(cmd, "");
	strcat(cmd, "grep VmSwap /proc/");
	strcat(cmd, pid.c_str());
	strcat(cmd, "/status > swap.txt");
	system(cmd);
	swaps = fopen("swap.txt", "r");
	if(swaps == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		fscanf(swaps,"%s %d %s\n",s1,p_swap,s3);
	}
	fclose(swaps);
}

void mem_info(string pid, float *mem, int *minfl, int *majfl) {
	FILE *memInfo;
	strcpy(cmd, "");
	strcat(cmd, "ps -o pmem,min_flt,maj_flt ");
	strcat(cmd, pid.c_str());
	strcat(cmd, " > mem_infos.txt");
	system(cmd);
	memInfo = fopen("mem_infos.txt", "r");
	if(memInfo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		fscanf(memInfo,"%s %s %s\n",s2,s3,s4);
		fscanf(memInfo,"%f %d %d\n",mem,minfl,majfl);
	}
	fclose(memInfo);
}

int main(int argc, char *argv[]){
	int v = 1; 
	int p_swap;
	float mem;
	char caminho[256];
	int minfl, majfl;
	string pid;
	DIR *dirp;

		system("clear");
		struct dirent *directory_entry;

		if ((dirp = opendir("/proc")) == NULL) {
			perror("Nao foi possivel abri /proc");
			return 1;
		}

		do {
			if ((directory_entry = readdir(dirp)) != NULL) {
				if (directory_entry->d_type == DT_DIR) {
					string nome = directory_entry->d_name;
					int b = nome.size();
					int d=0;
					for(int c=0;c<b;c++) {
				        if(isdigit(directory_entry->d_name[c])){
				       		d++;
				        }
					}
					if (d==b) {
						strcpy(caminho, "");
						strcat(caminho, "/proc/");
						strcat(caminho, directory_entry->d_name);
								
						pid = nome;
						swap(pid, &p_swap);			
						//cache(pid,&p_cache);
						mem_info(pid, &mem, &minfl, &majfl);
						cout << "PID: " << pid << "  Memória usada: " << mem << "%  Cache: " << "[VALOR]" << "  Swap: " << p_swap << " kB  PageFaults Minor: " << minfl << "  PageFaults Major: " << majfl << "\n"; 
					}
				}
			}
		} while (directory_entry != NULL);
	//DETERMINAR O VALOR DA CACHE
return 0;
}
