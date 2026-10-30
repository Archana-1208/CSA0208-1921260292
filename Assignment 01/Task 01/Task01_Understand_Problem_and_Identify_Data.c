#include <stdio.h>

typedef unsigned short meter_t;

struct BillRecord
{
    unsigned long household_number;
    meter_t previous_reading;
    meter_t current_reading;
    unsigned int units;
    long fixed_charge_paise;
    long energy_charge_paise;
    long total_paise;
};

int main(void)
{
    struct BillRecord bill;

    printf("Enter household number: ");
    scanf("%lu", &bill.household_number);

    printf("Enter previous reading: ");
    scanf("%hu", &bill.previous_reading);

    printf("Enter current reading: ");
    scanf("%hu", &bill.current_reading);

    /* Unsigned 16-bit arithmetic handles one meter rollover. */
    bill.units = (meter_t)(bill.current_reading -
                           bill.previous_reading);

    bill.fixed_charge_paise = 5000L;

    printf("\\n--- Electricity Reading Details ---\\n");
    printf("Household Number: %lu\\n", bill.household_number);
    printf("Previous Reading: %hu\\n", bill.previous_reading);
    printf("Current Reading: %hu\\n", bill.current_reading);
    printf("Units Consumed: %u\\n", bill.units);
    printf("Fixed Charge: Rs. 50.00\\n");

    return 0;
}
