#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define IS_D 1
#define IS_F 0

struct fnode{

    char *rel_location; // this is relative, the driver function will need to handle this when traversing tree
    struct stat st;

};

struct dnode{

    char *rel_location; // this is relative, the driver function will need to handle this when traversing tree
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

/*int f_o_d(char *fullpath){
    struct stat st;
    
    if (stat(fullpath, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return IS_D;
        } else if (S_ISREG(st.st_mode)) {
            return IS_F;
        }
    }
    }*/

void add_to_dnode_l(struct dnode_list *head, struct dnode *dval){

    if(head->val == NULL){

        head->val=dval;
        head->next=NULL;

    }
    else{

        struct dnode_list *trv =head;

        while(trv->next!=NULL){
            trv=trv->next;
        }

        trv->next=(struct dnode_list *)malloc(sizeof(struct dnode_list));
        trv->next->val=dval;
        trv->next->next=NULL;

    }

}

void add_to_fnode_l(struct fnode_list *head, struct fnode *fval){

    if(head->val == NULL){

        head->val=fval;
        head->next=NULL;

    }
    else{

        struct fnode_list *trv =head;

        while(trv->next!=NULL){
            trv=trv->next;
        }

        trv->next=(struct fnode_list *)malloc(sizeof(struct fnode_list));
        trv->next->val=fval;
        trv->next->next=NULL;

    }

}

struct dnode *init_dnode(char *dloc){

    struct dnode *root_dir=(struct dnode *)malloc(sizeof(struct dnode));
    
    root_dir->dlist=(struct dnode_list *)malloc(sizeof(struct dnode_list));
    root_dir->dlist->val=NULL;
    root_dir->flist=(struct fnode_list *)malloc(sizeof(struct fnode_list));
    root_dir->flist->val=NULL;

    return root_dir;

}

void construct_base_tree(struct dnode *root_dir){
    
    char *dloc = root_dir->rel_location;

    DIR *root = opendir(dloc);




    if(root == NULL){

        printf("%s can't be opened.\n", dloc);
        

    }

    else{

        struct dirent *trv;

        while(1){

            trv = readdir(root);

            if(trv == NULL){

                break;
            }

            else{

                // directory
                if(trv->d_type == DT_DIR){
                    
                    struct dnode *add_d = init_dnode(trv->d_name);
                    
                    add_to_dnode_l(root_dir->dlist,add_d);

                    construct_base_tree(add_d);
                    
                    
                }

                else{

                    struct fnode *add_f=(struct fnode *)malloc(sizeof(struct fnode));
                    add_f->rel_location=trv->d_name;

                    struct stat sta;

                if (stat("file.txt", &sta) == -1) {
                    perror("stat");
                } 

                else{
                    add_f->st=sta;
                }
                
                    add_to_fnode_l(root_dir->flist,add_f);

                }
            

            }



        }

    }

}

void trv_tree_test(struct dnode *root){

    printf("Location: %s\n\n",root->rel_location);

    // files
    struct fnode_list *trv=root->flist;

    while(trv!=NULL){

        printf("%s\n",trv->val->rel_location);
        trv = trv->next;
    }

    // directories
    struct dnode_list *dtrv= root->dlist;

    while(dtrv!=NULL){

        trv_tree_test(dtrv->val);

        dtrv = dtrv->next;

    }




}

int main(){

    struct dnode *loc = init_dnode("/home/dfmaaa1/Samex");

    trv_tree_test(loc);

    return 0;

}