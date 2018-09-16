#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//this program reads an input file, put each line into a node,
//and add it inside an array
//io.c has been able to push element into blocks manually


struct Node
{
	char* instruction;
	int memory;
	struct Node* next;	
};

struct Queue
{
	struct Node* front;
	struct Node* back;
};

struct Node* createBlock(char* instruction,int memo)
{
	
	struct Node* currentNode;
	currentNode = (struct Node*)malloc(sizeof(struct Node));


	//copying in string instruction
	char* insCopy;
	insCopy = malloc(sizeof(insCopy));
	strcpy(insCopy, instruction);
	currentNode->instruction = insCopy;

	currentNode->memory = memo;

	currentNode->next = NULL;

	return currentNode;

}

struct Queue* createQueue()
{
	struct Queue* q;
	q = (struct Queue*)malloc(sizeof(struct Queue));

	q->front = NULL;
	q->back = NULL;
	return q;
}


//exact from assignment1
struct Queue* Push(struct Queue* q, struct Node* block)
{	
	struct Node* curr = block;

	if(q->back == NULL)
	{
		q->back = curr;
		q->front = curr;
		return q;
	}
	else
	{
		q->back->next = curr;
		q->back = curr;
		curr->next = NULL; //in case we push someone from a middle of a queue

	}
	
	//display(q);
	
	return q;
}

//exact from assignment 1
struct Node* Pop(struct Queue* q)
{
	if(q->front == NULL) 
	{
		return NULL;
	}


	struct Node* curr = q->front;
	q->front = q->front->next;
	

	if(q->front == NULL) 
	{
		q->back = NULL;
	}

	return curr;

}

void display(struct Queue* q)
{
	int i = 0;
	if(q->front == NULL)
	{
		printf("queue is empty\n");
	}
	else
	{
		struct Node* curr = q->front;

		//traversing the list
		while(curr->next != NULL)
		{
			printf("%s-->", curr->instruction);
			curr = curr->next;
			
		}

		// at this point, curr pointer is pointing to the last block
		printf("%s-->NULL\n", curr->instruction);

	}
	
}

int isEmpty(struct Queue* q)
{
	if(q->front == NULL)
	{
		return 1;
	}
	return 0;
}


int hexToDec(char hex[])
{
	int len = strlen(hex);

	//initialise base value to 1,(16^0)
	int base = 1;
	int dec = 0;
	int i;

	for(i=len-1; i>=0; i--)
	{
		//if char lies in 0-9, convert by subtracting 48
		if(hex[i] >= '0' && hex[i] <= '9')
		{
			dec += (hex[i] - 48) * base;

			//incrementing base by power
			base = base * 16;
		}

		//if char lies in A-F, convert by subtract 55
		else if(hex[i] >= 'A' && hex[i] <= 'F')
		{
			dec += (hex[i] - 55) * base;

			//incrementing base by power
			base = base * 16;
		}

	}

	return dec;
}

// int decToBi(int dec)
// {
// 	int binary,i,j;
// 	binary = 0;
// 	i = 1;

// 	return binary;
// }

int main(int argc, char* argv[])
{
	//reading input

	FILE * fp = fopen(argv[1], "r");

	if(fp == NULL)
	{
		printf("cannot open file\n");
	}

	char ins[3];
	char memo[10];
	char* insCopy;
	char* memoCopy;

	struct Queue* q = createQueue();


	while (!feof(fp))
	{
		//scanning
	 	fscanf(fp, "%s %s",ins,memo);

	 	//making copy to save the two slots in
	 	insCopy = malloc(sizeof(insCopy));
	 	strcpy(insCopy, ins);


	 	memoCopy = malloc(sizeof(memoCopy));
	 	strcpy(memoCopy, memo);

	 	//a function to transfer the memoCopy from hexa to decimal
	 	int memoDec = hexToDec(memoCopy);
	 	
	 	//create a block to push to queue
	 	struct Node* temp = createBlock(insCopy,memoDec);
	 	Push(q,temp);
	}


	display(q);
	return 0;
}







