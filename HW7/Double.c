// CSCI-340 - Homework #7

// Starter file for the double linked list


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


// basic node structure

typedef struct __node_t {
    
    int key;
    struct __node_t *next;
    struct __node_t *prev;

} node_t;

// basic list structure (one used per list)

typedef struct {
    
    node_t *head;
    node_t *tail;

	pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;
    
} list_t;

// Initialize the list

void List_Init(list_t *L) {

	L->head = NULL;
	L->tail = NULL;
    
	pthread_mutex_init(&L->head_lock, NULL);
    pthread_mutex_init(&L->tail_lock, NULL);
}

// Insert into the list (At the front)

void List_Insert(list_t *L,
                 int key) {

    // Add code here to safely insert a new node at the beginning of the list

	node_t *tmp = malloc(sizeof(node_t));
	tmp->key = key;
	tmp->prev = NULL;
	pthread_mutex_lock(&L->head_lock);	
	tmp->next = L->head;
	if (L->head == NULL) {
		tmp->next = NULL;
		L->head = tmp;
		L->tail = tmp;
		return;
	}
	L->head->prev = tmp;
	L->head = tmp;
	pthread_mutex_unlock(&L->head_lock);

}

// Insert into the list (At the end)

void List_Append(list_t *L,
                 int key) {

    node_t *tmp = malloc(sizeof(node_t));
	tmp->key = key;
	tmp->next = NULL;
	pthread_mutex_lock(&L->head_lock);

	// if list is empty
	if (L->head == NULL) {
		tmp->prev = NULL;
		L->head = tmp;
		L->tail = tmp;
	}
	pthread_mutex_unlock(&L->head_lock);
	
	pthread_mutex_lock(&L->tail_lock);
	tmp->prev = L->tail;

	// if there's already something in the list
	if (L->tail != NULL)
		L->tail->next = tmp;
	L->tail = tmp;
	pthread_mutex_unlock(&L->tail_lock);
    
}

int List_Lookup(list_t *L,
                int key) {

    // Add code here to lookup an item in the list
    
}

int main()
{

    list_t *test_list = malloc(sizeof(list_t));
	List_Init(test_list);
	List_Insert(test_list, 2);
	List_Append(test_list, 3);
	List_Insert(test_list, 1);
	List_Append(test_list, 4);
	List_Insert(test_list, 0);
	List_Append(test_list, 5);
	List_Insert(test_list, -1);
	List_Append(test_list, 6);
	List_Insert(test_list, -2);
	node_t *current_node = test_list->head;
	printf("\nThese keys were not added to the linked list in order but they should display in order:\n\n");
	while (current_node != NULL) {
		printf("current node key: %d\n", current_node->key);
		current_node = current_node->next;
	}
    return 0;
}
