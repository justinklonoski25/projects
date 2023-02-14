#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Writing the two functions to do the rotations

void rotate_left(int *arr, int n, int r) {
	int temp;
    	for (int i = 0; i < r; i++) {
        	temp = arr[0];
        	for (int j = 0; j < n - 1; j++) {
            		arr[j] = arr[j + 1];
        	}
        	arr[n - 1] = temp;
    	}
}

void rotate_right(int *arr, int n, int r) {
	int temp;
    	for (int i = 0; i < r; i++) {
        	temp = arr[n - 1];
        	for (int j = n - 1; j > 0; j--) {
            		arr[j] = arr[j - 1];
        	}
        	arr[0] = temp;
    	}
}

int main() {
	int n, r;
    	char d;
    	int *arr;
    	FILE *fp; 
	fp=fopen("input.txt", "r");

// I wanna read in the variables n, r, and d from the file like input1.txt
    	fscanf(fp, "%d %d %c", &n, &r, &d);

// allocate memory for the array
    	arr = (int*) malloc((size_t) n * sizeof(int));


// read array elements from file
    	for (int i = 0; i < n; i++) {
        	fscanf(fp, "%d", &arr[i]);
    	}

// I want to perform a left or right rotation based on user input from the file  
    	if (d == 'L') {
        	rotate_left(arr, n, r);
    	} 
	else if (d == 'R') {
       		rotate_right(arr, n, r);
    	} 
	else {
        	printf("Invalid rotation direction\n");
        	return 1;
    	}

// print the rotated array
    	for (int i = 0; i < n; i++) {
        	printf("%d ", arr[i]);
    	}
    	printf("\n");

// Have to free the allocated memory according to the instructions
    	free(arr);
    	fclose(fp);
    	return 0;
}
