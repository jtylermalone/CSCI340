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

	// lock head while we manipulate it
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

	// unlock head
	pthread_mutex_unlock(&L->head_lock);

}

// Insert into the list (At the end)

void List_Append(list_t *L,
                 int key) {

    node_t *tmp = malloc(sizeof(node_t));
	tmp->key = key;
	tmp->next = NULL;

	// lock the head while we read it
	// and/or manipulate it
	pthread_mutex_lock(&L->head_lock);

	// if list is empty
	if (L->head == NULL) {
		tmp->prev = NULL;
		L->head = tmp;
		L->tail = tmp;
	}
	pthread_mutex_unlock(&L->head_lock);
	
	// lock the tail since we're manipulating
	// the tail
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
	int return_key;

	// locking the head and tail here... by locking the head
	// and tail throughout the search, any other threads are
	// prevented from manipulating the list, and we can know
	// that the data we're reading is accurate.
	pthread_mutex_lock(&L->head_lock);
	pthread_mutex_lock(&L->tail_lock);
    node_t *current_node = L->head;
	while (current_node != NULL) {
		if (current_node->key == key) {

			// just looking at the output, this print statement
			// makes very little sense. I really just want to 
			// illustrate here that the lookup succeeded. Though
			// I am printing two different values (key and
			// current_node-> key), the values should be the
			// same within the print statement.
			printf("found %d: %d\n", key, current_node->key);
			return_key = key;
		}
	current_node = current_node->next;
	}

	// unlock after search complete
	pthread_mutex_unlock(&L->head_lock);
	pthread_mutex_unlock(&L->tail_lock);

	// returning sought-after key
	return return_key;
    
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

	// printing out list to make sure append/insert working
	while (current_node != NULL) {
		printf("current node key: %d\n", current_node->key);
		current_node = current_node->next;
	}

	List_Lookup(test_list, 5);
	List_Lookup(test_list, 7);

	free(test_list);
    return 0;
}
