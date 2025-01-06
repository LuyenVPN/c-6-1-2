#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	loadCategoriesFromFile(); 
	loadProductsFromFile();
	printlogin(); //in man hinh dang nhap 
	

	return 0;
}
