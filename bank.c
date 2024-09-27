#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount{
    char accountHolder[100];
    int accountNumber;
    float balance;
};

void createAccount(struct BankAccount **accounts, int *numAccounts) {
    *accounts = realloc(*accounts, (*numAccounts + 1) * sizeof(struct BankAccount));  // Resize the array for one more account
    printf("Enter Account Holder's Name: ");
    scanf("%s", (*accounts)[*numAccounts].accountHolder);
    
    printf("Enter Account Number: ");
    scanf("%d", &(*accounts)[*numAccounts].accountNumber);
    
    (*accounts)[*numAccounts].balance = 0.0f;  // Initial balance is 0
    printf("Account created successfully!\n");
    (*numAccounts)++;  // Increment the number of accounts
}

void depositMoney(struct BankAccount *accounts , int numAccounts , int accountNumber , float amount )
{
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            printf("Deposit successful! Current balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
};

void withdrawMoney(struct BankAccount *accounts , int numAccounts , int accountNumber , float amount)
{
    for(int i = 0 ; i <numAccounts ; i++){
        if(accounts[i].accountNumber == accountNumber){
            accounts[i].balance -= amount;
            printf("Withdrawal successful! Current balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
};

// Function to check the balance of a specific account
void checkBalance(struct BankAccount *accounts, int numAccounts, int accountNumber) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Current balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

// Function to transfer money between two accounts
void transfer(struct BankAccount *accounts, int numAccounts, int fromAccount, int toAccount, float amount) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == fromAccount) {
            fromIndex = i;
        }
        if (accounts[i].accountNumber == toAccount) {
            toIndex = i;
        }
    }
    if (fromIndex == -1 || toIndex == -1) {
        printf("One or both accounts not found.\n");
        return;
    }
    if (accounts[fromIndex].balance >= amount) {
        accounts[fromIndex].balance -= amount;
        accounts[toIndex].balance += amount;
        printf("Transfer successful! Remaining balance: %.2f\n", accounts[fromIndex].balance);
    } else {
        printf("Insufficient balance in the source account.\n");
    }
}

// Function to view all accounts
void viewAllAccounts(struct BankAccount *accounts, int numAccounts) {
    for (int i = 0; i < numAccounts; i++) {
        printf("\nAccount Holder: %s\n", accounts[i].accountHolder);
        printf("Account Number: %d\n", accounts[i].accountNumber);
        printf("Balance: %.2f\n", accounts[i].balance);
    }
}



int main(){
    struct BankAccount *accounts = NULL;
    int numAccounts = 0;  // Keeps track of the number of accounts
    int choice, accountNumber, fromAccount, toAccount;
    float amount;

    while (1) {
        printf("\n--- Simple Banking System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Transfer Money\n");
        printf("6. View All Accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(&accounts, &numAccounts);
                break;
            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                depositMoney(accounts, numAccounts, accountNumber, amount);
                break;
            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdrawMoney(accounts, numAccounts, accountNumber, amount);
                break;
            case 4:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                checkBalance(accounts, numAccounts, accountNumber);
                break;
            case 5:
                printf("Enter Source Account Number: ");
                scanf("%d", &fromAccount);
                printf("Enter Destination Account Number: ");
                scanf("%d", &toAccount);
                printf("Enter amount to transfer: ");
                scanf("%f", &amount);
                transfer(accounts, numAccounts, fromAccount, toAccount, amount);
                break;
            case 6:
                viewAllAccounts(accounts, numAccounts);
                break;
            case 7:
                free(accounts);  // Free the dynamically allocated memory
                printf("Exiting... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
