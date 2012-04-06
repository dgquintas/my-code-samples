#include <glib.h>
#include <stdio.h>

/* Idea: Floyd's Cycle detection Algorithm. TAOCP Vol. 2, section 3.1 pag. 7, ex. 6. 
 * Let µ be the length of the "lolipop stick", lambda the cycle length. 
 * Let's have two pointers, one of them advancing one step a time; the other one 2x. 
 * We know we've found a cycle whenever X[i] == X[i+k*lambda] for integers k and i. ANY 
 * i >= µ. We can see that thinking about being at X[i] and looping around k times. 
 * We'll clearly end up at the same place!
 * That is, the fast pointer has gone around the loop k times and has then bumped 
 * into the slow one. The problem is that "i" is arbitrary and we don't yet know the
 * value of "lambda". So far we know there IS a loop, but not its length of where does it
 * start. 
 * Because "i" is arbitrary, we can choose it to be "k*lambda" as long as it's >= µ. Thus 
 *              
 *                  X[i] == X[i + k*lambda] 
 * becomes
 *
 *                  X[i] == X[2*i]
 *
 * which justifies the choice of a pointer moving 2x as fast at the other (this should
 * have been mentioned BEFORE, as it's the cause of that choice).
 *
 * Once we find such i (= k*lambda for a certain k), we can work out the µ by observing that
 *
 *                  X[µ + k*lambda] == X[µ] (which is just the special case i == µ). 
 *
 *                  Thus (i = k*lambda)
 *                  X[µ + i] == X[µ]
 *
 * Which means that if we take µ steps from where we stand at i, we'll end up at µ. In order
 * to gauge this µ, we simply reset one of the pointers to X[0] and move both pointers fw 
 * one step at a time. The reseted pointer fulfills the right side of the equation, X[µ], 
 * while the pointet at X[i] will be at X[i+µ]. When they first meet, the equation is made true,
 * hence revelaing the value of µ. 
 * If we then keep on iterating, after having noted the value of X[µ], we can derive lambda just
 * by counting the steps until we see the value of X[µ] again.
 *
 */

GSList* f(GSList* l){
    return l == NULL ? NULL : g_slist_next(l);
}

void printList(GSList* l){
    if(l){
        GSList* ll = l;
        gpointer e = ll->data;
        printf("[");
        while(ll){
            int i = GPOINTER_TO_INT(ll->data);
            printf("%d ", i);
            ll = ll->next;
        }
        printf("]\n");
    }
}

void makeLoop(GSList* l, int n){
    // go to the end of the list
    GSList* tail = g_slist_last(l);
    
    //make that tail point back to the n-th node
    GSList* nth = g_slist_nth(l,n);

    tail->next = nth;
}

int hasLoop(GSList *l){
    GSList *slow, *fast;
    slow = f(l);
    fast = f( f(l) );

    // look for the first "clash"
    while( fast && slow != fast){
        slow = f(slow);
        fast = f(f(fast));
    }
    if( fast == NULL ){
        return -1; // no loop
    }

    // "retrace" steps to find out µ
    int mu = 0;
    slow = l;
    while( slow != fast ){
        slow = f(slow);
        fast = f(fast);
        mu++;
    }
    return mu;


}

GSList* init(int n){
    GSList* l = NULL;
    for(int i=n; i>0; i--){
        l = g_slist_prepend(l, GINT_TO_POINTER(i));
    }
    return l;
}
    
#define N 2
int main(){

    GSList* l = init(N);
    printList(l);
    printf("%d\n", hasLoop(l));
 
    g_slist_free(l); l = init(N);
    makeLoop(l, 1);
    printf("%d\n", hasLoop(l));

    g_slist_free(l); l = init(N);
    makeLoop(l, 0);
    printf("%d\n", hasLoop(l));


    return 0;
}

