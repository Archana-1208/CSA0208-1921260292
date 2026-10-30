
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READING 65535
#define FIXED_CHARGE 5000

/* Rates are in paise */
#define RATE1 0
#define RATE2 225
#define RATE3 450

long long getNumber(char message[])
{
    char input[100], *end;
    long long value;

    printf("%s", message);

    if (fgets(input, sizeof(input), stdin) == NULL)
        return -1;

    value = strtoll(input, &end, 10);

    if (end == input)
        return -1;

    while (*end == ' ' || *end == '\t')
        end++;

    if (*end != '\n' && *end != '\0')
        return -1;

    return value;
}

int main()
{
    long long previous, current, units;
    long long bill = FIXED_CHARGE;

    previous = getNumber("Enter previous reading: ");
    current = getNumber("Enter current reading: ");

    if (previous < 0 || previous > MAX_READING ||
        current < 0 || current > MAX_READING)
    {
        printf("Invalid meter reading!\n");
        return 1;
    }

    if (current >= previous)
    {
        units = current - previous;
    }
    else if (previous >= 60000 && current <= 5535)
    {
        units = (MAX_READING - previous) + 1 + current;
        printf("Meter rollover detected!\n");
    }
    else
    {
        printf("Invalid reading: No valid rollover!\n");
        return 1;
    }

    if (units <= 100)
        bill += units * RATE1;
    else if (units <= 200)
        bill += 100 * RATE1 + (units - 100) * RATE2;
    else
        bill += 100 * RATE1 + 100 * RATE2
                + (units - 200) * RATE3;

    printf("\nElectricity Bill\n");
    printf("Units consumed: %lld\n", units);
    printf("Fixed charge: Rs. 50.00\n");
    printf("Total bill: Rs. %lld.%02lld\n",
           bill / 100, bill % 100);

    return 0;
}

