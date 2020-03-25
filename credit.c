#include <stdio.h>
#include <cs50.h>

int main(void)
// Get credit card number from user
{
    long n = get_long("Credit card number: ");

// Check if CC is American Express
if ((n >= 340000000000000 && n < 350000000000000) || (n >= 370000000000000 && n < 380000000000000))
{
    printf("AMEX\n");
}

// Check if CC is Mastercard
else if (n >= 5100000000000000 && n < 5600000000000000)
{
    printf("MASTERCARD\n");
}
// Check if CC is Visa
else if ((n >= 4000000000000 && n < 5000000000000) || (n >= 4000000000000000 && n < 5000000000000000))
{
    printf("VISA\n");
}
else
{
printf("INVALID\n");
}
}
