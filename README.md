
# FOR USERS THAT ONLY WANT THE TREE AND NOT THE HELPER CODE
Switch to the no_helpers branch, that branch has been made for users that want just the tree, because they wanna use it for something else. I get where those people are coming
from, because initially even I didn't know what I wanted to do after writing the tree generation code for a while. That tree can be used for anything.

- NOTE: people switching to the no_helpers branch should read this README too. It has all the information you need to work with the tree.


# FUNCTIONS YOU NEED TO USE TO INTERACT WITH THE TREE:

	1. `truct dnode *init_tree(char *absolute_location_of_dir)` - this creates the tree.
	
	2. `struct fnode *find_fnode_abs(struct dnode *tree, char *absolute_location_of_file)` - this will return the fnode corresponding to a file.
	
	3. `int write_abs(struct dnode *tree, char *absolute_location_of_file, char *content)` - this will write to a file, wont append.
	
	4. `struct str_blk *read_abs(struct dnode *tree, char *absolute_location_of_file)` - this will return the content of a file(str_blk explained below with all the structs)


# STRUCTURES YOU NEED UNDERSTANDING OF:
 
	
	## fnode
	
	```
	struct fnode{

    		char *location;
    		struct str_blk *text; 
    		struct stat st;
	};
	
	```
	
	- This is the structure in the tree that contains the file . Location is absolute.

	
	## dnode
	
	```
	struct dnode{
 
   	       char *location; 
    	       struct stat st;
               struct dnode *parent;
               struct dnode_list *dlist; 
               struct fnode_list *flist;

       };

	```

      - This is the structure in the tree that contains the directory. Location is absolute. dnode_list, fnode_list explained below.


      ## dnode_list
      ```
      struct dnode_list{

             struct dnode *val;
             struct dnode_list *next;

     };
     ```
 
    
     - This is just a linked list of sub-directories in a dnode
     
     ## fnode_list
     ```
     struct fnode_list{

    	    struct fnode *val;
    	    struct fnode_list *next;

    };
    ```
    
    - This is just a linked list of files in a dnode
    
    
    ## str_blk
    
    ```
    struct str_blk{

           char *content;

           struct str_blk *next;

    
    };
    ```
    
    - This is how the tree stores text, Instead of one big buffer, the program creates a linked list of blocks of text, with predefined size (BLK_SIZE defined in `str_ll.h`)
    
    
    
    
    
# CORE FUNCTIONALITY HAS BEEN ADDED. Will only return to make file creation and directory creation after I feel the need to prove to myself that I am good at something
    

     
     
     
