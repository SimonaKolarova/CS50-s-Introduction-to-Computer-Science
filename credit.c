#include <stdio.h>
#include <cs50.h>

int main(void)
// Get credit card number from user
{
    long n = get_long("Credit card number: ");
//Calculate CC checksum
int sum = (  (((n%100-n%10)/5)%10)+((((n%100-n%10)/5)%100-((n%100-n%10)/5)%10)/10)+
    (((n%10000-n%1000)/500)%10)+((((n%10000-n%1000)/500)%100-((n%10000-n%1000)/500)%10)/10)+
    (((n%1000000-n%100000)/50000)%10)+((((n%1000000-n%100000)/50000)%100-((n%1000000-n%100000)/50000)%10)/10)+
    (((n%100000000-n%10000000)/5000000)%10000000)+((((n%100000000-n%10000000)/5000000)%100-((n%100000000-n%10000000)/5000000)%10)/10)+
    (((n%10000000000-n%1000000000)/500000000)%10)+((((n%10000000000-n%1000000000)/500000000)%100-((n%10000000000-n%1000000000)/500000000)%10)/10)+
    (((n%1000000000000-n%100000000000)/50000000000)%10)+((((n%1000000000000-n%100000000000)/50000000000)%100-((n%1000000000000-n%100000000000)/50000000000)%10)/10)+
    (((n%100000000000000-n%10000000000000)/5000000000000)%10)+((((n%100000000000000-n%10000000000000)/5000000000000)%100-((n%100000000000000-n%10000000000000)/5000000000000)%10)/10)+
    (((n%10000000000000000-n%1000000000000000)/500000000000000)%10)+((((n%10000000000000000-n%1000000000000000)/500000000000000)%100-((n%10000000000000000-n%1000000000000000)/500000000000000)%10)/10)
+ ((n%10)+((n%1000-n%100)/100)+((n%100000-n%10000)/10000)+((n%10000000-n%1000000)/1000000)+((n%1000000000-n%100000000)/100000000)+((n%100000000000-n%10000000000)/10000000000)+((n%10000000000000-n%1000000000000)/1000000000000)+((n%1000000000000000-n%100000000000000)/100000000000000))
);
//Check if valid CC number
if (sum % 10 == 0)

// Check if CC is American Express
{
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
else
{
printf("INVALID\n");
}
}
