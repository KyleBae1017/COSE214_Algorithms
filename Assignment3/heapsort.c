#include <stdio.h>
#include <stdlib.h>

int length;
int heap_size;

int left(int i){
    return i*2;
}

int right(int i){
    return i*2 + 1;
}

void max_heapify(int *A, int i){

    int l = left(i);
    int r = right(i);
    
    int largest;

    if(l<=heap_size && A[l] > A[i]) largest = l;
    else largest = i;

    if(r<=heap_size && A[r] > A[largest]) largest = r;

    if(largest != i){

        int tmp = A[i];
        A[i] = A[largest];
        A[largest] = tmp;

        max_heapify(A, largest);

    }

}

void build_max_heap(int * A){

    heap_size = length;

    for(int i = length / 2;i>=1;i--){
        max_heapify(A, i);
    }

}

void heap_sort(int * A){

    build_max_heap(A);

    for(int i = length;i>=2;i--){

        int tmp = A[1];
        A[1] = A[i];
        A[i] = tmp;
        
        heap_size--;

        max_heapify(A, 1);

    }

}

int main(){

    scanf("%d", &length);

    int *arr = malloc(sizeof(int) * (length+1));

    for(int i=1;i<=length;++i){
        scanf("%d", &arr[i]);
    }

    heap_sort(arr);

    for(int i=1;i<=length;++i){
        printf("%d\n", arr[i]);
    }

    free(arr);

    return 0;

}