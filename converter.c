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

// main caller function
int main(){
    // variable to collect junk data
    int flag = 0;


    // file pointer to handle input and output streasms
    FILE *input;
    FILE *output;
    FILE *log = fopen("log.txt", "w");

    // assign file pointers to files
    input = fopen("ugly.c", "r");
    output = fopen("tidy.c", "w");
    log = fopen("log.txt", "w");

    // log operation starts
    fprintf(log, "%d\t%s\n", ++lineNumber, "Loaded 3 files as pointers");   

    //  get initial character form file
    char ch = fgetc(input);
    
    fclose(log);
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
            // push('{');
            flag = 1;
        }
        else if(processClosingBraces(output, ch)){
            flag = 1;
        }
        else{
            FILE *log = fopen("log.txt", "a+");
            fprintf(log, "%d\t%s%c\n", ++lineNumber, "printing : ", ch);
            fclose(log);

            indent(output);
            fputc(ch, output);
        }

        // read one more charcter form stream
        ch = getc(input);
    }

    fprintf(log, "%d\t%s\n", ++lineNumber, "ENDING !");   
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
        lineStart = 1;
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
        FILE *log = fopen("log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "printing ; , \\n");   
        fputc(';', output);
        fputc('\n', output);

        fprintf(log, "%d\t%s\n", ++lineNumber, "lineStart = 0");   
        lineStart = 0;
        fclose(log);
        return 1;
    }
    else{
        return 0;
    }

}

int processCommaSymbols(FILE *output, char ch){
    if(ch == ','){
        // update logs
        FILE *log = fopen("log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing ,");

        fputc(' ', output);
        fputc(',', output);

        fclose(log);
        return 1;
    }else{
        return 0;
    }
}

int processOpeningBraces(FILE *output, char ch){
    if(ch=='{'){

        // write logs
        FILE *log = fopen("log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing {");

        // first print the curly braces to preserve code style
        fputc('{', output);
        fputc('\n', output);

        // increase indent by one level

        indentLevel++;
        fprintf(log, "%d\t%s%d\n", ++lineNumber, "indentLevel=", indentLevel);
        
        lineStart = 0;

        fclose(log);
        return 1;
    }
    else{
        return 0;
    }
}

int processClosingBraces(FILE *output, char ch){
    if(ch=='}'){
        
        FILE *log = fopen("log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing }");

        // indent it bitch
        int i=0;
        for(i=0; i<indentLevel-1; i++){
            fputc('\t', output);
        }

        // print a new line chracter as closing brakets always come at newline
        fputc('}', output);
        fputc('\n', output);

        indentLevel--;
        fprintf(log, "%d\t%s%d\n", ++lineNumber, "indentLevel=", indentLevel);

        return 1;
    }
    else{
        return 0;
    }
}
