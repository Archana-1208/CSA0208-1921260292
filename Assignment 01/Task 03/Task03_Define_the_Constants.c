#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200

#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450

#define FIXED_CHARGE_PAISE 5000L

/* Returns the electricity bill in paise. */
long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;

    /* Charge for units 101 through 200. */
    if (units > SLAB1_UNITS)
    {
        int slab2_units = units - SLAB1_UNITS;

        if (slab2_units > SLAB2_UNITS - SLAB1_UNITS)
        {
            slab2_units = SLAB2_UNITS - SLAB1_UNITS;
        }

        paise += (long)slab2_units * RATE2_PAISE;
    }

    /* Charge for every unit above 200. */
    if (units > SLAB2_UNITS)
    {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
    }

    return paise;
}

int main(void)
{
    int tests[] = {0, 100, 150, 200, 350};
    int n = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < n; i++)
    {
        long p = compute_bill(tests[i]);

        printf("%3d units -> Rs %ld.%02ld\\n",
               tests[i], p / 100, p % 100);
    }

    return 0;
}
