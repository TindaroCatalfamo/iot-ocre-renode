/*#include <stdio.h>
#include <stdlib.h>

float run(void)
{
    const int samples = 100;
    float sum = 0.0f;
    float MIN = 0.0f;
    float MAX = 45.0f;

    for (int i = 0; i < samples; i++) {
        float temp = MIN + ((float)rand() / RAND_MAX) * (MAX - MIN);
        sum += temp;
    }

    float avg = sum / samples;
    printf("Temperatura media: %.2f\n", avg);
    return avg;
}
*/
#include <stdio.h>
#include <stdlib.h>

// Application entry point
int main()
{  
    const int samples = 100;
    float sum = 0.0f;
    float MIN = 0.0f;
    float MAX = 45.0f;

    for (int i = 0; i < samples; i++) {
        float temp = MIN + ((float)rand() / (float)RAND_MAX) * (MAX - MIN);

        sum += temp;
    }

    float avg = sum / samples;
    printf("Temperatura media: %.2f\n", avg);

    return 0;
}