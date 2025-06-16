
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_USERS 100
#define MAX_CUSTOMERS 50
#define MAX_ROOMS 50

#define SINGLE 1
#define DOUBLE 2
#define DISCOUNT_RATE 0.1f

typedef struct
{
    char email[50];
    char password[50];
} User;

typedef struct
{
    int id;
    int number;
    int isBooked;
} Room;

typedef struct
{
    char name[50];
    int nights;
    int roomID;
    int roomNo;
    int roomType;
    int hasDiscount;
    float bill;
    char feedback[200];
} Customer;

// Global Data
User users[MAX_USERS];
int totalUsers = 0;

Room rooms[MAX_ROOMS];
int roomCount = 20;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;
float grandTotal = 0.0f;
char confirmation;

// File I/O
void loadUsers();
void saveUsers();
void loadCustomers();
void saveCustomers();
void loadEarnings();
void saveEarnings();
void loadrooms();
void saverooms();

//  Utility
int isUserPresent(const char *email);
void addUser(const char *email, const char *password);
int validateUser(const char *email, const char *password);
int parseRoomType(const char *input);
int getAvailableRoom();
int findRoomIndexByID(int roomID);
int findCustomerByName(const char *name);

// Bookings + more
void calculateBill(Customer *c);
void printReceipt(Customer *c);
void processPayment(Customer *c);
void bookRoom();
void viewroomtypes();
void viewvacantrooms();
void cancelBooking();
void giveFeedback();
void viewFeedback();
void addroom();
void showEarnings();
void userMenu();
void adminMenu();

int main()
{
    loadUsers();
    loadCustomers();
    loadEarnings();
    loadrooms();
    int choice;
    char email[50], password[50];

    while (1)
    {
        printf("\n===================================================================================================\n");
        printf("                                        Abdullah's Hotel<3 ");
        printf("\n===================================================================================================\n");
        printf("Welcome to the Abdullah's Hotel<3\nPlease Sign Up if you are a new user OR Sign In(Existing User /Admin)\n");
        printf("\n1.Sign Up\n2.Sign In\n3.Exit\nEnter your choice--> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            printf("\n===================================================================================================\n");
            printf("                                     Sign Up\n");
            printf("===================================================================================================\n");
            printf("\nEnter your email: ");

            scanf("%s", email);
            printf("Make a strong password: ");
            scanf("%s", password);
            system("cls");
            if (isUserPresent(email))
                printf("User already exists\n");
            else
                addUser(email, password);
            break;
        case 2:
            system("cls");

            printf("\n===================================================================================================\n");
            printf("                                     Sign Up\n");
            printf("===================================================================================================\n");
            printf("\nEnter your email: ");
            scanf("%s", email);
            printf("Enter your password: ");
            scanf("%s", password);

            if (strcmp(email, "admin") == 0 && strcmp(password, "1234") == 0)
                adminMenu();
            else if (validateUser(email, password))
                userMenu();
            else
            {
                printf("Invalid\n");
                getch();
            }
            break;
        case 3:
            saveUsers();
            saveCustomers();
            saveEarnings();
            saverooms();

            return 0;
        default:
            printf("Invalid\n");
            getch();
        }
    }
}

// ---------------- Menus -------------------
void userMenu()
{
    int c;
    do
    {
        system("cls");
        printf("\n===================================================================================================\n");
        printf("                                        Abdullah's Hotel<3 ");
        printf("\n===================================================================================================\n");

        printf("\n                      Welcome! %s :)\n", users->email);
        printf("===================================================================================================\n");

        printf("\n1.View Room Types\n2.Book a Room\n3.Cancel Booking\n4.Give Feedback\n5.Logout\nEnter your choice--> ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            viewroomtypes();
            break;
        case 2:
            bookRoom();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            giveFeedback();
        case 5:
            return;
        default:
            printf("Invalid\n");
            getch();
        }
    } while (1);
}

