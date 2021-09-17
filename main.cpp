#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

//---------------------------------------------------------------------------------------------------------

int global_player_x = 10; //global para x do player
int global_player_y = 9; //global para y do player
int middle_player_y = global_player_y + 2; //meio do jogador

int global_enemy_x = 110; //global para x do oponente
int global_enemy_y = 9; //global para y do oponente
int middle_enemy_y = global_enemy_y + 2; //meio do oponente

int global_ball_x = 60; //global para x da bola
int global_ball_y = 15; //global para y da bola

int lado_bola; //global lado que a bola está indo
int lado_chance; //global chance da bola ir pra cima ou pra baixo 

int score_player; //pontuação do jogador
int score_enemy; //pontuação do oponente
int n_players; //numero de jogadores

//---------------------------------------------------------------------------------------------------------

void mgotoxy(int x, int y){ //função para movimentar o cursor pela tela
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
	
}

void desenhar_paredes_laterais(){ //função utilizada para desenhar os limites da tela

	
	int i = 0;
	
	for(i = 0; i < 118; i++){ //desenha linha superior e inferior
		
		mgotoxy(i + 1,0);
		printf("_");
		mgotoxy(i,28);
		printf("_");
		
	}
	
	for(i = 1; i < 29; i++){ //desenha linhas na esquerda e direita
		
		mgotoxy(0,i);
		printf("|");
		mgotoxy(119,i);
		printf("|");
	}
}

void menu(){ //menu do jogo

	SetConsoleTitle("Pong");
	int seletor;
	printf("bem vindo ao PONG! Quantos jogadores vao jogar? \n");
	scanf("%i", &seletor);
	n_players = seletor;
	system("cls");
	

}

void desenhar_jogador(int movimento){ //função criada para desenhar o jogador na tela e controla-lo apartir da função controles()
	
	char jogador[6] = "BBBBB";
	
	int i;
	
	for (i = 0; i < 6; i++){
		mgotoxy(global_player_x, global_player_y + i);
		printf("%c", jogador[i]);
	}
	
	
	if(movimento == 0){
		global_player_y = global_player_y + 1; //descer jogador 
	}
	
	if(movimento == 1){
		global_player_y = global_player_y - 1; //subir jogador
	}
	
	if (global_player_y > 24) {
		global_player_y = global_player_y - 1; //para o jogador não sair da tela na parte de baixo
	} 
	
		if (global_player_y < 1) {
		global_player_y = global_player_y + 1; //para o jogador não sair da tela na parte de cima
	} 		
}

void desenhar_oponente(){ //desenha o oponente na tela


	char oponente[] = "BBBBB";
	
	int i;
	
	for (i = 0; i < 6; i++){
		mgotoxy(global_enemy_x, global_enemy_y + i);
		printf("%c", oponente[i]);
	}
}

void desenhar_bola(){ //desenha a bola na tela
	
	mgotoxy(global_ball_x, global_ball_y);
	printf("O");
	
}

void oponente_real(int movimento){ //controla o oponente caso ele for uma pessoa

	if(movimento == 0){
		global_enemy_y = global_enemy_y - 1; //descer jogador 
	}
	
	if(movimento == 1){
		global_enemy_y = global_enemy_y + 1; //subir jogador
	}
	
	if (global_enemy_y > 24) {
		global_enemy_y = global_enemy_y - 1; //para o jogador não sair da tela na parte de baixo
	} 
	
		if (global_enemy_y < 1) {
		global_enemy_y = global_enemy_y + 1; //para o jogador não sair da tela na parte de cima
	} 		
}

void IA_oponente(){ //controla a IA do oponente

	
	if (global_ball_y > middle_enemy_y) {
		
		global_enemy_y = global_enemy_y + 1;
		middle_enemy_y = middle_enemy_y + 1;
		
		
	}	
	
	if (global_ball_y < middle_enemy_y) {
		
		global_enemy_y = global_enemy_y - 1;
		middle_enemy_y = middle_enemy_y - 1;
		
	}	
	
	if (global_enemy_y > 24) {
		global_enemy_y = global_enemy_y - 1; //para o jogador não sair da tela na parte de baixo
	} 
	
		if (global_enemy_y < 1) {
		global_enemy_y = global_enemy_y + 1; //para o jogador não sair da tela na parte de cima
	} 		
		
}

