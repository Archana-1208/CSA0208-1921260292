
#include <stdio.h>
#include <limits.h>

#define READINGS 35040

int main()
{
    FILE *fp;

    long long limit[3], rate[3];
    long long fixedCharge;
    long long previous = 0, current;
    long long totalWh = 0;
    long long chargeUnits = 0;
    long long remaining, portion, capacity;
    long long roundedPaise;

    int hour, minute;
    int first = 1;
    int i, multiplier;

    fp = fopen("tariff.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open tariff file!\n");
        return 1;
    }

    for (i = 0; i < 3; i++)
    {
        if (fscanf(fp, "%lld %lld",
                   &limit[i], &rate[i]) != 2)
        {
            printf("Invalid tariff file!\n");
            fclose(fp);
            return 1;
        }

        if (limit[i] <= 0 || rate[i] < 0 ||
            (i > 0 && limit[i] <= limit[i - 1]))
        {
            printf("Invalid tariff values!\n");
            fclose(fp);
            return 1;
        }

        limit[i] *= 1000;
    }

    if (fscanf(fp, "%lld", &fixedCharge) != 1 ||
        fixedCharge < 0)
    {
        printf("Invalid fixed charge!\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    fp = fopen("readings.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open readings file!\n");
        return 1;
    }

    for (i = 0; i < READINGS; i++)
    {
        if (fscanf(fp, "%d:%d %lld",
                   &hour, &minute, &current) != 3)
            break;

        if (hour < 0 || hour > 23 ||
            minute < 0 || minute > 59 ||
            current < 0)
        {
            printf("Invalid reading!\n");
            fclose(fp);
            return 1;
        }

        if (first)
        {
            previous = current;
            first = 0;
            continue;
        }

        if (current < previous)
        {
            printf("Invalid meter reading!\n");
            fclose(fp);
            return 1;
        }

        remaining = current - previous;

        totalWh += remaining;

        /* Peak hours: 6 PM to 10 PM */
        if (hour >= 18 && hour < 22)
            multiplier = 6;
        else
            multiplier = 5;

        /* Calculate slab-wise charges */
        while (remaining > 0)
        {
            for (int j = 0; j < 3; j++)
            {
                if (totalWh - remaining < limit[j])
                {
                    capacity = limit[j] -
                               (totalWh - remaining);

                    portion = remaining < capacity
                              ? remaining : capacity;

                    chargeUnits += portion *
                                   rate[j] * multiplier;

                    remaining -= portion;
                    break;
                }
            }

            if (remaining > 0 &&
                totalWh >= limit[2])
            {
                printf("Consumption exceeds tariff limit!\n");
                fclose(fp);
                return 1;
            }
        }

        previous = current;
    }

    fclose(fp);

    /* Add fixed charge */
    chargeUnits += fixedCharge * 5000;

    /* Convert to paise */
    roundedPaise = (chargeUnits + 2500) / 5000;

    printf("\nSMART METER BILL\n");
    printf("Total energy: %lld Wh\n", totalWh);

    printf("Total amount: Rs. %lld.%02lld\n",
           roundedPaise / 100,
           roundedPaise % 100);

    printf("Readings processed: %d\n", i);

    return 0;
}

