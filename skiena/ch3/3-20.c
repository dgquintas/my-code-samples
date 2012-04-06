#include <glib.h>
#include <stdio.h>

// Write a function to find the middle node of a singly-linked list.

/* Idea: 
 *
 * Two pointers. One advances one step at a time. The other one advances two. When the fast one
 * reaches the last node, the position of the slower one will be the middle node. 
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

GSList* safe_next(GSList* l){
    return l == NULL ? NULL : l->next;
}

GSList* getMiddle(GSList* l){
    GSList *slow, *fast;
    slow = l;
    fast = l;

    while( fast && fast->next ){
        slow = safe_next(slow);
        fast = safe_next( safe_next(fast) );
    }
    return slow;
}


int main(){
    GSList* l = NULL;

    l = g_slist_prepend(l, GINT_TO_POINTER(1));
    l = g_slist_prepend(l, GINT_TO_POINTER(2));
    l = g_slist_prepend(l, GINT_TO_POINTER(3));
    l = g_slist_prepend(l, GINT_TO_POINTER(4));
    l = g_slist_prepend(l, GINT_TO_POINTER(5));
    g_slist_free(l);


    printList(l); printf("\n");
    GSList* node = getMiddle(l);
    printf("%d\n", node->data);


    l = NULL;

    l = g_slist_prepend(l, GINT_TO_POINTER(1));
    l = g_slist_prepend(l, GINT_TO_POINTER(2));
    l = g_slist_prepend(l, GINT_TO_POINTER(3));
    l = g_slist_prepend(l, GINT_TO_POINTER(4));
 
    printList(l); printf("\n");
    node = getMiddle(l);
    printf("%d\n", node->data);



    return 0;
}


