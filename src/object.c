#include "../HCC/HCC_container.h"
#include "../HCC/HCC_config.h"

/* =================================================== Static Variable and Function Declaration =================================================== */

static int _HCC_object_count = 1;

static void __initialize(HCC_object* o);

/* =================================================== Function Definition =================================================== */

// Create object on the stack. Return the object with initialized value
HCC_object HCC_object_create(){
    HCC_object o;

    __initialize(&o);

    printf("LOG : Successfully create OBJECT %d.\n", o._id);

    _HCC_object_count++;

    return o;
}

// Create object on the heap and initialize it's value. Return a pointer to the object
HCC_object* HCC_object_create_heap(){ 
    HCC_object* o = malloc(sizeof(HCC_object));

    if (o == NULL){
        printf("LOG : FAILED to create OBJECT %d.\n", _HCC_object_count);

        return NULL;
    }

    __initialize(o);

    printf("LOG : Successfully create OBJECT %d.\n", o->_id);

    _HCC_object_count++;

    return o;
}

// Unloads object from memory and set it's pointer to NULL
void HCC_object_free_heap(HCC_object* o){
    int temp = o->_id;

    free(o);

    o = NULL;

    printf("LOG : Successfully unload OBJECT %d from memory.\n", temp);
}

// Set object state
void HCC_object_set_state(HCC_object* o, int state){
    if (_is_object_exist(o)) return;

    o->_state = state;
}

// Set object type
void HCC_object_set_type(HCC_object* o, int type){
    if (_is_object_exist(o)) return;

    o->_type = type;
}

// Get object's unique ID
const unsigned int HCC_object_get_id(HCC_object* o){
    return o->_id;
}

/* =================================================== Static Function Definition =================================================== */

static void __initialize(HCC_object* o){
    o->_id = _HCC_object_count;
    o->_a = 0;
    o->_b = 0;
    o->_format = 0;
    o->_g = 0;
    o->_h = 0;
    o->_gl_id = 0;
    o->_state = 0;
    o->_mipmaps = 0;
    o->_r = 0;
    o->_w = 0;
    o->_x = 0;
    o->_y = 0;
    o->_z = 0;
}