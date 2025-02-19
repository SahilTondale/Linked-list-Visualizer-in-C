#include <stdio.h>
#include <stdlib.h>

void test_merge(void);
void show_array(int* a, ssize_t N, const char* msg);
void merge(int* a, ssize_t p, ssize_t q, ssize_t r);
void* xmalloc(size_t size_in_bytes);

int main(void)
{
    test_merge();
    return (EXIT_SUCCESS);
}

void test_merge(void)
{
    int arr[] = {
        2, 5, 1, 33, 10,
        20, 30, 40, 50, 25,
        27, 29, 33, 38, 45,
        50, 55, 12, 459, 10
    };

    ssize_t p = 4;
    ssize_t q = 8;
    ssize_t r = 16;
    ssize_t N = (ssize_t)(sizeof(arr)/sizeof(arr[0]));
    show_array(arr, N, "Before Merge");
    merge(arr, p, q, r);
    show_array(arr, N, "After Merge");
}

void show_array(int* a, ssize_t N, const char* msg)
{
    if(msg)
        puts(msg);
    
    ssize_t i;
    for(i = 0; i < N; ++i)
        printf("a[%lld]:%d\n", i, a[i]);
}

void merge(int* a, ssize_t p, ssize_t q, ssize_t r)
{
    int* a1 = NULL; /* Pointer to store base address of sub-array 1*/
    int* a2 = NULL; /* Pointer to store base address of sub-array 2*/
    ssize_t N1, N2;
    ssize_t cnt;
    ssize_t i; /* Tracker of sub-array 1*/
    ssize_t j; /* Tracker of sub-array 2*/
    ssize_t k; /* tracker of Original array a*/

    N1 = q - p + 1;
    N2 = r - q;

    a1 = (int*)malloc(N1 * sizeof(int));
    a2 = (int*)malloc(N2 * sizeof(int));

    for(cnt = 0; cnt < N1; cnt++)
        a1[cnt] = a[p + cnt];
    for(cnt = 0; cnt < N2; cnt++)
        a2[cnt] = a[q + 1 + cnt];
    
    i = 0;
    j = 0;
    k = 0;

    while(TRUE)
    {
        if(a1[i] <= a2[j])
        {
            a[p+k] = a1[i];
            i++;
            k++;
            if(i == N1)
            {
                while(j < N2)
                {
                    a[p+k] = a2[j];
                    j++;
                    k++;
                }
                break;
            }
        }
        else
        {
            a[p+k] = a2[j];
            j++;
            k++;
            if(j == N2)
            {
                while(i < N1)
                {
                    a[p+k] = a1[i];
                    i++;
                    k++;
                }
                break;
            }
        }
    }

    free(a1);
    a1 = NULL;

    free(a2);
    a2 = NULL;
}

void* xmalloc(size_t size_in_bytes)
{
    void* ptr = NULL;

    ptr = malloc(size_in_bytes);
    if(ptr == NULL)
    {
        puts("Malloc failed");
        exit(EXIT_FAILURE);
    }

    return (ptr);
}

