#include <stdio.h> 
#include <stdlib.h> 

#define TRUE 1 
#define FALSE 0 

struct vector
{
	int* a_ptr;
	int a_size; 
}; 

struct vector* allocate_vector(void); 
void release_vector(struct vector* p_vec);

void push_back(struct vector* p_vec, int new_data); 
int search_vector(struct vector* p_vec, int search_data); 
void show_vector(struct vector* p_vec, char* msg); 

int main(void)
{
	struct vector* p_vec_1 = NULL; 
	int status; 

	p_vec_1 = allocate_vector(); 
	
	show_vector(p_vec_1, "Vector 1 after creation"); 
	push_back(p_vec_1, 10); 
	push_back(p_vec_1, 20); 
	push_back(p_vec_1, 30); 
	push_back(p_vec_1, 40); 
	show_vector(p_vec_1, "Vector 1 after pushing 4 elements"); 

	status = search_vector(p_vec_1, 30);
	if (status == TRUE)
		puts("30 is present in vector 1"); 

	status = search_vector(p_vec_1, 500); 
	if (status == FALSE)
		puts("500 is not present in vector 1"); 

	release_vector(p_vec_1); 
	p_vec_1 = NULL; 

	return (EXIT_SUCCESS); 
}

struct vector* allocate_vector(void)
{
	struct vector* p_vec = NULL; 

	p_vec = (struct vector*)malloc(sizeof(struct vector)); 
	if (p_vec == NULL)
	{
		puts("Error in allocating memory"); 
		exit(EXIT_FAILURE); 
	}

	p_vec->a_ptr = NULL; 
	p_vec->a_size = 0; 

	return (p_vec); 
}

void release_vector(struct vector* p_vec)
{
	free(p_vec->a_ptr); 
	p_vec->a_ptr = NULL; 

	free(p_vec); 
	p_vec = NULL; 
}

void push_back(struct vector* p_vec, int new_data)
{
	int desired_size_in_bytes; 
	
	desired_size_in_bytes = (p_vec->a_size + 1) * sizeof(int); 
	p_vec->a_ptr = (int*)realloc(p_vec->a_ptr, desired_size_in_bytes); 
	if (p_vec->a_ptr == NULL)
	{
		puts("Error in resizing an array"); 
		exit(EXIT_FAILURE); 
	}

	p_vec->a_size = p_vec->a_size + 1; 
	p_vec->a_ptr[p_vec->a_size - 1] = new_data; 
}

int search_vector(struct vector* p_vec, int search_data)
{
	int i; 

	i = 0; 
	while (i <= (p_vec->a_size - 1))
	{
		if (p_vec->a_ptr[i] == search_data)
			return (TRUE); 
		i = i + 1; 
	}

	return (FALSE); 
}

void show_vector(struct vector* p_vec, char* msg)
{
	int i; 

	puts(msg);
	puts("[START]"); 
	i = 0; 
	while (i <= (p_vec->a_size - 1))
	{
		printf("p_vec->a_ptr[%d]:%d\n", i, p_vec->a_ptr[i]); 
		i = i + 1; 
	}
	puts("[END]");
	puts("-------------------------------------------------"); 
}