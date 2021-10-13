/***************************************************************
Juego: Snake.io Game v1
UCSP : CIENCIAS DE LA COMPUTACIÓN
Grupo: 1
Integrantes:
 - Alexander Carpio Mamani
 - Marcelo Torres Acuña
 - Cristian Mellado Baca
****************************************************************/
#include <iostream>
#include <time.h>
#include "windows.hpp" // modulo simulacion de kbhit y getch
#include <unistd.h>

#define emoji_snake "\U0001f438" 
#define emoji_apple "\U0001f34e"
#define emoji_floor "\U0001F7e8"
#define emoji_mark "\U0001f7eb"
#define emoji_heart "\U0001f496"

bool collider_with_tail(int x, int y, int tail[][2], int lenght){ //funcion que detecta cocion con la cola.
  for(int i=1; i<lenght+1; i++){
    if (x==tail[i][0] && y==tail[i][1]) return true;
  }
  return false;
}

int main(){
	int x=10, y=10, score=0, snake[50][2], apple[2]={-1,-1}, lives=3;
	char state='w';
	bool tail, apple_show=false;

	snake[0][0] = 10; // inisializacion de la posicion por defectuo de la snake.
	snake[0][1] = 10;
	
	
	while(1){
		std::cout<<emoji_heart<<" LIVES: "<<lives<<"\t\t SCORE:"<<score<<std::endl;
		for (int i=0; i<22; i++){ //bucle i para el alto del tablero
			for (int j=0; j<22; j++){ //bucle j para el ancho del tablero
				tail = false;
				for (int k=0; k<score+1; k++){
					if (snake[k][0]==j && snake[k][1]==i) tail = true;
				}
				
				if (tail){
					std::cout << emoji_snake;
				}
				else if (apple[0] == j && apple[1]==i && apple_show){ //verifica si hay una manzana en el tablero
					std::cout << emoji_apple; //imprime la manzana
				}
				else if (i==0 || i == 21 || j ==0 || j == 21){ 
          std::cout<<emoji_mark; //imprime el marco marron
        }
				else{
          std::cout<<emoji_floor; //imprime el fondo amarillo
        }
      }
			std::cout<<std::endl;
		}
		
    if (lives==0){ // verifica si ya no le quedan vidas
    	std::cout<<"\n YOU LOSE\n"<<std::endl;
			break;
		}

		x = snake[0][0];
		y = snake[0][1];
	  //Detecta cuando el snake choca con una casilla marron o con su propia cola.
  	if (x == 0 || x == 21 || y == 0 || y == 21 || collider_with_tail(x,y,snake,score)){ 
      score = 0;
      lives--;
      x = 10;
      y = 10;
    }

		if (my_kbhit()){//detecta cuando la tecla es presionada 
			char key = my_getch(); // obtiene la ultima tecla presionada del buffer
			if (key == 'a' || key == 'd' || key == 'w' || key == 's')
				state = key;
		}

		switch(state){//movimientos del snake
			case 'a': x--;break;
			case 'd': x++;break;
			case 'w': y--;break;
			case 's': y++;break;
		}
			
		int ago_x=snake[0][0], ago_y=snake[0][1], copy_x, copy_y; //la cola sigue a la cabeza
		for (int i=0; i<score+1; i++){
			copy_x = snake[i][0];
			copy_y = snake[i][1];
			snake[i][0] = ago_x;
			snake[i][1] = ago_y;
			ago_x = copy_x;
			ago_y = copy_y;
		}
		snake[0][0] = x; snake[0][1] = y;

		if (apple_show){//aparece la fruta y desaparece cuando el snake pasa por ahí
			if (snake[0][0]==apple[0] && snake[0][1]==apple[1]){
				apple_show = false;
				score++;
			}
		}
		else{
			apple_show = true;
			srand(time(NULL));
			apple[0] = 1 + rand()%(20); // genera un random para el x en el rango de [1-20]
			apple[1] = 1 + rand()%(20); 
		}
    usleep(100000); // delay in miliseconds
    std::cout <<"\033[H\033[2J\033[3J";  // clear screen
	}
	return 0;
}