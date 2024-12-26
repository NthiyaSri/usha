#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototypes
void createAccount();
int validateEmail(const char *email);
int validatePassword(const char *password);
int login(char *loggedInEmail);
void createProfile(const char *email);
void showProfile(const char *email);
int validatePhoneNumber(const char *phone);
void calculatePF(const char *email);

int main() {
    int choice;
    char loggedInEmail[100];
    
    while (1) {
        printf("\n===== Employee Record System =====\n");
        printf("1. Create an Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                if (login(loggedInEmail)) {
                    printf("Login successful!\n");
                    int profileChoice;
                    while (1) {
                        printf("\n===== After Login =====\n");
                        printf("1. View Profile\n");
                        
                        printf("2. PF (Provident Fund)\n");
                        printf("3. Package (Feature Placeholder)\n");
                        printf("4. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &profileChoice);
                        
                        switch (profileChoice) {
                            case 1:
                                createProfile(loggedInEmail);
                                break;
                            case 2:
                                calculatePF(loggedInEmail);
                                break;
                            case 3:
                                printf("Package feature is under development.\n");
                                break;
                            case 4:
                                printf("Logging out...\n");
                                goto logout;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    }
                logout:
                    break;
                } else {
                    printf("Invalid email or password. Try again.\n");
                }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

void createAccount() {
    char firstName[50], lastName[50], email[100], password[50];
    
    printf("\n===== Create an Account =====\n");
    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);
    
    do {
        printf("Enter email: ");
        scanf("%s", email);
        if (!validateEmail(email)) {
            printf("Invalid email format. Please try again.\n");
        }
    } while (!validateEmail(email));
    
    do {
        printf("Enter password (min 6 characters): ");
        scanf("%s", password);
        if (!validatePassword(password)) {
            printf("Password must be at least 6 characters long. Please try again.\n");
        }
    } while (!validatePassword(password));
    
    // Save the account to a file
    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL) {
        perror("Error opening accounts.txt for writing");
        return;
    }
    fprintf(file, "%s %s %s %s\n", firstName, lastName, email, password);
    fclose(file);
    
    printf("Account created successfully!\n");
}

int validateEmail(const char *email) {
    int atSymbol = 0, dot = 0;
    const char *p = email;

    while (*p) {
        if (*p == '@') {
            atSymbol++;
        } else if (*p == '.' && atSymbol) {
            dot++;
        }
        p++;
    }
    return (atSymbol == 1 && dot >= 1);
}

int validatePassword(const char *password) {
    return (strlen(password) >= 6);
}

int login(char *loggedInEmail) {
    char email[100], password[50], fileEmail[100], filePassword[50];
    char firstName[50], lastName[50];
    
    printf("\n===== Login =====\n");
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);
    
    // Read from the file
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        perror("Error opening accounts.txt for reading");
        return 0;
    }
    
    while (fscanf(file, "%s %s %s %s", firstName, lastName, fileEmail, filePassword) != EOF) {
        if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            strcpy(loggedInEmail, email); // Save logged-in email
            return 1;  // Login successful
        }
    }
    
    fclose(file);
    return 0;  // Login failed
}

void createProfile(const char *email) {
    int age, experience, salary, startYear, endYear;
    char phone[15], id[20];
    
    printf("\n===== Create Profile =====\n");
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter working experience (in years): ");
    scanf("%d", &experience);
    printf("Enter monthly salary: ");
    scanf("%d", &salary);
    printf("Enter employee ID: ");
    scanf("%s", id);
    printf("Enter start year: ");
    scanf("%d", &startYear);
    printf("Enter end year: ");
    scanf("%d", &endYear);
    
    do {
        printf("Enter phone number (10 digits): ");
        scanf("%s", phone);
        if (!validatePhoneNumber(phone)) {
            printf("Phone number must be exactly 10 digits and numeric. Please try again.\n");
        }
    } while (!validatePhoneNumber(phone));
    
    // Save the profile to a file
    FILE *file = fopen("profiles.txt", "a");
    if (file == NULL) {
        perror("Error opening profiles.txt for writing");
        return;
    }
    fprintf(file, "%s %d %d %d %s %d %d %s\n", email, age, experience, salary, id, startYear, endYear, phone);
    fclose(file);
    
    printf("Profile created successfully!\n");
}

void showProfile(const char *email) {
    char fileEmail[100], phone[15], id[20];
    int age, experience, salary, startYear, endYear;
    int found = 0;
    
    printf("\n===== View Profile =====\n");
    
    // Read from the file
    FILE *file = fopen("profiles.txt", "r");
    if (file == NULL) {
        perror("Error opening profiles.txt for reading");
        return;
    }
    
    while (fscanf(file, "%s %d %d %d %s %d %d %s", fileEmail, &age, &experience, &salary, id, &startYear, &endYear, phone) != EOF) {
        if (strcmp(email, fileEmail) == 0) {
            printf("Email: %s\n", fileEmail);
            printf("Age: %d\n", age);
            printf("Experience: %d years\n", experience);
            printf("Monthly Salary: %d\n", salary);
            printf("Employee ID: %s\n", id);
            printf("Working Period: %d - %d\n", startYear, endYear);
            printf("Phone Number: %s\n", phone);
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if (!found) {
        printf("No profile found for this email.\n");
    }
}

int validatePhoneNumber(const char *phone) {
    if (strlen(phone) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

void calculatePF(const char *email) {
    int salary, years, pfAmount;
    
    printf("\n===== PF (Provident Fund) Calculation =====\n");
    printf("Enter current salary: ");
    scanf("%d", &salary);
    printf("Enter working years: ");
    scanf("%d", &years);
    
    pfAmount = salary * 0.1 * years * 12;  // PF = 10% * months
    
    printf("\n===== PF Details =====\n");
    printf("Employee Email: %s\n", email);
    printf("Provident Fund Amount: %d\n", pfAmount);
}