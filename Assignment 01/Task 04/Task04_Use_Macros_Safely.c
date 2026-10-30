#include <stdio.h>

/* Fully parenthesised macros. */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define RUPEES_TO_PAISE(x) ((x) * 100L)

int main(void)
{
    int a = 10;
    int b = 20;
    int number = 5;

    printf("Maximum value = %d\\n", MAX(a, b));
    printf("Square of %d = %d\\n", number, SQUARE(number));
    printf("Square of a+1 = %d\\n", SQUARE(a + 1));
    printf("Rs. 50 in paise = %ld\\n", RUPEES_TO_PAISE(50));

    return 0;
}
