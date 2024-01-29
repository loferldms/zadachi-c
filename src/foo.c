#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
typedef struct tree
{
    uint8_t id;
    struct tree*parent;
    struct tree*left;
    struct tree*right;
}tree;



void Main_foo(void);

void Main_foo(void){

}