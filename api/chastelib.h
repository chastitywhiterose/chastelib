/*! \file chastelib.h
 This file is a library of functions written by Chastity White Rose. The functions are for converting strings into integers and integers into strings.
 I did it partly for future programming plans and also because it helped me learn a lot in the process about how pointers work
 as well as which features the standard library provides and which things I need to write my own functions for.

 As it turns out, the integer output routines for C are too limited for my tastes. This library corrects this problem.
 Using the global variables and functions in this file, integers can be output in bases/radixes 2 to 36
*/

/**
 These two lines define a static array with a size big enough to store the digits of an integer including padding it with extra zeroes.
 The function which follows always returns a pointer to this global string and this allows other standard library functions
 such as printf to display the integers to standard output or even possibly to files.
*/

#define usl 32 /**< usl stands for Unsigned String Length*/
char int_string[usl+1]; /**< global string which will be used to store string of integers. Size is usl+1 for terminating zero*/

/**
 radix or base for integer output. 2=binary, 8=octal, 10=decimal, 16=hexadecimal, or anything 2 to 36
*/
int radix=2;
/**
default minimum digits for printing integers
For the most part, this should stay 1 unless you want numbers lined up according to their place values and padded with extra zeros.
*/
int int_width=1;

/**
 @brief Convert an unsigned integer to a string in the current global radix.

This function is one that I wrote because the standard library can display integers as decimai, octai, or hexadecimal but not any other bases(including binary which is my favorite).
My function corrects this and in my opinion such a function should have been part of the standard library but I'm not complaining because now I have my own which I can use forever!

 @param i The integer to convert.
 @return pointer to a zero terminated string ready to be printed
 
 @note This function does not work on negative numbers!

Example:
 @code
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
 @endcode


*/

char *intstr(unsigned int i)    /*Chastity's supreme integer to string conversion function*/
{
 int width=0;                   /*the width or how many digits including prefixed zeros are printed*/
 char *s=int_string+usl;        /*a pointer starting to the place where we will end the string with zero*/
 *s=0;                          /*set the zero that terminates the string in the C language*/
 while(i!=0 || width<int_width) /*loop to fill the string with every required digit plus prefixed zeros*/
 {
  s--;                          /*decrement the pointer to go left for corrent digit placing*/
  *s=i%radix;                   /*get the remainder of division by the radix or base*/
  i/=radix;                     /*divide the input by radix*/
  if(*s<10){*s+='0';}           /*fconvert digits 0 to 9 to the ASCII character for that digit*/
  else{*s=*s+'A'-10;}           /*for digits higher than 9, convert to letters starting at A*/
  width++;                      /*increment the width so we know when enough digits are saved*/
 }
 return s;                      /*return this string to be used by putstr,printf,std::cout or whatever*/
}

/**
 @brief print a string to stdout


 This function prints a string using fwrite.
 This is the best C representation of how my Assembly programs also work/
 It's true purpose is to be used in the putint function for conveniently printing integers, 
 but it can print any valid string.

 @param s The string to print
 @return void

 Example:
 @code
#include <stdio.h>
#include "chastelib.h"

int main(int argc, char *argv[])
{
 putstring("Hello World\n");
 return 0;
}
 @endcode

*/

int putstring(const char *s)
{
 int count=0;              /*used to count how many bytes will be written*/
 const char *p=s;          /*pointer used to find terminating zero of string*/
 while(*p){p++;}           /*loop until zero found and immediately exit*/
 count=p-s;                /*count is the difference of pointers p and s*/
 fwrite(s,1,count,stdout); /*https://cppreference.com/w/c/io/fwrite.html*/
 return count;             /*return how many bytes were written*/
}

/**
 @brief print integer using global radix


 This function uses both intstr and putstring to print an integer in the currently selected radix and width

 @param i The integer to print
 @return void


 Example:
 @code
#include <stdio.h>
#include <stdlib.h>
#include "chastelib.h"

int main(int argc, char *argv[])
{
 int a=0,b;

 radix=16;
 int_width=1;

 putstring("This program is the official test suite for the C version of chastelib.\n");

 b=strint("100");
 while(a<b)
 {
  radix=2;
  int_width=8;
  putint(a);
  putstring(" ");
  radix=16;
  int_width=2;
  putint(a);
  putstring(" ");
  radix=10;
  int_width=3;
  putint(a);

  if(a>=0x20 && a<=0x7E)
  {
   putstring(" ");
   putchar(a);
  }

  putstring("\n");
  a+=1;
 }
  
 return 0;
}
 @endcode
*/

void putint(unsigned int i)
{
 putstring(intstr(i));
}

/**
 @brief convert string into integer using global radix

 This function is my own replacement for the strtol function from the C standard library.
 I didn't technically need to make this function because the functions from stdlib.h can already convert strings from bases 2 to 36 into integers.
 However my function is simpler because it only requires 2 arguments instead of three and it also does not handle negative numbers.
 Never have I needed negative integers but if I ever do I can use the standard functions or write my own in the future.

 @param s The string to parse as an integer in the global radix
 @return integer conversion of the string

 Example:
 @code
#include <stdio.h>
#include <stdlib.h>
#include "chastelib.h"

int main(int argc, char *argv[])
{
 int a,b,c;

 radix=10;
 int_width=1;

 a=strint("3");
 b=strint("5");
 c=a+b;
 
 putint(c);
 putstring("\n");
  
 return 0;
}
 @endcode

*/

int strint(const char *s)
{
 int i=0;
 char c;
 strint_errors = 0; /*set zero errors before we parse the string*/
 if( radix<2 || radix>36 ){ strint_errors++; printf("Error: radix %i is out of range!\n",radix);}
 while( *s == ' ' || *s == '\n' || *s == '\t' ){s++;} /*skip whitespace at beginning*/
 while(*s!=0)
 {
  c=*s;
  if( c >= '0' && c <= '9' ){c-='0';}
  else if( c >= 'A' && c <= 'Z' ){c-='A';c+=10;}
  else if( c >= 'a' && c <= 'z' ){c-='a';c+=10;}
  else if( c == ' ' || c == '\n' || c == '\t' ){break;}
  else{ strint_errors++; printf("Error: %c is not an alphanumeric character!\n",*s);break;}
  if(c>=radix){ strint_errors++; printf("Error: %c is not a valid character for radix %i\n",*s,radix);break;}
  i*=radix;
  i+=c;
  s++;
 }
 return i;
}

/**
 Those four functions above are pretty much the entirety of chastelib.
 While there may be extensions written for specific programs, these functions are essential for absolutely every program.
 The only reason you would not need them is if you only output numbers in decimal or hexadecimal, because printf in C can do all that just fine.
*/
