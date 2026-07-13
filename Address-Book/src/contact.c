#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

/*====================================================================
 *                  PRIVATE FUNCTION PROTOTYPES
 *===================================================================*/

/* Validation Functions */
static int validate_name(char *name);
static int validate_phone(char *phone, AddressBook *addressBook);
static int validate_email(char *email, AddressBook *addressBook);

/* Duplicate Check Functions */
static int isDuplicatePhone(char *phone, AddressBook *addressBook);
static int isDuplicateEmail(char *email, AddressBook *addressBook);

/* Display Helper Function */
static void displayContact(Contact *contact);

/* Search Helper Functions */
static int search_by_name(AddressBook *addressBook);
static int search_by_phone(AddressBook *addressBook);
static int search_by_email(AddressBook *addressBook);

/* Helper function used only by editContact() */
static int isDuplicatePhoneEdit(char *phone,AddressBook *addressBook,int currentIndex);
static int isDuplicateEmailEdit(char *email,AddressBook *addressBook,int currentIndex);


/* Validation Status Codes are defined in contact.h */

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

    /* Populate sample contacts (for testing) */
    populateAddressBook(addressBook);

    /* Load contacts from file (Enable after implementing file.c) */
    // loadContactsFromFile(addressBook);
}

/*--------------------------------------------------------------------
 * Function : validate_name()
 *
 * Description :
 *      Validates the contact name.
 *      Allows only alphabets, spaces and '.' characters.
 *
 * Input :
 *      name - Contact name entered by the user.
 *
 * Returns :
 *      VALID                  -> Name is valid.
 *      NAME_EMPTY             -> Name string is empty.
 *      NAME_INVALID_CHARACTER -> Name contains an invalid character.
 *-------------------------------------------------------------------*/

static int validate_name(char *name)
{
    int i = 0;

    /* Check for empty name */
    if (strlen(name) == 0)
    {
        return NAME_EMPTY;
    }

    /* Validate each character */
    while (name[i] != '\0')
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ' || name[i] == '.'))
        {
            return NAME_INVALID_CHARACTER;
        }

        i++;
    }

    return VALID;
}

/*--------------------------------------------------------------------
 * Function : validate_phone()
 *
 * Description :
 *      Validates the entered phone number.
 *
 *      Validation Rules:
 *      - Phone number cannot be empty.
 *      - Must contain exactly 10 digits.
 *      - Only numeric digits are allowed.
 *      - Phone number must be unique.
 *
 * Input :
 *      phone        - Phone number entered by the user.
 *      addressBook  - Pointer to the Address Book.
 *
 * Returns :
 *      VALID                   -> Phone number is valid.
 *      PHONE_EMPTY             -> Phone string is empty.
 *      PHONE_INVALID_LENGTH    -> Phone is not exactly 10 digits.
 *      PHONE_INVALID_CHARACTER -> Phone contains a non-digit character.
 *      PHONE_DUPLICATE         -> Phone already exists in address book.
 *-------------------------------------------------------------------*/
static int validate_phone(char *phone, AddressBook *addressBook)
{
    int i = 0;

    /* Check for empty phone number */
    if (phone[0] == '\0')
    {
        return PHONE_EMPTY;
    }

    /* Check if phone number contains exactly 10 digits */
    if (strlen(phone) != 10)
    {
        return PHONE_INVALID_LENGTH;
    }

    /* Validate each character */
    while (phone[i] != '\0')
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return PHONE_INVALID_CHARACTER;
        }

        i++;
    }

    /* Check for duplicate phone number */
    if (isDuplicatePhone(phone, addressBook))
    {
        return PHONE_DUPLICATE;
    }

    return VALID;
}

/*--------------------------------------------------------------------
 * Function : validate_email()
 *
 * Description :
 *      Validates the entered email address.
 *
 *      Validation Rules:
 *      - Email cannot be empty.
 *      - Must contain exactly one '@' symbol.
 *      - Must contain at least one '.' after '@'.
 *      - Spaces are not allowed.
 *      - Email must be unique.
 *
 * Input :
 *      email        - Email entered by the user.
 *      addressBook  - Pointer to the Address Book.
 *
 * Returns :
 *      VALID                -> Email is valid.
 *      EMAIL_EMPTY          -> Email string is empty.
 *      EMAIL_INVALID_FORMAT -> Email format is incorrect.
 *      EMAIL_DUPLICATE      -> Email already exists in address book.
 *-------------------------------------------------------------------*/
