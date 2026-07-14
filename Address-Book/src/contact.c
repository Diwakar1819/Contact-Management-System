#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "contact_helper.h"
#include "file.h"

/*--------------------------------------------------------------------
 * Function : initialize()
 *
 * Description :
 *      Initializes the Address Book.
 *      Loads sample contacts during startup.
 *
 * Input :
 *      AddressBook *
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void initialize(AddressBook *addressBook)
{
    /* Initialize contact count */
    addressBook->contactCount = 0;

    /* Load contacts from file */
    if (loadContactsFromFile(addressBook) == SUCCESS)
    {
        printf("Contacts loaded successfully. (%d contacts)\n", addressBook->contactCount);
    }
    else
    {
        printf("No existing contacts found. Starting fresh.\n");
    }
}

/*--------------------------------------------------------------------
 * Function : createContact()
 *
 * Description :
 *      Creates a new contact after validating all user inputs.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void createContact(AddressBook *addressBook)
{
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
    int status;

    printf("\n========== CREATE CONTACT ==========\n");

    /* Check whether Address Book is full */
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("ERROR: Address Book is full.\n");
        return;
    }

    /* Read and validate contact name */
    while (1)
    {
        printf("Enter Name : ");
        fgets(name, NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = '\0';
        status = validate_name(name);

        if (status == VALID)
        {
            break;
        }

        switch (status)
        {
            case NAME_EMPTY:
                printf("ERROR: Name cannot be empty.\n");
                break;

            case NAME_INVALID_CHARACTER:
                printf("ERROR: Name should contain only alphabets, spaces and '.'.\n");
                break;
        }
    }

    /* Read and validate phone number */
    while (1)
    {
        printf("Enter Phone : ");
        fgets(phone, PHONE_LENGTH, stdin);
        phone[strcspn(phone, "\n")] = '\0';

        status = validate_phone(phone, addressBook, -1);

        if (status == VALID)
        {
            break;
        }

        switch (status)
        {
            case PHONE_EMPTY:
                printf("ERROR: Phone number cannot be empty.\n");
                break;

            case PHONE_INVALID_LENGTH:
                printf("ERROR: Phone number must contain exactly 10 digits.\n");
                break;

            case PHONE_INVALID_CHARACTER:
                printf("ERROR: Phone number should contain only digits.\n");
                break;

            case PHONE_DUPLICATE:
                printf("ERROR: Phone number already exists.\n");
                break;
        }
    }

    /* Read and validate email address */
    while (1)
    {
        printf("Enter Email : ");
        fgets(email, EMAIL_LENGTH, stdin);
        email[strcspn(email, "\n")] = '\0';

        status = validate_email(email, addressBook, -1);

        if (status == VALID)
        {
            break;
        }

        switch (status)
        {
            case EMAIL_EMPTY:
                printf("ERROR: Email cannot be empty.\n");
                break;

            case EMAIL_INVALID_FORMAT:
                printf("ERROR: Invalid email format.\n");
                break;

            case EMAIL_DUPLICATE:
                printf("ERROR: Email already exists.\n");
                break;
        }
    }

    /* Store the validated contact */
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    /* Update contact count */
    addressBook->contactCount++;

    printf("\nContact added successfully.\n");
}

