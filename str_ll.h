#include <stdio.h>
#include <stdlib.h>

#define BLK_SIZE 1025

struct str_blk{

    char *content; //

    struct str_blk *next;


};

void add_str(struct str_blk *, char *);