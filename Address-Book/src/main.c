#include <stdio.h>

#include "contact.h"
#include "file.h"

/*--------------------------------------------------------------------
 * Function : main()
 *
 * Description :
 *      Entry point of the Address Book Management System.
 *      Initializes the address book, displays the main menu,
 *      and executes user-selected operations until the user exits.
 *-------------------------------------------------------------------*/
int main(void)
{
    int choice;
    char saveChoice;
    AddressBook addressBook;

    /* Initialize Address Book */
    initialize(&addressBook);

    /* Welcome Screen */
    printf("\n==================================================\n");
    printf("           WELCOME TO ADDRESS BOOK\n");
    printf("==================================================\n");
    printf(" Manage your contacts quickly and efficiently.\n");
    printf("==================================================\n");

    /* Main Application Loop */
    do
    {
        printf("\n============== ADDRESS BOOK MENU ==============\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contacts\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("===============================================\n");
        printf("Enter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nERROR: Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); /* Clear input buffer */
            choice = 0; /* Force default case in the switch */
        }

        switch (choice)
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                break;

            case 5:
                listContacts(&addressBook);
                break;

            case 6:
                saveContactsToFile(&addressBook);
                printf("\nContacts saved successfully.\n");
                break;

            case 7:
                printf("\nDo you want to save before exiting? (Y/N) : ");
                scanf(" %c", &saveChoice);

                if (saveChoice == 'Y' || saveChoice == 'y')
                {
                    saveContactsToFile(&addressBook);
                    printf("\nContacts saved successfully.\n");
                }

                printf("\nThank you for using Address Book.\n");
                printf("Have a great day!\n");
                printf("Program exited successfully.\n");
                break;

            default:
                printf("\nERROR: Invalid menu choice.\n");
                printf("Please enter a number between 1 and 7.\n");
        }

    } while (choice != 7);

    return 0;
}