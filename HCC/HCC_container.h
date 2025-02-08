#ifndef HCC_container_h
#define HCC_container_h

#include <stdio.h>
#include <stdlib.h>

/* =================================================== Struct Declaration =================================================== */
                        
typedef struct HCC_object {                                                                             //  - Base object structure 
    unsigned int        _id;                                                                            // Object's unique ID
    int                 _state;                                                                         // The state of the object
    int                 _type;                                                                          // Object's type (Could be anything)
    unsigned int        _gl_id;                                                                         // Object's Texture ID for OpenGL
    float               _x;                                                                             // Object's X coordinate
    float               _y;                                                                             // Object's Y coordinate
    float               _z;                                                                             // Object's Z coordinate (Used for zoom)
    float               _w;                                                                             // Object's width
    float               _h;                                                                             // Object's height
    int                 _mipmaps;                                                                       // Object's texture mipmaps level
    int                 _format;                                                                        // Object's texture data format
    unsigned char       _r;                                                                             // Object's color red value
    unsigned char       _g;                                                                             // Object's color green value
    unsigned char       _b;                                                                             // Object's color blue value
    unsigned char       _a;                                                                             // Object's color alpha value
} HCC_object;

typedef struct _HCC_node {                                                                              //  - Base node for creating a list. NOT recommended to be used on it's own
    HCC_object          _data;                                                                          // List data
    struct _HCC_node*   _prev;                                                                          // Pointer to the previous node
    struct _HCC_node*   _next;                                                                          // Pointer to the next node
} _HCC_node;

typedef struct HCC_array {                                                                              //  - Dynamic array of HCC_object with bound checking 
    HCC_object*         _data;                                                                          // Array's data
    size_t              _size;                                                                          // Array's current size
    size_t              _capacity;                                                                      // Array's maximum capacity before resizing
} HCC_array;

typedef struct HCC_list {                                                                               //  - Doubly linked list of HCC_object
    _HCC_node*          _head;                                                                          // Pointer to the beginning node of the list
    _HCC_node*          _tail;                                                                          // Pointer to the end node of the list
    size_t              _size;                                                                          // List's current size
} HCC_list;


/* =================================================== Function Declaration =================================================== */

/* Object Function */

HCC_object              HCC_object_create();                                                            // Create object on the stack. Return the object with initialized value
HCC_object*             HCC_object_create_heap();                                                       // Create object on the heap and initialize it's value. Return a pointer to the HCC_object
void                    HCC_object_free_heap(HCC_object* o);                                            // Unloads object from memory and set it's pointer to NULL

void                    HCC_object_set_state(HCC_object* o, int state);                                 // Set object state
void                    HCC_object_set_type(HCC_object* o, int type);                                   // Set object type

const unsigned int      HCC_object_get_id(HCC_object* o);                                               // Return object's unique ID

int                     _is_object_exist(HCC_object* o);                                                // Check if an object pointer exist

/* Array Function */

HCC_array               HCC_array_create(size_t capacity);                                              // Create array on the stack and set it's capacity. Return an empty array
HCC_array*              HCC_array_create_heap(size_t capacity);                                         // Create array on the heap and set it's capacity. Return a pointer to empty array
void                    HCC_array_free_heap(HCC_array* a);                                              // Unloads array from memory and set it's pointer to NULL

HCC_object*             HCC_array_at(HCC_array* a, size_t index);                                       // Return a pointer to object at the specified index inside an array

int                     HCC_array_is_empty(HCC_array* a);                                               // Check if an array has no object
size_t                  HCC_array_size(HCC_array* a);                                                   // Return the size of the array
size_t                  HCC_array_capacity(HCC_array* a);                                               // Return the current maximum capacity of the array

void                    HCC_array_clear(HCC_array* a);                                                  // Remove every object from the array
void                    HCC_array_insert_at(HCC_array* a, HCC_object* o, size_t index);                 // Add object at the specified index in the array
void                    HCC_array_erase_at(HCC_array* a, size_t index);                                 // Remove object at the specified index in the array
void                    HCC_array_push_back(HCC_array* a, HCC_object* HCC_object);                      // Add object at the end of array
void                    HCC_array_pop_back(HCC_array* a);                                               // Remove object at the end of array. Array need at least 2 object
                                                                                                        
/* List Function */

HCC_list                HCC_list_create();                                                              // Create list on the stack. Return an empty list
HCC_list*               HCC_list_create_heap();                                                         // Create list on the stack. Return a pointer to empty list
void                    HCC_list_free_heap(HCC_list* l);                                                // Unloads list from memory and set it's pointer to NULL

HCC_object*             HCC_list_at(HCC_list* l, size_t index);                                         // Return a pointer to object at the specified index inside a list

int                     HCC_list_is_empty(HCC_list* l);                                                 // Check if a list has no object
size_t                  HCC_list_size(HCC_list* l);                                                     // Return the size of the list

void                    HCC_list_clear(HCC_list* l);                                                    // Remove all object from the list
void                    HCC_list_insert_at(HCC_list* l, HCC_object* o, size_t index);                   // Add object at the specified index in the list
void                    HCC_list_erase_at(HCC_list* l, size_t index);                                   // Remove object at the specified index in the list
void                    HCC_list_push_back(HCC_list* l, HCC_object* o);                                 // Add object at the end of list
void                    HCC_list_push_front(HCC_list* l, HCC_object* o);                                // Add object at the beginning of list
void                    HCC_list_pop_back(HCC_list* l);                                                 // Remove object at the end of list
void                    HCC_list_pop_front(HCC_list* l);                                                // Remove object at the beginning of list

#endif