void adminMenu()
{
    int c;
    do
    {
        system("cls");
        printf("\n===================================================================================================\n");
        printf("                                   Welcome  Abdullah <3 ");
        printf("\n===================================================================================================\n");
        printf("1.View Bookings\n2.View Vacant Rooms\n3.Add Rooms\n4.View Feedback\n5.Show Earnings\n6.Logout\nEnter your choice--> ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            for (int i = 0; i < customerCount; i++)
                printf("%s - Room %d (%d nights)\n", customers[i].name, customers[i].roomNo, customers[i].nights);
            getch();
            break;
        case 2:
            viewvacantrooms();
            break;
        case 3:
            addroom();
            break;
        case 4:
            viewFeedback();
            break;
        case 5:
            showEarnings();
            break;
        case 6:
            return;
        default:
            printf("Invalid\n");
            getch();
        }
    } while (1);
}

//  File I/O
void loadUsers()
{
    FILE *f = fopen("users.txt", "r");
    if (!f)
        return;
    while (fscanf(f, "%s %s", users[totalUsers].email, users[totalUsers].password) == 2)
        totalUsers++;
    fclose(f);
}

void saveUsers()
{
    FILE *f = fopen("users.txt", "w");
    for (int i = 0; i < totalUsers; i++)
        fprintf(f, "%s %s\n", users[i].email, users[i].password);
    fclose(f);
}

void loadCustomers()
{
    FILE *f = fopen("customers.txt", "r");
    if (!f)
        return;
    while (fscanf(f, "%[^,],%d,%d,%d,%d,%f,%[^\n]\n",
                  customers[customerCount].name,
                  &customers[customerCount].nights,
                  &customers[customerCount].roomID,
                  &customers[customerCount].roomNo,
                  &customers[customerCount].roomType,
                  &customers[customerCount].bill,
                  customers[customerCount].feedback) == 7)
        customerCount++;
    fclose(f);
}

void saveCustomers()
{
    FILE *f = fopen("customers.txt", "w");
    for (int i = 0; i < customerCount; i++)
    {
        fprintf(f, "%s,%d,%d,%d,%d,%.2f,%s\n",
                customers[i].name,
                customers[i].nights,
                customers[i].roomID,
                customers[i].roomNo,
                customers[i].roomType,
                customers[i].bill,
                customers[i].feedback);
    }
    fclose(f);
}

void loadEarnings()
{
    FILE *f = fopen("earnings.txt", "r");
    if (f)
    {
        fscanf(f, "%f", &grandTotal);
        fclose(f);
    }
}

void saveEarnings()
{
    FILE *f = fopen("earnings.txt", "w");
    if (f)
    {
        fprintf(f, "%.2f", grandTotal);
        fclose(f);
    }
}
void loadrooms()
{
    FILE *f = fopen("rooms.txt", "r");
    if (!f)
        return;
    roomCount = 0;
    while (fscanf(f, "%d %d %d", &rooms[roomCount].id, &rooms[roomCount].number, &rooms[roomCount].isBooked) == 3)
        roomCount++;
    fclose(f);
}
void saverooms()
{
    FILE *f = fopen("rooms.txt", "w");
    for (int i = 0; i < roomCount; i++)
        fprintf(f, "%d %d %d\n", rooms[i].id, rooms[i].number, rooms[i].isBooked);
    fclose(f);
}
// --------------- Utility --------------------
int isUserPresent(const char *email)
{
    for (int i = 0; i < totalUsers; i++)
        if (strcmp(users[i].email, email) == 0)
            return 1;
    return 0;
}

void addUser(const char *email, const char *password)
{
    if (totalUsers < MAX_USERS)
    {
        strcpy(users[totalUsers].email, email);
        strcpy(users[totalUsers].password, password);
        totalUsers++;
        saveUsers();
    }
}

int validateUser(const char *email, const char *password)
{
    for (int i = 0; i < totalUsers; i++)
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0)
            return 1;
    return 0;
}

int parseRoomType(const char *input)
{
    if (strcmp(input, "single") == 0)
        return SINGLE;
    if (strcmp(input, "double") == 0)
        return DOUBLE;
    return 0;
}

int getAvailableRoom()
{ // simple first-free logic
    for (int i = 0; i < roomCount; i++)
        if (!rooms[i].isBooked)
            return i;
    return -1;
}

int findRoomIndexByID(int roomID)
{
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].id == roomID)
            return i;
    return -1;
}

