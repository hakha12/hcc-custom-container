#include "../HCC/HCC_container.h"
#include "../HCC/HCC_config.h"

/* =================================================== Static Variable and Function Declaration =================================================== */

static int __initialize_array(HCC_array* a, size_t capacity);
static void __resize_array(HCC_array* a);

/* =================================================== Function Definition =================================================== */

// Create array on the stack and set it's capacity. Return an empty array
HCC_array HCC_array_create(size_t capacity){
    HCC_array a;

    if (!__initialize_array(&a, capacity)) return (HCC_array){0};

    return a;
}

// Create array on the heap and set it's capacity. Return a pointer to empty array
HCC_array* HCC_array_create_heap(size_t capacity){
    HCC_array* a = malloc(sizeof(HCC_array));

    if (a == NULL){
        printf("LOG : FAILED to create array.\n");
        return NULL;
    }

    if (!__initialize_array(a, capacity)) return NULL;

    return a;
}

// Unloads array from memory and set it's pointer to NULL
void HCC_array_free_heap(HCC_array* a){
    free(a->_data);

    free(a);

    a = NULL;
}

// Return a pointer to object at the specified index inside an array
HCC_object* HCC_array_at(HCC_array* a, size_t index){
    if (!_index_inside_bound(a->_size, index)) return NULL;

    return &(a->_data[index]);
}

// Check if an array has no object
int HCC_array_is_empty(HCC_array* a){
    if (a->_size == 0) return 1;
    
    return 0;
}

// Return the size of the array
size_t HCC_array_size(HCC_array* a){
    return a->_size;
}

// Return the current maximum capacity of the array
size_t HCC_array_capacity(HCC_array* a){
    return a->_capacity;
}

// Remove every object from the array
void HCC_array_clear(HCC_array* a){
    for (size_t i = 0; i < a->_size; i++){
        a->_data[i] = (HCC_object){0};
    }

    a->_size = 0;
}

// Add object at the specified index in the array
void HCC_array_insert_at(HCC_array* a, HCC_object* o, size_t index){
    if (!_index_inside_bound(a->_size + 1, index)) return;

    if (a->_size == a->_capacity){
        __resize_array(a);
    }

    for (size_t i = index; i < a->_size; i++){
        a->_data[i + 1] = a->_data[i];
    }

    a->_data[index] = *o;

    a->_size++;
}

// Remove object at the specified index in the array
void HCC_array_erase_at(HCC_array* a, size_t index){
    if (!_index_inside_bound(a->_size, index)) return;

    for (size_t i = index; i < a->_size; i++){
        a->_data[i] = a->_data[i + 1];
    }

    a->_size--;
}

// Add object at the end of array
void HCC_array_push_back(HCC_array* a, HCC_object* o){
    if (a->_size == a->_capacity){
        __resize_array(a);
    }

    a->_data[a->_size] = *o;

    a->_size++;
}

// Remove object at the end of array
void HCC_array_pop_back(HCC_array* a){
    if (a->_size == 0) return;

    a->_data[a->_size - 1] = (HCC_object){0};

    a->_size--;
}

/* =================================================== Static Function Definition =================================================== */

static int __initialize_array(HCC_array* a, size_t capacity){
    a->_data = malloc(sizeof(HCC_object) * capacity);

    if (a->_data == NULL){
        printf("LOG : FAILED to initialize array.\n");
        return 0;
    }

    a->_size = 0;
    a->_capacity = capacity;

    return 1;
}

static void __resize_array(HCC_array* a){
    a->_capacity *= 2;
    a->_data = realloc(a->_data, sizeof(HCC_object*) * a->_capacity);
}
