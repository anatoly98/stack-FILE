

#include "stdafx.h"

#include "iostream"
#include <cstdio> 




using namespace std;



struct node_s

{

	int data;

	node_s*prev;

};



struct stack_descr {

	node_s* top = nullptr;

};



void push(stack_descr*, int value);

int pop(stack_descr*);

void write_stack_in_file(stack_descr*, int, FILE*);

void read_stack_out_file(stack_descr*, int&, FILE*);

void question();





int main()

{
    stack_descr *descr = new stack_descr;
    int n;
    cout << "number of element in stack = "; cin >> n;
    cout << endl;
    cout << "source stack:" << endl;
    for (int i = 0; i < n; i++)
     {
       int value;
	   cin >> value;
       push(descr, value);
     }

	cout << endl;

    FILE *file;
	fopen_s(&file, "stack", "ab+");
	
	write_stack_in_file(descr, n, file);
	fclose(file);
	
	fopen_s(&file, "stack", "ab+");
	


	cout << "stack out file:" << endl;
	
	int counter = 0;
	read_stack_out_file(descr,counter,file);
	cout << endl;

	fclose(file);
	
	cout << endl;
	cout << "stack out new stack:" << endl;
	for(int i=0; i<counter; i++)
	cout<<pop(descr)<<" ";

	cout << endl<<endl;
	question();

	_gettch();

	return 0;

}

void push(stack_descr* descr, int value) {

	node_s *node = new node_s;

	node->data = value;

	node->prev = descr->top;

	descr->top = node;

}

int pop(stack_descr* descr)

{

	int newdata = descr->top->data;

	node_s *save_topptr;

	save_topptr = descr->top;

	descr->top = descr->top->prev;

	delete save_topptr;

	return newdata; 

}

void write_stack_in_file(stack_descr*descr, int n, FILE *file)
{
	for (int i = 0; i < n; i++)
	{
		int data = pop(descr);
		fwrite(&data, sizeof(int), 1, file);
	}
}

void read_stack_out_file(stack_descr *descr,int &counter, FILE *file)
{
	int buff;
	//int counter = 0;

	for (;;)
	{
		fread(&buff, sizeof(int), 1, file);

		if (feof(file))
			break;
		int value = buff;
		push(descr, value);
		cout << value << " ";
		counter++;

	}

}

void question()
{

	cout << "remove stack?" << endl;
	char answer[10];
	char yes[4] = "yes";
	cin >> answer;
	if (strcmp(yes, answer) == 0)
		remove("stack");
}