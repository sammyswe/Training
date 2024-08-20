#include <stdio.h>

int main(void){
float celsius;

printf("Input temperature in celsius: \n");
scanf("%f", &celsius);

float kelvin = celsius + 273.15;
float farenheit = celsius*9/5 + 32;

printf("Temperature in kelvin is %f \n" , kelvin);
printf("Temperature in farenheit is %f \n", farenheit);

}