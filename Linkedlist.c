#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t ;

typedef struct node * linkedlist_t ;

struct node {
	int element ;
	linkedlist_t tail ; 
} ;

linkedlist_t  
linkedlist_alloc()  ;

void
linkedlist_push (linkedlist_t * l, int e) ;
// list가 바뀔 수 있기에 *
  
int
linkedlist_retrieve (linkedlist_t l, int pos, int * e) ;
// list가 바뀔 일이 없기에 *없이 l

int 
linkedlist_length (linkedlist_t l) ;

int 
linkedlist_pop (linkedlist_t * l, int * e) ;

int
linkedlist_remove (linkedlist_t * l, int e) ;

linkedlist_t
linkedlist_alloc () 
{
	return 0x0 ;
}

void
linkedlist_push (linkedlist_t * l, int e)
{
	linkedlist_t new_list = (linkedlist_t) malloc(sizeof(node_t)) ;

	new_list->element = e ;
	new_list->tail = *l ;

	*l = new_list ;
}

int
linkedlist_retrieve (linkedlist_t l, int pos, int * e)
{
	int i = 0 ;
	while (l != 0x0) {
		if (i == pos) {
			*e = l->element ;
			return 0 ;
		}
		// i < pos
		i += 1 ;
		l = l->tail ; 
	}

	return 1 ;
}

int 
linkedlist_length (linkedlist_t l)
{
	int i = 0 ;

	while (l != 0x0) {
		i += 1 ;
		l = l->tail ; 
	}
	return i ;
}

int 
linkedlist_pop (linkedlist_t * l, int * e)
{
	if (*l == 0x0)
		return 1 ;

	linkedlist_t tmp ;
	*e = (*l)->element ; //head
	tmp = *l ;
	*l = (*l)->tail ;
	free(tmp) ;
	return 0 ;
}

int
linkedlist_remove (linkedlist_t * l, int e)
{
	linkedlist_t * p ;
	
	p = l ;
	while (*p != 0x0) {
		if ((*p)->element == e) {
			linkedlist_t tmp ;
			tmp = *p ;
			*p = (*p)->tail ; 
			free(tmp) ;
			return 0 ;
		}
		else {
			p = &((*p)->tail) ;
		}
	}
	return 1 ;
}


int 
main () 
{
	linkedlist_t l ; 

	l = linkedlist_alloc() ;

	linkedlist_push(&l, 1) ;
	linkedlist_push(&l, 2) ;
	linkedlist_push(&l, 3) ;

	int e ;
	if (linkedlist_retrieve(l, 1, &e)) 
		return 1 ;
	printf("%d\n", e) ;

	linkedlist_remove(&l, 3) ;

	while (linkedlist_length(l) > 0) {
		int e ;

		if (linkedlist_pop(&l, &e)) 
			return 1 ;
		printf("%d ", e) ;
	}
	printf("\n") ;
}
