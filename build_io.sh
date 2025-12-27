gcc -c -fPIC watcher_io.c watcher.c str_ll.c 
gcc -shared -o watcher_io.so watcher_io.o watcher.o str_ll.o
rm watcher.o watcher_io.o str_ll.o
