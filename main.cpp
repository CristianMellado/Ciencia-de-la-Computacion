/****************************************************************
Juego: Snake.io Game
UCSP : CIENCIAS DE LA COMPUTACIÓN
Grupo: 1
Integrantes:
 - Alexander Carpio Mamani
 - Marcelo Torres Acuña
 - Cristian Mellado Baca
*****************************************************************/

#include <iostream>
#include <time.h>
#include "windows.hpp" // kbhit y getch
#include <unistd.h>

#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67

#define emoji_1 "\U0001f438" 
#define emoji_2 "\U0001f648"
#define emoji_3 "\U0001f98a"
#define emoji_4 "\U0001f437"
#define emoji_5 "\U0001f981"
#define emoji_6 "\U0001f43c"

#define emoji_apple "\U0001f34e"
#define emoji_meat "\U0001f356"
#define emoji_cake "\U0001f9c1"
#define emoji_kiwi "\U0001f95d"
#define emoji_melon "\U0001f349"
#define emoji_corn "\U0001f33d"

#define emoji_floor "\U0001F7e8"
#define emoji_mark "\U0001f7eb"
#define emoji_heart "\U0001f496" 
#define emoji_win "\U0001f389"

void select_emoji(std::string , std::string&, std::string);

bool collide(int player[][2], int other[][2], int other_score){
  for(int i=1;i<other_score+1;i++){
    if(player[0][0]==other[i][0] && player[0][1]==other[i][1]) return true;
  }
    return false;
}

bool collide_app(int x, int y, int app[][4]){
  for(int i=0;i<20;i++){
    if (x==app[i][0] && y==app[i][1] && app[i][2]==1){
      app[i][2] = 0;
      return true;
    }
  }
  return false;
}

