#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Customer
{
char name[50];
char phone[15];
float call_duration; // in minutes
struct Customer *next;
};
struct Customer *head = NULL;
// Function prototypes
void addCustomer();
void viewCustomers();
struct Customer* searchCustomer(const char *phone);
void modifyCustomer();
void deleteCustomer();
void generateBill();
void menu();
int main()
{
menu();
return 0;
}
void menu()
{
int choice;
do
{
printf("\n--- TELECOM BILLING SYSTEM ---\n");
printf("1. Add Customer\n");
printf("2. View Customers\n");
printf("3. Search Customer\n");
printf("4. Modify Customer\n");
printf("5. Delete Customer\n");
printf("6. Generate Bill\n");
printf("0. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
getchar(); // Clear newline
switch (choice)
{
case 1: addCustomer(); break;
case 2: viewCustomers(); break;
case 3:
{
char phone[15];
printf("Enter phone number to search: ");
scanf("%s", phone);
struct Customer *found = searchCustomer(phone);
if (found)
{
printf("Customer Found: %s, Phone: %s,Duration: %.2f min\n", found->name, found->phone,
found->call_duration);
}
else
{
printf("Customer not found.\n");
}
break;
}
case 4: modifyCustomer(); break;
case 5: deleteCustomer(); break;
case 6: generateBill(); break;
case 0: printf("Exiting...\n"); break;
default: printf("Invalid choice.\n");
}
} while (choice != 0);
}
void addCustomer()
{
struct Customer *new_cust = (struct
Customer*)malloc(sizeof(struct Customer));
printf("Enter name: ");
fgets(new_cust->name, 50, stdin);
new_cust->name[strcspn(new_cust->name, "\n")] = 0; // Removenewline
printf("Enter phone number: ");
scanf("%s", new_cust->phone);
printf("Enter call duration (in minutes): ");
scanf("%f", &new_cust->call_duration);
new_cust->next = head;
head = new_cust;
printf("Customer added successfully.\n");
}
void viewCustomers()
{
struct Customer *temp = head;
if (!temp)
{
printf("No records to show.\n");
return;
}
printf("\n--- Customer Records ---\n");
while (temp)
{
printf("Name: %s, Phone: %s, Duration: %.2f min\n",
temp->name, temp->phone, temp->call_duration);
temp = temp->next;
}
}
struct Customer* searchCustomer(const char *phone)
{
struct Customer *temp = head;
while (temp)
{
if (strcmp(temp->phone, phone) == 0)
{
return temp;
}
temp = temp->next;
}
return NULL;
}
void modifyCustomer()
{
char phone[15];
printf("Enter phone number to modify: ");
scanf("%s", phone);
struct Customer *cust = searchCustomer(phone);
if (!cust)
{
printf("Customer not found.\n");
return;
}
getchar(); // Clear newline
printf("Enter new name: ");
fgets(cust->name, 50, stdin);
cust->name[strcspn(cust->name, "\n")] = 0;
printf("Enter new call duration (in minutes): ");
scanf("%f", &cust->call_duration);
printf("Customer modified successfully.\n");
}
void deleteCustomer()
{
char phone[15];
printf("Enter phone number to delete: ");
scanf("%s", phone);
struct Customer *temp = head, *prev = NULL;
while (temp)
{
if (strcmp(temp->phone, phone) == 0)
{
if (prev == NULL)
{
head = temp->next;
}
else
{
prev->next = temp->next;
}
free(temp);
printf("Customer deleted successfully.\n");
return;
}
prev = temp;
temp = temp->next;
}
printf("Customer not found.\n");
}
void generateBill()
{
char phone[15];
printf("Enter phone number to generate bill: ");
scanf("%s", phone);
struct Customer *cust = searchCustomer(phone);
if (!cust)
{
printf("Customer not found.\n");
return;
}
float rate_per_min = 0.5; // Fixed rate
float total = cust->call_duration * rate_per_min;
printf("\n--- BILL ---\n");
printf("Name: %s\n", cust->name);
printf("Phone: %s\n", cust->phone);
printf("Duration: %.2f min\n", cust->call_duration);
printf("Amount Due: Rs %.2f\n", total);
}
