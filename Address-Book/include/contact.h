#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 20
#define EMAIL_LENGTH 50

/*====================================================================
 *                  PROJECT STATUS CODES
 *===================================================================*/

/* Success Status */
#define VALID                           1

/* Name Validation Status */
#define NAME_EMPTY                     -1
#define NAME_INVALID_CHARACTER         -2

/* Phone Validation Status */
#define PHONE_EMPTY                    -3
#define PHONE_INVALID_LENGTH           -4
#define PHONE_INVALID_CHARACTER        -5
#define PHONE_DUPLICATE                -6

/* Email Validation Status */
#define EMAIL_EMPTY                    -7
#define EMAIL_INVALID_FORMAT           -8
#define EMAIL_DUPLICATE                -9

typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

/* Function Prototypes */
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);

#endif /* CONTACT_H */
