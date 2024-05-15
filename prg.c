#include <stdio.h>
#include <string.h>

// 1. a.
// struct datatype for person having a Bank Account XYZ
struct Person
{
    char name[100];
    char sex;
    double amount;
    int age;
    long int bank_no;
    long int phone_no;
    int is_suspended; // It's of to use int as boolean, but remember it should be only 0 and 1!
};

struct Person person_details[100];
int size = 0;
long int bank_no = 100010001000;

// 1. b. create person
int createPerson(char name[], char sex, double amount, int age, long int phone_no)
{
    for (int i = 0; i < size; i++)
    {
        // 1. e.
        if (person_details[i].phone_no == phone_no)
        {
            printf("Bank account with the mobile no. %ld already exist!\n", phone_no);
            return -1;
        }
    }
    person_details[size].amount = amount;
    person_details[size].phone_no = phone_no;
    person_details[size].age = age;
    strcpy(person_details[size].name, name);
    person_details[size].sex = sex;
    person_details[size].bank_no = bank_no + size;            // unique bank number
    person_details[size].is_suspended = amount < 500 ? 1 : 0; // 0 means false
    size = size + 1;
    return 0;
}

// 1. c. deposit and withdraw some amount from bank acc
int deposit(long int bank_no, double dep_amount)
{
    int i;
    int found_bank_acc = -1;
    for (i = 0; i < size; i++)
    {
        if (person_details[i].bank_no == bank_no)
        {
            found_bank_acc = 1;
            break;
        }
    }

    // Error handling
    if (found_bank_acc == -1)
    {
        printf("Invalid bank account number!\n");
        return -1;
    }
    else
    {
        if (person_details[i].is_suspended == 1)
        {
            printf("Sorry, your bank account has been suspended!\n");
            return -1;
        }
        else
        {
            person_details[i].amount = person_details[i].amount + dep_amount;
            printf("You have successfully deposited Rs %f!\n", dep_amount);
            return 0;
        }
    }
}
int withdraw(long int bank_no, double withdraw_amount)
{
    int i;
    int found_bank_acc = -1;
    for (i = 0; i < size; i++)
    {
        if (person_details[i].bank_no == bank_no)
        {
            found_bank_acc = 1;
            break;
        }
    }
    // Error handling
    if (found_bank_acc == -1)
    {
        printf("Invalid bank account number!\n");
        return -1;
    }
    else
    {
        if (person_details[i].is_suspended == 1)
        {
            printf("Sorry, your bank account has been suspended!\n");
            return -1;
        }
        else
        {
            if (person_details[i].amount < withdraw_amount)
            {
                printf("Sorry, your balance is low %f!\n", person_details[i].amount);
                return -1;
            }
            else
            {
                person_details[i].amount = person_details[i].amount - withdraw_amount;
                printf("You have successfully withdraw Rs %f!\n", withdraw_amount);
                // only after withdraw we can calculate the is_suspended value
                // 1. d.
                if (person_details[i].amount < 500)
                {
                    person_details[i].is_suspended = 1; // 1 means true
                }
                return 0;
            }
        }
    }
}

// 1. f. Send money
int send_money(long int src_bank_no, long int dest_bank_no, double amount)
{
    int i, j;
    int src_found_bank_acc = -1;
    int dest_found_bank_acc = -1;
    for (i = 0; i < size; i++)
    {
        if (person_details[i].bank_no == src_bank_no)
        {
            src_found_bank_acc = 1;
            break;
        }
    }
    if (src_found_bank_acc == -1)
    {
        printf("Source Bank Account no. is Invalid!\n");
        return -1;
    }
    if (person_details[i].is_suspended == 1) {
        printf("Sorry, src bank account has been suspended!\n");
        return -1;
    }

    for (j = 0; j < size; j++)
    {
        if (person_details[j].bank_no == dest_bank_no)
        {
            dest_found_bank_acc = 1;
            break;
        }
    }
    if (dest_found_bank_acc == -1)
    {
        printf("Destination Bank Account no. is Invalid!\n");
        return -1;
    }
    if (person_details[j].is_suspended == 1)
    {
        printf("Sorry, dest bank account has been suspended!\n");
        return -1;
    }

    if (withdraw(src_bank_no, amount) == 0)
    {
        deposit(dest_bank_no, amount);
        printf("Successfully the transaction has been compeleted!\n");
        return 0;
    }
    else
    {
        printf("Transaction has failed!\n");
        return -1;
    }
}

