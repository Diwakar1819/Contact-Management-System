# Address Book Management System — Requirements Analysis

## Revision History

| Version | Date         | Description                   |
|---------|--------------|-------------------------------|
| 1.0     | 11-Jul-2026  | Initial Requirements Analysis |

## Document Information

| Field             | Value                          |
|-------------------|--------------------------------|
| Project           | Address Book Management System |
| Language          | C                              |
| Development Model | Agile (Incremental)            |
| Sprint            | Sprint 0                       |
| Status            | In Progress                    |

---

## 1. Objective

The objective of this project is to develop a console-based Address Book Management System in C that adheres to the Software Requirements Specification (SRS) and the existing project structure.

The implementation must emphasize:

- Clean, readable code
- Modular design
- Thorough input validation
- Robust error handling
- Reliable file handling
- Maintainable architecture

### Project Goals

The project aims to:

- Develop a modular console-based application.
- Ensure data consistency through proper validation.
- Maintain a clean separation between user interface, business logic, and file handling.
- Build a maintainable and extensible codebase while adhering to the provided project structure.

---

## 2. Project Scope

### Included

- Create contact records
- Search contacts
- Edit contact details
- Delete contacts
- List all contacts
- Save contacts to a file
- Load contacts from a file

### Excluded

- Database integration
- Graphical user interface
- Network communication
- User authentication
- Cloud storage
- Multi-user support

---

## 3. Primary Actor

- User

The system is designed for a single user interacting through the terminal.

---

## 4. Functional Requirements

The system shall support the following operations:

### Requirement Traceability Matrix (RTM)

| Req ID | Feature        | Module    | Functions              | Tested  |
| ------ | -------------- | --------- | ---------------------- | --------|
| FR-01  | Create Contact | contact.c | createContact()        | ⬜      |
| FR-02  | Search Contact | contact.c | searchContact()        | ⬜      |
| FR-03  | Edit Contact   | contact.c | editContact()          | ⬜      |
| FR-04  | Delete Contact | contact.c | deleteContact()        | ⬜      |
| FR-05  | List Contact   | contact.c | listContacts()         | ⬜      |
| FR-06  | Save           | file.c    | saveContactsToFile()   | ⬜      |
| FR-07  | Load           | file.c    | loadContactsFromFile() | ⬜      |

---

## 5. Non-functional Requirements

### Performance

- Menus should respond quickly.
- Contact searches should be efficient within the array-based implementation.

### Reliability

- Invalid data must not be stored.
- File operations should preserve data integrity and prevent corruption.

### Maintainability

- Implementation should use small reusable functions.
- The codebase should follow a modular design.

### Usability

- Menu options must be easy to read and understand.
- Error messages should be clear and informative.

### Portability

- The application must compile with GCC.
- The application must run correctly on Linux.

---

## 6. Assumptions

- The maximum number of contacts is fixed.
- Contacts are stored in arrays.
- Persistent storage is file-based.
- Only one user interacts with the application at a time.

---

## 7. Constraints

- Implementation must use pure C.
- The existing project structure must remain unchanged.
- Arrays should be used instead of advanced data structures.
- The application must be console-based.

---

## 8. Success Criteria

The project will be considered successful when:

- All mandatory features are implemented.
- Input validation is complete and effective.
- File operations function correctly.
- The code follows a modular design.
- The application passes all test cases.

