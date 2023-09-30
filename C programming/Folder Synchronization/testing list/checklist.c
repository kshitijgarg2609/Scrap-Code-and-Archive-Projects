#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

int main()
{
initializ(4);
queue(0,"K");
queue(0,"g");
queue(0,"d");
queue(0,"h");
queue(0,"e");
queue(0,"q");

queue(1,"g");
queue(1,"f");
queue(1,"h");
queue(1,"j");

queue(2,"g");
queue(2,"f");
queue(2,"h");
queue(2,"j");

queue(3,"g");
queue(3,"f");
queue(3,"h");
queue(3,"j");

printf("Displaying : 0\n");
display(0);

printf("Displaying : 1\n");
display(1);

printf("Displaying : 2\n");
display(2);

printf("Displaying : 3\n");
display(3);

printf("Testing deletion : 0\n");
printf("deleting : %c result : %d\n",'h',delete(0,"h"));
display(0);

printf("Testing deletion : 1\n");
printf("deleting : %c result : %d\n",'h',delete(1,"h"));
display(1);

printf("Testing deletion : 2\n");
printf("deleting : %c result : %d\n",'h',delete(2,"h"));
display(2);

printf("Testing deletion : 3\n");
printf("deleting : %c result : %d\n",'h',delete(3,"h"));
display(3);

return 0;
}