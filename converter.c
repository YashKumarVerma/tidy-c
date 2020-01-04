#include<stdio.h>
#include<string.h>


// Stack Operations
#define MAX 1024
char stack[MAX];
int top = -1;

// functions to manage styling
int indentLevel = 0;
int lineStart = 0;
int lineNumber = 0;

// function to give indentation as per global config
void indent(FILE *fs);

// function to handle processes attached to termination symbol
int processTerminationSymbols(FILE*, char);

// function to handle operations related to comma (,) symbol
int processCommaSymbols(FILE*, char);

// function to handle operations related to ({) symbol 
int processOpeningBraces(FILE*, char);

// function to handle operations related to (}) symbol
int processClosingBraces(FILE*, char);

// function to handle operations related to `(` symbol
int processOpeningBracket(FILE*, char);

// function to handle operations related to `)` symbol
int processClosingBracket(FILE*, char);

// function to handle operations related to string i/o
int processInvertedComma(FILE*, char);

// stack operations
int isFull();
int isEmpty();
int push(char);
int pop();
char peek();

// main program with application logic
int main(){

    // variable to collect junk data, currently being used as placeholder
    int flag = 0;

    // FILE POINTERS
    // to handle read from input ugly file
    FILE *input;

    // to write output as formatted code
    FILE *output;

    // to log operations into log.txt
    FILE *log;

    // assigning pointers to files

    // open input file in read mode
    input = fopen("./example/ugly.c", "r");

    // open output file in write mode
    output = fopen("./example/tidy.c", "w");

    // open logs file in write mode, not in append to overwrite old data
    log = fopen("./example/log.txt", "w");

    // starting log operations
    fprintf(log, "%d\t%s\n", ++lineNumber, "Logger Started");   

    //  feed initial character from file stream to set while true
    char ch = fgetc(input);
    
    // close the log file to allow other processes to append it.
    fclose(log);

    // MAIN ENGINE

    // read all characters till the end of file
    while(ch != EOF){

        // apply semicolon conditions, and process if success
        if(processTerminationSymbols(output, ch)){
            flag = 1;
        }

        // apply comma conditions, and process if success
        else if(processCommaSymbols(output, ch)){
            flag = 1;
        }

        // apply opening braces ({) conditions, and process if success
        else if(processOpeningBraces(output, ch)){
            flag = 1;
        }

        // apply closing braces (}) conditions, and process if success
        else if(processClosingBraces(output, ch)){
            flag = 1;
        }

        // apply opening  bracket conditions
        else if(processOpeningBracket(output, ch)){
            flag = 1;
        }

        // apply closing bracket conditions
        else if(processClosingBracket(output, ch)){
            flag = 1;
        }

		// process operations related to inverted comma
		else if(processInvertedComma(output, ch)){
			flag = 1;
		}

        // when none of above, just print the character with indent
        else{
            // open the logger, and write the character being printed, close it.
            FILE *log = fopen("./example/log.txt", "a+");
            fprintf(log, "%d\t%s%c\n", ++lineNumber, "printing : ", ch);
            fclose(log);

            // apply indentation as per global config, and then print the character to output
            indent(output);
            fputc(ch, output);
        }

        // read next character from stream, and continue the while loop
        ch = getc(input);

    }

	while(top!=-1){
		printf("%c\t", peek());
		pop();
	}

    // print the closing line of logs, and close 
    fprintf(log, "%d\t%s\n", ++lineNumber, "ENDING !");   
    fclose(log);

    // return the operation to os
    return 0;
}

// CORE ENGINE FUNCTIONS

// to apply inline indent before printing character
void indent(FILE *output){

    // if given instance is the start of line character
    if(lineStart){
        // just a variable, what do you want it's description as ?
        int i;

        // add indent to output stream
        for(i=0; i<indentLevel; i++){
            // writing character to output stream 
            fputc('\t',output);
        }

        // well, now since the first character is done, let's wait for line to end; 
        lineStart = 0;
    }
}

