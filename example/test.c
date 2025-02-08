#include "../HCC/HCC_config.h"

typedef enum {
    HAPPY = 1,
    SAD,
    ANGRY,
    SLEEPY
} State;

char* get_state(HCC_object* o){
    switch (o->_state){
        case HAPPY:
            return "HAPPY"; break;
        case SAD:
            return "SAD"; break;
        case ANGRY:
            return "ANGRY"; break;
        case SLEEPY:
            return "SLEEPY"; break;
    }
}

int main(){
    HCC_object o = HCC_object_create();

    HCC_object p = HCC_object_create();

    HCC_object q = HCC_object_create();

    HCC_object r = HCC_object_create();



    HCC_object_set_state(&o, HAPPY);
    HCC_object_set_state(&p, SAD);
    HCC_object_set_state(&q, ANGRY);
    HCC_object_set_state(&r, SLEEPY);

    HCC_array* a = HCC_array_create_heap(3);

    HCC_array_push_back(a, &o);
    HCC_array_push_back(a, &p);
    HCC_array_push_back(a, &q);

    HCC_object* s = HCC_array_at(a,2);

    HCC_object_set_state(s, SAD);

    HCC_array_erase_at(a, 0);
    HCC_array_insert_at(a, &o, 2);

    //HCC_array_pop_back(a);
    //HCC_array_pop_back(a);
    //HCC_array_pop_back(a);

    //if (!HCC_array_is_empty(a)) return 1;

    //HCC_array_push_back(a, &q);
    printf("\nARRAY\n");
    for (int i = 0; i < HCC_array_size(a); i++){
        
        printf("%d : %s\n", HCC_array_at(a, i)->_id, get_state(HCC_array_at(a, i)));
    }

    HCC_list* l = HCC_list_create_heap();

    HCC_list_push_back(l, &o);
    HCC_list_push_back(l, &p);
    HCC_list_push_front(l, &q);
    HCC_list_push_front(l, &r);
    //HCC_list_push_back(l, &q);

    HCC_object t = HCC_object_create();

    HCC_object_set_state(&t, SLEEPY);

    //HCC_list_clear(l);
    HCC_list_insert_at(l, &t, 3);
    //HCC_list_erase_at(l, 3);

    //HCC_list_pop_back(l);
    //HCC_list_pop_back(l);
    //HCC_list_pop_front(l);

    size_t sz = HCC_list_size(l);

    printf("\nLIST\n");
    for (int i = 0; i < HCC_list_size(l); i++){
        int id = HCC_list_at(l, i)->_id;
        printf("%d : %s\n", id, get_state(HCC_list_at(l, i)));
    }

}