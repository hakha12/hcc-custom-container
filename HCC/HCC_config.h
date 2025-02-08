#ifndef HCC_config_h
#define HCC_config_h

#include "HCC_container.h"

int                     _is_object_exist(HCC_object* o);                                                // Check if an object pointer exist
int                     _index_inside_bound(size_t size, size_t index);                                 // Check if an index is inside a container

#endif