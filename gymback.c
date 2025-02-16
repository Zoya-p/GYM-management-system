#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to store personal information
struct PersonalInfo {
    char *fullName;
    char *dob;
    int  *age;
    char *address;
    char *phoneNumber;
    char *emailAddress;
    char *identification;
    char *healthInfo;
    char *emergencyContact;
};

// Structure to store payment information
struct PaymentInfo {
    char *paymentMethod;
    char *paymentSchedule;
    int price;
};

// Structure to store agreement information
struct Agreement {
    bool termsAndConditions;
    char *signatureFileName;
};

// Structure to store user account information
struct User {
    char *username;
    char *password;
    struct PersonalInfo personalInfo;
    struct PaymentInfo paymentInfo;
    struct Agreement agreement;
};

// Function to allocate memory for a string
char *allocateString() {
    char buffer[MAX_SIZE];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    char *str = malloc(strlen(buffer) + 1);
    if (str == NULL) {
        printf("Memory allocation error. Exiting program.\n");
        exit(1);
    }
    strcpy(str, buffer);
    return str;
}

// Function to allocate memory for a string in a structure
void allocateStringInStruct(char **str) {
    *str = allocateString();
}

// Function to free memory allocated for a string
void freeString(char *str) {
    free(str);
}

// Function to free memory allocated for strings in a structure
void freeStringsInStruct(struct PersonalInfo *info) {
    freeString(info->fullName);
    freeString(info->dob);
    freeString(info->address);
    freeString(info->phoneNumber);
    freeString(info->emailAddress);
    freeString(info->identification);
    freeString(info->healthInfo);
    freeString(info->emergencyContact);
}

// Function to free memory allocated for a structure
void freeUser(struct User *user) {
    freeString(user->username);
    freeString(user->password);
    freeStringsInStruct(&user->personalInfo);
    freeString(user->paymentInfo.paymentMethod);
    freeString(user->paymentInfo.paymentSchedule);
    freeString(user->agreement.signatureFileName);
}

// Function to check if the given string is numeric
bool isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Function to calculate age based on date of birth
int calculateAge(const char *dob) {
    int day, month, year;
    if (sscanf(dob, "%d/%d/%d", &day, &month, &year) != 3) {
        printf("Invalid date format. Exiting program.\n");
        exit(1);
    }

    // Assuming the current date is 2023-12-01
    int currentYear = 2023;
    int currentMonth = 12;
    int currentDay = 1;

    int age = currentYear - year;
    if (currentMonth < month || (currentMonth == month && currentDay < day)) {
        age--;
    }

    return age;
}

// Function to select payment schedule
char *selectPaymentSchedule() {
    printf("Select Payment Schedule:\n");
    printf("1. January\n");
    printf("2. February\n");
    printf("3. March\n");
    printf("4. April\n");
    printf("5. May\n");
    printf("6. June\n");
    printf("7. July\n");
    printf("8. August\n");
    printf("9. September\n");
    printf("10. October\n");
    printf("11. November\n");
    printf("12. December\n");

    int choice;
    printf("Enter your choice (1-12): ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 12) {
        printf("Invalid choice. Exiting program.\n");
        exit(1);
    }
    getchar(); // clear the buffer

    switch (choice) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default:
            printf("Invalid choice. Exiting program.\n");
            exit(1);
    }
}

