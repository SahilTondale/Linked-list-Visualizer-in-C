#define _CRT_RAND_S 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef long long int ssize_t; 

void populate_array(unsigned int* arr, ssize_t N); 
void sort(unsigned int* arr, ssize_t N); 
void show_array(unsigned int* arr, ssize_t N, const char* msg); 


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
    //show_array(arr, N, "Before sorting:"); 
    start = time(0); 
    sort(arr, N); 
    end = time(0); 
    //show_array(arr, N, "After sort:"); 

    delta = end - start; 
    printf("Physical time:Insertion Sort for size:%lld:Seconds:%lld\n", N, delta); 

    free(arr); 
    arr = NULL; 

    return (0); 
}

void sort(unsigned int* arr, ssize_t N){
    ssize_t i, j; 
    unsigned int key; 

    for(j = 1; j < N; ++j){
        key = arr[j]; 
        i = j - 1; 
        while(i > -1 && arr[i] > key){
            arr[i + 1] = arr[i]; 
            i = i - 1; 
        }
        arr[i + 1] = key; 
    }
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
