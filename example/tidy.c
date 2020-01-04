#include<stdio.h>
#include<stdlib.h>
struct StackArr{
	int top;
	int capacity;
	int *array;
}
;
typedef struct StackArr stack;
int isFull(stack *s){
	return (s->top == s->capacity -1) ? 1 : 0;
}
int isEmpty(stack *s){
	return (s->top == -1) ? 1 : 0;
}
int push(stack *s , int data){
	if (isFull(s)){
		printf("\nSTACK OVERFLOW !\n");
		return 0;
	}
	else{
		printf("\n Pushing %d to stack \n" , data);
		s->array[++s->top] = data;
	}
	return 1;
}
int pop(stack *s){
	if(isEmpty(s)){
		printf("\nSTACK UNDERFLOW\n");
		return 0;
	}
	else{
		printf("\n Removing Element : %d " , s->array[s->top]);
		s->top = s->top - 1;
		return 1;
	}
}
int display(stack *s){
	int i;
	printf("\n Displaying Stack \n");
	for(i=s->top;	 i>=0;	 i--){
		printf(" %d \t" , s->array[i]);
	}
	printf("\n");
	return 0;
}
int main(){
	int choice;
	int caller;
	stack *numbers;
	numbers->capacity = 10;
	numbers->top = -1;
	numbers->array = malloc(sizeof(stack)*numbers->capacity);
	menu:printf("\n 1. Display \n 2. Push \n 3. Pop \n Press any other key to exit \n");
	scanf(" %d" , &choice);
	switch(choice){
		case 1:caller = display(numbers);
		goto menu;
		case 2:printf("\n Enter a number to push to stack : ");
		scanf(" %d" , &caller);
		caller = push(numbers , caller);
		goto menu;
		case 3:caller = pop(numbers);
		goto menu;
		default:return 0;
	}
	return 0;
}

