#include "watcher.h"

struct dnode *init_tree(char *);
struct fnode *find_fnode_abs(struct dnode *, char *);
int write_abs(struct dnode *, char *, char *);