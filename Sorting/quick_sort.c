#define _CRT_RAND_S 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef long long int ssize_t; 

void populate_array(unsigned int* arr, ssize_t N); 
void sort(unsigned int* arr, ssize_t N); 
void show_array(unsigned int* arr, ssize_t N, const char* msg); 

ssize_t partition(unsigned int* a, ssize_t p, ssize_t r); 
ssize_t quick_sort(unsigned int*, ssize_t, ssize_t); 
void swap(unsigned int* ,unsigned int*);

int main(int argc, char* argv[]){   
    unsigned int* arr = NULL; 
    ssize_t N = 0; 
    time_t start, end, delta; 

    if(argc != 2){
        printf("UsageError:Correct usage:%s number_of_elements\n", argv[0]); 
        exit(EXIT_FAILURE); 
    }

    N = atoll(argv[1]); 
    if(N <= 0){
        puts("ValueError:size must be positive"); 
        exit(EXIT_FAILURE); 
    }

    arr = (unsigned int*)malloc(N * sizeof(unsigned int)); 
    if(arr == NULL){
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    populate_array(arr, N); 
    show_array(arr, N, "Before sorting:"); 
    start = time(0); 
    sort(arr, N); 
    end = time(0); 
    show_array(arr, N, "After sort:"); 

    delta = end - start; 
    printf("Seconds:%lld\n", delta); 

    free(arr); 
    arr = NULL; 

    return (0); 
}

void sort(unsigned int* arr, ssize_t N){
    quick_sort(arr, 0, N-1); 
}

ssize_t quick_sort(unsigned int* a, ssize_t low, ssize_t high)
{
    ssize_t pivot;

    if(low < high)
    {
        pivot = partition(a, low, high);
        quick_sort(a, low, pivot-1);
        quick_sort(a, pivot+1, high);
    }
    return(pivot);
}

ssize_t partition(unsigned int* a, ssize_t p, ssize_t r){
    ssize_t i, j; 

    unsigned int pivot; 

    pivot = a[r]; 
    i = p - 1; 
    for(j = p; j < r; ++j){
        if(a[j] < pivot)
        {
            i = i + 1; 
            swap(&a[i], &a[j]);
        }
    } 

    swap(&a[i+1], &a[r]);

    return (i + 1); 
}

void populate_array(unsigned int* arr, ssize_t N){
    ssize_t i; 

    srand(time(0)); 
    for(i = 0; i < N; ++i)
        rand_s(arr + i); 
}

void show_array(unsigned int* arr, ssize_t N, const char* msg){
    ssize_t i; 

    if(msg)
        puts(msg); 

    for(i = 0; i < N; ++i)
        printf("arr[%lld]:%u\n", i, arr[i]); 
}

void swap(unsigned* a, unsigned int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}