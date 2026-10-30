
#include <stdio.h>
#include <limits.h>

#define MAX_READING 65535

int main()
{
    const long long limits[] = {
        100, 200, LLONG_MAX
    };

    const long long rates[] = {
        0, 225, 450
    };

    const long long fixedCharge = 5000;

    long long previous, current, units;
    long long bill = fixedCharge;
    long long remaining;
    long long lower = 0;
    int i;

    printf("Enter previous reading: ");
    if (scanf("%lld", &previous) != 1)
        return 1;

    printf("Enter current reading: ");
    if (scanf("%lld", &current) != 1)
        return 1;

    if (previous < 0 || previous > MAX_READING ||
        current < 0 || current > MAX_READING)
    {
        printf("Invalid reading!\n");
        return 1;
    }

    if (current >= previous)
        units = current - previous;
    else if (previous >= 60000 && current <= 5535)
        units = MAX_READING - previous + 1 + current;
    else
    {
        printf("Invalid meter reading!\n");
        return 1;
    }

    remaining = units;

    for (i = 0; i < 3 && remaining > 0; i++)
    {
        long long slabUnits;

        slabUnits = limits[i] - lower;

        if (slabUnits > remaining)
            slabUnits = remaining;

        bill += slabUnits * rates[i];

        remaining -= slabUnits;
        lower = limits[i];
    }

    printf("\nFINAL ELECTRICITY BILL\n");
    printf("Units consumed: %lld\n", units);
    printf("Fixed charge: Rs. 50.00\n");

    printf("Total amount: Rs. %lld.%02lld\n",
           bill / 100, bill % 100);

    return 0;
}

