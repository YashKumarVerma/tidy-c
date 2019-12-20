#include<stdio.h>
#include<string.h>

#define MAX 1024
char stack[MAX];
int top = -1;
int indentLevel = 0;
int lineStart = 0;
int lineNumber = 0;

// stack operations
void push(char s);
int pop();
char getTop();

// styling functions
void indent(FILE *fs);

int processTerminationSymbols(FILE*, char);

int processCommaSymbols(FILE*, char);

int processOpeningBraces(FILE*, char);

int processClosingBraces(FILE*, char);


// loggging functions
void write(FILE*, char *);

// main caller function
int main(){
    // variable to collect junk data
    int flag = 0;

    // dummy string to write logs
    char str[2];
    str[0] = ' ';
    str[1] = '\0';

    // file pointer to handle input and output streasms
    FILE *input;
    FILE *output;
    FILE *log;

    // assign file pointers to files
    input = fopen("ugly.c", "r");
    output = fopen("tidy.c", "w");
    log = fopen("log.txt", "w");

    // log operation starts
    write(log, "3 Files loaded as pointers");

    //  get initial character form file
    char ch = fgetc(input);
    str[0] = ch;
    write(log, "reading character");
    write(log, str);

    // loop through all characters of file
    while(ch != EOF){

        // if charcter is semi colon, handle it
        if(processTerminationSymbols(output, ch)){
            // add termination symbol to stack;
            // push(';');
            flag = 1;
        }
        else if(processCommaSymbols(output, ch)){
            flag = 1;
        }
        else if(processOpeningBraces(output, ch)){
            // push('{');
            flag = 1;
        }
        else if(processClosingBraces(output, ch)){
            flag = 1;
        }
        else{

            indent(output);
            fputc(ch, output);
        }

        // read one more charcter form stream
        ch = getc(input);
    }
    return 0;
}

// stack operations
void push(char s){
    if(top = MAX){
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


char getTop(){
    if(top==-1){
        return '~';
    }else{
        return stack[top];
    }
}


// styling operations
void indent(FILE *fs){

    if(!lineStart){
        int i;
        for(i=0; i<indentLevel; i++){
            fputc('\t',fs);
        }
    }

    // // give n level indent
}

// function returns 1 when passed character was termination symbol and add newline at end
int processTerminationSymbols(FILE* output, char ch){
    if( ch == ';' ){
        fputc(';', output);
        fputc('\n', output);
        lineStart = 0;
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
        fputc('\n', output);

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
        fputc('\n', output);

        indentLevel--;

        return 1;
    }
    else{
        return 0;
    }
}

// logging operations
void write(FILE *log,int type, char str[]){
    
    // print lineNumber
    lineNumber++;
    fprintf(log, "%d", lineNumber);
    fputc('\t', log);
    fputs(str, log);
    fputs("\n", log);
}