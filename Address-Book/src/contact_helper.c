#include <stdio.h>
#include <string.h>
#include "contact_helper.h"

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
int validate_name(char *name)
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
int validate_phone(char *phone, AddressBook *addressBook, int currentIndex)
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
    if (currentIndex == -1)
    {
        if (isDuplicatePhone(phone, addressBook))
        {
            return PHONE_DUPLICATE;
        }
    }
    else
    {
        if (isDuplicatePhoneEdit(phone, addressBook, currentIndex))
        {
            return PHONE_DUPLICATE;
        }
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
int validate_email(char *email, AddressBook *addressBook, int currentIndex)
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
    if (currentIndex == -1)
    {
        if (isDuplicateEmail(email, addressBook))
        {
            return EMAIL_DUPLICATE;
        }
    }
    else
    {
        if (isDuplicateEmailEdit(email, addressBook, currentIndex))
        {
            return EMAIL_DUPLICATE;
        }
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
int isDuplicatePhone(char *phone, AddressBook *addressBook)
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
int isDuplicateEmail(char *email, AddressBook *addressBook)
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
int isDuplicatePhoneEdit(char *phone, AddressBook *addressBook, int currentIndex)
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
int isDuplicateEmailEdit(char *email, AddressBook *addressBook, int currentIndex)
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
void displayContact(Contact *contact)
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
int search_by_name(AddressBook *addressBook)
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
int search_by_phone(AddressBook *addressBook)
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
int search_by_email(AddressBook *addressBook)
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