int main(){
  int x, y,a,b, score=0, snake[200][2] = {{10,10}}, snake2[200][2] = {{10,11}}, score2=0, live1=3, live2=3, apples[20][4], n_app, n_fruit;
  char state2=DOWN, state='w';
	bool tail, apple_show, tail2;
  std::string emoji_player1="none", emoji_player2="none";
	
  for(int i=0;i<20;i++){  //inicializate apples
    for(int j=0;j<4;j++){
      apples[i][j] = 0;
    }
  }

  select_emoji(" Player 1", emoji_player1, emoji_player2);
  select_emoji(" Player 2", emoji_player2, emoji_player1);

	while(1){
    std::cout<<"\n\t"<<emoji_heart<<" Player " << emoji_player1 << ": "<<live1<< "\t\t"<<emoji_heart<<" Player " << emoji_player2 << ": "<<live2<<std::endl<<std::endl;
    
		for (int i=0; i<22; i++){
			for (int j=0; j<22; j++){
				tail = false;
				for (int k=0; k<score+1; k++){ // recorre la serpiente
					if (snake[k][0]==j && snake[k][1]==i) tail = true;
				}         

				tail2 = false;
				for (int k=0; k<score2+1; k++){
					if (snake2[k][0]==j && snake2[k][1]==i) tail2 = true;
				}         
				apple_show = false;
				for (int k=0; k<20; k++){
					if (apples[k][0]==j && apples[k][1]==i && apples[k][2]==1){
            apple_show = true;
            n_fruit = apples[k][3];
          }
				}

				if (tail){
          std::cout <<emoji_player1;
				}
				else if (tail2){
          std::cout <<emoji_player2;
				}
        else if (apple_show){
          switch(n_fruit){
            case 0:std::cout <<emoji_apple; break;
            case 1:std::cout <<emoji_meat; break;
            case 2:std::cout <<emoji_cake; break;
            case 3:std::cout <<emoji_kiwi; break;
            case 4:std::cout <<emoji_melon; break;
            case 5:std::cout <<emoji_corn; break;
          }
        }
				else if (i==0 || i == 21 || j ==0 || j == 21){
          std::cout<<emoji_mark;
        }
				else{
          std::cout<<emoji_floor;
        }
			}
			std::cout<<std::endl;
		}

    if (live1==0){
			std::cout<<"\n\t\t\t YOU WIN player "<<emoji_player2<<" "<<emoji_win<<"\n\n";
			break;     
    }
    if (live2==0){
			std::cout<<"\n\t\t\t YOU WIN player "<<emoji_player1<<" "<<emoji_win<<"\n\n";
			break;
		}

		x = snake[0][0]; y = snake[0][1]; 
		//if (x == 0 || x == 21 || y == 0 || y == 21 || collide(snake,snake2,score2)){
    if (collide(snake,snake2,score2)){
      live1--;
      score = 0;
      x = 10;
      y = 10;
    }

		a = snake2[0][0]; b = snake2[0][1]; 
		//if (a == 0 || a == 21 || b == 0 || b == 21 || collide(snake2,snake,score)){
    if (collide(snake2,snake,score)){
      live2--;
      score2 = 0;
      a = 10;
      b = 11;
    }

		if (my_kbhit()){
      char key = my_getch();
        //if (key == 97 || key == 100 || key == 119 || key ==115)
      if (key == 'a' || key == 'd' || key == 'w' || key == 's') state = key;
      if (key == LEFT || key == RIGHT || key == UP || key == DOWN) state2 = key;
    }

    switch(state){
			case 'a': if (x > 1) x--;
                else state = 'd';
                break;
			case 'd': if (x < 20) x++;
                else state = 'a';
                break;
			case 'w': if (y > 1) y--;
                else state = 's';
                break;
			case 's': if (y < 20) y++;
                else state = 'w';
                break;
    }

    switch(state2){
			case LEFT: if (a > 1) a--;
                else state2 = RIGHT;
                break;
			case RIGHT: if (a < 20) a++;
                else state2 = LEFT;
                break;
			case UP: if (b > 1) b--;
                else state2 = DOWN;
                break;
			case DOWN:if (b < 20)  b++;
                else state2 = UP;
                break;
    }
		// la cola sigue a la cabeza
		int ago_x=snake[0][0], ago_y=snake[0][1], copy_x, copy_y;
		for (int i=1; i<score+1; i++){
			copy_x = snake[i][0];
			copy_y = snake[i][1];
			snake[i][0] = ago_x;
			snake[i][1] = ago_y;
			ago_x = copy_x;
			ago_y = copy_y;
		}
		snake[0][0] = x; snake[0][1] = y;

		ago_x=snake2[0][0], ago_y=snake2[0][1];
		for (int i=1; i<score2+1; i++){
			copy_x = snake2[i][0];
			copy_y = snake2[i][1];
			snake2[i][0] = ago_x;
			snake2[i][1] = ago_y;
			ago_x = copy_x;
			ago_y = copy_y;
		}
		snake2[0][0] = a; snake2[0][1] = b;

    srand(time(NULL));
    n_app = rand()%(20);
    if (apples[n_app][2]==0){
      srand(time(NULL));
      apples[n_app][0] = 1 + rand()%(20); 
      apples[n_app][1] = 1 + rand()%(20);
      apples[n_app][2] = 1;
      apples[n_app][3] = rand()%6;
    }

    if (collide_app(snake[0][0], snake[0][1], apples)){
      score++;
    }
    if (collide_app(snake2[0][0], snake2[0][1], apples)){
      score2++;
    }

    usleep(100000); // delay in miliseconds
    std::cout<<"\033[H\033[2J\033[3J"; // limpia la pantalla
  }
	return 0;
}

void select_emoji(std::string text, std::string& var, std::string selected){
  int op; bool error;
  std::cout<<"\n Emojis: "<<std::endl;
  std::cout<<" 1)"<<emoji_1<<std::endl;
  std::cout<<" 2)"<<emoji_2<<std::endl;
  std::cout<<" 3)"<<emoji_3<<std::endl;
  std::cout<<" 4)"<<emoji_4<<std::endl;
  std::cout<<" 5)"<<emoji_5<<std::endl;
  std::cout<<" 6)"<<emoji_6<<std::endl;

  do{
    std::cout <<text<<" enter emoji: ";std::cin>>op;
    error = false;
    if (op==1 && selected!=emoji_1)
      var = emoji_1;
    else if (op==2 && selected!=emoji_2)
      var = emoji_2;
    else if (op==3 && selected!=emoji_3)
      var = emoji_3;
    else if (op==4 && selected!=emoji_4)
      var = emoji_4;
    else if (op==5 && selected!=emoji_5)
      var = emoji_5;
    else if (op==6 && selected!=emoji_6)
      var = emoji_6;
    else
      error = true;
  }while(error);
}