// handles the processes attached to termination symbol (;)
int processTerminationSymbols(FILE* output, char ch){

    // if stream character is a termination symbol
    if( ch == ';' ){

        // open log file, add an entry of semicolon
        FILE *log = fopen("./example/log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "printing ; , \\n");   

        // write the semicolon to output stream
        fputc(';', output);

		// to tackle for loop breaking into multiple files, don't give newline if inside brackets
		if(peek()=='('){
		}else{
			fputc('\n', output);
		}
        

        // since ; signifies line end, we set lineStart=1 to indicate that next character is from new lien
        fprintf(log, "%d\t%s\n", ++lineNumber, "lineStart = 0");   
        lineStart = 1;

        // release the log file and memory
        fclose(log);

        // return 1 for success
        return 1;
    }
    else{
        // return 0 for the sake of.
        return 0;
    }

}

// function to handle processes related to comma symbol
int processCommaSymbols(FILE *output, char ch){

    // if stream character is a comma (,)
    if(ch == ','){
        
        // add entry to logs about processing comma
        FILE *log = fopen("./example/log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing ,");

        // just add a space before comma, and write to output
        fputc(' ', output);
        fputc(',', output);

        // release the log file and memory
        fclose(log);

        // return 1 for success
        return 1;
    }
    else{
        // return 0 for skip
        return 0;
    }
}

// function to handle Opening Braces
int processOpeningBraces(FILE *output, char ch){
    
    // if the passed character is an opening bracket ({)
    if(ch=='{'){

        // mention in logs about the opening bracket
        FILE *log = fopen("./example/log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing {");

        // print the curly bracket, don't add an extra line to preserve code style
        fputc('{', output);
        fputc('\n', output);
		
		// add { to stack
		push('{');

        // since { means a new code block, it must be one more level indented
        indentLevel++;

        // log about the indent level 
        fprintf(log, "%d\t%s%d\n", ++lineNumber, "indentLevel=", indentLevel);
        
        // since opening brackets are always new line (mostly), trigger newLine
        lineStart = 1;

        // close logs and relaase memory
        fclose(log);

        // return 1 for success
        return 1;
    }
    else{

        // return 0 for skip
        return 0;
    }
}

// function to handle processes related to closing braces
int processClosingBraces(FILE *output, char ch){

    // if stream character is closing bracket
    if(ch=='}'){
        
        // mention about the closing bracket in logs
        FILE *log = fopen("./example/log.txt", "a+");
        fprintf(log, "%d\t%s\n", ++lineNumber, "processing }");

        // indent, but indentLevel-1 to make it look nested
        int i=0;
        for(i=0; i<indentLevel-1; i++){
            // write tabs !
            fputc('\t', output);
        }

        // print a new line chracter as closing brakets always come at newline
        fputc('}', output);
        fputc('\n', output);

		if(peek()=='{'){
			pop();
		}

        // since closing brackets mark end of codeblock, decrease indentLevel by 11
        indentLevel--;

        // mention the indentLevel in logs
        fprintf(log, "%d\t%s%d\n", ++lineNumber, "indentLevel=", indentLevel);

        // close logs and relase memory
        fclose(log);

        // return 1 for success
        return 1;
    }
    else{
        // return 0 for skip ! there's no fail
        return 0;
    }
}

// function to handle operations related to opening bracket `(`
int processOpeningBracket(FILE *output, char ch){
  // check if incoming character is (
	if(ch == '('){
		// mention in logs about the opening bracket
		FILE *log = fopen("./example/log.txt", "a+");
		fprintf(log, "%d\t%s\n", ++lineNumber, "Adding ( to stack");
		
		// push a bracket into stack
		push('(');

		// write bracket to file
		fputc('(', output);

		return 1;
	}
	else{
		return 0;
	}
}

// function to handle operations related to closing bracket `)`
int processClosingBracket(FILE *output, char ch){
  // check if incoming character is )
  if(ch == ')'){
	FILE *log = fopen("./example/log.txt", "a+");
	fprintf(log, "%d\t%s\n", ++lineNumber, "Popping ) from stack");
	
	// then pop a character, removing a (
	if(peek() == '('){
		pop();
	}

	// writ to output
	fputc(')', output);
    return 1;
  }
  else{
    return 0;
  }
}

// function to handle operations related to inverted commas
int processInvertedComma(FILE *output, char ch){
	// check if incoming character is "
	if(ch == '"'){
		FILE *log = fopen("./example/log.txt", "a+");
		fprintf(log, "%d\t%s\n", ++lineNumber, "processing \" ");

		// if opening exists in stack
		if(peek() == '"'){
			fprintf(log, "%d\t%s\n", ++lineNumber, "popping \" ");
			pop();
		}
		// if this inverted comma represents opening string
		else{
			fprintf(log, "%d\t%s\n", ++lineNumber, "pushing \" ");
			push('"');
		}

		// write icomma to output strea
		fputc(ch, output);
		return 1;
	}else{
		return 0;
	}
}

// return 1 when stack is full
int isFull(){
  return top==MAX;
}

// returns 1 when stack is empty
int isEmpty(){
  return top==-1;
}

// returns 1 when character pushed to stack, 0 when stack full
int push(char c){
  if(isFull()){
    return 0;
  }
  else{
    top++;
    stack[top] = c;
    return 1;
  }
}

// returns 1 when element removed, 0 when stack empty
int pop(){
  if(isEmpty()){
    return 0;
  }
  else{
    top--;
    return 1;
  }
}

// return the top element of stack
char peek(){
  if(isEmpty()){
    return '0';
  }
  else{
    return stack[top];
  }
}
