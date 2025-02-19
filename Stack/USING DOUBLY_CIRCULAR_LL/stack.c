#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define SUCCESS     1 
#define TRUE        1 
#define FALSE       0 

#define LIST_INVALID_DATA   2 
#define LIST_EMPTY          3 
#define STACK_EMPTY         LIST_EMPTY 

struct node
{
    int data; 
    struct node* prev; 
    struct node* next; 
}; 

/* Stack - Interface functions */
struct node* create_stack(void); 
int push(struct node* p_stack, int new_data); 
int top(struct node* p_stack, int* p_top_data); 
int pop(struct node* p_stack, int* p_poped_data); 
int is_stack_empty(struct node* p_stack); 
int destroy_stack(struct node** pp_stack); 

/* List - Interface functions */

struct node* create_list(void); 

int insert_start(struct node* p_list, int new_data); 
int insert_end(struct node* p_list, int new_data); 
int insert_after(struct node* p_list, int e_data, int new_data); 
int insert_before(struct node* p_list, int e_data, int new_data); 

int get_start(struct node* p_list, int* p_start_data); 
int get_end(struct node* p_list, int* p_end_data); 

int pop_start(struct node* p_list, int* p_start_data); 
int pop_end(struct node* p_list, int* p_end_data); 

int remove_start(struct node* p_list);  
int remove_end(struct node* p_list); 
int remove_data(struct node* p_list, int r_data); 

int find_data(struct node* p_list, int f_data); 
int is_list_empty(struct node* p_list); 
int get_length(struct node* p_list); 
void show_list(struct node* p_list, char* msg); 

int destroy_list(struct node** pp_list); 

/* List - Helper functions */

struct node* search_node(struct node* p_list, int search_data); 
void generic_insert(struct node* p_beg, struct node* p_mid, struct node* p_end); 
void generic_delete(struct node* p_delete_node); 
struct node* get_node(int new_data); 

void* xmalloc(size_t number_of_bytes); 

int main(void)
{
    struct node* p_stack = NULL; 
    int data; 
    int status; 

    p_stack = create_stack();

    status = is_stack_empty(p_stack); 
    if(status == TRUE)
        puts("The stack is empty at the start"); 

    status = top(p_stack, &data); 
    if(status == STACK_EMPTY)
        puts("Cannot top from empty stack"); 

    status = pop(p_stack, &data); 
    if(status == STACK_EMPTY)
        puts("Cannot pop from empty stack"); 


    for(data = 1; data <= 50; ++data)
    {
        status = push(p_stack, data); 
        assert(status == SUCCESS); 
    }

    status = top(p_stack, &data); 
    printf("TOP OF STACK = %d\n", data); 

    while(is_stack_empty(p_stack) == FALSE)
    {
        status = pop(p_stack, &data); 
        assert(status == SUCCESS); 
        printf("POPED DATA = %d\n", data); 
    }

    status = destroy_stack(&p_stack); 
    assert(status == SUCCESS && p_stack == NULL); 

    return (EXIT_SUCCESS); 
}

struct node* create_stack(void)
{
    return create_list(); 
}

int push(struct node* p_stack, int new_data)
{
    return insert_end(p_stack, new_data); 
}

int top(struct node* p_stack, int* p_top_data)
{
    return get_end(p_stack, p_top_data); 
}

int pop(struct node* p_stack, int* p_poped_data)
{
    return pop_end(p_stack, p_poped_data); 
}

int is_stack_empty(struct node* p_stack)
{
    return is_list_empty(p_stack); 
}

int destroy_stack(struct node** pp_stack)
{
    return destroy_list(pp_stack); 
}

struct node* create_list(void)
{
    struct node* p_list = NULL; 

    p_list = get_node(0); 
    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (p_list); 
}

int insert_start(struct node* p_list, int new_data)
{
    generic_insert(p_list, get_node(new_data), p_list->next); 
    return (SUCCESS); 
}

int insert_end(struct node* p_list, int new_data)
{
    generic_insert(p_list->prev, get_node(new_data), p_list); 
    return (SUCCESS); 
} 

int insert_after(struct node* p_list, int e_data, int new_data)
{   
    struct node* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, e_data); 
    if(p_existing_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(p_existing_node, get_node(new_data), p_existing_node->next); 
    
    return (SUCCESS); 
}

int insert_before(struct node* p_list, int e_data, int new_data)
{
    struct node* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, e_data); 
    if(p_existing_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(p_existing_node->prev, get_node(new_data), p_existing_node); 
    
    return (SUCCESS); 
}

int get_start(struct node* p_list, int* p_start_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

int get_end(struct node* p_list, int* p_end_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_end_data = p_list->prev->data; 
    return (SUCCESS); 
}

int pop_start(struct node* p_list, int* p_start_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

int pop_end(struct node* p_list, int* p_end_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 
    
    *p_end_data = p_list->prev->data; 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

int remove_start(struct node* p_list)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    generic_delete(p_list->next); 
    return (SUCCESS);
}
int remove_end(struct node* p_list)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

int remove_data(struct node* p_list, int r_data)
{
    struct node* p_remove_node = NULL; 

    p_remove_node = search_node(p_list, r_data); 
    if(p_remove_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_delete(p_remove_node); 

    return (SUCCESS); 
}

int find_data(struct node* p_list, int f_data)
{
    struct node* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, f_data); 

    return (p_existing_node != NULL); 
}

int is_list_empty(struct node* p_list)
{
    return (p_list->prev == p_list && p_list->next == p_list); 
}

int get_length(struct node* p_list)
{
    int N = 0; 
    struct node* p_run = NULL; 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        ++N; 

    return (N); 
}

void show_list(struct node* p_list, char* msg) 
{
    struct node* p_run = NULL; 

    if(msg != NULL)
        puts(msg); 

    printf("[START]<->"); 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        printf("[%d]<->", p_run->data); 

    puts("[END]"); 
}

int destroy_list(struct node** pp_list)
{
    struct node* p_list = NULL; 
    struct node* p_run = NULL; 
    struct node* p_run_next = NULL; 

    p_list = *pp_list;

    for(p_run = p_list->next; p_run != p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next; 
        free(p_run); 
    }

    free(p_list); 
    p_list = NULL; 

    *pp_list = NULL; 

    return (SUCCESS); 
}

/* List - Helper functions */

struct node* search_node(struct node* p_list, int search_data)
{
    struct node* p_run = NULL; 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        if(p_run->data == search_data)
            return (p_run); 

    return (NULL); 
}

void generic_insert(struct node* p_beg, struct node* p_mid, struct node* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void generic_delete(struct node* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node); 
}


struct node* get_node(int new_data)
{
    struct node* p_new_node = NULL; 

    p_new_node = (struct node*)xmalloc(sizeof(struct node)); 
    p_new_node->data = new_data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 

    return (p_new_node); 
}

void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL; 

    ptr = malloc(number_of_bytes); 
    if(ptr == NULL)
    {
        puts("AllocationError: Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}
