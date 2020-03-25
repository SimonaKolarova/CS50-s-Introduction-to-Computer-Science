#include <cs50.h>
#include <stdio.h>

int main(void)
// User input
{
    int n;
    do 
{
    n = get_int("Height: ");
}
while (n<1 || n>8);

for (int i = 0; i < n; i++)
{
// make integer m - resiprocal to n 
  int m = n -1 -i;
// print m-related spaces
   for (int j = 0; j < m ; j++)
   { 
            printf(" ");
   }
// print n-related #
   for (int j = 0; j <= i ; j++)
   { 
       printf("#");
   }
// print middle spaces
   printf("  ");
// print n-related #
    for (int j = 0; j <= i ; j++)
   { 
       printf("#");
   }
// print new line
   printf("\n");
}
}
