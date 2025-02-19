#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

void test_partition(void);
ssize_t partition(int* a, ssize_t p, ssize_t r);
void show_array(int* a, ssize_t N, const char* msg);
void swap(int* , int*);

int main(void)
{
    test_partition();
    return (EXIT_SUCCESS);
}

void test_partition(void)
{
    int arr[] = {
        10, 65, 85, 75, 25,
        35, 95, 23, 11, 63,
    };
    ssize_t N = (ssize_t)(sizeof(arr)/sizeof(arr[0])); 
    ssize_t q; 
    show_array(arr, N, "Before partition:"); 
    q = partition(arr, 0, N-1); 
    show_array(arr, N, "After partition:");   
}

ssize_t partition(int* a, ssize_t p, ssize_t r)
{
    ssize_t i;
    ssize_t ;

    int pivot;
    pivot = a[j];
    j = p;
    i = p - 1;
    while(j < r)
    {
        if(a[j] < pivot)
        {
            i = i + 1;
            swap(&a[i], &a[j]);
        }
        j = j + 1;
    }
    swap(&a[i+1], &a[r]);
    return (i + 1);
}

void show_array(int* a, ssize_t N, const char* msg){
    
    if(msg)
        puts(msg); 

    ssize_t i; 

    for(i = 0; i < N; ++i)
        printf("a[%lld]:%d\n", i, a[i]); 
}

void swap(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}