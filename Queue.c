#include <stdio.h>
#include <stdlib.h>

struct Queue {
   int tail;
   int head;
   int length;
   void** q;
};

struct Queue*   NewQueue( int size );
int   GrowQueue( struct Queue* Q           );
int     Enqueue( struct Queue* Q, void* x  );
void*   Dequeue( struct Queue* Q           );
void  FreeQueue( struct Queue* Q           );
void    Display( struct Queue* Q );

int main() {
   int It = 0;
   char *node;
   struct Queue *Q = NewQueue(8);

   FreeQueue( Q );

   return 0;
}

/* Display() assumes that Q->q is an array of char* */
void Display( struct Queue* Q ) {
   int It = 0;
   for(It = 0; It < Q->length; It++) {
      if( (It <  Q->tail &&     It >= Q->head) ||
          (It <  Q->tail && Q->tail < Q->head) ||
          (It >= Q->head && Q->tail < Q->head) ) {
         char c = *(char*)Q->q[It];
         printf("%c", c );
      }
      else printf("-");
   }
   puts("");

   for(It = 0; It < Q->length; It++ ){
      if(It == Q->head)
         putchar('h');
      else if(It == Q->tail)
         putchar('t');
      else if( (It <  Q->tail &&     It >= Q->head) ||
          (It <  Q->tail && Q->tail < Q->head) ||
          (It >= Q->head && Q->tail < Q->head) )
         putchar('-');
      else
         putchar(' ');
   }
   puts("");
}

struct Queue* NewQueue( int size ) {
   struct Queue* Q = malloc( sizeof(struct Queue) );
   if( Q == NULL ){
      return NULL;
   }
   Q->q = calloc( sizeof(void*), size );
   if( Q->q == NULL ){
      return NULL;
   }
   Q->tail = 0;
   Q->head = 0;
   Q->length = size;

   return Q;
}

void FreeQueue( struct Queue* Q ) {
   free( Q->q );
   free( Q );
   return;
}

int GrowQueue( struct Queue* Q ) {
   void** temp;
   temp = realloc(Q->q, Q->length*2 * sizeof(void *));
   if( temp == NULL ){
      return 0;
   }
   Q->q = temp;
   if( Q->tail < Q->head ){
      int It;
      for(It = 0; It < Q->tail; It++)
         Q->q[Q->length+It] = Q->q[It];

      Q->tail += Q->length;
   }
   Q->length *= 2;

   return 1;
}

int Enqueue( struct Queue* Q, void* x ) {
   if( Q->head == (Q->tail + 1) % Q->length ) {
      if( GrowQueue( Q ) == 0 ) 
         return 0;
   }
   Q->q[Q->tail] = x;
   if(Q->tail == Q->length-1)
      Q->tail = 0;
   else
      Q->tail += 1;
   return 1;
}

void* Dequeue( struct Queue* Q ) {
   void* x = Q->q[Q->head];

   if( Q->head == Q->tail )
      return NULL;

   if( Q->head == Q->length )
      Q->head = 0;
   else
      Q->head += 1;
   return x;
}
