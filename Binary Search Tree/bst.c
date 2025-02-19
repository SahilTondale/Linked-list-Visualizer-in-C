#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define BST_EMPTY 2
#define BST_INVALID_DATA 3
#define BST_NO_SUCCCESSOR 4
#define BST_NO_PREDECESSOR 5

typedef int data_t;
typedef int status_t;

typedef struct bst_node bst_node_t;
typedef struct bst bst_t;

struct bst_node
{
    data_t data;
    bst_node_t* left;
    bst_node_t* right;
    bst_node_t* parent;
};

struct bst
{
    bst_node_t* root_node;
    size_t number_of_elements;
};

bst_t* create_bst(void)
{
    bst_t* p_bst = NULL;
    p_bst = (bst_t*)xmalloc(sizeof(bst_t));
    p_bst->root_node = NULL;
    p_bst->number_of_elements = 0;

    return (p_bst);
}

static void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL;
    ptr = malloc(number_of_bytes);
    if(ptr == NULL)
    {
        puts("Error in allocating Memory");
        exit(EXIT_FAILURE);
    }

    return (ptr);
}

static bst_node_t* get_node(data_t new_data)
{
    bst_node_t* p_new_node = NULL;
    p_new_node = (bst_node_t*)xmalloc(sizeof(bst_node_t));

    p_new_node->data = new_data;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->parent = NULL;

    return (p_new_node);
}

status_t insert_bst(bst_t* p_bst, data_t new_data)
{
    bst_node_t* p_node = NULL;
    p_node = get_node(new_data);

    if(p_bst->root_node == NULL)
    {
        p_bst->root_node = p_node;
        p_bst->number_of_elements += 1;
        return (SUCCESS);
    }

    bst_node_t* run = NULL;
    run = p_bst->root_node;
    while(TRUE)
    {
        if(new_data <= run->data)
        {
            if(run->left == NULL)
            {
                run->left = p_node;
                run->left->parent = run;
                break;
            }
            else
            {
                run = run->left;
            }
        }
        else
        {
            if(run->right == NULL)
            {
                run->right = p_node;
                run->right->parent = run;
                break;
            }
            else
            {
                run = run->right;
            }
        }
    }

    p_bst->number_of_elements += 1;
    return (SUCCESS);
}

status_t search_bst(bst_t* p_bst, data_t s_data)
{
    bst_node_t* search = NULL;

    search = search_nodelevel(p_bst->root_node, s_data);
    return (search != NULL);
}

static bst_node_t* search_nodelevel(bst_node_t* root_node, data_t s_data)
{
    bst_node_t* run = NULL;
    run = root_node;

    while(run != NULL)
    {
        if(s_data == run->data)
            return (run);
        else if(s_data < run->data)
            run = run->left;
        else
            run = run->right;
    }
    return (NULL)
}

void inorder(bst_t* p_bst)
{
    printf("[START]<->");
    inorder_nodelevel(p_bst->root_node);
    printf("[END]");
}
static void inorder_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        inorder_nodelevel(root_node->left);
        printf("[%d]<->", root_node->data);
        inorder_nodelevel(root_node->right);
    }
}

void preorder(bst_t* p_bst)
{
    printf("[START]<->");
    preorder_nodelevel(p_bst->root_node);
    printf("[END]");
}
static void preorder_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        printf("[%d]<->", root_node->data);
        preorder_nodelevel(root_node->left);
        preorder_nodelevel(root_node->right);
    }
}

void postorder(bst_t* p_bst)
{
    printf("[START]<->");
    postorder_nodelevel(p_bst->root_node);
    printf("[END]");
}
static void postorder_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        postorder_nodelevel(root_node->left);
        postorder_nodelevel(root_node->right);
        printf("[%d]<->", root_node->data);
    }
}

status_t destroy_bst(bst_t** pp_bst)
{
    bst_t* p_bst = *pp_bst;
    destroy_nodelevel(p_bst->root_node);
    free(p_bst);
    *pp_bst = NULL;
}

static void destroy_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        destroy_nodelevel(root_node->left);
        destroy_nodelevel(root_node->right);
        free(root_node);
    }
}

status_t get_max(bst_t* p_bst, data_t* p_max_data)
{
    bst_node_t* run = NULL;

    if(p_bst->root_node == NULL)
        return (BST_EMPTY);
    
    run = p_bst->root_node;
    while(run->right != NULL)
        run = run->right;

    *p_max_data = run->data;
    return (SUCCESS);
}

status_t get_min(bst_t* p_bst)
{
    bst_node_t* run = NULL;
    
    if(p_bst->root_node == NULL)
        return (BST_EMPTY);
    
    run = p_bst->root_node;
    while(run->left != NULL)
        run = run->left;

    *p_min_data = run->data;
    return (SUCCESS);
}

status_t get_inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data)
{
    bst_node_t* e_node = NULL;
    e_node = search_nodelevel(p_bst->root_node, e_data);
    if(e_node == NULL)
        return (BST_INVALID_DATA);
    bst_node_t* p_node = NULL;
    p_node = inorder_successor_nodelevel(e_node);
    if(p_node == NULL)
        return (BST_NO_SUCCCESSOR);
    *p_succ_data = p_node->data;
    return (SUCCESS);
}

static inorder_successor_nodelevel(bst_node_t* e_node)
{
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;

    x = e_node;
    if(x->right != NULL)
    {
        y = x->right;
        while(y->left != NULL)
            y = y->left;
        return (y);
    }
    
    y = x->parent;
    while(y != NULL && y->right)
}

