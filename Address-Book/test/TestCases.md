# Address Book Management System
## Test Cases

---

## Test Environment

- Language : C
- Compiler : GCC
- Platform : Linux
- Storage : CSV File

---

# Module 1 : Create Contact

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC001 | Create valid contact | Name, Phone, Email | Contact created uccessfully | Pass |
| TC002 | Empty name | "" | Error message displayed | Pass |
| TC003 | Invalid name | John123 | Invalid name error | Pass |
| TC004 | Duplicate phone | Existing phone | Duplicate phone error | Pass |
| TC005 | Duplicate email | Existing email | Duplicate email error | Pass |
| TC006 | Invalid phone length | 98765 | Invalid phone length | Pass |
| TC007 | Invalid email format | abcgmail.com | Invalid email error | Pass |

---

# Module 2 : Search Contact

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC008 | Search by Name | John | Contact displayed | Pass |
| TC009 | Search by Phone | 9876543210 | Contact displayed | Pass |
| TC010 | Search by Email | john@gmail.com | Contact displayed | Pass |
| TC011 | Search non-existing contact | Unknown | Contact not found | Pass |
| TC012 | Multiple contacts with same name | John | Occurrence list displayed | Pass |

---

# Module 3 : Edit Contact

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC013 | Edit Name | Valid Name | Name updated | Pass |
| TC014 | Edit Phone | Valid Phone | Phone updated | Pass |
| TC015 | Edit Email | Valid Email | Email updated | Pass |
| TC016 | Duplicate Phone | Existing Phone | Duplicate error | Pass |
| TC017 | Duplicate Email | Existing Email | Duplicate error | Pass |

---

# Module 4 : Delete Contact

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC018 | Delete existing contact | Y | Contact deleted | Pass |
| TC019 | Cancel deletion | N | Contact retained | Pass |
| TC020 | Delete invalid contact | Unknown | Contact not found | Pass |

---

# Module 5 : List Contacts

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC021 | List contacts | - | All contacts displayed | Pass |
| TC022 | Empty address book | - | No contacts available | Pass |

---

# Module 6 : File Operations

| Test ID | Test Scenario | Input | Expected Result | Status |
|----------|---------------|-------|-----------------|--------|
| TC023 | Save contacts | Exit Program | contacts.csv updated | Pass |
| TC024 | Load contacts | Program Start | Contacts loaded | Pass |
| TC025 | Restart application | Existing CSV | Previous contacts available | Pass |

---

# Overall Result

| Total Test Cases | Passed | Failed |
|------------------|--------|--------|
| 25 | 25 | 0 |

---

## Conclusion

All functional requirements specified in the Software Requirements Specification (SRS) were tested successfully. The Address Book Management System performs contact creation, searching, editing, deletion, listing, and file operations as expected. Input validation, duplicate detection, and data persistence were verified through functional testing.