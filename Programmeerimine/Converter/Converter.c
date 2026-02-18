#include <stdio.h>
#include <stdlib.h>

double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double feetToMeters(double feet) {
    return feet * 0.3048;
}

double metersToFeet(double meters) {
    return meters / 0.3048;
}

double milesToKilometers(double miles) {
    return miles * 1.60934;
}

double kilometersToMiles(double kilometers) {
    return kilometers / 1.60934;
}

double poundsToKilograms(double pounds) {
    return pounds * 0.453592;
}

double kilogramsToPounds(double kilograms) {
    return kilograms / 0.453592;
}

int main() {
    int choice;
    double value, result;

    while (1) {
        printf("\nUnit Converter Menu:\n");
        printf("1. Celsius to Fahrenheit\n");
        printf("2. Fahrenheit to Celsius\n");
        printf("3. Feet to Meters\n");
        printf("4. Meters to Feet\n");
        printf("5. Miles to Kilometers\n");
        printf("6. Kilometers to Miles\n");
        printf("7. Pounds to Kilograms\n");
        printf("8. Kilograms to Pounds\n");
        printf("9. Exit\n");
        printf("Enter your choice (1-9): ");
        scanf("%d", &choice);

        if (choice == 9) {
            printf("Exiting program.\n");
            break;
        }

        if (choice < 1 || choice > 9) {
            printf("Invalid choice. Please enter a number between 1 and 9.\n");
            continue;
        }

        printf("Enter the value to convert: ");
        scanf("%lf", &value,"\n\n");

        switch (choice) {
            case 1:
                result = celsiusToFahrenheit(value);
                printf("%.2f Celsius is equal to %.2f Fahrenheit\n", value, result);
                break;
            case 2:
                result = fahrenheitToCelsius(value);
                printf("%.2f Fahrenheit is equal to %.2f Celsius\n", value, result);
                break;
            case 3:
                result = feetToMeters(value);
                printf("%.2f Feet is equal to %.2f Meters\n", value, result);
                break;
            case 4:
                result = metersToFeet(value);
                printf("%.2f Meters is equal to %.2f Feet\n", value, result);
                break;
            case 5:
                result = milesToKilometers(value);
                printf("%.2f Miles is equal to %.2f Kilometers\n", value, result);
                break;
            case 6:
                result = kilometersToMiles(value);
                printf("%.2f Kilometers is equal to %.2f Miles\n", value, result);
                break;
            case 7:
                result = poundsToKilograms(value);
                printf("%.2f Pounds is equal to %.2f Kilograms\n", value, result);
                break;
            case 8:
                result = kilogramsToPounds(value);
                printf("%.2f Kilograms is equal to %.2f Pounds\n", value, result);
                break;
        }
    }

    return 0;
}