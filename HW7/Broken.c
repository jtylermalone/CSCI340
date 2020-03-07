
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct __node_t {
    
    int               value;
    struct __node_t * next;
    
} node_t;

typedef struct {
    
    node_t *        head;
    node_t *        tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;

} queue_t;

void Queue_Init(queue_t *q) {
    
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
    
}

void Queue_Enqueue(queue_t * q,
                   int       value) {
    
	// one issue is where this tail node is
	// being locked. there's no need to
	// lock the tail this early. Generally
	// we want to have as few commands as 
	// possible between lock and unlock. we can
	// create the new node and assign
	// its value before we set it as the
	// tail node. the queue_dequeue method
	// below does this correctly

    // pthread_mutex_lock(&q->tail_lock);		  /* moving this line down */

    node_t *tmp = malloc(sizeof(node_t));         /* Get a new node */
    if (tmp == NULL) {                            /* Did the allocation fail? */
        perror("malloc");
        return -1;
    }

    assert(tmp != NULL);
    tmp->value = value;                           /* Set the node's contents */
    tmp->next  = NULL;                            /* Show it's the tail */
	pthread_mutex_lock(&q->tail_lock);			  /* lock moved here */
    q->tail->next = tmp;                          /* Point old tail to new tail */
    q->tail = tmp;                                /* Point tail to new node */
    
    pthread_mutex_unlock(&q->tail_lock);
    
}

int Queue_Dequeue(queue_t * q,
                  int *     value) {

    // Failure is always an option
    int rc = -1;
    
    
    if (q_head->next != NULL) {
        *value = q_head->next->value;             /* Return the value */
        pthread_mutex_lock(&q->head_lock);        /* Lock the list */
        node_t *tmp = q->head;                    /* Save the old head node pointer */
        q->head = q_head->next;                   /* Reset the head */
        pthread_mutex_unlock(&q->head_lock);      /* Unlock the list */
        free(tmp);                                /* Free the old head node */
        rc = 0;
    }
    
    
    return rc;
    
}
