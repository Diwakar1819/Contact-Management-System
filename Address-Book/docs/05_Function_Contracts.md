# Address Book Management System — Function Contracts

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Function Contracts |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document defines the responsibilities, inputs, outputs, dependencies, and expected behavior of each public function in the Address Book Management System.

The objective is to ensure that every function has a well-defined responsibility and a clear contract before implementation.

---

# 2. Function Design Principles

Every function in the project follows these principles:

- Perform only one logical responsibility.
- Validate inputs before processing.
- Avoid modifying data on failure.
- Return control gracefully.
- Keep functions short and readable.
- Avoid duplicate logic.

---

# 3. Function Contracts

---

## initialize()

### Purpose

Initialize the Address Book before the application starts.

### Input

- AddressBook *

### Output

- Initialized AddressBook

### Responsibilities

- Initialize contact count.
- Load sample contacts or file data.

### Dependencies

- populateAddressBook()
- loadContactsFromFile()

---

## createContact()

### Purpose

Create a new contact.

### Input

- AddressBook *

### Output

- New contact added to AddressBook.

### Responsibilities

- Receive user input.
- Validate all fields.
- Check duplicate phone number.
- Check duplicate email.
- Store contact.
- Increment contact count.

### Failure Conditions

- Invalid name
- Invalid phone
- Invalid email
- Duplicate phone
- Duplicate email
- Address book full

---

## searchContact()

### Purpose

Search for an existing contact.

### Input

- AddressBook *

### Output

- Matching contact(s)

### Responsibilities

- Allow search by Name
- Allow search by Phone
- Allow search by Email
- Display matching contact(s)

### Failure Conditions

- Contact not found
- Invalid search option

---

## editContact()

### Purpose

Modify an existing contact.

### Input

- AddressBook *

### Output

- Updated contact

### Responsibilities

- Search contact.
- Select editable field.
- Validate new value.
- Update record.

### Failure Conditions

- Contact not found
- Invalid data
- Duplicate phone/email

---

## deleteContact()

### Purpose

Delete an existing contact.

### Input

- AddressBook *

### Output

- Contact removed

### Responsibilities

- Search contact.
- Confirm deletion.
- Remove contact.
- Shift remaining contacts.
- Update contact count.

### Failure Conditions

- Contact not found

---

## listContacts()

### Purpose

Display all stored contacts.

### Input

- AddressBook *

### Output

- Contact list

### Responsibilities

- Display every stored contact.
- Sort contacts if required.

### Failure Conditions

- Empty AddressBook

---

## saveContactsToFile()

### Purpose

Store contacts permanently.

### Input

- AddressBook *

### Output

- contacts.csv

### Responsibilities

- Open file.
- Write every contact.
- Close file safely.

### Failure Conditions

- File open failure
- Write failure

---

## loadContactsFromFile()

### Purpose

Load contacts during startup.

### Input

- AddressBook *

### Output

- Contacts loaded into memory

### Responsibilities

- Open CSV file.
- Read contacts.
- Populate AddressBook.
- Close file.

### Failure Conditions

- File missing
- Corrupted file

---

# 4. Validation Functions

The following helper functions support the public APIs.

| Function | Responsibility |
|----------|----------------|
| validate_name() | Verify name format |
| validate_phone() | Verify phone format and uniqueness |
| validate_email() | Verify email format and uniqueness |
| search_by_name() | Search using name |
| search_by_phone() | Search using phone |
| search_by_email() | Search using email |

These functions are internal helper functions and are not directly accessible from the main application menu.

---

# 5. Function Interaction

```

```text
main()

│

├── initialize()

│

├── createContact()

│      ├── validate_name()

│      ├── validate_phone()

│      └── validate_email()

│

├── searchContact()

│      ├── search_by_name()

│      ├── search_by_phone()

│      └── search_by_email()

│

├── editContact()

│

├── deleteContact()

│

├── listContacts()

│

└── saveContactsToFile()
```

```markdown

---

# 6. General Function Rules

Every public function shall:

- Validate input before processing.
- Preserve AddressBook integrity.
- Avoid duplicate code.
- Return gracefully after execution.
- Display meaningful status messages.

---

# 7. Key Design Decisions

| Decision | Reason |
|----------|--------|
| One function, one responsibility | Improve maintainability |
| Helper functions for validation | Avoid duplicate code |
| Validation before modification | Preserve data integrity |
| Public functions coordinate workflow | Improve readability |
| Helper functions remain internal | Better modularity |

---

# 8. Conclusion

The defined function contracts establish a clear implementation guideline for every feature in the Address Book Management System. Following these contracts ensures consistency, modularity, and easier debugging during development.