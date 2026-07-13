# Address Book Management System — Data Model

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Data Model |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document defines the data model used in the Address Book Management System.

It explains how contact information is represented, stored, and managed throughout the application's lifecycle.

---

# 2. Data Overview

The application stores all contact information in memory while it is running.

The AddressBook structure acts as the container for all contacts, while each Contact structure stores the information of an individual contact.

The complete address book is later written to a CSV file for persistent storage.

---

# 3. Entity Relationship


AddressBook
│
├── contactCount
│
└── contacts[]
        │
        ├── Name
        ├── Phone Number
        └── Email Address

# 4. Data Structures

## AddressBook

The AddressBook structure represents the entire application database.

Responsibilities:

- Store all contacts
- Maintain the total contact count
- Provide access to every contact

Attributes

| Field | Description |
|--------|-------------|
| contacts[] | Array of Contact structures |
| contactCount | Number of valid contacts stored |

---

## Contact

The Contact structure represents a single contact.

Responsibilities

- Store contact name
- Store phone number
- Store email address

Attributes

| Field | Description |
|--------|-------------|
| name | Contact Name |
| phone | Mobile Number |
| email | Email Address |

---

# 5. Data Lifecycle

A contact follows the lifecycle below.

```

```
User Input
      │
      ▼
Validation
      │
      ▼
Temporary Variables
      │
      ▼
Contact Structure
      │
      ▼
AddressBook
      │
      ▼
CSV File
```

---

```markdown
# 6. Data Ownership

| Data | Owner |
|------|-------|
| Contact Name | Contact Structure |
| Phone Number | Contact Structure |
| Email Address | Contact Structure |
| Contact Count | AddressBook |
| Contact List | AddressBook |

Only the AddressBook structure owns the contact list.

Individual functions should never create duplicate copies of contacts unless absolutely necessary.

---

# 7. Data Constraints

| Field | Constraint |
|--------|------------|
| Name | Cannot be empty |
| Phone | Must contain exactly 10 digits |
| Email | Must follow valid email format |
| Contact Count | Cannot exceed maximum capacity |

---

# 8. Data Integrity Rules

To maintain consistency, the following rules must always be satisfied.

- Every contact must contain a valid name.
- Phone numbers must be unique.
- Email addresses must be unique.
- Invalid contacts must never be stored.
- contactCount must always represent the actual number of stored contacts.
- Data should only be updated after successful validation.

---

# 9. Design Decisions

| Decision | Reason |
|----------|--------|
| Array-based storage | Required by SRS |
| Fixed-size structures | Simple memory management |
| Single AddressBook object | Centralized data management |
| Validation before insertion | Maintain data integrity |
| Store data in CSV | Human-readable and portable |

---

# 10. Conclusion

The proposed data model provides a simple and efficient representation of contact information while satisfying all project requirements. The centralized AddressBook structure ensures easy management of contacts and simplifies file storage operations.