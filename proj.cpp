#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
void printboard(int n , int**board);
void startgame();
bool endgame(int n , int **board);
void game(int n , int **board , int **check);
bool checkWin(int n  ,int **board , int x , int y , int **check);
bool isSafe(int n , int **board , int x , int y);
void menuscrn();
bool pc = false;//true pc playing
bool pc_as = false; //false means eater true means passer
void printboard(int n , int **board){
	int i , j;
		printf("\t\ty:x:");
	for(i = 0 ; i< n ; i++){
		printf(" %d   " ,  i);
	}
	printf("\n");
	for(i = 0 ; i<n ; i++){
		printf("  \t\t%d " , i);
		for(j =0 ; j<n ; j++){
			switch(board[i][j]){
				case 0:
					printf("  |-|" );
					break;
				case 1:
					printf("  |P|");
					break;
				case 2:
					printf("  |E|");
					break;		
			}
			
		}
		printf("\n");
	}
}
void startgame(){
	int n,j,i;
	printf("enter size of board : ");
	scanf("%d",&n);

	 int ** board = (int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++)
        *(board+i) = (int*)malloc(sizeof(int)*n);
	
	
	for(i = 0 ; i<n ; i++){
		for(j =0 ; j<n ; j++){
		board[i][j] = 0;
		}
	}
	
	 int ** check = (int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++)
        *(check+i) = (int*)malloc(sizeof(int)*n);
	for(i = 0 ; i<n ; i++){
		for(j =0 ; j<n ; j++){
			check[i][j] = 0;
		}
	}

	game(n,board,check);
	printboard(n , board);
}
bool endgame(int n , int **board){
	int i , j;
	for(i =0 ; i<n ; i++){
		for(j = 0 ; j<n ; j++){
			if(board[i][j] == 0){
				return false;
			}
		}	
	}
	printf("eater won\n");
	printboard(n,board);
	getchar();
	getchar();
	menuscrn();
	return true;
}
void game(int n , int **board , int **check){
	bool end = false;
	int px , py , ex , ey , i;
	
	while(!endgame(n,board) && !end){
		printboard(n , board);
		//mooves  for passer
		if(pc && pc_as){ // pc as passer
			while(true){
				px = (rand() % (n - 0 + 1)) + 0;
				py = (rand() % (n - 0 + 1)) + 0;
				
			if( px<n && py<n && board[px][py] == 0 ){
				printf("PC move : y:%d x:%d" , py , px);
				break;
			}
			
		}
			
		}
		else{ // human as passer
			while(true){
				printf("passer enter move \npasser y:");
				scanf("%d" , &px);
				printf("passer x:");
				scanf("%d",&py);
				if(px<n && py<n && board[px][py] == 0  ){
				break;
				}else{
					printf("move not valid please enter again");
				}
			}
	}
		if(pc && !pc_as){
			while(true){
				ex = (rand() % (n - 0 + 1)) + 0;
				ey = (rand() % (n - 0 + 1)) + 0;
			
			if( ex<n && ey<n && board[ex][ey] == 0 ){
				printf("PC move : y:%d x:%d" , ey , ex);
				break;
			}
		}
			
		}
		else{
		
		while(true){
			printf("eater enter move \neater y:");
			scanf("%d" , &ex);
			printf("eater x:");
			scanf("%d" , &ey);
			if( ex<n && ey<n && board[ex][ey] == 0 ){
				break;
			}else{
				printf("move not valid please enter again");
			}
		}
	}
			board[px][py] = 1;
			board[ex][ey] = 2;
		
		int i = 0 ;
		for(i = 0 ; i<n ; i++){ // calls checkWin for first line
			if(checkWin(n , board , 0 ,i , check)){
				system("cls");
				printboard(n,board);	
				printf("\n");
				printboard(n,check);			
				printf("passer win\n enter any key to continue");
				getchar();
				getchar();
				end = true;
				menuscrn();	
			}
		}
		
		getchar();
		getchar();
		system("cls");	
	
	}
}
bool checkWin(int n  ,int **board , int y, int x , int **check){
	if(y == n-1 && board[y][x]==1){//base condition
		check[y][x] = 1;
		return true; //paser win
	}
	if(isSafe(n , board , y ,x)){
		if(check[y][x] == 1){
			return false;
		}
		
		check[y][x] = 1;
		
		if(checkWin(n,board, y+1 ,x ,check)){
			return true;
		}		
		if(checkWin(n,board,y+1,x+1,check)){
			return true;
		}		
		if(checkWin(n,board,y+1,x-1,check)){
			return true;
		}		
		
		// move up y+1
		//move down y-1
		//move right x+1
		//move left x-1
		
		
		check[y][x] = 0;  //marks 0 for later use
		return false;
	}
	return false;
}
bool isSafe(int n , int **board , int y , int x ){
//	printf("y:%d x:%d \n" , y , x );

	if(x < n && y < n && x >= 0 && y >= 0 && board[y][x] == 1 ){//out of bounds  passer
	//		printf("safe\n");
		return true;
	}
//	printf("not safe\n");
	return false;
}
void menuscrn(){
	int x;
	system("cls");
	printf("\t1 - multiplayer \n\t2 - VS pc\n");
	scanf("%d", &x);
	switch(x){
		case 1:
			pc = false; // bool false means  pc not playing
			printf("***playing multiplayer***");
			break;
			
		case 2:
			pc = true;
			printf("1 - PC as EATER\n2 - PC as PASSER\n");
			int xx;
			scanf("%d",&xx);
			if(xx==1){
				pc_as = false;
				printf("***playing with PC as EATER***");
			}
			else{
				printf("***playing with PC as PASSSER***");
				pc_as = true;
			}
			break;
			
		default:
			printf("invalid input");
			sleep(1);
			menuscrn();
	}
	sleep(1.7);
	system("cls");
	startgame();
}


int main(){
	sleep(1);
	printf("\n\n\n\n\n\n");
	printf("\t\t\t==========================================================\n");
	sleep(1);
	printf("\t\t\t==========================================================\n");
	sleep(1);
	printf("\t\t\t\t\t\t  WELCOME\n");
	sleep(1);
	printf("\t\t\t\t\t\t    TO\n");
	sleep(1);
	printf("\t\t\t\t\t\t THE GAME\n");
	sleep(1);
	printf("\t\t\t==========================================================\n");
	sleep(1);
	printf("\t\t\t==========================================================\n");
	sleep(1);
	printf("\t\t\t\t\t  press enter to start");
	sleep(1);
	getchar();
	system("cls");
	menuscrn();
	
}