int findCustomerByName(const char *name)
{
    for (int i = 0; i < customerCount; i++)
        if (strcmp(customers[i].name, name) == 0)
            return i;
    return -1;
}

// booking starts here
void calculateBill(Customer *c)
{
    float rate = (c->roomType == SINGLE) ? 2000 : 3500;
    c->bill = rate * c->nights;
    if (c->hasDiscount)
        c->bill -= c->bill * DISCOUNT_RATE;
}

void printReceipt(Customer *c)
{
    system("cls");
    printf("======================================\n");
    printf("\n========== Booking Receipt ==========\n");
    printf("=======================================\n");

    printf("Name       : %s\n", c->name);
    printf("Room No    : %d\n", c->roomNo);
    printf("Room Type  : %s\n", c->roomType == SINGLE ? "Single" : "Double");
    printf("Nights     : %d\n", c->nights);
    printf("Bill       : %.2f\n", c->bill);
    printf("=====================================\n");
}

void processPayment(Customer *c)
{
    float paid = 0, due = c->bill;
    while (1)
    {
        printf("Pay: ");
        scanf("%f", &paid);
        if (paid < due)
        {
            due -= paid;
            printf("Remaining: %.2f\n", due);
        }
        else
        {
            if (paid > due)
                printf("Change: %.2f\n", paid - due);

            break;
        }
    }
    printf("Payment complete. Thank you \n");
}

void bookRoom()
{
    system("cls");
    printf("======================================\n");
    printf("============ Room Booking ============\n");
    printf("======================================\n");

    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("Limit reached\n");
        getch();
        return;
    }

    Customer *c = &customers[customerCount];
    char typeInput[20], discountCode[50];

    printf("Name: ");
    getchar();
    fgets(c->name, 50, stdin);
    c->name[strcspn(c->name, "\n")] = 0;

    do
    {
        printf("Room type (single/double): ");
        scanf("%s", typeInput);
        c->roomType = parseRoomType(typeInput);
    } while (c->roomType == 0);

    do
    {
        printf("Nights: ");
        scanf("%d", &c->nights);
    } while (c->nights <= 0);

    do
    {
        printf("Do you have a discount code? (y/n): ");
        scanf(" %c", &confirmation);
        if (confirmation != 'y' && confirmation != 'n')
        {
            printf(" Invalid input. Please enter 'y' or 'n'.\n");
        }
    } while (confirmation != 'y' && confirmation != 'n');

    c->hasDiscount = 0;
    if (confirmation == 'y')
    {
        printf("Enter code: ");
        scanf("%s", discountCode);
        if (strcmp(discountCode, "newyear123") == 0)
        {
            c->hasDiscount = 1;
            printf(" Discount applied!\n");
        }
        else
            printf("Invalid discount code\n");
    }

    int rIndex = getAvailableRoom();
    if (rIndex == -1)
    {
        printf("No rooms\n");
        getch();
        return;
    }

    c->roomID = rooms[rIndex].id;
    c->roomNo = rooms[rIndex].number;
    rooms[rIndex].isBooked = 1;

    do
    {
        printf("Confirm booking (y/n): ");
        scanf(" %c", &confirmation);
        if (confirmation != 'y' && confirmation != 'n')
        {
            printf(" Please enter only 'y' or 'n'\n");
        }
    } while (confirmation != 'y' && confirmation != 'n');

    if (confirmation == 'y')
    {
        calculateBill(c);
        printReceipt(c);
        processPayment(c);
        grandTotal += c->bill;
        customerCount++;
        saveCustomers();
        saveEarnings();
        saverooms();
        printf("======================================\n");
        printf("             Room Booked\n");
        printf("======================================\n");
    }
    else
        rooms[rIndex].isBooked = 0;
    getch();
    system("cls");
}

void viewroomtypes()
{
    system("cls");
    printf("===================================\n");
    printf("============ Room Types ===========\n");
    printf("===================================\n");
    printf("1. Single Bed Room - 2000 PKR/Night\n");
    printf("2. Double Bed Room - 3500 PKR/Night\n");
    printf("===================================\n");
    getch();
    // system("cls");
}

