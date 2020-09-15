#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string username = get_string("Name: ");
    printf("hello, %s \n", username);
}
