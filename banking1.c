#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
struct transaction
{
    float amount;
    char type; 
};

struct user
{
    char phone[50];
    char ac[50];
    char password[50];
    char account_type[20]; 
    char admin_rights;     
    char customer_rights;  
    float balance;
    struct transaction transactions[100]; 
    int transaction_count;               
};
// Function to display the monthly balance sheet
void displayBalanceSheet(struct user usr)
{
    printf("\n\n------ Monthly Balance Sheet ------");
    printf("\nAccount Type: %s", usr.account_type);
    printf("\nAccount Holder: %s", usr.phone);
    printf("\nCurrent Balance: Rs %.2f", usr.balance);
    printf("\n\nTransaction History:");

    for (int i = 0; i < usr.transaction_count; i++)
    {
        printf("\nTransaction %d: Rs %.2f (%c)", i + 1, usr.transactions[i].amount,
               usr.transactions[i].type);
    }

    printf("\n------------------------------------\n");
}
void generateRandomAccountNumber(char *accountNumber)
{
    srand((unsigned int)time(NULL));

    // Generate a random 6-digit account number
    sprintf(accountNumber, "%06d", rand() % 1000000);
}
int main()
{

    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int opt, choice;
    char cont = 'y';
    float amount;
    const float MIN_CURRENT_ACCOUNT_BALANCE = -50000;
    const float MIN_SAVINGS_ACCOUNT_BALANCE = 50;
    const float MIN_OPENING_CURRENT_ACCOUNT_BALANCE = 5000;
    const float MIN_OPENING_SAVINGS_ACCOUNT_BALANCE = 100;
    const float CURRENT_ACCOUNT_SURCHARGE_RATE = 0.06;
    const float CURRENT_ACCOUNT_INTEREST_RATE = 0.04;
    const float SAVINGS_ACCOUNT_INTEREST_RATE = 0.05;
    const float DEBIT_CARD_CHARGE = 10;
    const float MESSAGE_SERVICE_CHARGE = 5;
    printf("\t\t\t*****BANKING SOFTWARE*****\t\t\t\n");
    printf("\n\t\t\t   -----Welcome Back-----\t\t");
    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d", &opt);

    if (opt == 1)
    {
        system("cls");
        // printf("Enter your account number:\t");
        // scanf("%s", usr.ac);
         generateRandomAccountNumber(usr.ac);
        printf("Account Number :\t%d\n",usr.ac);
        printf("Enter your phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);
        printf("Enter account type (Current/Savings):\t");
        scanf("%s", usr.account_type);
        printf("Do you have administrative rights? (y/n):\t");
        scanf(" %c", &usr.admin_rights);
        printf("Do you have customer rights? (y/n):\t");
        scanf(" %c", &usr.customer_rights);

        if (strcmp(usr.account_type, "Current") == 0)
        {
            // For Current Account
            usr.balance = MIN_OPENING_CURRENT_ACCOUNT_BALANCE;
        }
        else if (strcmp(usr.account_type, "Savings") == 0)
        {
            // For Savings Account
            usr.balance = MIN_OPENING_SAVINGS_ACCOUNT_BALANCE;
        }

        strcpy(filename, usr.phone);
        fp = fopen(strcat(filename, ".dat"), "w");
        if (fp != NULL)
        {
            fwrite(&usr, sizeof(struct user), 1, fp);
            printf("\n\nAccount successfully registered");
        }
        else
        {
            printf("\n\nSomething went wrong. Please try again");
        }
        fclose(fp);
    }

    if (opt == 2)
    {
        system("cls");
        printf("\nPhone number:\t");
        scanf("%s", phone);
        printf("Password:\t");
        scanf("%s", pword);
        strcpy(filename, phone);
        fp = fopen(strcat(filename, ".dat"), "r");
        if (fp == NULL)
        {
            printf("\nAccount number not registered");
        }
        else
        {
            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);
            if (!strcmp(pword, usr.password))
            {
                printf("\n\t\tWelcome %s", usr.phone);
                while (cont == 'y')
                {
                    system("cls");
                    printf("\n\nPress 1 for balance inquiry");
                    printf("\nPress 2 for depositing cash");
                    printf("\nPress 3 for cash withdrawal");
                    printf("\nPress 4 for online transfer");
                    printf("\nPress 5 for password change");
                    printf("\nPress 6 for debit card charge");
                    printf("\nPress 7 for text message service charge");
                    printf("\n\nYour choice:\t");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        printf("\nYour current balance is Rs.%.2f", usr.balance);
                        break;
                    case 2:
                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance += amount;
                        fp = fopen(filename, "w");
                        if (fp != NULL)
                        {
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            printf("\nSuccessfully deposited.");
                        }
                        fclose(fp);
                        break;
                        // Updated deposit functionality for different account types
                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance += amount;

                        // For Current Account: Check minimum balance and apply surcharge
                        if (strcmp(usr.account_type, "Current") == 0)
                        {
                            if (usr.balance < MIN_CURRENT_ACCOUNT_BALANCE)
                            {
                                usr.balance -= amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                printf("\nSurcharge applied on negative balance.");
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * CURRENT_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // For Savings Account: Check minimum balance and apply fine
                        else if (strcmp(usr.account_type, "Savings") == 0)
                        {
                            if (usr.balance < MIN_SAVINGS_ACCOUNT_BALANCE)
                            {
                                printf("\nBalance below minimum. Fine applied.");
                                usr.balance -= amount * 0.10; // Fine of 10%
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * SAVINGS_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // Write updated balance to file
                        fp = fopen(filename, "w");
                        if (fp != NULL)
                        {
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            printf("\nSuccessfully deposited.");
                        }
                        fclose(fp);
                        break;
                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance += amount;

                        // For Current Account: Check minimum balance and apply surcharge
                        if (strcmp(usr.account_type, "Current") == 0)
                        {
                            if (usr.balance < MIN_CURRENT_ACCOUNT_BALANCE)
                            {
                                usr.balance -= amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                printf("\nSurcharge applied on negative balance.");
                                usr.transactions[usr.transaction_count].amount =
                                    amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                usr.transactions[usr.transaction_count].type = 'S'; // 'S' for surcharge
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * CURRENT_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // For Savings Account: Check minimum balance and apply fine
                        else if (strcmp(usr.account_type, "Savings") == 0)
                        {
                            if (usr.balance < MIN_SAVINGS_ACCOUNT_BALANCE)
                            {
                                printf("\nBalance below minimum. Fine applied.");
                                usr.balance -= amount * 0.10; // Fine of 10%
                                usr.transactions[usr.transaction_count].amount = amount * 0.10;
                                usr.transactions[usr.transaction_count].type = 'F'; // 'F' for fine
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * SAVINGS_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // Record the transaction
                        usr.transactions[usr.transaction_count].amount = amount;
                        usr.transactions[usr.transaction_count].type = 'D'; // 'D' for deposit
                        usr.transaction_count++;

                        // Write updated balance to file
                        fp = fopen(filename, "w");
                        if (fp != NULL)
                        {
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            printf("\nSuccessfully deposited.");
                        }
                        fclose(fp);
                        break;
                        // case 2:
                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance += amount;

                        // Updated deposit functionality for different account types
                        if (strcmp(usr.account_type, "Current") == 0)
                        {
                            // For Current Account: Check minimum balance and apply surcharge
                            if (usr.balance < MIN_CURRENT_ACCOUNT_BALANCE)
                            {
                                usr.balance -= amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                printf("\nSurcharge applied on negative balance.");
                                usr.transactions[usr.transaction_count].amount = amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                usr.transactions[usr.transaction_count].type = 'S'; // 'S' for surcharge
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * CURRENT_ACCOUNT_INTEREST_RATE;
                            }
                        }
                        else if (strcmp(usr.account_type, "Savings") == 0)
                        {
                            // For Savings Account: Check minimum balance and apply fine
                            if (usr.balance < MIN_SAVINGS_ACCOUNT_BALANCE)
                            {
                                printf("\nBalance below minimum. Fine applied.");
                                usr.balance -= amount * 0.10; // Fine of 10%
                                usr.transactions[usr.transaction_count].amount = amount * 0.10;
                                usr.transactions[usr.transaction_count].type = 'F'; // 'F' for fine
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * SAVINGS_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // Record the transaction
                        usr.transactions[usr.transaction_count].amount = amount;
                        usr.transactions[usr.transaction_count].type = 'D'; // 'D' for deposit
                        usr.transaction_count++;

                        printf("\nSuccessfully deposited.");
                        displayBalanceSheet(usr);

                        break;

                    case 3:
                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance -= amount;
                        fp = fopen(filename, "w");
                        if (fp != NULL)
                        {
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            printf("\nYou have withdrawn Rs.%.2f", amount);
                        }
                        fclose(fp);
                        break;

                        printf("\nEnter the amount:\t");
                        scanf("%f", &amount);
                        usr.balance -= amount;

                        // Update balance based on account type
                        if (strcmp(usr.account_type, "Current") == 0)
                        {
                            // Check minimum balance and apply surcharge
                            if (usr.balance < MIN_CURRENT_ACCOUNT_BALANCE)
                            {
                                usr.balance -= amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                printf("\nSurcharge applied on negative balance.");
                                usr.transactions[usr.transaction_count].amount = amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                usr.transactions[usr.transaction_count].type = 'S'; // 'S' for surcharge
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * CURRENT_ACCOUNT_INTEREST_RATE;
                            }
                        }
                        else if (strcmp(usr.account_type, "Savings") == 0)
                        {
                            // Check minimum balance and apply fine
                            if (usr.balance < MIN_SAVINGS_ACCOUNT_BALANCE)
                            {
                                printf("\nBalance below minimum. Fine applied.");
                                usr.balance -= amount * 0.10; // Fine of 10%
                                usr.transactions[usr.transaction_count].amount = amount * 0.10;
                                usr.transactions[usr.transaction_count].type = 'F'; // 'F' for fine
                            }
                            // Apply interest on positive balance
                            else if (usr.balance > 0)
                            {
                                usr.balance += usr.balance * SAVINGS_ACCOUNT_INTEREST_RATE;
                            }
                        }

                        // Record the transaction
                        usr.transactions[usr.transaction_count].amount = amount;
                        usr.transactions[usr.transaction_count].type = 'W'; // 'W' for withdrawal
                        usr.transaction_count++;

                        printf("\nYou have withdrawn Rs.%.2f", amount);
                        displayBalanceSheet(usr);

                        break;

                    case 4:
                        
                        printf("\nPlease enter the phone number to transfer the balance:\t");
                        scanf("%s", phone);
                        printf("\nPlease enter the amount to transfer:\t");
                        scanf("%f", &amount);
                        strcpy(filename, phone);
                        fp = fopen(strcat(filename, ".dat"), "r");
                        if (fp == NULL)
                            printf("\nAccount number not registered");
                        else
                        {
                            fread(&usr1, sizeof(struct user), 1, fp);
                            fclose(fp);
                            if (amount > usr.balance)
                                printf("\nInsufficient balance");
                            else
                            {
                                fp = fopen(filename, "w");
                                usr1.balance += amount;
                                fwrite(&usr1, sizeof(struct user), 1, fp);
                                fclose(fp);

                                // For Current Account: Update sender's balance and apply surcharge
                                if (strcmp(usr.account_type, "Current") == 0)
                                {
                                    usr.balance -= amount * CURRENT_ACCOUNT_SURCHARGE_RATE;
                                    printf("\nSurcharge applied on negative balance.");
                                }

                                // Write updated balance to sender's file
                                strcpy(filename, usr.phone);
                                fp = fopen(strcat(filename, ".dat"), "w");
                                if (fp != NULL)
                                {
                                    fwrite(&usr, sizeof(struct user), 1, fp);
                                }
                                fclose(fp);

                                printf("\nYou have successfully transferred Rs.%.2f to %s", amount, phone);
                            }
                        }
                        break;
                    case 5:
                        
                        printf("\nPlease enter your new password:\t");
                        scanf("%s", pword);
                        fp = fopen(filename, "w");
                        if (fp != NULL)
                        {
                            strcpy(usr.password, pword);
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            printf("\nPassword successfully changed");
                        }
                        fclose(fp);
                        break;
                    case 6:
                        // Debit card charge
                        if (usr.customer_rights == 'y')
                        {
                            usr.balance -= DEBIT_CARD_CHARGE;
                            printf("\nDebit card charge applied.");
                        }
                        break;
                    case 7:
                        // Text message service charge
                        if (usr.customer_rights == 'y')
                        {
                            usr.balance -= MESSAGE_SERVICE_CHARGE;
                            printf("\nText message service charge applied.");
                            usr.transactions[usr.transaction_count].amount = MESSAGE_SERVICE_CHARGE;
                            usr.transactions[usr.transaction_count].type = 'M'; // 'M' for message charge
                            usr.transaction_count++;
                        }
                        break;

                    default:
                        printf("\nInvalid option");
                    }
                    
                    printf("\nDo you want to continue the transaction [y/n]\t");
                    scanf(" %c", &cont);
                }
                //displayBalanceSheet(usr);
            }
            else
            {
                printf("\nInvalid password");
            }
        }
    }
    

    return 0;
}
