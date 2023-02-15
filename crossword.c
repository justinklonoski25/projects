#define _GNU_SOURCE   // needed for strfry 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h>
#include <time.h>

#define boardsize 15
#define wordsize 15     
#define wordcount 20

typedef struct{        // struct is pass by value
    	bool inserted; 
	int x; 
	int y; 
	bool position; 
	char str[50]; 
}WordData;


// all the function prototypes 
void initialize_board(char [][boardsize+2]);
void display_solution_board(char [][boardsize+2], FILE *fp); 
void display_puzzle_board(char [][boardsize+2], FILE *fp);  
void display_clues(WordData [], int, FILE *fp); 
int getwords(WordData []); 
int all_letters(char [], int); 
int getfile(char [], WordData []);  
void uppercase(WordData [], int); 
void sort_words(WordData [], int); 
void insert(char [][boardsize+2], WordData [], int, int, bool, int); 
bool open(char [][boardsize+2], WordData , int, int, bool, int);
void insert_all(char board[][boardsize+2], WordData [], int); 
void continue_insert(char board[][boardsize+2], WordData [], int);

 int main(int argc, char *argv[]) {              
 	WordData words[wordcount];            
 	char board[boardsize+2][boardsize+2];          
 	int count = 0;                  
 	initialize_board(board);                    
 // If user enters no arguments then function prompts user to enter words                           
 	if (argc == 1) {                                                                                                                                                                                
		printf("\nAnagram Crossword Puzzle Generator\n");                                                                                     
		printf("-----------------------------------\n\n"); 
		count = getwords(words); 
 	}                                                                                                                                                                                            
 // If user enters at least 1 argument then it obtains the txt file of words                                                                                                                        
 	else if (argc > 1) {    
		count = getfile(argv[1], words); 
	}                                                                                                                                                                       
// If user enters more than 3 arguments then it returns an error                                                                                                                                   
 	else if (argc > 3) {                                                                                                                                                                         
		printf("Error: too many arugments entered.\n");                                                                                                                                     
		return 1;                                                                                                                                                        
 	}                                                                                                                                                                         
 // If the file is not found then it returns an error                                                                                                                                               
 	if (count == -1) {                                                                                                                                                                   
		printf("Error: file does not exist.\n");                                                                                                            
		return 1;   
	}                                                                                                                                                                                             
 	uppercase(words, count);       // call in the function to convert characters to uppercase                                                                                          
   	sort_words(words, count);                                                                                                                                                                        
 	int middle_x = (boardsize - strlen(words[0].str))/2;        
	int middle_y = boardsize/2;                                                                                                                                     
 // Places the first word on the board                                                                                                                                                              
 	insert(board, words, middle_x, middle_y, true, 0);                                                                                                                                                 
// Places the remaining words on the board                                                                                                                                                         
 	insert_all(board, words, count);                                                                                                                                                                  
 	continue_insert(board, words, count);                                                                                                                                       
 // If the user enters less than 3 arguments then it prints the output to the screen                                                                                                                
 	if(argc < 3) {                                                                                                                                                                                   
  		display_solution_board(board, stdout);                                                                                                                                                   
 		display_puzzle_board(board, stdout);                                                                                                                                                     
  		display_clues(words, count, stdout);                                                                                                                                                 
	}                                                                                                                                                                                             
// If the user enters 3 arguments then it prints the output to a txt file                                                                                                                          
	else if(argc == 3) {                                                                                                                                                                          
		FILE *fp = fopen(argv[2], "w"); // w to write
		display_solution_board(board, fp);                                                                                                                                                     
		display_puzzle_board(board, fp);                                                                                                                                          
		display_clues(words, count, fp);                                                                                                                                                        
    	}                                                                                                                                                                                            
 	return 0;                                                                                                                                                                                    
}
      
