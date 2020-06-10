// circular LinkedList
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	void * element ;
	struct node * next ; 
} ;

struct linkedlist {
	int unit ;
	struct node * last ;
} ;


typedef struct node node_t ;
typedef struct linkedlist linkedlist_t ;

linkedlist_t * 
linkedlist_alloc (int unit)  ;

void
linkedlist_free (linkedlist_t * l) ;

int 
linkedlist_length (linkedlist_t * l) ;

void
linkedlist_insert_first (linkedlist_t * l, void * e) ;

void
linkedlist_insert_last (linkedlist_t * l, void * e) ;

int
linkedlist_remove (linkedlist_t * l, node_t * n) ;

int
linkedlist_remove_first (linkedlist_t * l, void * e) ;

int
linkedlist_remove_last (linkedlist_t * l, void * e) ;

int
linkedlist_get (linkedlist_t * l, int pos, void * e) ;

linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->unit = unit ;
	l->last = 0x0 ;	
	return l ;
}

void
linkedlist_free (linkedlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	if (l->last) {
		curr = l->last->next ; 
		do {
			node_t * next = curr->next ;
			free(curr->element) ;
			free(curr) ;
			curr = next ;
		} while (curr != l->last) ;
	}
	free(l) ;
}

int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;
	if (l->last) {
		node_t * curr = l->last ;
		do {
			len += 1 ;
			curr = curr->next ;
		} while (curr != l->last) ;
	}
	return len ; 
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	node_t * n = (node_t *) malloc(sizeof(node_t)) ;
	n->element = malloc(l->unit) ;
	memcpy(n->element, e, l->unit) ;

	if (l->last) {
		node_t * first ;
		first = l->last->next ;
		n->next = first ;
		l->last->next = n ;
	}
	else {
		l->last = n ;
		l->last->next = n ;
	}
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	node_t * n = (node_t *) malloc(sizeof(node_t)) ;
	n->element = malloc(l->unit) ;
	memcpy(n->element, e, l->unit) ;

	if (l->last) {
		node_t * first ;
		first = l->last->next ;
		n->next = first ;
		l->last->next = n ;
		l->last = n ;
	}
	else {
		l->last = n ;
		l->last->next = n ;
	}
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	if (l->last == 0x0)
		return 1 ;

	node_t * prev = l->last ;
	node_t * curr = l->last->next ;
	while (curr != n && curr != l->last) {
		prev = curr ;
		curr = curr->next ;		
	}
	if (curr != n) 
		return 1 ;

	if (prev != curr) 
		prev->next = curr->next ;
	else 
		l->last = 0x0 ;
	free(curr->element) ;
	free(curr) ;
	return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->last == 0x0)
		return 1 ;

	node_t * first = l->last->next ;
	memcpy(e, first->element, l->unit) ;
	linkedlist_remove(l, first) ;
	return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->last == 0x0)
		return 1 ;

	node_t * last = l->last ;


	if (l->last == l->last->next) {
		l->last = 0x0 ;
	} 
	else {
		node_t * n = l->last ;
		while (n->next != l->last) {
			n = n->next ;
		}
		n->next = l->last->next ;
		l->last = n ;
	}

	memcpy(e, last->element, l->unit) ;
	free(last->element) ;
	free(last) ;
	return 0 ;
}

int
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0 || l->last == 0x0)
		return 1 ;

	int i = 0 ;
	node_t * n = l->last->next ;
	while (i < pos && n != l->last) {
		n = n->next ;
		i++ ;
	}
	if (i != pos)
		return 1 ;

	memcpy(e, n->element, l->unit) ;
	return 0 ;
}

int 
main () 
{
	int data ;
	linkedlist_t * l ; 

	l = linkedlist_alloc(sizeof(int)) ;

	data = 1 ;
	linkedlist_insert_last(l, &data) ;

	data = 2 ;
	linkedlist_insert_last(l, &data) ;

	data = 3 ;
	linkedlist_insert_first(l, &data) ;

	data = 4 ;
	linkedlist_insert_first(l, &data) ;

	if (linkedlist_get(l, 1, &data)) 
		return 1 ;
	printf("%d\n\n", data) ;

	linkedlist_remove_last(l, &data) ;
	printf("%d\n", data) ;

	while (linkedlist_length(l) > 0) {
		linkedlist_remove_first(l, &data) ;
		printf("%d ", data) ;
	}
	printf("\n") ;

	//linkedlist_free(l) ;
}