static int validate_email(char *email, AddressBook *addressBook)
{
    int i = 0;
    int atCount = 0;
    int atPosition = -1;
    int dotAfterAt = 0;

    /* Check for empty email */
    if (email[0] == '\0')
    {
        return EMAIL_EMPTY;
    }

    /* Validate email format */
    while (email[i] != '\0')
    {
        /* Spaces are not allowed */
        if (email[i] == ' ')
        {
            return EMAIL_INVALID_FORMAT;
        }

        /* Count '@' symbol */
        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }

        /* Check for '.' after '@' */
        if (email[i] == '.' && atPosition != -1 && i > atPosition)
        {
            dotAfterAt = 1;
        }

        i++;
    }

    /* Email must contain exactly one '@' */
    if (atCount != 1)
    {
        return EMAIL_INVALID_FORMAT;
    }

    /* '@' cannot be the first or last character */
    if (atPosition == 0 || atPosition == i - 1)
    {
        return EMAIL_INVALID_FORMAT;
    }

    /* '.' must appear after '@' */
    if (!dotAfterAt)
    {
        return EMAIL_INVALID_FORMAT;
    }

    /* Check for duplicate email */
    if (isDuplicateEmail(email, addressBook))
    {
        return EMAIL_DUPLICATE;
    }

    return VALID;
}

/*--------------------------------------------------------------------
 * Function : isDuplicatePhone()
 *
 * Description :
 *      Checks whether the entered phone number already exists
 *      in the Address Book.
 *
 * Input :
 *      phone        - Phone number entered by the user.
 *      addressBook  - Pointer to Address Book.
 *
 * Returns :
 *      1 -> Duplicate phone number found.
 *      0 -> Phone number is unique.
 *-------------------------------------------------------------------*/
static int isDuplicatePhone(char *phone, AddressBook *addressBook)
{
    int i;

    /* Compare with every existing contact */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/*--------------------------------------------------------------------
 * Function : isDuplicateEmail()
 *
 * Description :
 *      Checks whether the entered email address already exists
 *      in the Address Book.
 *
 * Input :
 *      email        - Email entered by the user.
 *      addressBook  - Pointer to the Address Book.
 *
 * Returns :
 *      1 -> Duplicate email found.
 *      0 -> Email is unique.
 *-------------------------------------------------------------------*/
static int isDuplicateEmail(char *email, AddressBook *addressBook)
{
    int i;

    /* Compare with every existing contact */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return 1;
        }
    }

    return 0;
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

        status = validate_phone(phone, addressBook);

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

        status = validate_email(email, addressBook);

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

/*====================================================================
 *                  DISPLAY HELPER FUNCTION
 *===================================================================*/

/*--------------------------------------------------------------------
 * Function : displayContact()
 *
 * Description :
 *      Displays a single contact in a formatted manner.
 *
 * Input :
 *      contact - Pointer to the contact to be displayed.
 *
 * Returns :
 *      None
 *-------------------------------------------------------------------*/
static void displayContact(Contact *contact)
{
    printf("----------------------------------------\n");
    printf("Name  : %s\n", contact->name);
    printf("Phone : %s\n", contact->phone);
    printf("Email : %s\n", contact->email);
    printf("----------------------------------------\n");
}

/*--------------------------------------------------------------------
 * Function : search_by_name()
 *
 * Description :
 *      Searches for contacts by name.
 *      If multiple contacts have the same name, displays all
 *      matching contacts and allows the user to choose one.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      Index of selected contact.
 *      -1 if contact is not found or user cancels.
 *-------------------------------------------------------------------*/
