# Address Book Management System — System Architecture

---

## Document Information

| Field    | Value                          |
|----------|--------------------------------|
| Project  | Address Book Management System |
| Document | System Architecture            |
| Version  | 1.0                            |
| Sprint   | Sprint 0                       |
| Status   | Final                          |

---

# 1. Purpose

This document defines the overall software architecture of the Address Book Management System.

It explains:

- Overall system design
- Component interaction
- Software layers
- Data flow
- Control flow
- Module communication

This document serves as the implementation blueprint.

---

# 2. System Overview

The Address Book Management System is a console-based application that allows a user to manage contact information.

The application stores all contacts in memory during execution and persists them to a CSV file before exiting.

The architecture follows a modular design where every module performs a single responsibility.

---

# 3. System Boundary

External Components

• User
• CSV File

Internal Components

• Main Menu
• Contact Module
• Validation Module
• File Module
• Address Book Data

---

# 4. High Level Architecture

The high-level architecture of the Address Book Management System is illustrated below:

                    USER
                      │
                      ▼
             Console Interface
            (Menus & User Input)
                      │
                      ▼
             Application Controller
                  (main.c)
                      │
      ┌─────────┬─────────┬─────────┐
      ▼         ▼         ▼         ▼
   Create    Search     Edit    Delete/List
                      │
                      ▼
              Contact Module
                 (contact.c)
                      │
                      ▼
             Validation Module
                      │
                      ▼
              AddressBook Memory
                      │
                      ▼
                File Operations
                  (file.c)
                      │
                      ▼
                 contacts.csv

# 5. Software Layers

| Layer          | Responsibility                       |
|----------------|--------------------------------------|
| Presentation   | Display menus and receive user input |
| Application    | Route user requests                  |
| Business Logic | Contact operations                   |
| Validation     | Validate user inputs                 |
| Storage        | Load and save contacts               |

---

# 6. Data Flow

User

↓

Input

↓

Validation

↓

AddressBook

↓

Memory

↓

CSV File

↓

Display Result

---

# 7. Control Flow

Application Start

↓

Load Contacts

↓

Main Menu

↓

User Operation

↓

Validation

↓

Business Logic

↓

Update Memory

↓

Save File

↓

Exit

---

# 8. Architectural Principles

The project follows the following design principles:

- Separation of Concerns
- Single Responsibility Principle
- Modular Design
- Data Integrity
- Low Coupling
- High Cohesion
- Code Reusability

---

# 9. Key Design Decisions

| Decision                            | Reason                  |
|-------------------------------------|-------------------------|
| Preserve existing project structure | Project requirement     |
| Use helper functions                | Improve readability     |
| Validate before storing             | Maintain data integrity |
| Store contacts in arrays            | SRS constraint          |
| CSV based storage                   | Simple and portable     |

---

# 10. Conclusion

The proposed architecture provides a simple, modular, and maintainable design while complying with the project constraints. It allows each module to perform a single responsibility, making the application easier to understand, test, and extend.