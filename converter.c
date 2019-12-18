#include<stdio.h>
#define MAX 1024
char stack[MAX];
int top = -1;

int push(char s);
int pop();
int isCurlyBracket(char s);
int main(){

    // file pointer to handle input and output streasms
    FILE *input;
    FILE *output;

    input = fopen("ugly.c", "r");
    output = fopen("tody.c", "w");

    //  parse charcter wise
    char ch = getc(input);
    while(ch != EOF){
        // if ch is opening curly start

    }
    return 0;
}

int push(char s){
    if(top = MAX){
        return 0;
    }
    else{
        top = top + 1;
        stack[top] = s;
    }
}

int pop(){
    if(top == -1){
        return 0;
    }else{
        top = top-1;
        return 1;
    }
}

int isCurlyBracket(char s){
    if(s=="{" || s == "}"){
        return 1;
    }else{
        return 0;
    }
}