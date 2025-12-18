#include "str_ll.h"

//text given to below function must be <=1025 characters
void add_str(struct str_blk *head, char *str){

    struct str_blk *trv=head;

    while(trv->next!=NULL){

        trv=trv->next;

    }

    trv->next=(struct str_blk *)malloc(sizeof(struct str_blk));

    trv->next->content=str;
    trv->next->next=NULL;




}