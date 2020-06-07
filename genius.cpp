#include <iostream>
#include "BlackGPIO/BlackGPIO.h"
#define MAX 13
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <sys/time.h>


using namespace std;
using namespace BlackLib;

//GLOBAIS 
	BlackGPIO vermelho(GPIO_27,output);
	BlackGPIO amarelo(GPIO_65,output);
	BlackGPIO verde(GPIO_47,output);
	BlackGPIO azul(GPIO_46,output);

	BlackGPIO botaoRestart(GPIO_26,input);

	BlackGPIO in_verm(GPIO_112,input);
	BlackGPIO in_amar(GPIO_115,input);
	BlackGPIO in_verd(GPIO_20,input);
	BlackGPIO in_azul(GPIO_49,input);

	BlackGPIO displayA(GPIO_66,output);
	BlackGPIO displayB(GPIO_67,output);
	BlackGPIO displayC(GPIO_69,output);
	BlackGPIO displayD(GPIO_68,output);
	BlackGPIO displayE(GPIO_45,output);
	BlackGPIO displayF(GPIO_44,output);
	BlackGPIO displayG(GPIO_60,output);
	//BlackGPIO //displayPonto(GPIO_46,output);
	struct timeval tempo_inicial, tempo_final;
	int numeroAcertos = 0;
	int level = 1;
	int sequencia[MAX];
	bool flagPiscarSequencia = false;
	bool firstStart = true;
	string restart = "0";
	bool perdeu = false;
	bool lerBotao = false;

void blink(int n);
void blink_seq();
void getBotao();
void piscar();
void displayLevel();
void funcaoRestart();
void criarSequencia();

int main(int argc,char * argv[]){
	
	criarSequencia();
	gettimeofday(&tempo_inicial,NULL);
	gettimeofday(&tempo_final,NULL);

	thread threadLeituraBotao (getBotao);
	thread threadDisplayLevel (displayLevel);
	thread threadBlinkLeds (blink_seq);
	thread threadRestart (funcaoRestart);

	threadLeituraBotao.join();
	threadBlinkLeds.join();
	threadDisplayLevel.join();
	threadRestart.join();
	while (1){

	}
}

/*void tempo()
{
	gettimeofday(&temp,NULL);

	thread threadLeituraBotao (getBotao);
}*/

void displayLevel(){
	cout<<"entrou no display lv\n";
		sleep(1);
	while(1){
		switch(level-1){
			case 0:
				//10 9 7 5 4 2 
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(low);
				displayF.setValue(low);
				displayG.setValue(high);
				////displayPonto.setValue(low);
				break;
			case 1:
				//9 7
				displayA.setValue(high);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(high);
				displayE.setValue(high);
				displayF.setValue(high);
				displayG.setValue(high);
				////displayPonto.setValue(low);
				break;
			case 2:
				//10 9 1 4 5
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(high);
				displayD.setValue(low);
				displayE.setValue(low);
				displayF.setValue(high);
				displayG.setValue(low);
				//displayPonto.setValue(low);
				break;
			case 3:
				//10 9 1 7 5
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(high);
				displayF.setValue(high);
				displayG.setValue(low);
				//displayPonto.setValue(low);
				break;
			case 4:
				//2 1 9 7
				displayA.setValue(high);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(high);
				displayE.setValue(high);
				displayF.setValue(low);
				displayG.setValue(low);
				//displayPonto.setValue(low);
				break;
			case 5:
				//10 2 1 7 5
				displayA.setValue(low);
				displayB.setValue(high);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(high);
				displayF.setValue(low);
				displayG.setValue(low);
				//displayPonto.setValue(low);
				break;
			case 6:
				//10 2 1 7 5 4 6
				displayA.setValue(low);
				displayB.setValue(high);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(low);
				displayF.setValue(low);
				displayG.setValue(low);
				//displayPonto.setValue(high);
				break;
			case 7:
				//10 9 7
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(high);
				displayE.setValue(high);
				displayF.setValue(high);
				displayG.setValue(high);
				//displayPonto.setValue(low);
				break;
			case 8:
				//1 2 4 5 7 9 10
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(low);
				displayF.setValue(low);
				displayG.setValue(low);
				//displayPonto.setValue(low);
				break;
			case 9:
				//1 2 5 7 9 10 6
				displayA.setValue(low);
				displayB.setValue(low);
				displayC.setValue(low);
				displayD.setValue(low);
				displayE.setValue(high);
				displayF.setValue(low);
				displayG.setValue(low);
				//displayPonto.setValue(high);
				break;
		};
	}
}
void criarSequencia(){
	srand(time(NULL));
	int i;

	for (i=0;i<MAX;i++)
	{
		sequencia[i] = rand()%4;	
	}
}

