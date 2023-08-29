#include <cs50.h>
#include <stdio.h>

long get_credit(void);
long count_digits(long credit);
long brand_check(long credit, int count);
long luhns(long credit, int count);

int main(void)
{

    long credit;
    int count;
    long luhnbool;
    long brandcheck;

    // GET CREDIT NUMBER
    credit = get_credit();
    // COUNT DIGITS IN CREDIT NUMBER
    count = count_digits(credit);
    // CHECK FOR LUHNS ALGORITHM
    luhnbool = luhns(credit, count);
    // IF TRUE CONTINUE TO BRAND CHECK AND PRINT
    if (luhnbool == 1)
    {
        brandcheck = brand_check(credit, count);
        if (brandcheck == 1)
        {
            printf("AMEX\n");
        }
        else if (brandcheck == 2)
        {
            printf("MASTERCARD\n");
        }
        else if (brandcheck == 3)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // IF FALSE PRINT INVALID
    else
    {
        printf("INVALID\n");
    }
}

long get_credit(void)
{
    long credit;
    // PROMPT FOR credit NUMBER INPUT
    do
    {
        credit = get_long("Enter your credit number: ");
    }
    while (credit < 0);

    return credit;
}

long count_digits(long credit)
{
    int count = 0;

    while (credit != 0)
    {
        credit = credit / 10;
        count++;
    }
    return count;
}

long brand_check(long credit, int count)
{
    // CHECK FOR credit BRAND
    // AMEX 15-DIGIT (34, 37 START), RETURN 1
    if (count == 15)
    {
        credit = credit / 10000000000000;
        if (credit == 34 || credit == 37)
        {
            return 1;
        }
    }
    // MC 16-DIGIT (51, 52, 53, 54, 55 START), RETURN 2 or VISA 16-DIGIT (4 START), RETURN 3
    else if (count == 16)
    {
        credit = credit / 100000000000000;
        if (credit > 50 && credit < 56)
        {
            return 2;
        }
        else if (credit > 39 && credit <50)
        {
            return 3;
        }
    }
    // VISA 13-DIGIT (4 START), RETURN 3
    else if (count == 13)
    {
        credit = credit / 1000000000000;
        if (credit == 4)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
    // INVALID DIGIT, RETURN 0
    else
    {
        return 0;
    }
    return 0;
}

long luhns(long credit, int count)
{
    // LUHN SUM
    long luhnsum = 0;
    long prodsum = 0;
    long addsum = 0;
    int temp = 0;
    int digit;

    for (digit = 0; digit < count; digit++)
    {
        if ((digit % 2) == 0)
        {
            addsum += (credit % 10);
        }
        else
        {
            temp = (2 * (credit % 10));
            prodsum += temp;
            temp = temp / 10;
            prodsum += temp % 10;
            temp = 0;
        }

        credit = credit / 10;
    }

    luhnsum = addsum + prodsum;

    if (luhnsum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
