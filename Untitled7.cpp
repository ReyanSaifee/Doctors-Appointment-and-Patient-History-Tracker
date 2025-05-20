#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char history[200];
};

struct Appointment {
    int patientId;
    char doctor[50];
    char date[20];
    char time[10];
};

// Check if patient exists
int patientExists(int id) {
    FILE *fp = fopen("patients.txt", "r");
    if (!fp) return 0;
    struct Patient p;
    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        scanf(line, "%d|%*[^|]|%*d|%*[^|]|%*s", &p.id);
        if (p.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Add new patient
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "a");

    printf("Patient ID: ");
    scanf("%d", &p.id);
    getchar(); // remove newline

    printf("Name: ");
    fgets(p.name, sizeof(p.name),stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = '\0';

    printf("Medical History: ");
    fgets(p.history, sizeof(p.history), stdin);
    p.history[strcspn(p.history, "\n")] = '\0';

    fprintf(fp, "%d|%s|%d|%s|%s\n", p.id, p.name, p.age, p.gender, p.history);
    fclose(fp);
    printf("Patient added.\n");
}

// View patient by ID
void viewPatientHistory() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    int id, found = 0;
    char line[300];

    printf("Enter Patient ID: ");
    scanf("%d", &id);
    getchar();

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%49[^|]|%d|%9[^|]|%199[^\n]", &p.id, p.name, &p.age, p.gender, p.history);
        if (p.id == id) {
            printf("\n--- Patient History ---\n");
            printf("Name: %s\nAge: %d\nGender: %s\nHistory: %s\n", p.name, p.age, p.gender, p.history);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Error: Patient with ID %d not found.\n", id);

    fclose(fp);
}

// Schedule appointment
void scheduleAppointment() {
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "a");

    printf("Patient ID: ");
    scanf("%d", &a.patientId);
    getchar();

    printf("Date (YYYY-MM-DD): ");
    fgets(a.date, sizeof(a.date), stdin);
    a.date[strcspn(a.date, "\n")] = '\0';

    printf("Time (e.g., 1030): ");
    fgets(a.time, sizeof(a.time), stdin);
    a.time[strcspn(a.time, "\n")] = '\0';

    printf("Doctor Name: ");
    fgets(a.doctor, sizeof(a.doctor), stdin);
    a.doctor[strcspn(a.doctor, "\n")] = '\0';

    fprintf(fp, "%d|%s|%s|%s\n", a.patientId, a.doctor, a.date, a.time);
    fclose(fp);
    printf("Appointment scheduled.\n");
}

// View all appointments
void viewAppointments() {
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "r");
    char line[256];

    printf("\n--- Appointments ---\n");
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%49[^|]|%19[^|]|%9[^\n]", &a.patientId, a.doctor, a.date, a.time);

        int h = 0, m = 0;
        sscanf(a.time, "%d", &h);
        if (strlen(a.time) > 2) {
            m = h % 100;
            h = h / 100;
        }

        printf("Patient ID: %d\nDoctor: %s\nDate: %s\nTime: %02d:%02d\n\n", a.patientId, a.doctor, a.date, h, m);
    }

    fclose(fp);
}

// Main menu
int main() {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Add Patient\n2. View Patient History\n3. Schedule Appointment\n4. View Appointments\n5. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatientHistory(); break;
            case 3: scheduleAppointment(); break;
            case 4: viewAppointments(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

