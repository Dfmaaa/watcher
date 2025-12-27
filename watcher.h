#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "str_ll.h"


struct fnode{

    char *location;
    struct str_blk *text; 
    struct stat st;

};

struct dnode{
    
    char *location; 
    struct stat st;
    struct dnode *parent;
    struct dnode_list *dlist; 
    struct fnode_list *flist;

};

struct dnode_list{

    struct dnode *val;
    struct dnode_list *next;

};
struct fnode_list{

    struct fnode *val;
    struct fnode_list *next;

};

struct dnode *get_tree(char *);