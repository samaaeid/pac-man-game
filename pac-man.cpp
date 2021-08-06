#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 4;  //TWL
const int M = 8; //3RD
int counter=0;
char grid[N][M];

//This function prints the grid of Gomoku as the game progresses
void print_grid() {
    cout << "\n";
	cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "";
        for (int i = 0; i < M; cout << "", i++);
    }
    for (int i = 0; i < M; cout << "---", i++);
    cout << "----\n";
}

//This function checks if the game has a win state or not
bool check_win() {
    if (counter==N*M-(N*M*1/6 + N*M*1/8)-1) {return true;}
    else {return false;}
}
//This function checks if the game has a tie state or not for the given mark
bool check_lose(int i,int a , int b) {
if (i==3){  if(grid[a][b+1]=='G'){return true;}}

 else if (i==1){ if(grid[a-1][b]=='G'){return true;}}

 else if (i==2){  if(grid[a+1][b]=='G'){return true;}}

 else if (i==4){  if(grid[a][b-1]=='G'){return true;}}
  return false;
}

//This function checks if the game has a tie state or not for the given mark
bool check_wall(int i, int a , int b) {
if (i==3){  if(grid[a][b+1]=='|'){return true;}}

else if (i==1){ if(grid[a-1][b]=='|'){return true;}}

else if (i==2){  if(grid[a+1][b]=='|'){return true;}}

else if (i==4){  if(grid[a][b-1]=='|'){return true;}}
  return false;
}


//This function checks if given position is valid or not
bool check_available_move(int i,int &a,int &b) {
 if (i==3){  if(b+1>M-1){return false;}  } //right
 else if (i==1){  if(a-1<0){return false;} }   // up
 else if (i==2){  if(a+1>N-1){return false;}}   //down
 else if (i==4){  if(b-1<0){return false;}}     //left
return true;
 }


//This function checks if given position is valid or not
bool check_valid_direction(int i) {
    if (i==1 || i==2 || i==3 || i==4 ){
        return true;
        }
    else{return false;}
}

//This function generates pac man
void generate_pac_man(int &a , int &b) {
    srand( (unsigned)time( NULL ) );
    a = rand() % N;
	b = rand() % M;
    grid[a][b] = 'P';
}

//This function generates ghosts
void generate_ghost() {
    srand( (unsigned)time( NULL ) );
    int f=N*M*1/6;
    while ( f>0 )
    {
    int a = rand() % N;
	int b = rand() % M;
    while (grid[a][b] == 'P') {
        a = rand() % N;
        b = rand() % M;
	}
    grid[a][b] = 'G';
    f--;
    }
}

//This function generates a wall
void generate_wall() {
    srand( (unsigned)time( NULL ) );
    int f=N*M*1/8;
    while ( f>0 )
    {
    int a = rand() % N;
	int b = rand() % M;
    while (grid[a][b] == 'G' || grid[a][b] == 'P') {
        a = rand() % N;
        b = rand() % M;
	}
    grid[a][b] = '|';
    f--;
    }
}

//Move with the input direction
void move(int i,int &a,int &b) {
    grid[a][b]='.';
    if (i==3){  if(grid[a][b+1]=='+'){counter+=1; grid[a][b+1]='P';   }
                else if(grid[a][b+1]=='.'){ grid[a][b+1]='P';  } b+=1;  } //right

 else if (i==1){ if(grid[a-1][b]=='+'){counter+=1; grid[a-1][b]='P';}
                 else if(grid[a-1][b]=='.'){ grid[a-1][b]='P'; }  a-=1;  }   // up

 else if (i==2){  if(grid[a+1][b]=='+'){counter+=1; grid[a+1][b]='P';}
                    else if(grid[a+1][b]=='.'){ grid[a+1][b]='P'; } a+=1;}  //down

 else if (i==4){  if(grid[a][b-1]=='+'){counter+=1; grid[a][b-1]='P';}
                  else if(grid[a][b-1]=='.'){ grid[a][b-1]='P'; }b-=1;}  }   //left

//This function clears the game structures
void grid_clear() {
     for (int i =0 ; i<N; i++){
            for (int j =0 ; j<M; j++){
                grid[i][j]='+';
            }
        }
}
//This function reads a valid direction
void read_input(int &i,int &a, int &b) {
    cout << "Enter the direction: ";
	cin >> i;
    while (!check_valid_direction(i) || !check_available_move(i,a,b)) {
        cout << "Enter a valid direction: ";
		cin >> i;
	}
}
//MAIN FUNCTION
void play_game(int &a,int &b) {
    cout << "Pac-Man Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {

        //Prints the grid
        print_grid();
        //Read an input from the player
		int i;
		read_input(i,a,b);

        //Check if the state of the grid has a tie state
        if (check_lose(i,a,b)) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "GAME OVER!\n";
            break;
        }
        if(check_wall(i,a,b)){
            cout<<"WHATCH OUT you hit a wall !! please " ;
            read_input(i,a,b);
        }
        //Move with the input direction
        move(i,a,b);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, you won!\n";
            break;
        }

    }
}
int main() {
    while (true) {
        int a,b;
        grid_clear();
        //
        generate_pac_man(a,b);
        //
        generate_ghost();
        //
        generate_wall();
    	play_game(a,b);
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