static int search_by_name(AddressBook *addressBook)
{
    char name[NAME_LENGTH];
    int matchedIndex[MAX_CONTACTS];
    int matchCount = 0;
    int choice;
    int i;

    printf("Enter Name : ");
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0)
    {
        printf("ERROR: Name cannot be empty.\n");
        return -1;
    }

    /* Search for matching contacts */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(name, addressBook->contacts[i].name) == 0)
        {
            matchedIndex[matchCount] = i;
            matchCount++;
        }
    }

    /* No matching contact found */
    if (matchCount == 0)
    {
        printf("\nERROR: Contact not found.\n");
        return -1;
    }

    printf("\n========== SEARCH RESULTS ==========\n");

    /* Only one contact found — display it directly */
    if (matchCount == 1)
    {
        displayContact(&addressBook->contacts[matchedIndex[0]]);
        return matchedIndex[0];
    }

    /* Display all matching contacts */
    for (i = 0; i < matchCount; i++)
    {
        printf("\nOccurrence : %d\n", i + 1);
        displayContact(&addressBook->contacts[matchedIndex[i]]);
    }


    /* Allow user to choose one occurrence */
    while (1)
    {
        printf("\nEnter occurrence number (0 to Cancel) : ");
        if (scanf("%d", &choice) != 1)
        {
            printf("ERROR: Invalid input.\n");

            while (getchar() != '\n');

            continue;
        }

        while (getchar() != '\n');

        if (choice == 0)
        {
            return -1;
        }

        if (choice >= 1 && choice <= matchCount)
        {
            return matchedIndex[choice - 1];
        }

        printf("ERROR: Invalid occurrence number.\n");
    }
}

/*--------------------------------------------------------------------
 * Function : search_by_phone()
 *
 * Description :
 *      Searches for a contact using the phone number.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      Index of the matching contact.
 *      -1 if contact is not found.
 *-------------------------------------------------------------------*/
static int search_by_phone(AddressBook *addressBook)
{
    char phone[PHONE_LENGTH];
    int i;

    printf("Enter Phone : ");

    if (fgets(phone, PHONE_LENGTH, stdin) == NULL)
    {
        printf("ERROR: Failed to read phone number.\n");
        return -1;
    }

    /* Remove trailing newline */
    phone[strcspn(phone, "\n")] = '\0';

    /* Check for empty input */
    if (phone[0] == '\0')
    {
        printf("ERROR: Phone number cannot be empty.\n");
        return -1;
    }

    /* Search for matching phone number */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printf("\n========== SEARCH RESULT ==========\n");
            displayContact(&addressBook->contacts[i]);

            return i;
        }
    }

    printf("\nERROR: Contact not found.\n");

    return -1;
}

/*--------------------------------------------------------------------
 * Function : search_by_email()
 *
 * Description :
 *      Searches for a contact using the email address.
 *
 * Input :
 *      addressBook - Pointer to the Address Book.
 *
 * Returns :
 *      Index of the matching contact.
 *      -1 if contact is not found.
 *-------------------------------------------------------------------*/
static int search_by_email(AddressBook *addressBook)
{
    char email[EMAIL_LENGTH];
    int i;

    printf("Enter Email : ");

    if (fgets(email, EMAIL_LENGTH, stdin) == NULL)
    {
        printf("ERROR: Failed to read email address.\n");
        return -1;
    }

    /* Remove trailing newline */
    email[strcspn(email, "\n")] = '\0';

    /* Check for empty input */
    if (email[0] == '\0')
    {
        printf("ERROR: Email address cannot be empty.\n");
        return -1;
    }

    /* Search for matching email address */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printf("\n========== SEARCH RESULT ==========\n");
            displayContact(&addressBook->contacts[i]);

            return i;
        }
    }

    printf("\nERROR: Contact not found.\n");

    return -1;
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
 * Function : isDuplicatePhoneEdit()
 * Description :
 *      Check if a phone number is a duplicate of an existing contact
 *      (excluding the contact being edited).
 *
 * Input :
 *      phone        - Phone number to check
 *      addressBook  - Pointer to the address book
 *      currentIndex - Index of the contact currently being edited
 *
 * Returns :
 *      1 if phone is a duplicate, 0 otherwise
 *--------------------------------------------------------------------*/
static int isDuplicatePhoneEdit(char *phone, AddressBook *addressBook, int currentIndex)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        /* Skip current contact */
        if (i == currentIndex)
        {
            continue;
        }

        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/*--------------------------------------------------------------------
 * Function : isDuplicateEmailEdit()
 * Description :
 *      Check if an email address is a duplicate of an existing contact
 *      (excluding the contact being edited).
 *
 * Input :
 *      email        - Email address to check
 *      addressBook  - Pointer to the address book
 *      currentIndex - Index of the contact currently being edited
 *
 * Returns :
 *      1 if email is a duplicate, 0 otherwise
 *--------------------------------------------------------------------*/
static int isDuplicateEmailEdit(char *email, AddressBook *addressBook, int currentIndex)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (i == currentIndex)
        {
            continue;
        }

        if (strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

