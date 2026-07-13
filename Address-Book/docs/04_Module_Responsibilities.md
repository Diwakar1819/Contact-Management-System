# Address Book Management System — Module Responsibilities

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Module Responsibilities |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document defines the responsibility of each source file in the Address Book Management System.

The objective is to ensure that every module performs a single responsibility, promoting modularity, maintainability, and ease of debugging.

---

# 2. Module Overview

The project consists of the following primary modules.

```

| Module | Responsibility |
|----------|----------------|
| main.c | Application entry point and menu navigation |
| contact.c | Contact management operations |
| file.c | Persistent storage management |
| populate.c | Sample contact initialization |
| contact.h | Contact structure definitions and function declarations |
| file.h | File operation declarations |
| populate.h | Populate function declarations |

---

```markdown
# 3. Module Responsibilities

---

## 3.1 main.c

### Responsibility

Acts as the Application Controller.

### Handles

- Application startup
- AddressBook initialization
- Main menu display
- User menu selection
- Function dispatch
- Application shutdown

### Does NOT Handle

- Contact validation
- Contact searching
- File parsing
- Contact storage

---

## 3.2 contact.c

### Responsibility

Implements all business logic related to contact management.

### Handles

- Create Contact
- Search Contact
- Edit Contact
- Delete Contact
- List Contacts
- Input Validation
- Duplicate Checking

### Does NOT Handle

- Program initialization
- File opening
- File writing
- Application termination

---

## 3.3 file.c

### Responsibility

Handles permanent storage of contact information.

### Handles

- Save contacts
- Load contacts
- CSV parsing
- CSV generation
- File error detection

### Does NOT Handle

- User interaction
- Validation
- Contact searching

---

## 3.4 populate.c

### Responsibility

Populate the address book with predefined sample contacts for testing and demonstration.

### Handles

- Creating sample records
- Initial testing data

### Does NOT Handle

- User-generated contacts
- File operations
- Contact validation

---

## 3.5 Header Files

Header files expose interfaces between modules.

Responsibilities include:

- Structure declarations
- Constant definitions
- Function prototypes
- Shared macros

They must never contain implementation logic.

---

# 4. Module Interaction

```

```
                 main.c
                    │
        ┌───────────┴───────────┐
        ▼                       ▼
   contact.c               file.c
        │
        ▼
   populate.c
```

---

```markdown
Interaction Summary

- main.c invokes contact operations.
- contact.c requests file operations when necessary.
- populate.c initializes default contacts.
- Header files provide shared declarations.

---

# 5. Dependency Rules

The following dependency rules must always be followed.

| Rule | Description |
|------|-------------|
| DR-01 | main.c controls the application flow |
| DR-02 | contact.c owns contact operations |
| DR-03 | file.c owns storage operations |
| DR-04 | Modules communicate only through function calls |
| DR-05 | Global variables should be avoided whenever possible |

---

# 6. Design Principles

Each module follows these engineering principles.

### Single Responsibility

Each module should perform only one primary task.

---

### Low Coupling

Modules should depend on each other as little as possible.

---

### High Cohesion

Functions within a module should be closely related.

---

### Reusability

Modules should be reusable without modification.

---

### Maintainability

Changes in one module should have minimal impact on others.

---

# 7. Key Design Decisions

| Decision | Reason |
|----------|--------|
| Separate contact and file operations | Improve modularity |
| Keep business logic in contact.c | Easier maintenance |
| Keep file logic in file.c | Clear separation of concerns |
| Header files contain only declarations | Reduce compilation dependencies |
| Centralize application flow in main.c | Simplify navigation |

---

# 8. Conclusion

The proposed module organization provides a clean separation of responsibilities while maintaining a simple and maintainable architecture. Each module has a clearly defined purpose, reducing complexity and improving readability.