#ifndef FILE_H
#define FILE_H

#include "contact.h"

/*====================================================================
 *                  FILE CONFIGURATION
 *===================================================================*/

#define FILE_NAME "contacts.csv"

/*====================================================================
 *                  FILE FUNCTION PROTOTYPES
 *===================================================================*/

/* Load all contacts from CSV file */
int loadContactsFromFile(AddressBook *addressBook);

/* Save all contacts to CSV file */
int saveContactsToFile(AddressBook *addressBook);

#endif /* FILE_H */