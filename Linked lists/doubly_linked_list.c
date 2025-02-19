#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS             1
#define TRUE                1
#define FALSE               0
#define LIST_INVALID_DATA   2
#define LIST_EMPTY          3

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};

struct node* create_list(void);
void insert_start(struct node*, int);
void insert_end(struct node*, int);
int insert_after(struct node*, int, int);
int insert_before(struct node*, int, int);
int get_start(struct node*, int*);
int get_end(struct node*, int*);
int pop_start(struct node*, int*);
int pop_end(struct node*, int*);
int remove_start(struct node*);
int remove_end(struct node*);
int remove_data(struct node*, int);
int is_list_empty(struct node*);
int get_length(struct node*);
void show_list(struct node*, char*);
void destroy_list(struct node*);

struct node* get_node(int);
void* xmalloc(size_t);
struct node* search_node(struct node*, int);

int main(void)
{
    struct node* p_list = NULL;
    int data;
    int status;
    int length;

    p_list = create_list();
    assert(p_list != NULL); 

    assert(get_start(p_list, &data) == LIST_EMPTY); 
    assert(pop_start(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_start(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(get_length(p_list) == 0); 
    assert(is_list_empty(p_list) == TRUE); 
    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on empty list...OK"); 
    puts("testing, get_length() on empty list ... ok ");
    puts("testing, is_list_empty() on empty list ... ok"); 
    show_list(p_list, "testing, empty list"); 

    for(data = 0; data <= 40; data = data + 10)
        insert_start(p_list, data); 

    show_list(p_list, "testing, insert_start()"); 

    for(data = 50; data <= 100; data = data + 10)
        insert_end(p_list, data); 

    show_list(p_list, "testing, insert_end()"); 

    puts("testing, insert_after() for false case"); 
    status = insert_after(p_list, -300, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_after() false case... ok"); 

    puts("testing insert_before() for false case"); 
    status = insert_before(p_list, 8976, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_before() false case ... ok"); 

    puts("testing insert_after() and insert_before() for valid data"); 
    status = insert_after(p_list, 0, 1000); 
    assert(status == SUCCESS); 
    status = insert_before(p_list, 0, 2000); 
    assert(status == SUCCESS); 

    show_list(p_list, "test, insert_after(), insert_before()... ok"); 

    status = get_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_start()"); 

    status = get_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_end()"); 

    status = pop_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_start()"); 

    status = pop_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_end()"); 

    status = remove_start(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_start()"); 

    status = remove_end(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_end()"); 

    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on non-empty list...OK"); 

    length = get_length(p_list); 
    printf("length = %d\n", length); 

    puts("testing remove_data() for false case"); 
    status = remove_data(p_list, 1234); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing remove data for false case ... ok"); 

    puts("testing remove_data() for success case"); 
    status = remove_data(p_list, 0); 
    assert(status == SUCCESS); 
    puts("testing remove data for success case ... ok"); 
    show_list(p_list, "showing list after removing 0"); 

    assert(is_list_empty(p_list) == FALSE); 
    puts("testing, is_list_empty() for non-empty list...ok"); 

    destroy_list(p_list); 
    p_list = NULL;

    puts("exiting from application:SUCCESS"); 
    return (EXIT_SUCCESS); 
}

struct node* create_list(void)
{
    struct node* p_head_node = NULL;
    p_head_node = get_node(0);
    return (p_head_node);
}

struct node* get_node(int new_data)
{
    struct node* p_new_node = NULL;
    p_new_node = (struct node*)malloc(sizeof(struct node));
    p_new_node->data = new_data;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;
    
    return (p_new_node);
}

void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL;
    ptr = malloc(number_of_bytes);
    if(ptr == NULL)
    {
        puts("Error in allocating memory");
        exit(-1);
    }
    return (ptr);
}

void insert_start(struct node* p_head_node, int new_data)
{
    struct node* p_node = NULL;
    p_node = get_node(new_data);

    p_node->prev = p_head_node;
    p_node->next = p_head_node->next;
    
    if(p_head_node->next != NULL)
        p_head_node->next->prev = p_node;
    p_head_node->next = p_node;
}

void insert_end(struct node* p_head_node, int new_data)
{
    struct node* p_node = NULL;
    p_node = get_node(new_data);

    struct node* run = NULL;
    run = p_head_node;
    while(run->next != NULL)
    {
        run = run->next;
    }
    p_node->prev = run;
    run->next = p_node;
}

int insert_after(struct node* p_head_node, int e_data, int new_data)
{
    struct node* p_node = NULL;
    struct node* search = NULL;

    search = search_node(p_head_node, e_data);
    if(search == NULL)
        return (LIST_INVALID_DATA);
    p_node = get_node(new_data);
    p_node->next = search->next;
    p_node->prev = search;

    if(search->next != NULL)
        search->next->prev = p_node;
    search->next = p_node;

    return (SUCCESS);
}

struct node* search_node(struct node* p_head_node, int search_data)
{
    struct node* run = NULL;
    run = p_head_node->next;

    while(run != NULL)
    {
        if(run->data == search_data)
            break;
        run = run->next;
    }
    return (run);
}

int insert_before(struct node* p_head_node, int e_data, int new_data)
{
    struct node* p_node = NULL;
    struct node* search = NULL;

    search = search_node(p_head_node, e_data);
    if(search == NULL)
        return (LIST_INVALID_DATA);
    p_node = get_node(new_data);
    p_node->next = search;
    p_node->prev = search->prev;

    search->prev->next = p_node;
    search->prev = p_node;
    return (SUCCESS);
}

int get_start(struct node* p_head_node, int* p_start_data)
{
    if(p_head_node->next == NULL && p_head_node->prev == NULL)
        return (LIST_EMPTY);
    *p_start_data = p_head_node->next->data;
    return (SUCCESS);
}

int get_end(struct node* p_head_node, int* p_end_data)
{
    
    struct node* run = NULL;
    run = p_head_node;

    while(run->next != NULL)
        run = run->next;
    if(run == p_head_node)
        return (LIST_EMPTY);

    *p_end_data = run->data;
    return (SUCCESS);
}

int pop_start(struct node* p_head_node, int* p_start_data)
{
    if(p_head_node->next == NULL && p_head_node->prev == NULL)
        return (LIST_EMPTY);
    
    struct node* first_node = NULL;
    first_node = p_head_node->next;
    *p_start_data = first_node->data;

    if(first_node->next != NULL)
        first_node->next->prev = p_head_node;
    p_head_node->next = first_node->next;
    
    free(first_node);
    first_node = NULL;
    return (SUCCESS);
}

int pop_end(struct node* p_head_node, int* p_end_data)
{
    struct node* run = NULL;
    run = p_head_node;

    while(run->next != NULL)
        run = run->next;
    if(run == p_head_node)
        return (LIST_EMPTY);

    *p_end_data = run->data;
    run->prev->next = NULL;
    free(run);
    run = NULL;
    return (SUCCESS);
}

int remove_start(struct node* p_head_node)
{
    if(p_head_node->next == NULL && p_head_node->prev == NULL)
        return (LIST_EMPTY);
    
    struct node* first_node = NULL;
    first_node = p_head_node->next;

    if(first_node->next != NULL)
        first_node->next->prev = p_head_node;
    p_head_node->next = first_node->next;

    free(first_node);
    first_node = NULL;
    return (SUCCESS);
}

int remove_end(struct node* p_head_node)
{
    struct node* run = NULL;
    run = p_head_node;
    while(run->next != NULL)
        run = run->next;
    if(run == p_head_node)
        return (LIST_EMPTY);

    run->prev->next = NULL;
    free(run);
    run = NULL;
    return (SUCCESS);
}

int remove_data(struct node* p_head_node, int r_data)
{
    struct node* search = NULL;

    search = search_node(p_head_node, r_data);
    if(search == NULL)
        return (LIST_INVALID_DATA);

    search->prev->next = search->next;
    if(search->next != NULL)
        search->next->prev = search->prev;
    free(search);
    search = NULL;
    return (SUCCESS);
}

int get_length(struct node* p_head_node)
{
    struct node* run = NULL;
    int length = 0;

    run = p_head_node->next;
    while(run != NULL)
    {
        length = length + 1;
        run = run->next;
    }

    return (length);
}

int is_list_empty(struct node* p_head_node)
{
    return (p_head_node->next == NULL && p_head_node->prev == NULL);
}

void show_list(struct node* p_head_node, char* msg)
{
    if(msg != NULL)
        puts(msg);
    
    struct node* run = NULL;
    run = p_head_node->next;

    printf("[START]<->");
    while(run != NULL)
    {
        printf("[%d]<->", run->data);
        run = run->next;
    }
    printf("[END]");
}

void destroy_list(struct node* p_head_node)
{
    struct node* run = NULL;
    struct node* run_next = NULL;

    run = p_head_node;
    while(run != NULL)
    {
        run_next = run->next;
        free(run);
        run = run_next;
    }
}