// Initializes the board by setting all values to null value                                                                                                                                             
void initialize_board(char board[][boardsize+2]) {                                                                                                                                                  
 int row, col;                                                                                                                                                                                      
 for (row = 0; row < boardsize+2; row++) {                                                                                                                                                          
  for (col = 0; col < boardsize+2; col++) {                                                                                                                                                         
   board[row][col] = '\0';                                                                                                                                                                          
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Displays the solution board                                                                                                                                                                      
void display_solution_board(char board[][boardsize+2], FILE *fp) {                                                                                                                                  
 fprintf(fp, "\nSolution:\n");                                                                                                                                                                      
 int row, col;                                                                                                                                                                                      
 for (row = 0; row < boardsize+2; row++) {                                                                                                                                                          
  for (col = 0; col < boardsize+2; col++) {                                                                                                                                                         
   if((row == 0) || (row == boardsize+1)) {       // different cases for formatting                                                                                                                  
    fprintf(fp, "-");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else if((col == 0) || (col == boardsize+1)) {                                                                                                                                                    
    fprintf(fp, "|");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else if(board[row][col] == '\0') {                                                                                                                                                               
    fprintf(fp, ".");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else {                                                                                                                                                                                           
    fprintf(fp, "%c", board[row][col]);                                                                                                                                                             
   }                                                                                                                                                                                                
   if(col == boardsize+1) {                                                                                                                                                                         
    fprintf(fp, "\n");                                                                                                                                                                              
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 fprintf(fp, "\n");                                                                                                                                                                                 
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Displays the unsolved board                                                                                                                                                                      
void display_puzzle_board(char board[][boardsize+2], FILE *fp) {                                                                                                                                    
 fprintf(fp, "Crossword puzzle:\n");                                                                                                                                                                
 int row, col;                                                                                                                                                                                      
 for (row = 0; row < boardsize+2; row++) {                                                                                                                                                          
  for(col = 0; col < boardsize+2; col++) {                                                                                                                                                          
   if((row == 0) || (row == boardsize+1)) {                                                                                                                                                         
    fprintf(fp, "-");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else if((col == 0) || (col == boardsize+1)) {                                                                                                                                                    
    fprintf(fp, "|");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else if(board[row][col] == '\0') {                                                                                                                                                               
    fprintf(fp, "#");                                                                                                                                                                               
   }                                                                                                                                                                                                
   else {                                                                                                                                                                                           
    fprintf(fp, " ");                                                                                                                                                                               
   }                                                                                                                                                                                                
   if(col == boardsize+1) {                                                                                                                                                                         
    fprintf(fp, "\n");                                                                                                                                                                              
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Displays the clues (user will see them below the board)                                                                                                                                       
void display_clues(WordData words[], int count, FILE *fp) {                                                                                                                                         
 fprintf(fp, "\nClues:\n\n");                                                                                                                                                                       
 char shuff[15];                                                                                                                                                                                    
 int n;                                                                                                                                                                                             
 for(n = 0; n < count; n++) {                                                                                                                                                                       
  if(words[n].inserted == true) {                                                                                                                                                                   
   strcpy(shuff, words[n].str);                                                                                                                                                                     
   strfry(shuff);                                                                                                                                                                                   
   fprintf(fp, "%2d,%2d ", words[n].x, words[n].y);                                                                                                                                                 
   if(words[n].position == true) {                                                                                                                                                                  
    fprintf(fp, "Across ");                                                                                                                                                                         
   }                                                                                                                                                                                                
   else {                                                                                                                                                                                           
    fprintf(fp, "Down   ");                                                                                                                                                                         
   }                                                                                                                                                                                                
   fprintf(fp, "%s\n", shuff);                                                                                                                                                                      
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Obtains words from the user's input                                                                                                                                                                      
int getwords(WordData words[]) {                                                                                                                                                                    
 int count = 0;                                                                                                                                                                                     
 char new_word[wordsize];                                                                                                                                                                           
 while(1) {                                                                                                                                                                                         
  printf("Enter next word or period to end: ");                                                                                                                                                     
  fgets(new_word, wordsize, stdin);                                                                                                                                                                 
  char *last = strchr(new_word, '\n');                                                                                                                                                              
  if (last != NULL) {                                                                                                                                                                               
   *last = '\0';                                                                                                                                                                                    
  }                                                                                                                                                                                                 
  else {                                                                                                                                                                                            
   while(fgetc(stdin) != '\n') {}                                                                                                                                                                   
   printf("Error: word is too long. Try again.\n");                                                                                                                                                 
   continue;                                                                                                                                                                                        
  }                                                                                                                                                                                                 
  if(strcmp(new_word, ".") == 0) {                                                                                                                                                                  
   break;                                                                                                                                                                                           
  }                                                                                                                                                                                                 
  if(all_letters(new_word, strlen(new_word)) == 0) {                                                                                                                                                
   printf("Error: word contains characters that are not letters. Try again.\n");                                                                                                                    
   continue;                                                                                                                                                                                        
  }                                                                                                                                                                                                 
  if(strlen(new_word) < 2) {                                                                                                                                                                        
   printf("Error: word is too short. Try again.\n");                                                                                                                                                
   continue;                                                                                                                                                                                        
  }                                                                                                                                                                                                 
  strcpy(words[count].str, new_word);                                                                                                                                                               
  words[count].inserted = false;                                                                                                                                                                    
  words[count].x = -1;                                                                                                                                                                              
  words[count].y = -1;                                                                                                                                                                              
  words[count].position = true;                                                                                                                                                                     
  count++;                                                                                                                                                                                          
  if(count > wordcount - 1) {                                                                                                                                                                       
   printf("Word count has reached maximum.\n");                                                                                                                                                     
   break;                                                                                                                                                                                           
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 printf("\n");                                                                                                                                                                                      
 return count;                                                                                                                                                                                      
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Checks to see if the word consists of all letters                                                                                                                                                
int all_letters(char word[], int size) {                                                                                                                                                            
 bool letter = true;                                                                                                                                                                                
 int n;                                                                                                                                                                                             
 for(n = 0; n < size; n++) {                                                                                                                                                                        
  if(isalpha(word[n]) == 0) {                                                                                                                                                                       
   letter = false;                                                                                                                                                                                  
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 return letter;                                                                                                                                                                                     
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Reads the words from a txt file                                                                                                                                                                  
int getfile(char name[], WordData words[]) {                                                                                                                                                        
 FILE *fp = fopen(name, "r");                                                                                                                                                                       
 int count = 0;                                                                                                                                                                                     
 char new_word[wordsize];                                                                                                                                                                           
 if(!fp) {                                                                                                                                                                                          
  return -1;                                                                                                                                                                                        
 }                                                                                                                                                                                                  
 while(1) {                                                                                                                                                                                         
  fgets(new_word, wordsize, fp);                                                                                                                                                                    
  char *last = strchr(new_word, '\n');                                                                                                                                                              
  if(last != NULL) {                                                                                                                                                                                
   *last = '\0';                                                                                                                                                                                    
  }                                                                                                                                                                                                 
  if((feof(fp)) || (strcmp(new_word, ".") == 0)) {                                                                                                                                                  
   break;                                                                                                                                                                                           
  }                                                                                                                                                                                                 
  strcpy(words[count].str, new_word);                                                                                                                                                               
  words[count].inserted = false;                                                                                                                                                                    
  words[count].x = -1;                                                                                                                                                                              
  words[count].y = -1;                                                                                                                                                                              
  words[count].position = true;                                                                                                                                                                     
  count++;                                                                                                                                                                                          
 }                                                                                                                                                                                                  
 return count;                                                                                                                                                                                      
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Converts all letters in a string to uppercase                                                                                                                                                    
void uppercase(WordData words[], int count) {                                                                                                                                                       
 int n, i;                                                                                                                                                                                          
 char str[wordsize];                                                                                                                                                                                
 for(n = 0; n < count; n++) {                                                                                                                                                                       
  strcpy(str, words[n].str);                                                                                                                                                                        
  for(i = 0; i < strlen(str); i++) {                                                                                                                                                                
   str[i] = toupper(str[i]);                                                                                                                                                                        
  }                                                                                                                                                                                                 
  strcpy(words[n].str, str);                                                                                                                                                                        
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Sorts words by length from longest to shortest                                                                                                                                                   
void sort_words(WordData words[], int count) {                                                                                                                                                      
 bool check = true;                                                                                                                                                                                 
 char temp_word[wordsize];                                                                                                                                                                          
 while(1) {                                                                                                                                                                                         
  check = true;                                                                                                                                                                                     
  int n;                                                                                                                                                                                            
  for(n = 0; n < count-1; n++) {                                                                                                                                                                    
   if(strlen(words[n].str) < strlen(words[n+1].str)) {                                                                                                                                              
    strcpy(temp_word, words[n+1].str);                                                                                                                                                              
        strcpy(words[n+1].str, words[n].str);                                                                                                                                                       
        strcpy(words[n].str, temp_word);                                                                                                                                                            
        check = false;                                                                                                                                                                              
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
  if(check == true) {                                                                                                                                                                               
   break;                                                                                                                                                                                           
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Inserts a single word onto the board                                                                                                                                                             
void insert(char board[][boardsize+2], WordData words[], int x, int y, bool position, int index) {                                                                                                  
 if (position == false) {                                                                                                                                                                           
  int n;                                                                                                                                                                                            
  for(n = 0; n < strlen(words[index].str); n++) {                                                                                                                                                   
   board[y+n+1][x+1] = words[index].str[n];                                                                                                                                                         
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 else {                                                                                                                                                                                             
  int i;                                                                                                                                                                                            
  for(i = 0; i < strlen(words[index].str); i++) {                                                                                                                                                   
   board[y+1][x+i+1] = words[index].str[i];                                                                                                                                                         
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 words[index].x = x;                                                                                                                                                                                
 words[index].y = y;                                                                                                                                                                                
 words[index].position = position;                                                                                                                                                                  
 words[index].inserted = true;                                                                                                                                                                      
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Checks to see if there are open spaces for a word to be placed                                                                                                                                   
bool open(char board[][boardsize+2], WordData word, int x, int y, bool position, int blocked) {                                                                                                     
 bool free = true;                                                                                                                                                                                  
 if(position == false) {                                                                                                                                                                            
  int n;                                                                                                                                                                                            
  for(n = 0; n < strlen(word.str); n++) {                                                                                                                                                           
   if(((board[y+n+1][x+1] != '\0') && (board[y+n+1][x+1] != word.str[n])) || ((board[y+n+1][x] != '\0') && (n != blocked)) || ((board[y+n+1][x+2] != '\0') && (n != blocked)) || ((n == 0) && (board
[y+n][x+1] != '\0')) || ((n == strlen(word.str)-1 && (board[y+n+2][x+1])))) {                                                                                                                       
    free = false;                                                                                                                                                                                   
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
  else {                                                                                                                                                                                            
  int n;                                                                                                                                                                                            
  for(n = 0; n < strlen(word.str); n++){                                                                                                                                                            
   if(((board[y+1][x+n+1] != '\0') && (board[y+1][x+n+1] != word.str[n])) || ((board[y][x+n+1] != '\0') && (n != blocked)) || ((board[y+2][x+n+1] != '\0') && (n != blocked)) || ((n == 0) && (board
[y+1][x+n] != '\0')) || ((n == strlen(word.str)-1) && (board[y+1][x+n+2]))) {                                                                                                                       
    free = false;                                                                                                                                                                                   
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
 return free;                                                                                                                                                                                       
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Attempts to place all words after the first on to the board                                                                                                                                      
void insert_all(char board[][boardsize+2], WordData words[], int count) {                                                                                                                           
 bool position = false;                                                                                                                                                                             
 int n, i, j, k;                                                                                                                                                                                    
 for(n = 1; n < count; n++) {                                                                                                                                                                       
  bool check = false;                                                                                                                                                                               
  for(i = 0; i < boardsize; i++) {                                                                                                                                                                  
   for(j = 0; j < boardsize; j++) {                                                                                                                                                                 
    if(board[i+1][j+1] != '\0') {                                                                                                                                                                   
     if((board[i][j+1] == '\0') && (board[i+2][j+1] == '\0')) {                                                                                                                                     
      position = false;                                                                                                                                                                             
         for(k = 0; k < strlen(words[n].str); k++) {                                                                                                                                               
          if(board[i+1][j+1] == words[n].str[k]) {                                                                                                                                                     
           if((k <= i) && (strlen(words[n].str)-(k+1) <= boardsize - (i+1))) {                                                                                                                         
            if(open(board, words[n], j, i-k, position, k)) {                                                                                                                                           
             insert(board, words, j, i-k, position, n);                                                                                                                                                
                  check = true;                                                                                                                                                                     
                  break;                                                                                                                                                                            
            }                                                                                                                                                                                  
           }                                                                                                                                                                                   
          }                                                                                                                                                                                        
         }                                                                                                                                                                                         
         if(check == true) {                                                                                                                                                                       
       	      break;                                                                                                                                                                                       
         }                                                                                                                                                                                         
       }                                                                                                                                                                                          
     else if((board[i+1][j] == '\0') && (board[i+1][j+2] == '\0')) {       // reached the end so use \0                                                                                                                  
          position = true;                                                                                                                                                                          
          for(k = 0; k < strlen(words[n].str); k++) {                                                                                                                                               
       if(board[i+1][j+1] == words[n].str[k]) {                                                                                                                                                     
        if((k <= j) && (strlen(words[n].str)-(k+1) <= boardsize - (j+1))) {                                                                                                                         
         if(open(board, words[n], j-k, i, position, k)) {                                                                                                                                           
          insert(board, words, j-k, i, position, n);                                                                                                                                                
                  check = true;                                                                                                                                                                     
                  break;                                                                                                                                                                            
                 }                                                                                                                                                                                  
                }                                                                                                                                                                                   
           }                                                                                                                                                                                        
          }                                                                                                                                                                                         
          if(check == true){                                                                                                                                                                        
       break;                                                                                                                                                                                       
          }                                                                                                                                                                                         
     }                                                                                                                                                                                              
        }                                                                                                                                                                                           
   }                                                                                                                                                                                                
   if(check == true) {                                                                                                                                                                              
    break;                                                                                                                                                                                          
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
  if (check == false) {                                                                                                                                                                             
   printf("%s could not be placed.\n", words[n].str);                                                                                                                                               
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}                                                                                                                                                                                                   
                                                                                                                                                                                                    
// Inserts all of the words that were not placed the first time                                                                                                                                     
void continue_insert(char board[][boardsize+2], WordData words[], int count) {                                                                                                                      
 bool marker = true;                                                                                                                                                                                
 while(marker == true) {                                                                                                                                                                            
  marker = false;                                                                                                                                                                                   
  int n, i, j, k;                                                                                                                                                                                   
  bool position = false;                                                                                                                                                                            
  for(n = 0; n < count; n++) {                                                                                                                                                                      
   bool check = false;                                                                                                                                                                              
   if(words[n].inserted == false) {                                                                                                                                                                 
    for(i = 0; i < boardsize; i++) {                                                                                                                                                                
     for(j = 0; j < boardsize; j++) {                                                                                                                                                               
      if(board[i+1][j+1] != '\0') {                                                                                                                                                                 
       if((board[i][j+1] == '\0') && (board[i+2][j+1] == '\0')) {                                                                                                                                   
        position = false;                                                                                                                                                                           
        for(k = 0; k < strlen(words[n].str); k++) {                                                                                                                                         
         if(board[i+1][j+1] == words[n].str[k]) {                                                                                                                                                   
          if((k <= i) && (strlen(words[n].str)-(k+1) <= boardsize - (i+1))) {     // use && to make sure both conditions are met                                                                                             
           if(open(board, words[n], j, i-k, position, k)) {                                                                                                                                         
            insert(board, words, j, i-k, position, n);                                                                                                                                              
            marker = true;                                                                                                                                                              
            check = true;                                                                                                                                                                           
            break;                                                                                                                                                                      
           }                                                                                                                                                                                
          }                                                                                                                                                                                 
         }                                                                                                                                                                                  
        }                                                                                                                                                                                   
        if(check == true) {                                                                                                                                                                 
         break;                                                                                                                                                                                     
        }                                                                                                                                                                                   
       }                                                                                                                                                                                        
           else if((board[i+1][j] == '\0') && (board[i+1][j+2] == '\0')) {                                                                                                                          
        	position = true;                                                                                                                                                                            
                for(k = 0; k < strlen(words[n].str); k++) {                                                                                                                                         
         	 if(board[i+1][j+1] == words[n].str[k]) {                                                                                                                                                   
                  if((k <= j) && (strlen(words[n].str) - (k+1) <= boardsize - (j+1))) {                                                                                                                     
                   if(open(board, words[n], j-k, i, position, k)) {                                                                                                                                         
                   insert(board, words, j-k, i, position, n);                                                                                                                                              
                   marker = true;                                                                                                                                                                  
                   check = true;                                                                                                                                                               
                   break;                                                                                                                                                                      
                   }                                                                                                                                                                                
                  }                                                                                                                                                                                 
                 }                                                                                                                                                                                  
                }                                                                                                                                                                                   
                if(check == true) {                                                                                                                                                                 
                 break;                                                                                                                                                                             
                }                                                                                                                                                                                   
            }                                                                                                                                                                                        
          }                                                                                                                                                                                         
         }                                                                                                                                                                                          
         if(check == true) {                                                                                                                                                                        
      		break;                                                                                                                                                                                        
         }                                                                                                                                                                                          
      }                                                                                                                                                                                           
   }                                                                                                                                                                                                
  }                                                                                                                                                                                                 
 }                                                                                                                                                                                                  
}   
