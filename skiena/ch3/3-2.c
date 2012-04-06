#include <glib.h>
#include <stdio.h>

/* Idea: 
 *
 * Process in pairs. Get two nodes, flip the pointer in between and 
 * change the next pointer of the first node to the "carried" node. 
 * This carried node will be NULL the first time (so that the first item
 * of the list gets to point to NULL). After each pair, this carry is 
 * set to the address of the second node. 
 *
 *        c == NULL
 *   l -> * -> * -> * -> * -> * -> NULL
 *        a    b 
 *       
 *  NULL <- * <- * -> * -> * -> * -> NULL
 *               c    a    b
 *
 *  NULL <- * <- * <- * <- * -> * -> NULL
 *                         c    a     b
 *
 *  NULL <- * <- * <- * <- * <- * <- l 
 *                                 
 *
 */ 

void printList(GSList* l){
    if(l){
        GSList* ll = l;
        gpointer e = ll->data;
        while(ll){
            int i = GPOINTER_TO_INT(ll->data);
            printf("%d ", i);
            ll = ll->next;
        }
    }
}

GSList* reverse(GSList* l){
    GSList *a, *b, *c;
    a = b = l;
    c = NULL; //holds "carry" over iterations

    while(a && b){
        b = a->next; 
        a->next = c; //left elem of the pair points to right elem from last iter

        if(b){
            c = b->next; 
            b->next = a;

            //prepare for next iteration
            a = c;
            c = b;
        }
    }
    l = b ? b : a;
    return l;
}



int main(){
    GSList* l = NULL;

    l = g_slist_prepend(l, GINT_TO_POINTER(1));
    l = g_slist_prepend(l, GINT_TO_POINTER(2));
    l = g_slist_prepend(l, GINT_TO_POINTER(3));

    printList(l); printf("\n");
    GSList* ll = reverse(l);
    printList(ll); printf("\n");

    g_slist_free(l);

    return 0;
}