int main() {
    struct User user = {0};

    // Setting up username and password
    printf("Set up your username: ");
    allocateStringInStruct(&user.username);

    printf("Set up your password: ");
    allocateStringInStruct(&user.password);

    // Check if username and password are the same
    if (strcmp(user.username, user.password) == 0) {
        printf("Error: Username and password cannot be the same. Exiting program.\n");
        freeUser(&user);
        return 1;
    }

    printf("Welcome to the Gym Management System\n");
    printf("Enter your username: ");
    char enteredUsername[MAX_SIZE];
    fgets(enteredUsername, sizeof(enteredUsername), stdin);
    enteredUsername[strcspn(enteredUsername, "\n")] = 0;

    printf("Enter your password: ");
    char enteredPassword[MAX_SIZE];
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;

    // Authenticating the user
    if (strcmp(enteredUsername, user.username) == 0 && strcmp(enteredPassword, user.password) == 0) {
        printf("Authentication successful\n");
        printf("Please provide your information:\n");

        // Taking personal information input
        printf("Enter your Full Name: ");
        allocateStringInStruct(&user.personalInfo.fullName);

        printf("Enter your Date of Birth (in the format dd/mm/yyyy): ");
        allocateStringInStruct(&user.personalInfo.dob);

        // Validate date of birth format
        if (strlen(user.personalInfo.dob) != 10 || user.personalInfo.dob[2] != '/' || user.personalInfo.dob[5] != '/') {
            printf("Invalid data: Date of birth must be in the format dd/mm/yyyy. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        // Calculate age
        user.personalInfo.age = calculateAge(user.personalInfo.dob);

        // Validate age
        if (user.personalInfo.age < 5 || user.personalInfo.age > 100) {
            printf("Invalid data: Age must be between 5 and 100. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        // Check if the person is an adult or a teenager
        printf("Age: %d\n", user.personalInfo.age);
        if (user.personalInfo.age >= 18) {
            printf("Person is an adult\n");
            user.paymentInfo.price = 5000; // Default price for adults
        } else {
            printf("Person is a teenager\n");
            user.paymentInfo.price = 5000 * 0.75; // 25% less for teenagers
        }

        // Continue taking personal information input
        printf("Enter your Address: ");
        allocateStringInStruct(&user.personalInfo.address);

        // Validate phone number
        printf("Enter your Phone Number: ");
        allocateStringInStruct(&user.personalInfo.phoneNumber);
        if (!isNumeric(user.personalInfo.phoneNumber) || strlen(user.personalInfo.phoneNumber) != 10) {
            printf("Invalid data: Phone number must contain exactly 10 numeric characters. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        // Validate email address format
        printf("Enter your Email Address: ");
        allocateStringInStruct(&user.personalInfo.emailAddress);
        if (strchr(user.personalInfo.emailAddress, '@') == NULL) {
            printf("Invalid data: Email address must contain '@'. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        printf("Enter your Identification: ");
        allocateStringInStruct(&user.personalInfo.identification);

        printf("Enter your Health Information: ");
        allocateStringInStruct(&user.personalInfo.healthInfo);

        // Validate emergency contact number
        printf("Enter your Emergency Contact Information: ");
        allocateStringInStruct(&user.personalInfo.emergencyContact);
        if (!isNumeric(user.personalInfo.emergencyContact) || strlen(user.personalInfo.emergencyContact) != 10) {
            printf("Invalid data: Emergency contact number must contain exactly 10 numeric characters. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        // Ensure emergency contact and phone number are different
        if (strcmp(user.personalInfo.emergencyContact, user.personalInfo.phoneNumber) == 0) {
            printf("Error: Emergency contact and phone number cannot be the same. Exiting program.\n");
            freeUser(&user);
            return 1;
        }

        // Taking payment information input
        printf("Enter your Payment Method: ");
        allocateStringInStruct(&user.paymentInfo.paymentMethod);

        // Select payment schedule
        user.paymentInfo.paymentSchedule = selectPaymentSchedule();

        // Taking agreement input
        printf("Do you agree to the gym's terms and conditions? (1 for Yes, 0 for No): ");
        scanf("%d", &user.agreement.termsAndConditions);
        getchar(); // clearing the buffer

        // Upload a picture for the signature
        printf("Enter the filename/path of the picture for your signature: ");
        allocateStringInStruct(&user.agreement.signatureFileName);

        // Displaying the entered information
        printf("\n\nPersonal Information:\n");
        printf("Full Name: %s\n", user.personalInfo.fullName);
        printf("Date of Birth: %s\n", user.personalInfo.dob);
        printf("Age: %d\n", user.personalInfo.age);
        printf("Address: %s\n", user.personalInfo.address);
        printf("Phone Number: %s\n", user.personalInfo.phoneNumber);
        printf("Email Address: %s\n", user.personalInfo.emailAddress);
        printf("Identification: %s\n", user.personalInfo.identification);
        printf("Health Information: %s\n", user.personalInfo.healthInfo);
        printf("Emergency Contact: %s\n", user.personalInfo.emergencyContact);

        printf("\n\nPayment Information:\n");
        printf("Payment Method: %s\n", user.paymentInfo.paymentMethod);
        printf("Monthly Package: %s\n", user.paymentInfo.paymentSchedule);
        printf("Price: %d rupees\n", user.paymentInfo.price);

        printf("\n\nAgreement Information:\n");
        printf("Terms and Conditions: %s\n", (user.agreement.termsAndConditions) ? "Agreed" : "Not Agreed");
        printf("Signature: %s\n", user.agreement.signatureFileName);

    } else {
        printf("Authentication failed. Exiting program.\n");
    }

    // Free allocated memory
    freeUser(&user);

    return 0;
}