void fisica_bola(){ //controla a fisica da bola
	
	if(lado_bola == 0){
		
		global_ball_x = global_ball_x - 2; //lado do jogador
		
		if (global_ball_y == 28){
			
			lado_chance = 1;
			Beep(600, 50);
		
		}
	
		if (global_ball_y == 2){
		
			lado_chance = 10;
			Beep(600, 50);
		}

		
		if (lado_chance % 2 == 0){
				
				global_ball_y = global_ball_y + 1; 
				
		}
		
		if (lado_chance % 2 == 1){
			
				global_ball_y = global_ball_y - 1; 
			
		}
	}
	
	if(lado_bola == 1){
		
		global_ball_x = global_ball_x + 2;	//lado do openente
		
		if (global_ball_y == 28){
		
			lado_chance = 1;
			Beep(600, 50);
		
		}
	
		if (global_ball_y == 1){
		
			lado_chance = 10;
			Beep(600, 50);
			
		}

		
		if (lado_chance % 2 == 0){
				
				global_ball_y = global_ball_y + 1; 
				
		}
		
		if (lado_chance % 2 == 1){
			
				global_ball_y = global_ball_y - 1; 
			
		}
	}
	


	if(global_ball_x == global_player_x && (global_ball_y == global_player_y || global_ball_y == global_player_y + 1 || global_ball_y == global_player_y + 2 || global_ball_y == global_player_y + 3 || global_ball_y == global_player_y + 4 )){ //checar colisão com o player
		
		lado_bola = 1; // se a colisão for verdadeira, a bola vai para o lado do oponente
		lado_chance = rand() % 100;
		Beep(600, 50);
		
	}
	
	if(global_ball_x == global_enemy_x && (global_ball_y == global_enemy_y || global_ball_y == global_enemy_y + 1 || global_ball_y == global_enemy_y + 2 || global_ball_y == global_enemy_y + 3 || global_ball_y == global_enemy_y + 4 )){ //checar colisão com o oponente
		
		lado_bola = 0; // se a colisão for verdadeira, a bola vai para o lado do jogador
		lado_chance = rand() % 100;
		Beep(600, 50);
		
	}
	
	
	
}

void pontuacao(){ //conta os pontos de cada competidor

	if (global_ball_x == 2) {
		
		score_enemy = score_enemy + 1;
		global_ball_x = 60;
		global_ball_y = 15;
		
	}
	
	if (global_ball_x == 118) {
		
		score_player = score_player + 1;
		global_ball_x = 60;
		global_ball_y = 15;
		
		
	}

}

int controles(){ //função responsavel por movimentar o personagem e checar as teclas apertadas
	
	char key;
	
	if(kbhit()){
		key = getch();
	}
	
	if(int(key) == 119){
		int(key) = 00;
		return(1); //descer
	}
	
	if(int(key) == 115){
		int(key) = 00;
		return(0); //subir
	}
	
	else{
		return(3); //faz nada
	}
		
}

int controles_oponente(){ //define os controles do oponente

	char key;
	
	if(kbhit()){
		key = getch();
	}
	
	if(int(key) == 108){
		int(key) = 00;
		return(1); //descer
	}
	
	if(int(key) == 111){
		int(key) = 00;
		return(0); //subir
	}
	
	else{
		return(3); //faz nada
	}

}

int main(void){
	
	int mover;
	int mover_op;
	srand(time(NULL)); //inicializa a função para criação de numeros aleatorios
	lado_bola = rand() % 1;
	menu();

	while(1){
		
		desenhar_paredes_laterais();
		mover = controles();
		mover_op = controles_oponente();
		desenhar_bola();
		fisica_bola();
		desenhar_jogador(mover);
		desenhar_oponente();
		if(n_players == 1){
			IA_oponente();
		}
		else{
			oponente_real(mover_op);
		}
		pontuacao();
		printf("\e[?25l"); //esconder cursor
		system("cls");	
		mgotoxy(10, 29);
		printf("%i", score_player);
		mgotoxy(110, 29);
		printf("%i", score_enemy);
	}
	
	return 0;
}