/*--------------------------------------------------------------------
 * Function : searchContact()
 *
 * Description :
 *      Displays the search menu and performs the selected
 *      search operation.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void searchContact(AddressBook *addressBook)
{
    int choice;

    printf("\n========== SEARCH CONTACT ==========\n");

    while (1)
    {
        printf("\nSearch By\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Back\n");

        printf("\nEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            printf("ERROR: Invalid input.\n");

            while (getchar() != '\n');

            continue;
        }

        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
                search_by_name(addressBook);
                return;

            case 2:
                search_by_phone(addressBook);
                return;

            case 3:
                search_by_email(addressBook);
                return;

            case 4:
                return;

            default:
                printf("ERROR: Invalid choice.\n");
        }
    }
}

/*--------------------------------------------------------------------
 * Function : editContact()
 *
 * Description :
 *      Searches for a contact and edits the selected field.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void editContact(AddressBook *addressBook)
{
    int searchChoice;
    int editChoice;
    int index = -1;
    int status;

    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];

    printf("\n========== EDIT CONTACT ==========\n");

    /*---------------- Search Menu ----------------*/
    while (1)
    {
        printf("\nSearch Contact By\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Cancel\n");

        printf("\nEnter your choice : ");

        if (scanf("%d", &searchChoice) != 1)
        {
            printf("ERROR: Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (searchChoice)
        {
            case 1:
                index = search_by_name(addressBook);
                break;

            case 2:
                index = search_by_phone(addressBook);
                break;

            case 3:
                index = search_by_email(addressBook);
                break;

            case 4:
                return;

            default:
                printf("ERROR: Invalid choice.\n");
                continue;
        }

        break;
    }

    /* Contact not found */
    if (index == -1)
    {
        return;
    }

    /* Display current contact */
    printf("\nCurrent Contact Details\n");
    displayContact(&addressBook->contacts[index]);

    /*---------------- Edit Menu ----------------*/
    printf("\n========== EDIT MENU ==========\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("4. Cancel\n");

    printf("\nEnter your choice : ");

    if (scanf("%d", &editChoice) != 1)
    {
        printf("ERROR: Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    switch (editChoice)
    {
        /*---------------- Edit Name ----------------*/
        case 1:

            while (1)
            {
                printf("Enter New Name : ");
                fgets(name, NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';

                status = validate_name(name);

                if (status == VALID)
                {
                    strcpy(addressBook->contacts[index].name, name);
                    printf("\nName updated successfully.\n");
                    return;
                }

                switch (status)
                {
                    case NAME_EMPTY:
                        printf("ERROR: Name cannot be empty.\n");
                        break;

                    case NAME_INVALID_CHARACTER:
                        printf("ERROR: Name should contain only alphabets, spaces and '.'.\n");
                        break;
                }
            }
            break;

        /*---------------- Edit Phone ----------------*/
        case 2:

            while (1)
            {   
                printf("Enter New Phone : ");
                fgets(phone, PHONE_LENGTH, stdin);
                phone[strcspn(phone, "\n")] = '\0';

                status = validate_phone(phone, addressBook, index);

                if (status == VALID)
                {
                    strcpy(addressBook->contacts[index].phone, phone);
                    printf("\nPhone updated successfully.\n");
                    return;
                }

                switch(status)
                {
                    case PHONE_EMPTY:
                        printf("ERROR: Phone number cannot be empty.\n");
                        break;

                    case PHONE_INVALID_LENGTH:
                        printf("ERROR: Phone number must contain exactly 10 digits.\n");
                        break;

                    case PHONE_INVALID_CHARACTER:
                        printf("ERROR: Phone number should contain only digits.\n");
                        break;

                    case PHONE_DUPLICATE:
                        printf("ERROR: Phone number already exists.\n");
                        break;
                }
            }
            break;

        /*---------------- Edit Email ----------------*/
        case 3:

            while (1)
            {
                printf("Enter New Email : ");
                fgets(email, EMAIL_LENGTH, stdin);
                email[strcspn(email, "\n")] = '\0';

                status = validate_email(email, addressBook, index);

                if (status == VALID)
                {
                    strcpy(addressBook->contacts[index].email, email);
                    printf("\nEmail updated successfully.\n");
                    return;
                }

                switch(status)
                {
                    case EMAIL_EMPTY:
                        printf("ERROR: Email cannot be empty.\n");
                        break;

                    case EMAIL_INVALID_FORMAT:
                        printf("ERROR: Invalid email format.\n");
                        break;

                    case EMAIL_DUPLICATE:
                        printf("ERROR: Email already exists.\n");
                        break;
                }
            }
            break;

        /*---------------- Cancel ----------------*/
        case 4:
            return;

        /*---------------- Default ----------------*/
        default:
            printf("ERROR: Invalid choice.\n");
            break;
    }
}

/*--------------------------------------------------------------------
 * Function : deleteContact()
 *
 * Description :
 *      Searches and deletes a contact from the Address Book.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void deleteContact(AddressBook *addressBook)
{
    int searchChoice;
    int index = -1;
    int i;
    char confirm;

    printf("\n========== DELETE CONTACT ==========\n");

    /*---------------- Search Menu ----------------*/
    while (1)
    {
        printf("\nSearch Contact By\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Cancel\n");

        printf("\nEnter your choice : ");

        if (scanf("%d", &searchChoice) != 1)
        {
            printf("ERROR: Invalid input.\n");

            while (getchar() != '\n');

            continue;
        }

        while (getchar() != '\n');

        switch (searchChoice)
        {
            case 1:
                index = search_by_name(addressBook);
                break;

            case 2:
                index = search_by_phone(addressBook);
                break;

            case 3:
                index = search_by_email(addressBook);
                break;

            case 4:
                return;

            default:
                printf("ERROR: Invalid choice.\n");
                continue;
        }

        break;
    }

    /* Contact not found */
    if (index == -1)
    {
        return;
    }

    /* Display selected contact */
    printf("\nContact Selected\n");
    displayContact(&addressBook->contacts[index]);

    while (1)
    {
        printf("\nAre you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &confirm);
        while (getchar() != '\n');

        if (confirm == 'Y' || confirm == 'y')
        {
            break;
        }

        if (confirm == 'N' || confirm == 'n')
        {
            printf("\nDelete operation cancelled.\n");
            return;
        }

        printf("ERROR: Please enter Y or N.\n");
    }

    /* Shift remaining contacts */
    for (i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    /* Update contact count */
    addressBook->contactCount--;

    printf("\nContact deleted successfully.\n");
}

/*--------------------------------------------------------------------
 * Function : listContacts()
 *
 * Description :
 *      Displays all contacts stored in the Address Book.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
void listContacts(AddressBook *addressBook)
{
    int i;

    printf("\n========== CONTACT LIST ==========\n");

    /* Check if address book is empty */
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    /* Display every contact */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nContact %d\n", i + 1);
        displayContact(&addressBook->contacts[i]);
    }

    printf("\nTotal Contacts : %d\n", addressBook->contactCount);
}