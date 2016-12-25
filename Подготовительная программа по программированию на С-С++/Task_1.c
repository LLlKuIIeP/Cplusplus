#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


void fun1(char *str, double *count) {
	int i;

	for(i = 0; str[i] != '\0'; i++) {		
		
		if(isspace(str[i])) {
			str[i] = ' '; 
		}	
		
		switch (str[i]) {
			case '.': case '!': case '?':
				str[i] = '.';
				(*count)++;	
				break;
			default:
				break;
		}
	}	
}

void fun2(char *str) {
	int i;

	for(i = 0; str[i] != '\0'; i++) {		
		if(ispunct(str[i]) && str[i] != '.') {
			str[i] = ' ';
		}
	}	
}


int numberWordsSentence(const char *word, char *str) {
int num = 0;			
		if(strlen(word) == strlen(str)) {			
			if(strcmp(str, word) == 0) {				
			num++;
			}
		}
return num;
}

int main() 
{
int i;
double count = 0;
int numWord = 0;
//printf("numWord: %d\n", numWord);
int m = 0;
char d;
char *str = (char *)malloc(sizeof(char));
char *word = (char *)malloc(sizeof(char));
//printf("7\n");

for(i = 0; scanf("%c", &d) != EOF; i++) {	
	str = (char *)realloc(str,(2 + i)*sizeof(char));
	str[i] = d;
	str[i + 1] = '\0';	
}
//printf("str1: %s\n", str);

fun1(str, &count);
fun2(str);
//printf("NEWstr: %s\n", str);
//printf("str2: %s\n", str);
	for(i = 0; str[i] != '\0'; i++) {		
		if(isspace(str[i])) {
			word = (char *)realloc(word,(i)*sizeof(char));
			strncpy(word, str, i);
			word[i] = '\0';
			break;
		}
	}
//printf("word: %s\n", word);
//printf("NEWstr_2: %s\n", str);
m = i;
	for(i = m; str[i] != '\0'; i++) {		
		if(str[i] != ' ' && str[i] != '.') {
			m = i;
			//printf("Start_i = %d\n", i);
			while(str[i] != ' ' && str[i] != '.') {
				i++;
			}
			//printf("Stop_i = %d\n", i);
			char *sentence = (char *)malloc((i - m + 1)*sizeof(char));
			
			int j;
			for(j = 0; j < i - m; j++) {			
				sentence[j] = str[m + j];
				}		
			sentence[j] = '\0';
			//printf("sentence: %s\n", sentence);					
			numWord += numberWordsSentence(word, sentence);
			//printf("numWord: %d\n", numWord);
			free(sentence);	
		}
	}

if(count != 0) {
	printf("%f", numWord/count);
}

free(str);
free(word);
return 0;
}
