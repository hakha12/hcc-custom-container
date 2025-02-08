#include "../HCC/HCC_config.h"

// Check if an object pointer exist
int _is_object_exist(HCC_object* o){
    if (o == NULL){
        printf("LOG : FAILED to execute. OBJECT DOES NOT EXIST\n");
        return 1;
    } 
    
    return 0;
}

int _index_inside_bound(size_t size, size_t index){
    if (index >= size){
        printf("LOG : FAILED to retrieve object. Index out of bound\n");
        return 0;
    }

    return 1;
}