#include <stdio.h>
#include <stdlib.h>

struct node {
	int element ;
	struct node * next ; 
} ;

struct linkedlist {
	int length ;
	struct node * first ;
	struct node * last ;
} ;

typedef struct node node_t ;
typedef struct linkedlist linkedlist_t ;

linkedlist_t * 
linkedlist_alloc()  ;

void
linkedlist_push (linkedlist_t * l, int e) ;

void
linkedlist_insert (linkedlist_t * l, int e) ;

int
linkedlist_retrieve (linkedlist_t * l, int pos, int * e) ;

int 
linkedlist_length (linkedlist_t * l) ;

int 
linkedlist_pop (linkedlist_t * l, int * e) ;

int
linkedlist_remove (linkedlist_t * l, int e) ;


linkedlist_t * 
linkedlist_alloc () 
{
	linkedlist_t * l ;
	l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->first = 0x0 ;
	l->last = 0x0 ;
	l->length = 0 ;
	return l ;
}

void
linkedlist_push (linkedlist_t * l, int e)
{
	node_t * n ;
	n = (node_t *) malloc(sizeof(node_t)) ;
	n->element = e ;
	n->next = l->first ;
	l->first = n ;
	if (l->last == 0x0 /* l->length == 0 */)
		l->last = n ;
	l->length += 1 ;
}


void
linkedlist_insert (linkedlist_t * l, int e)
{
	node_t * n ;

	n = (node_t *) malloc(sizeof(node_t)) ;
	n->element = e ;
	n->next = 0x0 ;

	if (l->length == 0) {
		l->first = n ;
	}
	else {
		l->last->next = n ;
	}
	l->last = n ;
	l->length += 1 ;
}

int
linkedlist_retrieve (linkedlist_t * l, int pos, int * e)
{
	int i ;
	node_t * itr ;

	if (!(pos < l->length))
		return 1 ;

	i = 0 ; 
	itr = l->first ; 
	while (i < pos) {
		i++ ;
		itr = itr->next ;
	}
	*e = itr->element ;
	return 0 ;
}

int 
linkedlist_length (linkedlist_t * l)
{
	return l->length ;
}

int 
linkedlist_pop (linkedlist_t * l, int * e)
{
	if (l->length == 0)
		return 1 ;

	*e = l->first->element ;

	node_t * tmp ; // to-be-deleted/freed
	tmp = l->first ;
	l->first = l->first->next ;
	free(tmp) ;

	l->length -= 1 ;
	if (l->length == 0) {
		l->first = 0x0 ; 
		l->last = 0x0 ;
	}
	return 0 ;
}

int
linkedlist_remove (linkedlist_t * l, int e)
{
	node_t * prev = 0x0 ;
	node_t * curr = 0x0 ; // prev->next == curr when curr is not first
	for (curr = l->first ; curr != 0x0 ; curr = curr->next) {
		if (curr->element == e) {
			if (prev != 0x0) 
				prev->next = curr->next ;
			else 
				l->first = curr->next ;	
			
			if (curr == l->last)
				l->last = prev ;

			free(curr) ;
			l->length -= 1 ;
			return 0 ;
		}
		else {
			prev = curr ;
		}
	}
	return 1 ;
}

int 
main () 
{
	linkedlist_t * l ; 

	l = linkedlist_alloc() ;

	linkedlist_insert(l, 1) ;
	linkedlist_insert(l, 2) ;
	linkedlist_insert(l, 3) ;
	linkedlist_push(l, 0) ;

	int e ;
	if (linkedlist_retrieve(l, 1, &e)) 
		return 1 ;
	printf("%d\n", e) ;

	linkedlist_remove(l, 3) ;
	linkedlist_remove(l, 1) ;

	while (linkedlist_length(l) > 0) {
		int e ;

		if (linkedlist_pop(l, &e)) 
			return 1 ;
		printf("%d ", e) ;
	}
	printf("\n") ;
}