// Helper Function
void print_person(int index_no)
{
    printf("%s \t %c \t %ld \t %d \t %ld \t %f\n", person_details[index_no].name, person_details[index_no].sex,
           person_details[index_no].phone_no, person_details[index_no].age,
           person_details[index_no].bank_no, person_details[index_no].amount);
}
// 1. g.
void print_unsuspended_person()
{
    for (int i = 0; i < size; i++)
    {
        if (person_details[i].is_suspended == 0)
        {
            print_person(i);
        }
    }
}

// helper function
void print_all()
{
    for (int i = 0; i < size; i++)
    {
        print_person(i);
    }
}

// helper function
void initially_persons()
{
    char names[100][100] = {"Sam", "Alan", "Alex", "Rose", "Violet"};
    char sex[10] = {'M', 'M', 'M', 'F', 'F'};
    double amounts[10] = {30000, 20000, 40000, 50000, 10000};
    int age[10] = {25, 26, 27, 32, 24};
    long int phone_no[10] = {8178921232, 8178921233, 8178921235, 8178921237, 8178921239};
    for (int i = 0; i < 5; i++)
    {
        createPerson(names[i], sex[i], amounts[i], age[i], phone_no[i]);
    }
}

int main()
{
    int choice;

    char name[100];
    char sex;
    double amount;
    int age;
    long int phone_no;

    long int src_bank_no;
    long int dest_bank_no;

    initially_persons();
    while (1)
    {
        printf("Menu Driven Program: Enter your choice!\n");
        printf("1. Create a New Person\n");
        printf("2. Deposit a Amount to a Bank no.\n");
        printf("3. Withdraw a Amount from a Bank no.\n");
        printf("4. Send Money from account 'A' to account 'B'\n");
        printf("5. Print All!\n");
        printf("6. Print Only Unsuspended Accounts\n");
        printf("7. Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nEnter person name: ");
            getchar();
            scanf("%s", name);
            printf("\nEnter person sex (M | F | O): ");
            getchar();
            scanf("%c", &sex);
            printf("\nEnter person age: ");
            scanf("%d", &age);
            printf("\nEnter mobile no.: ");
            scanf("%ld", &phone_no);
            printf("\nEnter person initially amount (>= 500): ");
            scanf("%lf", &amount);
            createPerson(name, sex, amount, age, phone_no);
        }
        else if (choice == 2)
        {
            printf("\nEnter person bank no.: ");
            scanf("%ld", &src_bank_no);
            printf("\nEnter person amount: ");
            scanf("%lf", &amount);
            deposit(src_bank_no, amount);
        }
        else if (choice == 3)
        {
            printf("\nEnter person bank no.: ");
            scanf("%ld", &src_bank_no);
            printf("\nEnter person amount: ");
            scanf("%lf", &amount);
            withdraw(src_bank_no, amount);
        }
        else if (choice == 4)
        {
            printf("\nEnter src person bank no.: ");
            scanf("%ld", &src_bank_no);
            printf("\nEnter dest person bank no.: ");
            scanf("%ld", &dest_bank_no);
            printf("\nEnter person amount: ");
            scanf("%lf", &amount);
            send_money(src_bank_no, dest_bank_no, amount);
        }
        else if (choice == 5)
        {
            printf("Name \t Sex \t Phone_no \t Age \t Bank_no \t Amount\n");
            print_all();
        }
        else if (choice == 6)
        {
            printf("Name \t Sex \t Phone_no \t Age \t Bank_no \t Amount\n");
            print_unsuspended_person();
        }
        else if (choice == 7)
        {
            printf("Thank You!!\n");
            return 0;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}