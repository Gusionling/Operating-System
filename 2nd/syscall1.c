#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Character classes
#define DIGIT 1
#define UNKNOWN 2
#define ERROR 3

//Token codes
#define INT_LIT 10
#define IDENT 11
#define START 12

//iserror
#define FALSE 0
#define TRUE 1

char input[100];
char ret[100];
long reversed;
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
unsigned int i;
int iserror = FALSE;
long unit;
int len;

void getChar();
void addChar();
void getNonBlank();
int lex();


long reverse(char *str){
    int length = 0;
    int i;
    long k;

    while(str[length] != '\0'){
        length++;
    }

    for(i = 0; i<length; i++){
        ret[length-i-1] = str[i];
    }
    ret[length] ='\0';
    k = strtol(ret,NULL, 10);
    
    return k;
}

int lookup(char ch){
   
    addChar();
    nextToken = EOF;
    
    return nextToken;
}
void addChar(){
    if(lexLen <= 98){
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long");
}

void getChar(){
    if(i != len){
        nextChar = input[i++];
        if(isdigit(nextChar)){
            charClass = DIGIT;
        }
        else{
            if(nextChar == ' '){
                charClass = UNKNOWN;
            }
            else{
                iserror = TRUE;
                charClass = UNKNOWN;
            }
        }
    }
    else
        charClass = EOF;
}


int lex(){
    lexLen = 0;

    while(isspace(nextChar)){
        getChar();
    }
    switch (charClass)
    {
        case DIGIT:
            addChar();
            getChar();
            while(charClass == DIGIT){
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
            break;
    }
    return nextToken;
}


int main(int argc, char *argv)
{

    while (1) {
        printf("input: ");
        fgets(input, sizeof(input), stdin);  // 사용자로부터 문자열 입력을 받습니다.

        len = strlen(input)-1; //"\n"을 전체길이에서 빼주기위해서 위해서 -1
        // 문자열의 길이를 확인하여 사용자가 아무 문자열도 입력하지 않으면 루프를 종료합니다.
        if (len == 0 && input[0] == '\n') {
            break;
        }
        // 입력받은 문자열을 출력합니다.
        printf("입력한 문자열: %s", input);
        printf("입력한 문자열 길이 %d\n", len);

        getChar();
        while(1){
            //문자열의 토큰을 다 받았을 때 break
			//break후 바깥쪽 while문 실행해서 다시 새로운 입력을 받음

            if(nextToken == EOF){
                len = 0;
                i = 0;
                //nextToken의 상태를 초기화

                nextToken = START; 
                if(iserror == TRUE){
                    printf("Wrong input!\n");
                }
                else{
                    printf("ouput: %ld\n", reversed);
                }
                iserror = FALSE;
                break;
            }

            lex();
            if(nextToken == INT_LIT){
                reversed = reverse(lexeme);
            }
        }
    }
    
        
    
   return 0;
}

