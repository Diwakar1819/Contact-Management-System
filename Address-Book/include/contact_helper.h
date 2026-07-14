#ifndef CONTACT_HELPER_H
#define CONTACT_HELPER_H

#include "contact.h"

/*====================================================================
   *                  HELPER FUNCTION PROTOTYPES
   *===================================================================*/

/* Validation Functions */
int validate_name(char *name);
int validate_phone(char *phone, AddressBook *addressBook, int currentIndex);
int validate_email(char *email, AddressBook *addressBook, int currentIndex);

/* Duplicate Check Functions */
int isDuplicatePhone(char *phone, AddressBook *addressBook);
int isDuplicateEmail(char *email, AddressBook *addressBook);

/* Helper functions used by editContact() */
int isDuplicatePhoneEdit(char *phone, AddressBook *addressBook, int currentIndex);
int isDuplicateEmailEdit(char *email, AddressBook *addressBook, int currentIndex);

/* Display Helper Function */
void displayContact(Contact *contact);

/* Search Helper Functions */
int search_by_name(AddressBook *addressBook);
int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);

#endif /* CONTACT_HELPER_H */
