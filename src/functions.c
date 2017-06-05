#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void affiche_tab(int *tab, int size) {
	int count;
	printf("{");
	for (count = 0; count < size; count++)
		printf("%d", tab[count]);
	printf("}\n");
}

void shuffle(int *array, size_t n) {

	int temp;
	int swap;
 	int i;
 	
	// create sequence
	srand(time(0));  
	 
	// shuffle in loop
	for (i =  n; i > 0; i--){
		swap = rand() % i;
	    temp =  array[i];
	    array[i] = array[swap];
	    array[swap] = temp; 
	 }
}