void cancelBooking()
{
    char name[50];
    int roomID;
    system("cls");
    printf("=============================================\n");
    printf("============ Booking Cancellation ===========\n");
    printf("=============================================\n");

    printf("Enter your name: ");
    while (getchar() != '\n')
        ; // to remove previous \n

    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    int idx = findCustomerByName(name);
    if (idx == -1)
    {
        printf("Booking not found\n");
        getch();
        return;
    }

    printf("Your booking: Room ID %d, Room No %d\n", customers[idx].roomID, customers[idx].roomNo);
    printf("Enter Room ID to cancel: ");
    scanf("%d", &roomID);

    if (roomID != customers[idx].roomID)
    {
        printf("Room ID mismatch\n");
        getch();
        return;
    }

    int rIndex = findRoomIndexByID(roomID);
    if (rIndex != -1)
    {
        rooms[rIndex].isBooked = 0;
        saverooms();
    }

    grandTotal -= customers[idx].bill;

    for (int i = idx; i < customerCount - 1; i++)
        customers[i] = customers[i + 1];
    customerCount--;

    saveCustomers();
    saveEarnings();
    printf("=============================================\n");
    printf("              Booking cancelled\n");
    printf("=============================================\n");

    getch();
    system("cls");
}

void giveFeedback()
{
    char name[50];
    system("cls");
    printf("=============================================\n");
    printf("=============== Feedback Form ===============\n");
    printf("=============================================\n");
    printf("Enter your name: ");
    scanf("%s", name);

    int idx = findCustomerByName(name);
    if (idx == -1)
    {
        printf("Booking required for feedback\n");
        getch();
        return;
    }

    printf("Your feedback: \n");
    getchar();
    fgets(customers[idx].feedback, 200, stdin);
    customers[idx].feedback[strcspn(customers[idx].feedback, "\n")] = 0;

    saveCustomers();
    printf("=============================================\n");
    printf("             Thanks for feedback!\n");
    printf("=============================================\n");

    getch();
}

void viewvacantrooms()
{
    system("cls");
    printf("=============================================\n");
    printf("================== Vacant Rooms =============\n");
    printf("=============================================\n");

    int vacantCount = 0;

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].isBooked == 0)
        {
            printf("Room ID: %d | Room No: %d\n", rooms[i].id, rooms[i].number);
            vacantCount++;
        }
    }

    if (vacantCount == 0)
    {
        printf("No rooms are currently available.\n");
    }
    else
    {
        printf("\nTotal vacant rooms: %d\n", vacantCount);
    }

    printf("=============================================\n");
    getch();
}

void viewFeedback()
{
    system("cls");
    printf("=============================================\n");
    printf("================ Feedback's List ============\n");
    printf("=============================================\n");
    for (int i = 0; i < customerCount; i++)
        if (strlen(customers[i].feedback) > 0)
            printf("%s: %s\n", customers[i].name, customers[i].feedback);
    printf("=============================================\n");

    getch();
}
void addroom() {
    if (roomCount >= MAX_ROOMS) {
        printf(" Cannot add more rooms. Limit reached.\n");
        getch();
        return;
    }

    int id, number;
    printf("=============================================\n");
    printf("=============== Add New Room ================\n");
    printf("=============================================\n");
    
    do {
        printf("Enter new Room ID (numeric): ");
        scanf("%d", &id);

        int exists = 0;
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].id == id) {
                printf("Room ID already exists. Try another.\n");
                exists = 1;
                break;
            }
        }

        if (!exists) break;
    } while (1);

    printf("Enter Room Number (e.g., 110): ");
    scanf("%d", &number);

    
    rooms[roomCount].id = id;
    rooms[roomCount].number = number;
    rooms[roomCount].isBooked = 0;
    roomCount++;

    saverooms(); 

    printf(" Room added successfully.\n");
    getch();
}


void showEarnings()
{
    system("cls");
    printf("=============================================");

    printf("\n=================== Revenue ================\n");
    printf("=============================================\n");

    for (int i = 0; i < customerCount; i++)
        printf("%s : %.2f\n", customers[i].name, customers[i].bill);
    printf("=============================================\n");
    printf("Total: %.2f\n", grandTotal);
    printf("=============================================\n");

    getch();
}
