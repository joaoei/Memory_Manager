#include "spaces.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

char caminho[256],cmd[256],s1[9], s2[9], s3[9], s4[9];

int swap(string pid, int *p_swap) {
	DIR *dir;
	strcpy(caminho, "");
	strcat(caminho, "/proc/");
	strcat(caminho, pid.c_str());
	if ((dir = opendir(caminho)) == NULL) {
		*(p_swap) = 0;
		return -1;
	} else {
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
			char c;
			c = getc(swaps); /* Lê o primeiro caracter */	
			if (feof(swaps))		/* Verifica se o caracter lido é o fim de arquivo */	{
				*(p_swap) = 0;
			} else {
				rewind(swaps);
				fscanf(swaps,"%s %d %s\n",s1,p_swap,s3);
			}	

		}
		fclose(swaps);
		return 0;
	}
}

int mem_info(string pid, float *mem, int *minfl, int *majfl) {
	DIR *dir;
	strcpy(caminho, "");
	strcat(caminho, "/proc/");
	strcat(caminho, pid.c_str());
	if ((dir = opendir(caminho)) == NULL) {
		*(mem) = 0.0;
		*(minfl) = 0;
		*(majfl) = 0;
		return -1;
	} else {
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
		return 0;
	}
	
}

int main(int argc, char *argv[]){

	int v = 1; 
	int p_swap;
	float mem;
	int minfl, majfl, n_pid;
	string pid, param, p;
	vector<string> ordem;
	FILE *ordemInfo;

	param = "pid";
	if (argc >= 2)  {
		cout << argv[1] << "\n";
		stringstream( argv[1] ) >> p;
    	if (p == "-m") {
    		param = "pmem";
    	} else if (p == "-pgmin") {
    		param = "min_flt";
    	} else if (p == "-pgmaj") {
    		param = "maj_flt";
    	} else {
    		cout << "-m: ordenação pela memómia\n";
    		cout << "-pgmin: ordenação pelo Page Faults Minor\n";
    		cout << "-pgmaj: ordenação pelo Page Faults Major\n";
    		cout << "Parâmetro inválido, o programa irá funcionar com a ordenação pelo pid\n";

    	}
    } 


		//system("clear");

		strcpy(cmd, "");
		strcat(cmd, "ps -eo pid --sort ");
		strcat(cmd, param.c_str());
		strcat(cmd, " > ordem.txt");
		system(cmd);

		ifstream myfile ("ordem.txt");
		if (myfile.is_open()) {
		  	getline (myfile,pid);
		    while (! myfile.eof() ) {
		     	getline (myfile,pid);
    			pid.erase(remove(pid.begin(), pid.end(), ' '), pid.end());
		      	ordem.push_back(pid);
		    }
		    myfile.close();
		}

	cout << "PID:   " << "%Memória usada:  " << "\%Cache: " << " Swapping:  " << "PageFaults Minor:   " << "PageFaults Major:" << "\n";
	for(int i = 0; i < ordem.size() - 1; i++) {
		int s = swap(ordem[i], &p_swap);			
		//cache(pid,&p_cache);
		int m = mem_info(ordem[i], &mem, &minfl, &majfl);
		if ( !((s == -1) || (m == -1)) ) {
			cout << ordem[i] <<spacePID(atoi(ordem[i].c_str()));//
			printf("%.1f",mem);//
			cout << spaceM(mem)<< "[VALOR]" <<"   "<< p_swap << spaceSWAP(p_swap)<< minfl <<spaceMIN(minfl)<< majfl <<endl;
		} 
	}
		system("rm mem_infos.txt swap.txt");
return 0;
}
