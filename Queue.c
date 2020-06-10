#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;*/

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
	} 
	queue ;

queue * 
create_queue (int capacity, int unit) ;

void
delete_queue (queue * que) ;

int 
enqueue (queue * que, void * elem) ;

int
dequeue (queue * que, void * elem) ;

int 
is_empty (queue * que) ;

int 
is_full (queue * que) ;

void
print_queue (queue * que, void (* print_element)(void * element)) ;

queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity + 1, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	// que->full=0;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % (que->capacity + 1) ;
	
	// que->rear++ if(capacitiy보다rear의 값이  크면) que->rear=0;

	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % (que->capacity + 1) ;
	return 0;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) ;
		// && que->full == 0
}

int 
is_full (queue * que) 
{
	return (((que->rear + 1) % (que->capacity + 1)) == que->front) ;
		// rear랑 front가 한칸차이
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity + 1)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}

void
print_int (void * p)
{
	int * elem = (int *) p ; 
	printf("%d", *elem) ;
}

int
main () 
{
	int data ;
	queue * que ;

	que = create_queue(4, sizeof(int)) ;

	data = 1 ;
	enqueue(que, &data) ;

	data = 2 ;
	enqueue(que, &data) ;

	data = 3 ;
	enqueue(que, &data) ;

	data = 4 ;
	enqueue(que, &data) ;

	dequeue(que, &data) ;

	data = 5 ;
	enqueue(que, &data) ;

	print_queue(que, print_int) ;

	delete_queue(que) ;
	return 0 ;
}
