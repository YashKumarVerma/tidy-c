#include<stdio.h>
#define MAX 1024
char stack[MAX];
int top = -1;
int indentLevel = 0;

int push(char s);
int pop();
int isCurlyBracket(char s);
int indent(FILE *fs);

// styling functions

int processTerminationSymbols(FILE*, char);

int processCommaSymbols(FILE*, char);

int processOpeningBraces(FILE*, char);

int processClosingBraces(FILE*, char);



// main caller function
int main(){
    // variable to collect junk data
    int flag = 0;

    // file pointer to handle input and output streasms
    FILE *input;
    FILE *output;

    // assign file pointers to files
    input = fopen("ugly.c", "r");
    output = fopen("tidy.c", "w");

    //  get initial character form file
    char ch = fgetc(input);

    // loop through all characters of file
    while(ch != EOF){

        // if charcter is semi colon, handle it
        if(processTerminationSymbols(output, ch)){
            flag = 1;
        }
        else if(processCommaSymbols(output, ch)){
            flag = 1;
        }
        else if(processOpeningBraces(output, ch)){
            flag = 1;
        }
        else if(processClosingBraces(output, ch)){
            flag = 1;
        }
        else{
            fputc(ch, output);
        }

        // read one more charcter form stream
        ch = getc(input);
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
    if(s=='{' || s == '}'){
        return 1;
    }else{
        return 0;
    }
}


int indent(FILE *fs){
    int i;
    for(i=0; i<indentLevel; i++){
        fputc('\t',fs);
    }
}

// function returns 1 when passed character was termination symbol and add newline at end
int processTerminationSymbols(FILE* output, char ch){
    if( ch == ';' ){
        fputc(';', output);
        fputc('\n', output);
        return 1;
    }
    else{
        return 0;
    }
}

int processCommaSymbols(FILE *output, char ch){
    if(ch == ','){
        fputc(' ', output);
        fputc(',', output);
        return 1;
    }else{
        return 0;
    }
}

int processOpeningBraces(FILE *output, char ch){
    if(ch=='{'){
        // first print the curly braces to preserve code style
        fputc('{', output);

        // increase indent by one level
        indentLevel++;
        
        return 1;
    }
    else{
        return 0;
    }
}


int processClosingBraces(FILE *output, char ch){
    if(ch=='}'){
        // print a new line chracter as closing brakets always come at newline
        fputc('\n', output);
        fputc('}', output);

        indentLevel--;

        return 1;
    }
    else{
        return 0;
    }
}