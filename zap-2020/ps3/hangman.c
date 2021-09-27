#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}


int is_word_guessed(const char secret[], const char letters_guessed[]){
    int letterAreIn =0;
    int strlen = 0;
    while(secret[strlen] != '\0'){
        strlen++;
    }
    for(int i = 0; secret[i] != '\0';i++){
        for(int j = 0; letters_guessed[j] !='\0'; j++){
            if(secret[i] == letters_guessed[j]){
                letterAreIn++;
            }
        }
    }

    return (strlen <= letterAreIn) ?  1:0;
}
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    int k=0;
    while(secret[k] !='\0'){
        guessed_word[k] = secret[k];
        k++;
    }
    guessed_word[k]='\0';
    int flag = 0;
    for(int i = 0; guessed_word[i] !='\0'; i++){
        flag = 0;
        for(int j = 0; letters_guessed[j] != '\0'; j++){
            if(guessed_word[i] == letters_guessed[j]){
                flag = 1;
            }
        }
        if(!flag){
            guessed_word[i] = '_';
        }
    }
}
void get_available_letters(const char letters_guessed[], char available_letters[]){
    const char abc[] ="abcdefghijklmnopqrstuvwxyz";
    int k = 0;
    int flag =0;
    for(int i=0;abc[i] != '\0';i++){
        flag=0;
        for(int j = 0;letters_guessed[j] !='\0'; j++){
            if(abc[i] == letters_guessed[j]){
                flag =1;
            }
        }
        if(!flag){
            available_letters[k] = abc[i];
            k++;
        }
    }
    available_letters[k] = '\0';
}
int check_letter_before(const char letter, const char letters_guessed[]){
	for(int i = 0; letters_guessed[i] !='\0'; i++){
		if(letters_guessed[i] == letter){
			return 1;
		}
	}
	return 0;
}
int is_letter(const char  letter){
	const char abcABC[] ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(int i = 0; abcABC[i] != '\0'; i++){
		if(letter == abcABC[i]){
			return 1;
		}
	}
	return 0;
}
int letter_in_secret(const char letter, const char secret[]){
	for(int i = 0; secret[i] != '\0'; i++){
		if(letter == secret[i]){
			return 1;
		}
	}
	return 0;
}
int equal_word(char word[], const char secret[]){
		for(int i=0; word[i] != '\0'; i++){
			if(word[i] >64 && word[i] <91){word[i] +=32;}
			if(word[i] != secret[i]){
				return 0;
			}
		}
	return 1;
}

int len_word(const char word[]){
	int k=0;
	while(word[k]){
		k++;
	}
	return k;
}
int have_pou(const char word[]){
	const char abcABC[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int flag = 1;
	for(int i = 0;word[i] != '\0';i++){
		flag = 1;
		for(int j = 0; abcABC[j] !='\0'; j++){
			if(word[i] == abcABC[j]){
				flag =0;
				break;
			}
		}
		if(flag){
			return 1;
		}
	}
	return 0;
}
void space_word(const char guessed_word[], char wrd_space[]){
	int i;
	for(i = 0;guessed_word[i] !='\0';i++){
		wrd_space[2*i]=guessed_word[i];
		wrd_space[2*i+1]=' ';
	}
	wrd_space[i*2-1]='\0';
}
void hangman(const char secret[]){
	printf("Welcome to the game, Hangman!\n");
	int len_secret = 0;
	while(secret[len_secret] != '\0'){len_secret++;}

	printf("I am thinking of a word that is %d letters long.\n",len_secret);
	printf("-------------\n");
	int i_word =0;
	int guesses = 8;
	int count_letter = 0;
	char buffer;
	char word[15];
	char letter;
	char letters_guessed[30] = "";
	char available_letters[30] = "";
	char guessed_word[15] = "";
	char wrd_space[31]="";
	get_guessed_word(secret,letters_guessed,guessed_word);
	int never_used = is_word_guessed(secret,letters_guessed);// i dont need this stupid function
	if(never_used && !never_used){
		printf("Break my code!\n");
	}
	while(guesses){
		get_available_letters(letters_guessed,available_letters);
		printf("You have %d guesses left.\n",guesses);
		printf("Available letters: %s\n", available_letters);
		printf("Please guess a letter: ");
		i_word = 0;
		while(1){
			buffer = getchar();
			if(buffer == '\n'){
				word[i_word]='\0';
				break;
			}else{
				word[i_word]=buffer;
				i_word++;
			}
		}
		if(i_word <2){
			letter = word[0];
		}else if(i_word != len_word(secret)){
			printf("Oops! '%s' is not a valid: %s\n", word, guessed_word);
			continue;
		}else if(have_pou(word)){
			printf("Oops! '%s' is not a valid: %s\n", word, guessed_word);
			continue;
		}else if(equal_word(word, secret)){
			printf("Congratulations, you won!\n");
			break;
		}else{
			printf("Sorry, bad guess. The word was %s.\n",secret);
			break;
		}

		if(is_letter(letter)){
			if(letter < 97){
				letter+=32;
			}
			if(check_letter_before(letter,letters_guessed)){
				get_guessed_word(secret,letters_guessed,guessed_word);
				space_word(guessed_word,wrd_space);
				printf("Oops! You've already guessed that letter: %s\n",wrd_space);////
			}else if(letter_in_secret(letter, secret)){
				letters_guessed[count_letter] = letter;
				count_letter++;
				get_guessed_word(secret,letters_guessed,guessed_word);
				space_word(guessed_word,wrd_space);
				printf("Good guess: %s\n",wrd_space);/////////////

					if(equal_word(guessed_word,secret)){
						printf("-------------\n");
						printf("Congratulations, you won!\n");
						break;
					}
			}else{
				letters_guessed[count_letter] = letter;
				count_letter++;
				get_guessed_word(secret,letters_guessed,guessed_word);
				space_word(guessed_word,wrd_space);
				printf("Oops! That letter is not in my word: %s\n",wrd_space);/////
				guesses--;
			}
		}else{
			get_guessed_word(secret,letters_guessed,guessed_word);
			space_word(guessed_word,wrd_space);
			printf("Oops! '%c' is not a valid letter: %s\n",letter, wrd_space);//////
		}

	printf("-------------\n");
	}
	if(guesses == 0){
		printf("Sorry, you ran out of guesses. The word was %s.\n",secret);
	}
}
