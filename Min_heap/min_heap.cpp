#include <iostream>

using namespace std;

typedef struct minimum_heap
{
    int capacity;
    int hsize;
    int* harray;
}minheap;


minheap* initheap(int c)
{
    minheap* h = new minheap;
    h->hsize = 0;
    h->capacity = c;
    h->harray = new int[c];

    return h;
}

void percolate_down(minheap *h, int index);
void printHeap(minheap *h);

void hswap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }


//*****************************************INSERT_BY_ARRAY******************************************************

// Initializes the heap using the first length number of items in the array values.

minheap* initHeapfromArray(int* values, int length)
{
    minheap* h= new minheap;
    h->harray = new int[length];
    h->capacity = length;
    h->hsize = length-1;

    for(int i=0; i<length; i++)
        h->harray[i] = values[i];

    for(int i= (length-1)/2; i>=0; i--)
        percolate_down(h, i);

    cout<<"Elements in heap after insertion through array\n";
    for(int i=0; i<length; i++)
        cout<<h->harray[i]<<" ";
    cout<<endl;

    return h;
}



//*****************************************INSERT****************************************************************

//To insert an element say x, into the heap with n elements, we first create a hole in position (n+1) and see if the heap
//property is violated by putting x into the hole. If the heap property is not violated, then we have found the correct position
// for x. Otherwise, we ``push-up'' or ``percolate-up'' x until the heap property is restored. To do this, we slide the element
//that is in the hole's parent node into the hole, thus bubbling the hole up toward the root. We continue this process until x
//can be placed in the whole

void percolate_up(minheap* heap, int index)
{
    if(index > 0)
    {
        if( heap->harray[index/2] > heap->harray[index] )
        {
            hswap(&heap->harray[index/2] , &heap->harray[index]);
            index= index/2;
            percolate_up(heap, index);
        }
    }
}



void insert_heap(minheap* heap, int val)
{
    if( (heap->hsize ) == heap->capacity )
    {
        cout<<"heap is full\n";
        return;
    }

    heap->harray[ heap->hsize ]= val;
    percolate_up(heap, heap->hsize);
    heap->hsize ++;
}




//******************************************REMOVE_MIN*******************************************************

//When the minimum is deleted, a hole is created at the root level. Since the heap now has one less element and the heap is a
//complete binary tree, the element in the least position is to be relocated. This we first do by placing the last element in
//the hole created at the root. This will leave the heap property possibly violated at the root level. We now ``push-down'' or
//``percolate-down'' the hole at the root until the violation of heap property is stopped. While pushing down the hole, it is
//important to slide it down to the less of its two children (pushing up the latter). This is done so as not to create another
//violation of heap property.

void percolate_down(minheap* heap, int index)
{
    int minval= index;
    int left= 2*index + 1;
    int right= 2*index + 2;

    if(left < heap->hsize && heap->harray[left] < heap->harray[minval])
        minval= left;

    if(right < heap->hsize && heap->harray[right] < heap->harray[minval])
        minval= right;

    if(minval != index)
    {
        hswap(&heap->harray[index] , &heap->harray[minval]);
        percolate_down(heap, minval);
    }
}


int remove_min(minheap* heap)
{
    int minval;
    if(heap->hsize >= 0)
    {
        minval= heap->harray[0];
        heap->harray[0] = heap->harray[ heap->hsize];
        heap->hsize--;
        percolate_down(heap, 0);
        return minval;
    }
    return -1;
}

//********************************************HEAP_SORT*************************************************************

void heapsort(int val[], int l)
{
    minheap* h = initHeapfromArray(val, l);

    for (int i=0; i<l; i++) {
         val[i] = remove_min(h);
     }

    cout<<"\nAfter Heapsort\n";
    for(int i=0; i<l; i++)
        cout<<val[i]<<" ";
    cout<<endl<<endl;
}

//******************************************PRINT_HEAP***********************************************

void printHeap(minheap *h) {
    int i;

    for (i=0; i<h->hsize; i++)
        printf("%d ", h->harray[i]);
    printf("\n");
}


int main()
{
    minheap *h;
    h = initheap(9);
    int vals[10];


    // Test out individual inserts.
    insert_heap(h, 7);
    insert_heap(h, 3);
    insert_heap(h, 5);
    insert_heap(h, 12);
    insert_heap(h, 2);
    insert_heap(h, 8);
    insert_heap(h, 4);
    insert_heap(h, 9);
    insert_heap(h, 1);
    insert_heap(h, 18);

    cout<<"Elements in heap after normal Insertion\n";
    printHeap(h);
    cout<<endl;

    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;
    cout<<"min val = "<<remove_min(h)<<endl<<endl;

    vals[0] = 12, vals[1] = 3, vals[2] = 18, vals[3] = 14, vals[4] = 5;
    vals[5] = 9, vals[6] = 1, vals[7] = 7; vals[8] = 2, vals[9] = 13;


    heapsort(vals, 10);

    return 0;
}
