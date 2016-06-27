// heapsort program
//
// W. E. Cohen
// 11/23/98
//

#include <stdio.h>
#include <stdlib.h>

struct item_type{
        int             key;    // used to order the items
};

struct list_type{
        int             count;  // number of elements in entry array
        item_type       *entry; // array of items_type, entry=&(entry[0])
};

extern void heap_sort(list_type *lp);
extern void insert_heap(list_type *lp, item_type item, int start, int maxheap);
extern void build_heap(list_type *lp);

extern list_type input_data();
extern void output_data(list_type online);


int main(int argc, char *argv[])
{
  list_type on_line;

  // read in all the data from cin, one element per line
  on_line=input_data();
  // perform the sort
  heap_sort(&on_line);
  // write out the sorted values
  output_data(on_line);

  return EXIT_SUCCESS;
}


list_type input_data()
{
  list_type data;
  item_type *temp_buffer;
  int capacity;
  int value;
  int success;
  int DEFAULT_CAPACITY=2;
  int i;


  data.count=0;
  // allocate some space for elements
  data.entry = new item_type[DEFAULT_CAPACITY];
  capacity = DEFAULT_CAPACITY;

  // loop to read in each element
  success = fscanf(stdin, "%d", &value);
  // fscanf should return 1 element each time
  while (success==1){
    // if out of room make bigger array and copy
    if (data.count >= capacity){
      // make bigger buffer
      temp_buffer = new item_type[capacity*2];
      // copy everything over
      for (i=0; i<data.count; ++i){
	temp_buffer[i] = data.entry[i];
      }
      // replace old array with new
      delete [] data.entry;
      data.entry = temp_buffer;
      capacity = capacity*2;
    }
    data.entry[data.count].key = value;
    ++data.count;
    // read in next value
    success = fscanf(stdin, "%d", &value);
  }


  return data;
}


void output_data(list_type data)
{
  int i;

  // print out each of the sorted elements
  for (i=0; i<data.count; ++i){
    printf("%d\n", data.entry[i].key);
  }
}

/* heap_sort: Sort a contiguous list beginning at index 0 of the array. */
void heap_sort(list_type *lp)
{
        // The array indices used start at 0
        int i;
        item_type item;                // temporary storage

        build_heap(lp);
        for(i=(lp->count-1); i>=0; --i){
                // Extract the last element from the unsorted portion of the
                // array
                item = lp->entry[i];
                // Move top of the heap (largest element) to beginning
                // of the sorted portion of the array
                lp->entry[i] = lp->entry[0];
                // Restore the heap properties.
                insert_heap(lp, item, 0, i-1);
        }
}

// insert_heap: inserts a single item in partial heap with empty root at start.
// the heap is from  start to maxheap in the array.
void insert_heap(list_type *lp, item_type item, int start, int maxheap)
{
        int m;        // child of start with larger key

        m = 2*start + 1; // When start is 0, child is at 1.

        while (m<=maxheap){
                if (m<maxheap && lp->entry[m].key<lp->entry[m+1].key)
                        m++;        // m contains index of larger key.
                if (item.key>=lp->entry[m].key){
			// indicate place for item
                        break;        // item belongs in position start.
                } else {
                        lp->entry[start] = lp->entry[m];
                        start = m;
                        m = 2*start + 1;
                }
        }
        lp->entry[start] = item;
}

// build_heap: build a heap from a contiguous list.
void build_heap(list_type *lp)
{
        int i;

        for (i=(lp->count)-1; i>=0; --i){
                insert_heap(lp, lp->entry[i], i, lp->count-1);
        }
}
