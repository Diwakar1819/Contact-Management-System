#include <stdio.h>

#include "file.h"

/*====================================================================
 *                  FILE FUNCTION DEFINITIONS
 *===================================================================*/

/*--------------------------------------------------------------------
 * Function : loadContactsFromFile()
 *
 * Description :
 *      Loads all contacts from the CSV file into memory.
 *
 * Input :
 *      addressBook - Pointer to Address Book.
 *
 * Returns :
 *      SUCCESS -> Contacts loaded successfully.
 *      FAILURE -> Unable to open file.
 *-------------------------------------------------------------------*/
int loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;

    /* Open the contacts file in read mode */
    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        return FAILURE;
    }

    /* Initialize contact count */
    addressBook->contactCount = 0;

    /* Read contacts from file */
    while (addressBook->contactCount < MAX_CONTACTS &&
           fscanf(fp,
                  " %49[^,],%19[^,],%49[^\n]",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    /* Close the file */
    fclose(fp);

    return SUCCESS;
}

/*--------------------------------------------------------------------
 * Function : saveContactsToFile()
 *
 * Description :
 *      Saves all contacts from memory into the CSV file.
 *
 * Input :
 *      addressBook - Pointer to Address Book.
 *
 * Returns :
 *      SUCCESS -> Contacts saved successfully.
 *      FAILURE -> Unable to open file.
 *-------------------------------------------------------------------*/
int saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    int i;

    /* Open the contacts file in write mode */
    fp = fopen(FILE_NAME, "w");

    if (fp == NULL)
    {
        return FAILURE;
    }

    /* Write every contact into the file */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp,
                "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    /* Close the file */
    fclose(fp);

    return SUCCESS;
}