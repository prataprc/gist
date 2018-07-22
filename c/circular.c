#include <stdio.h>

struct node {
    int a;
    struct node* next;
};

void check_circular(struct node *);
struct node* reverse(struct node *);


int main(void) {
    int i;
    struct node ns[10];

    /* Sample linked list */
    for(i=0; i<10; i++) {
        ns[i].a = i+100;
        ns[i].next = i < 9 ?  &ns[i+1] : NULL;
    }
    check_circular( &ns[0] );   // without circular loop.

    // Print the list
    for(i=0; i < 10; i++) printf("%d ", ns[i].a);
    printf("\n");

    ns[9].next = &ns[4];    // with circular loop.
    check_circular( &ns[0] );

    // Print the list
    for(i=0; i < 10; i++) printf("%d ", ns[i].a);
    printf("\n");
}

void check_circular(struct node* start) {
    struct node *newstart;
    newstart = reverse(start); 
    if(newstart == start) {
        printf("There is circular loop in list\n");
    } else {
        printf("No circular loop\n");
    }
    reverse(newstart);  // Fix the list to original order.
}

struct node* reverse(struct node* this) {
    struct node *element = NULL, *next;
    while(this) {
        next = this->next;
        this->next = element;
        element = this;
        this = next;
    }
    return element;
}

