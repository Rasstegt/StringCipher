/*
	Assignment 1. Message encipher/decipher
	Author: Arslan Khalikov
	Date: June 7, 2020
*/
#include <stdio.h>	// scanf() & printf()
#include <ctype.h> // isalpha() & tolower()
#include <stdlib.h>	// exit()
#include <string.h> // strlen()

// decipher function goes on top of other functions since it's called last
void decipher(char encrypter[], char key[]){
	// init and declaring message string inside the function so it can get the value inside the for-loop and be printed out inside of the method
	char message[100] = "";		

	// for-loop that runs until encrypter's string is over
	// reversed formula from encipher function
	// also makes sure that char has value over 97 in ASCII
	for (int i=0; i < strlen(encrypter); ++i){
		int e = (int)encrypter[i] - 97;
		int k = (int)key[i] - 97;
		message[i] = (e - k) % 26 + 97;
		if(message[i] < 97) 
			message[i] += 26;
	}

	// prints out the result
	printf("***** Decipher *****\nEnc: %s\nKey: %s\nMessage: %s\n", encrypter, key, message);

// end of decipher
}

// encipher function called second in the main method, so goes on top of the main
void encipher(char message[], char key[]) {
	// init and declaring string that will get encrypted
	char c[100] = "";

	// for-loop runs until the last character of the message
	for (int i=0; i < strlen(message); ++i){
		int m = (int)message[i] - 97;
		int k = (int)key[i] - 97;
		c[i] = (m + k) % 26 + 97; 
	}

	// prints out the result
	printf("\n***** Encipher *****\nMessage: %s\nKey: %s\nEnc: %s\n", message, key, c);
	// calls decipher function to continue calculations
	decipher(c, key);

// end of encipher
}

// begginning of our program
int main(void) {
		
	// init-ing necessary variables outside of the loop
	char message[100] = "", key[100] = "";
	int i, j, countMsg = 0, countKey = 0, try = 0;

	// do-while loop that gives second chance to the user
	do {
		// to take input
		printf("Enter a message and a keyword (letters only): ");
		scanf("%s%s", message, key);
						
		// 1st block to fill the key if it's shorter than a message
		// "sheridan" -> "sheridansh"
		if (strlen(key) < strlen(message)){
			int x = strlen(key);		
        	for(int i = 0; i <= strlen(message) - strlen(key); i++)
				key[x+i] = key[i];
		} 
		// 2nd block to fill the message if its shorter than a key
		// "algo" -> "algoal"
		if (strlen(message) < strlen(key)){
			int x = strlen(message);
			for(int i = 0; i <= strlen(key) - strlen(message); i++){
				message[x+i] = message[i];
			}
		}

		// 1st for-loop: to lower the case of the message
		// to check if message is a numeric value
		for(i = 0; message[i]!='\0'; i++) {
			if (isalpha(message[i]) != 0) {
				countMsg++;
				message[i] = tolower(message[i]);
			}
		}

		// 2nd for-loop: to lower the case of the key
		// to check if key is a numeric value
		for(j=0; key[j]!='\0'; j++){
			if (isalpha(key[j]) != 0) {
				countKey++;
				key[j] = tolower(key[j]);
			}
		}	
		
		// nested if-statement
		// outside if does: checks if message is correct
		// inside if does: kicks user out of the program 
		// or gives him the last chance
		if (countKey != strlen(key) || countMsg != strlen(message)) {
			if(try == 1) {
				printf("You can't type non-alpha characters, bye-bye!\n");
				exit(0);
			} else {
				printf("You can't type non-alphabetic characters! LAST CHANCE!\n");
				try++;
			}
		} 
		else {
			encipher(message, key);
		}

	} while (countKey != strlen(key) || countMsg != strlen(message));
								
return 0;
// end of main
}