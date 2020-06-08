#include <stdio.h>
#include <stdlib.h>

struct arraylist {
	int capacity ;
	int length ;
	int * elements ;
} ;

typedef struct arraylist arraylist_t ;

arraylist_t * 
arraylist_alloc ()  ;

void
arraylist_insert (arraylist_t * l, int e) ;

int
arraylist_retrieve (arraylist_t * l, int pos, int * e) ;

int 
arraylist_length (arraylist_t * l) ;

int 
arraylist_pop (arraylist_t * l, int * e) ;

arraylist_t * 
arraylist_alloc () 
{
	arraylist_t * l ;

	l = (arraylist_t *) malloc(sizeof(arraylist_t)) ;
	
	l->length = 0 ;
	l->capacity = 10 ;
	l->elements = (int *) calloc(l->capacity, sizeof(int)) ;
			// malloc(l->capacity * sizeof(int));
	return l ;
}

void
arraylist_insert (arraylist_t * l, int e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;	
		l->elements = (int *) realloc(l->elements, l->capacity) ;
	}

	l->elements[l->length] = e ;  
	l->length += 1 ;            // array[i]에 e 넣고 length++ => 스켈레톤
}

int
arraylist_retrieve (arraylist_t * l, int pos, int * e)
{
	if (l->length <= pos) 
		return 1 ;
	
	*e = l->elements[pos] ;
	return 0 ;
}

int
arraylist_recapa (arraylist_t *l){
	int n;
	n = l->capacity;
	return n;
}

int 
arraylist_length (arraylist_t * l)
{
	return l->length ;
}

int 
arraylist_pop (arraylist_t * l, int * e) 
{
	if (l->length == 0)
		return 1 ;

	*e = l->elements[0] ;
	l->length -= 1 ;

	for (int i = 1 ; i <= l->length ; i++) {
		l->elements[i-1] = l->elements[i] ;
	}

	if (l->length * 4 <= l->capacity) {
		l->capacity = l->length * 2 ;
		l->elements = (int *) realloc(l->elements, l->capacity) ;
	}
	return 0 ;
}


int 
main () 
{
	arraylist_t * l ; 

	l = arraylist_alloc() ; // ()

	arraylist_insert(l, 1) ; // (1)
	arraylist_insert(l, 2) ; // (1, 2)
	arraylist_insert(l, 3) ; // (1, 2, 3)

	int c;
	c = arraylist_recapa(l);

	printf("capa: %d\n", c);

	int e ;
	if (arraylist_retrieve(l, 1, &e)) {// e <- 2
		fprintf(stderr, "Error") ;
		return 1 ;
	}
	printf("%d\n", e) ;

	while (arraylist_length(l) > 0) {
		int e ;

		if (arraylist_pop(l, &e)) 
			return 1 ;
		printf("%d ", e) ;
	}
	printf("\n") ;
}
