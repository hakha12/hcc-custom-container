#include "../HCC/HCC_container.h"
#include "../HCC/HCC_config.h"

/* =================================================== Static Variable and Function Declaration =================================================== */

static void __initialize_list(HCC_list* l);
static _HCC_node* __create_node(HCC_object* o);
static _HCC_node* __get_node_at(HCC_list* l, size_t index);

/* =================================================== Function Definition =================================================== */

// Create list on the stack. Return an empty list
HCC_list HCC_list_create(){
    HCC_list l;

    __initialize_list(&l);

    return l;
}

// Create list on the heap. Return a pointer to empty list
HCC_list* HCC_list_create_heap(){
    HCC_list* l = malloc(sizeof(HCC_list));

    if (l == NULL){
        printf("LOG : Failed to create list\n");

        return NULL;
    }

    __initialize_list(l);

    return l;
}

// Unloads list from memory and set it's pointer to NULL
void HCC_list_free_heap(HCC_list* l){
    free(l);

    l = NULL;
}

// Return a pointer to object at the specified index inside a list
HCC_object* HCC_list_at(HCC_list* l, size_t index){
    if (!_index_inside_bound(l->_size, index)) return NULL;

    _HCC_node* temp = __get_node_at(l, index);

    return &(temp->_data);
}

// Check if a list has no object
int HCC_list_is_empty(HCC_list* l){
    if (l->_size == 0) return 1;
    
    return 0;
}

// Return the size of the list
size_t HCC_list_size(HCC_list* l){
    return l->_size;
}

// Remove all object from the list
void HCC_list_clear(HCC_list* l){
    _HCC_node* temp = l->_head;

    while (temp != NULL){
        _HCC_node* next = temp->_next;
        free(temp);
        temp = next;
    }

    __initialize_list(l);
}

// Add object at the specified index in the list 
void HCC_list_insert_at(HCC_list* l, HCC_object* o, size_t index){
    if (!_index_inside_bound(l->_size, index)) return;

    if (index == 0){
        HCC_list_push_front(l, o);

        return;
    }

    if (index == l->_size){
        HCC_list_push_back(l, o);

        return;
    }

    _HCC_node* n = __create_node(o);
    _HCC_node* temp = __get_node_at(l, index);
    _HCC_node* temp_prev = temp->_prev;

    n->_next = temp;
    n->_prev = temp_prev;

    temp->_prev = n;
    temp_prev->_next = n;

    l->_size++;
}

// Remove object at the specified index in the list
void HCC_list_erase_at(HCC_list* l, size_t index){
    if (!_index_inside_bound(l->_size, index)) return;

    if (index == 0){
        HCC_list_pop_front(l);

        return;
    }

    if (index == l->_size - 1){
        HCC_list_pop_back(l);

        return;
    }
    
    _HCC_node* temp = __get_node_at(l, index);

    temp->_prev->_next = temp->_next;
    temp->_next->_prev = temp->_prev;

    free(temp);

    l->_size--;
}

// Add object at the end of list
void HCC_list_push_back(HCC_list* l, HCC_object* o){
    _HCC_node* n = __create_node(o);

    if (l->_tail == NULL){
        l->_head = l->_tail = n;
    } else {
        l->_tail->_next = n;
        n->_prev = l->_tail;
        l->_tail = n;
    }

    l->_size++;
}

// Add object at the beginning of list
void HCC_list_push_front(HCC_list* l, HCC_object* o){
    _HCC_node* n = __create_node(o);

    if (l->_head == NULL){
        l->_head = l->_tail = n;
    } else {
        n->_next = l->_head;
        l->_head->_prev = n->_next;
        l->_head = n;
    }

    l->_size++;
}

// Remove object at the end of list
void HCC_list_pop_back(HCC_list* l){
    if (l->_tail == NULL) return;

    _HCC_node* temp = l->_tail;

    l->_tail = l->_tail->_prev;

    if (l->_tail != NULL){
        l->_tail->_next = NULL;
    } else {
        l->_head = NULL;
    }

    free(temp);

    l->_size--;
}

// Remove object at the beginning of list
void HCC_list_pop_front(HCC_list* l){
    if (l->_head == NULL) return;

    _HCC_node* temp = l->_head;

    l->_head = l->_head->_next;

    if (l->_head != NULL){
        l->_head->_prev = NULL;
    } else {
        l->_tail = NULL;
    }

    free(temp);

    l->_size--;
}


/* =================================================== Static Function Definition =================================================== */

static void __initialize_list(HCC_list* l){
    l->_head = NULL;
    l->_tail = NULL;
    l->_size = 0;
}

static _HCC_node* __create_node(HCC_object* o){
    _HCC_node* n = malloc(sizeof(_HCC_node));

    if (n == NULL){
        printf("LOG : FAILED to create node.\n");

        return NULL;
    }

    n->_data = *o;
    n->_prev = NULL;
    n->_next = NULL;

    return n;
}

static _HCC_node* __get_node_at(HCC_list* l, size_t index){
    _HCC_node* temp;

    if (index < l->_size/2){
        temp = l->_head;
        for (int i = 0; i < index; i++){
            temp = temp->_next;
        }
    } else {
        temp = l->_tail;
        for (int i = l->_size - 1; i > index; i--){
            temp = temp->_prev;
        }
    }

    return temp;
}