
#include <stdio.h>
#include <limits.h>

#define FIXED 5000LL

long long calculateBill(long long units)
{
    long long bill = FIXED;

    if (units <= 100)
        bill += 0;
    else if (units <= 200)
        bill += (units - 100) * 225;
    else
        bill += 100 * 225 + (units - 200) * 450;

    return bill;
}

int main()
{
    long long units, bill, counts[] = {
        4000, 60000, 800000
    };

    int i;

    printf("Enter units consumed by one house: ");
    scanf("%lld", &units);

    if (units < 0)
    {
        printf("Invalid units!\n");
        return 1;
    }

    bill = calculateBill(units);

    printf("\nSingle bill: Rs. %lld.%02lld\n",
           bill / 100, bill % 100);

    printf("\nType Size and Range\n");
    printf("int: %zu bytes, %d to %d\n",
           sizeof(int), INT_MIN, INT_MAX);

    printf("long: %zu bytes, %ld to %ld\n",
           sizeof(long), LONG_MIN, LONG_MAX);

    printf("long long: %zu bytes, %lld to %lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);

    printf("\nTOTAL BILL COMPARISON\n");

    for (i = 0; i < 3; i++)
    {
        long long count = counts[i];
        long long exactPaise = bill * count;

        float floatTotal =
            (float)(bill / 100.0) * (float)count;

        double doubleTotal =
            (double)bill * count / 100.0;

        printf("\nNumber of bills: %lld\n", count);

        printf("Float total: Rs. %.2f\n", floatTotal);

        printf("Double total: Rs. %.2f\n", doubleTotal);

        printf("Paise total: Rs. %lld.%02lld\n",
               exactPaise / 100, exactPaise % 100);

        if (count <= LLONG_MAX / bill)
            printf("Integer total: Rs. %lld.%02lld\n",
                   exactPaise / 100, exactPaise % 100);
        else
            printf("Integer total: OVERFLOW\n");

        if (exactPaise > INT_MAX)
            printf("int: OVERFLOW\n");

        if (exactPaise > LONG_MAX)
            printf("long: OVERFLOW\n");

        if (exactPaise > LLONG_MAX)
            printf("long long: OVERFLOW\n");
    }

    return 0;
}

