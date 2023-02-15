#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

#define size 40

void initialize(char board[40][40]); 
char dispmenu(); 
void dispboard(char board[40][40]); 
bool checkcell(int, int); 
void addcell(char board[40][40]); 
void rmcell(char board[40][40]); 
int max(int, int); 
int min(int, int); 
void copyboard(char org[40][40], char cp[40][40]); 
void play(char board[40][40], char boardcp[40][40]); 
void autoplay(char board[40][40], char boardcp[40][40]); 
void control(char, char board[40][40], char boardcp[40][40]); 

int main(int argc, char* argv[]) { 
	system("clear"); 
	char board[40][40]; 
	char boardcp[40][40]; 
	initialize(board); 
	initialize(boardcp); 
	char choice; 
	switch(argc) { 
		case(1): { //interactive mode 
			dispboard(board); 
			
			while(1) {
				choice = dispmenu(); 
				control(choice, board, boardcp); 
			
			} 
			break; 
		}
		
		case(2): { // now batch mode with data file 
			FILE* fp; 
			int x, y; 
			fp = fopen(argv[1], "r"); // read the file 
			if(fp == NULL) {
				printf("File %s not found!\n", argv[1]); 
				return 2; 
			} 
			while(!feof(fp)) {
				fscanf(fp, "%c", &choice); 
				if(choice == 'a') { 
					fscanf(fp, "%d %d", &x, &y); 
					board[x][y] = 'X'; 
				} 
				if(choice == 'p') { //play 
					(autoplay(board, boardcp)); 
				}  
			}
			break;
		} 
		default: // for invalid execution 
			puts("Too many arguments!!!\n"); 
			return 1; 
		
	}
	return 0; 	
}

void initialize(char board[40][40]){ // initialize an empty board
	int i,j; 
	for(i=0; i<40; i=i+1) {
		for(j=0; j<40; j=j+1) {
			board[i][j] = ' '; 
		} 
	}
}

char dispmenu() { // have to display the menu of options and ask for user input 
	printf("Select an option: \n"); 
	printf("a to add a new live cell \n"); 
	printf("r to remove a live cell \n"); 
	printf("n to advance to the next iteration \n"); 
	printf("q to quit the program \n"); 
	printf("p to play the game continously \n"); 
	char choice = getchar();
	getchar(); // to get rid of the new line character 
	return choice; 
}

void dispboard(char board[40][40]) { // now display the contents of the board 
	system("clear"); 
	int i,j; 
	putchar(' '); 
	for(i=0; i<40; i=i+1) { 
		putchar('-'); 
	}
	printf("\n"); 
	for(i=0; i<40; i=i+1) { 
		putchar('|'); 
		for(j=0; j<40; j=j+1) { 
			printf("%c", board[i][j]); 
		}
		puts("|"); 
		}
	putchar(' '); 
	for(i=0; i<40; i=i+1) {putchar('-');}
	putchar('\n');
}

bool checkcell(int i, int j) { 	// check if a cell is in the board or out of bounds 
	if(i>=0 && i<40 && j>=0 && j < 40) {return true;} 
	else {return false;} 
} 

void addcell(char board[40][40]) {//add a live cell 
	int x,y; 
	while(1){
		printf("Coordinates for the new cell: "); 
		scanf("%d %d", &x, &y); 
		getchar();
		if(checkcell(x,y)) {break;}
		else {printf("Invalid input");} 
	}
	if(board[x][y] == ' ') { 
		board[x][y] = 'X'; 
	}
	dispboard(board); 
	printf("\n Operation done! \n \n"); 
}


void rmcell(char board[size][size]) {//add a live cell 
	int x,y; 
	while(1){
		printf("\n Coordinates for the removed cell: "); 
		scanf("%d %d", &x, &y); 
		getchar();
		if(checkcell(x,y)) {break;}
		else {printf("Invalid input");} 
	}
	if(board[x][y] == 'X') { 
		board[x][y] = ' '; 
	}
	dispboard(board); 
	printf("\n Operation done! \n \n"); 
}

int max(int a, int b) {  //Find the bigger number between the two integers
	int res = (a>b) ? a : b; 
	return res; 
} 

int min(int a, int b) {  // Find the smaller number between the two 
	int res = (a<b) ? a : b; 
	return res; 
} 

void copyboard(char org[40][40], char cp[40][40]) { // need to copy org's contents to cp 
	int i,j; 
	for(i=0; i<40; i = i+1) { 
		for(j=0; j<40; j=j+1) { 
			cp[i][j] = org[i][j]; 
		}
	}
}

void play(char board[40][40], char boardcp[40][40]) { //simulate a single move in the game 
	int i,j,m,n,count; 
	for(i=0; i<40; i=i+1) {
		for(j=0; j<40; j = j+1) { 
			if(board[i][j] == ' ') { // rule a
				count = 0; // Count the live neighbors 
				for(m=max(0,i-1); m<=min(40-1, i+1); m=m+1) { 
					for(n=max(0,j-1); n<=min(size-1, j+1); n=n+1) {   // The max restricts program to non-negative integers
						if(m==i && n==j) {continue;} 
						else if(board[m][n] == 'X') {count=count+1;} 
					}
				}
				if(count == 3) {boardcp[i][j] = 'X';}
 			}
		} 
	}
	for(i=0; i<40; i=i+1) {
		for(j=0; j<40; j = j+1) { 
			if(board[i][j] == 'X') { // rule b
				count = 0;
				for(m=max(0,i-1); m<=min(40-1, i+1); m=m+1) {
					for(n=max(0,j-1); n<=min(size-1, j+1); n=n+1) {
						if(m==i && n==j) continue;  
					}
				// Rule to check neighbors
					//char board[40][40];
					int delta[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
					int count = 0;
					for (int m = 0; m < 8; m++) {
						int nx = i + delta[m][0];
						int ny = j + delta[m][1];
						if (board[nx][ny] == 'X') count++;
					} 
					//if(board[m][n] == 'X') {count=count+1;}
					if(count == 3 || count== 2) {boardcp[i][j] = 'X';}
					else {boardcp[i][j] = ' ';} 
				}
			}
		}
	}
	// display
	copyboard(boardcp, board); 
	dispboard(board); 		
} 


void autoplay(char board[size][size], char boardcp[size][size]) {
	while(1){ 
		play(board,boardcp); 
		usleep(200000); 
	}
}

void control(char choice, char board[size][size], char boardcp[size][size]) { 
	switch(choice) { 
		case 'a': //add a new cell 
			addcell(board);
			break; 
		case 'r': // remove an existing cell 
			rmcell(board); 
			break; 
		case 'n': //simulate a move 
			play(board,boardcp);
			break; 
		case 'q': //quit a program 
			printf("\nThank you for playing the game!\n"); 
			exit(0); 
		case 'p': //auto play 
			autoplay(board, boardcp); 
			break; 
		default: 
			printf("Invalid input.\n"); 
	} 
}
