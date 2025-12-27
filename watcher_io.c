#include "watcher_io.h"

char *get_rel_path(char *abs_path){

    char *ptr = strrchr(abs_path,'/');

    if(ptr == NULL){

        return NULL;

    }
    

    char *trv = ptr;
    int size = 0;

    do{
        trv++;
        size++;
    }while(*trv!='\0');

    char *ret =(char*)malloc(sizeof(char)*size);

    char *ret_trv = ret;
    do{
        *ret_trv = *ptr;

        ret_trv++;
        ptr++;

    }while(*ptr!='\0');



    return ret;

}


struct dnode *init_tree(char *loc){

    return get_tree(loc);

}

struct fnode *find_fnode_abs(struct dnode *tree, char *loc){


    struct dnode *trv = tree;

    char *rel_root = get_rel_path(trv->location);

    /*Now we find where rel_root is in loc.
     but first, we need to protect loc with strdup.
     dont forget to free this memory.*/

     char *trv_loc = strdup(loc);

     char *token = strtok(trv_loc,"/");

     if(token == NULL){

        free(rel_root);
        free(trv_loc);

        return NULL;

     }

     while(strcmp(rel_root,token)!=0){

        token = strtok(NULL, "/");
        if(token == NULL){


        free(rel_root);
        free(trv_loc);

        return NULL;

        }
     }

     // we wont need this condition actually, it's just there
     while(token!=NULL){

        // check in the file linked list first, maybe we found it.
        struct fnode_list *li = trv->flist;

        while(li != NULL){

            if(strcmp(li->val->location,loc) == 0){

                free(rel_root);
                free(trv_loc);

                return li->val;

            }
            else{

                li = li->next;


            }

        }

        // alright so that didnt work

        token = strtok(NULL,"/"); // this is the next subdirectory

        // file does not exist
        if(token == NULL){

            free(rel_root);
            free(trv_loc);

            return NULL;

        }

        struct dnode_list *dli = trv->dlist;

        int flag = 0;

        while(dli != NULL){

            char *rel_dir = get_rel_path(dli->val->location);

            if(strcmp(rel_dir,token) == 0){

                trv = dli->val;
                flag = 1;

                break;

            }
            else{

                dli = dli->next;

            }


        }

        if(flag == 0){

            free(rel_root);
            free(trv_loc);
            return NULL; // the file does not exist, as the subdir doesnt.

        }




     }

     free(rel_root);
     free(trv_loc);

     return NULL; // File does not exist.


}

int write_abs(struct dnode *tree, char *loc, char *content){

    struct fnode *f = find_fnode_abs(tree,loc);

    if(f == NULL){

        return -1;

    }

    free_str(f->text); // we're gonna add our own string.

    f->text = (struct str_blk *)malloc(sizeof(struct str_blk));

    int t_len = strlen(content);

    char *move = content;

    if(((content + t_len) - move) > BLK_SIZE-1){

        char *buffer = (char *)malloc(sizeof(char)*(BLK_SIZE));

        memcpy(buffer, move, BLK_SIZE-1);
        move+=BLK_SIZE-1;
        buffer[BLK_SIZE-1] = '\0';

        f->text->content = buffer;
        f->text->next = NULL;


    }
    else{

        int left = (content + t_len) - move;
        char *buffer =(char*)malloc(sizeof(char)*(left+1));

        memcpy(buffer,content,left);
        buffer[left] = '\0';

        f->text->content = buffer;
        f->text->next = NULL;

        return 0;


    }


    while(*move!='\0'){

        // subtracting pointers to find out how many chars left
        if(((content + t_len) - move) >= BLK_SIZE-1){

            char *buffer = (char *)malloc(sizeof(char)*(BLK_SIZE));

            memcpy(buffer, move, BLK_SIZE-1);

            buffer[BLK_SIZE-1] = '\0';
            move+=BLK_SIZE-1;
            add_str(f->text,buffer);


        }

        else{

            int left = (content + t_len) - move;
            char *buffer =(char*)malloc(sizeof(char)*(left+1));
    
            memcpy(buffer,move,left);
    
            buffer[left] = '\0';
    
            add_str(f->text, buffer);
    
            return 0;
    
    
        }


    }

    return -2; // unusual cases, as all cases of failure and success have been covered.

}