void funcaoRestart(){
	while(1){
		if((tempo_final.tv_sec - tempo_inicial.tv_sec) > 15 ){
			lerBotao = false;
			perdeu = true;
			cout<<"tempo_esgotado\n";
		}

		restart = botaoRestart.getValue();
		if (restart == "1" || perdeu){
			while(botaoRestart.getValue() == "1"){
		//faz nada
			}
			//restart = botaoRestart.getValue();//penso em retirar isso
			cout<<"deu restart\n";
			level = 1;
			numeroAcertos = 0;
			criarSequencia();
			sleep(3);
			flagPiscarSequencia = true;
		}
	perdeu = false;
	}
}

void getBotao(){
	while(1){
		
	int n;

	if(lerBotao){
		gettimeofday(&tempo_final,NULL);
		if(in_verm.getValue() == "1"){
		n = 0;
			if(sequencia[numeroAcertos]==n){
				numeroAcertos ++;
				gettimeofday(&tempo_final,NULL);
				cout<<"bt_vermelho\n";
				while(in_verm.getValue() == "1"){
					vermelho.setValue(high);
				}
					vermelho.setValue(low);
				if(numeroAcertos == level){
					level ++;
					numeroAcertos = 0;
					flagPiscarSequencia = true;
				} else {

				}
			} else {
				perdeu = true;
			}			
		}	else if(in_amar.getValue()  == "1"){
			n = 1;
			if(sequencia[numeroAcertos]==n){
				numeroAcertos ++;
				cout<<"bt_amar\n";
				while(in_amar.getValue()  == "1"){
				amarelo.setValue(high);
				}
				amarelo.setValue(low);
				if(numeroAcertos == level){
					level ++;
					numeroAcertos = 0;
					flagPiscarSequencia = true;
				} else {
				}
			}
			else {
				perdeu = true;
			}
		}	else if(in_verd.getValue()  == "1"){
			n = 2;
			if(sequencia[numeroAcertos]==n){
				numeroAcertos ++;
				cout<<"bt_verde\n";
				while(in_verd.getValue()  == "1"){
					verde.setValue(high);
				}
				verde.setValue(low);
				if(numeroAcertos == level){
					level ++;
					numeroAcertos = 0;
					flagPiscarSequencia = true;
				}  else {
					}
				} 
			else {
				perdeu = true;
			}
		}	else if (in_azul.getValue()  == "1"){
			n =3;
			if(sequencia[numeroAcertos]==n){
				numeroAcertos ++;
				cout<<"bt_azul\n";
				while(in_azul.getValue()  == "1"){
				azul.setValue(high);
				}
				azul.setValue(low);
				if(numeroAcertos == level){
					level ++;
					numeroAcertos = 0;
					flagPiscarSequencia = true;
				} else {
				}
			}
			else {
				perdeu = true;
				}
			}
		}	
	}
}


void blink(int n)
{	
	vermelho.setValue(low);
	amarelo.setValue(low);
	verde.setValue(low);
	azul.setValue(low);
	cout<<"Valor de n = "<<n<<endl;
	if(n==0){vermelho.setValue(high);
		sleep(1);
		vermelho.setValue(low);
	}
	if(n==1){amarelo.setValue(high);
			sleep(1);
		amarelo.setValue(low);
	}
	
	if(n==2){verde.setValue(high);
			sleep(1);
		verde.setValue(low);
	}
	
	if(n==3){azul.setValue(high);
			sleep(1);
		azul.setValue(low);
	}
}

void piscar(){
	vermelho.setValue(low);
	amarelo.setValue(low);
	verde.setValue(low);
	azul.setValue(low);
	sleep(1);
	vermelho.setValue(high);
	amarelo.setValue(high);
	verde.setValue(high);
	azul.setValue(high);
	sleep(1);
	vermelho.setValue(low);
	amarelo.setValue(low);
	verde.setValue(low);
	azul.setValue(low);
	sleep(1);
	vermelho.setValue(high);
	amarelo.setValue(high);
	verde.setValue(high);
	azul.setValue(high);
	sleep(1);
	vermelho.setValue(low);
	amarelo.setValue(low);
	verde.setValue(low);
	azul.setValue(low);
	sleep(1);
}

void blink_seq(){
	lerBotao =false;
	cout<<"entrou blink_seq\n";
	while (1){
		if(flagPiscarSequencia){
			cout<<"Piscando Sequencia\n";
			piscar();
			for (int it=0;it<level;it++){
				blink(sequencia[it]);
				sleep(1);
			}
			gettimeofday(&tempo_inicial,NULL);
			gettimeofday(&tempo_final,NULL);
			lerBotao = true;
			flagPiscarSequencia = false;
		}
	}
}
