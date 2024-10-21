#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PATIENTS 100

struct Patient {
    char name[100];
    int age;
    char gender[10];
    char contact[15];
    char email[100];
    char address[200];
    char emergencyContact[15];
    char medicalHistory[500];
    char diagnosis[200];
    char doctorName[100];
    time_t checkupDate;
};

void addPatient(struct Patient patients[], int *patientCount);
void viewPatientHistory(struct Patient patients[], int patientCount);
void checkupReminder(struct Patient patients[], int patientCount);
void healthAnalytics(struct Patient patients[], int patientCount);
int validateGender(char gender[]);
int validateContact(char contact[]);
int validateAge(int age);
int validateEmail(char email[]);
void formatName(char *str);
int inputDate(struct tm *dateStruct);

int main() {
    struct Patient patients[MAX_PATIENTS];
    int patientCount = 0;
    int choice;

    while (1) {
        printf("\n===== Automated Health Monitoring System =====\n");
        printf("1. Add Patient Information\n");
        printf("2. View Patient History\n");
        printf("3. Checkup Reminder\n");
        printf("4. View Health Analytics\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                viewPatientHistory(patients, patientCount);
                break;
            case 3:
                checkupReminder(patients, patientCount);
                break;
            case 4:
                healthAnalytics(patients, patientCount);
                break;
            case 5:
                printf("Team Name: AlgoRhythm\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

void addPatient(struct Patient patients[], int *patientCount) {
    if (*patientCount >= MAX_PATIENTS) {
        printf("Maximum number of patients reached.\n");
        return;
    }

    struct Patient newPatient;
    int valid = 0;

    printf("Enter patient's name: ");
    getchar();
    fgets(newPatient.name, 100, stdin);
    newPatient.name[strlen(newPatient.name) - 1] = '\0';
    formatName(newPatient.name);

    do {
        printf("Enter patient's age: ");
        scanf("%d", &newPatient.age);
        if (validateAge(newPatient.age)) {
            valid = 1;
        } else {
            printf("Invalid age. Please enter a valid age between 0 and 120.\n");
        }
    } while (!valid);
    valid = 0;

    do {
        printf("Enter patient's gender (Male/Female/Other): ");
        scanf("%s", newPatient.gender);
        if (validateGender(newPatient.gender)) {
            valid = 1;
        } else {
            printf("Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n");
        }
    } while (!valid);
    valid = 0;

    do {
        printf("Enter patient's contact number (10-15 digits): ");
        scanf("%s", newPatient.contact);
        if (validateContact(newPatient.contact)) {
            valid = 1;
        } else {
            printf("Invalid contact number. Please enter a valid number.\n");
        }
    } while (!valid);
    
    do {
        printf("Enter patient's email: ");
        scanf("%s", newPatient.email);
        if (validateEmail(newPatient.email)) {
            valid = 1;
        } else {
            printf("Invalid email format. Please enter a valid email.\n");
        }
    } while (!valid);
    valid = 0;

    printf("Enter patient's address: ");
    getchar();
    fgets(newPatient.address, 200, stdin);
    newPatient.address[strlen(newPatient.address) - 1] = '\0';

    do {
        printf("Enter patient's emergency contact (10-15 digits): ");
        scanf("%s", newPatient.emergencyContact);
        if (validateContact(newPatient.emergencyContact)) {
            valid = 1;
        } else {
            printf("Invalid emergency contact number. Please enter a valid number.\n");
        }
    } while (!valid);

    printf("Enter patient's medical history: ");
    getchar();
    fgets(newPatient.medicalHistory, 500, stdin);
    newPatient.medicalHistory[strlen(newPatient.medicalHistory) - 1] = '\0';

    printf("Enter patient's diagnosis: ");
    fgets(newPatient.diagnosis, 200, stdin);
    newPatient.diagnosis[strlen(newPatient.diagnosis) - 1] = '\0';

    printf("Enter doctor's name: ");
    fgets(newPatient.doctorName, 100, stdin);
    newPatient.doctorName[strlen(newPatient.doctorName) - 1] = '\0';
    formatName(newPatient.doctorName);

    printf("Enter the next checkup date (DD-MM-YYYY): ");
    struct tm checkupDate = {0};
    if (inputDate(&checkupDate)) {
        newPatient.checkupDate = mktime(&checkupDate);
        patients[*patientCount] = newPatient;
        (*patientCount)++;
        printf("Patient information added successfully.\n");
    } else {
        printf("Invalid date format. Patient not added.\n");
    }
}

void viewPatientHistory(struct Patient patients[], int patientCount) {
    if (patientCount == 0) {
        printf("No patient records available.\n");
        return;
    }

    char name[100];
    printf("Enter the patient's name to view history: ");
    getchar();
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';
    formatName(name);

    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, name) == 0) {
            printf("\nPatient Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %s\n", patients[i].gender);
            printf("Contact: %s\n", patients[i].contact);
            printf("Email: %s\n", patients[i].email);
            printf("Address: %s\n", patients[i].address);
            printf("Emergency Contact: %s\n", patients[i].emergencyContact);
            printf("Medical History: %s\n", patients[i].medicalHistory);
            printf("Diagnosis: %s\n", patients[i].diagnosis);
            printf("Doctor's Name: %s\n", patients[i].doctorName);

            char checkupDateStr[100];
            strftime(checkupDateStr, sizeof(checkupDateStr), "%d-%m-%Y", localtime(&patients[i].checkupDate));
            printf("Next Checkup Date: %s\n", checkupDateStr);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient not found.\n");
    }
}

void checkupReminder(struct Patient patients[], int patientCount) {
    time_t currentTime;
    time(&currentTime);

    printf("\nUpcoming Checkups:\n");
    int upcomingFound = 0;

    for (int i = 0; i < patientCount; i++) {
        double diffDays = difftime(patients[i].checkupDate, currentTime) / (60 * 60 * 24);

        if (diffDays <= 30 && diffDays >= 0) {
            printf("Patient Name: %s, Checkup Date: %s", patients[i].name, ctime(&patients[i].checkupDate));
            upcomingFound = 1;
        }
    }

    if (!upcomingFound) {
        printf("No upcoming checkups in the next 30 days.\n");
    }
}

void healthAnalytics(struct Patient patients[], int patientCount) {
    if (patientCount == 0) {
        printf("No data available for analytics.\n");
        return;
    }

    int maleCount = 0, femaleCount = 0, otherCount = 0, totalAge = 0;

    for (int i = 0; i < patientCount; i++) {
        totalAge += patients[i].age;
        if (strcasecmp(patients[i].gender, "Male") == 0) {
            maleCount++;
        } else if (strcasecmp(patients[i].gender, "Female") == 0) {
            femaleCount++;
        } else if (strcasecmp(patients[i].gender, "Other") == 0) {
            otherCount++;
        }
    }

    printf("\nHealth Analytics:\n");
    printf("Total Patients: %d\n", patientCount);
    printf("Average Age: %.2f\n", (double)totalAge / patientCount);
    printf("Male Patients: %d\n", maleCount);
    printf("Female Patients: %d\n", femaleCount);
    printf("Other Gender Patients: %d\n", otherCount);
}


int validateGender(char gender[]) {
    if (strcasecmp(gender, "Male") == 0 || strcasecmp(gender, "Female") == 0 || strcasecmp(gender, "Other") == 0) {
        return 1;
    }
    return 0;
}

int validateContact(char contact[]) {
    for (int i = 0; i < strlen(contact); i++) {
        if (!isdigit(contact[i])) {
            return 0;
        }
    }
    int len = strlen(contact);
    return (len >= 10 && len <= 15);
}

int validateEmail(char email[]) {
    int atFound = 0, dotFound = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atFound = 1;
        } else if (atFound && email[i] == '.') {
            dotFound = 1;
        }
    }
    return (atFound && dotFound);
}

int validateAge(int age) {
    return (age >= 0 && age <= 120);
}

void formatName(char *str) {
    str[0] = toupper(str[0]);
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i - 1] == ' ') {
            str[i] = toupper(str[i]);
        } else {
            str[i] = tolower(str[i]);
        }
    }
}

int inputDate(struct tm *dateStruct) {
    char dateStr[11];
    scanf("%s", dateStr);
    
    if (sscanf(dateStr, "%2d-%2d-%4d", &dateStruct->tm_mday, &dateStruct->tm_mon, &dateStruct->tm_year) != 3) {
        return 0;
    }
    
    dateStruct->tm_mon -= 1;
    dateStruct->tm_year -= 1900;

    if (dateStruct->tm_mday < 1 || dateStruct->tm_mday > 31 ||
        dateStruct->tm_mon < 0 || dateStruct->tm_mon > 11 ||
        dateStruct->tm_year < 0) {
        return 0;
    }

    return 1;
}
