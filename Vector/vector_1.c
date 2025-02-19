#include <stdio.h> 
#include <stdlib.h> 

#define TRUE 1 
#define FALSE 0 

struct vector
{
    int* a_ptr; 
    int a_length; 
}; 

struct vector* allocate_vector(void); 
void release_vector(struct vector* p_vec); 

void push_back(struct vector* p_vec, int new_data); 
int search_vector(struct vector* p_vec, int search_data); 
void show_vector(struct vector* p_vec, char* msg); 

struct vector* allocate_vector(void)
{
    struct vector* p_vec = NULL; 

    p_vec = (struct vector*)malloc(sizeof(struct vector)); 
    if(p_vec == NULL)
    {
        puts("Error");
        exit(-1); 
    }
    p_vec->a_ptr = NULL; 
    p_vec->a_length = 0; 
    return (p_vec); 
}

void release_vector(struct vector* p_vec)
{
    if(p_vec->a_ptr != NULL)
    {
        free(p_vec->a_ptr); 
        p_vec->a_ptr = NULL; 
    }

    free(p_vec); 
    p_vec=NULL; 
}

void push_back(struct vector* p_vec, int new_data)
{
    int new_size_in_bytes; 

    new_size_in_bytes = (p_vec->a_length + 1) * sizeof(int); 
    p_vec->a_ptr = (int*)realloc(p_vec->a_ptr, new_size_in_bytes); 
    if(p_vec->a_ptr == NULL)
    {
        puts("error");
        exit(-1); 
    }
    p_vec->a_length = p_vec->a_length + 1; 
    p_vec->a_ptr[p_vec->a_length - 1] = new_data; 
}

int search_vector(struct vector* p_vec, int search_data)
{
    int i; 

    if(p_vec->a_ptr != NULL)
    {
        i = 0; 
        while(i <= (p_vec->a_length - 1))
        {
            if(p_vec->a_ptr[i] == search_data)
                return (TRUE); 
            i = i + 1; 
        }
    }

    return (FALSE); 
}

void show_vector(struct vector* p_vec, char* msg)
{
    int i; 

    puts(msg); 
    puts("[START]"); 
    if(p_vec->a_ptr != NULL)
    {
        i = 0; 
        while(i <= (p_vec->a_length -1))
        {
            printf("p_vec->a_ptr[%d]:%d\n", i, p_vec->a_ptr[i]); 
            i = i + 1; 
        }
    }
    puts("[END]"); 
    puts("---------------------------------"); 
}
