#include <stdio.h>
#include "chastelib.h"

int main(int argc, char *argv[])
{
 int x;

 radix=2;
 int_width=4;

 x=0;
 while(x<16)
 {
  printf("the number x is %s\n",intstr(x));
  x++;
 }
 return 0;
}

