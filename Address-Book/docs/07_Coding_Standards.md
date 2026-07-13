# Address Book Management System — Coding Standards

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Coding Standards |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document defines the coding standards followed throughout the Address Book Management System.

The objective is to improve readability, maintainability, consistency, and code quality.

---

# 2. Naming Conventions

## Variables

Use meaningful names.

Examples

```c
contactCount
phoneNumber
emailAddress
contactIndex
```

Avoid

`c
a
b
temp
abc
```

---

## Functions

Use camelCase for function names.

Examples

```c
createContact()
searchContact()
validatePhone()
saveContactsToFile()
```

---

## Constants

Use uppercase.

```c
MAX_CONTACTS
NAME_LENGTH
PHONE_LENGTH
EMAIL_LENGTH
```

---

# 3. Formatting Rules

- Proper indentation (4 spaces)
- One statement per line
- Opening braces on same line
- Blank lines between logical sections
- Maximum function size should remain small and readable

---

# 4. Comments

Comments should explain **why**, not **what**.

Good

```c
/* Prevent duplicate phone numbers */
```

Avoid

```c
/* Increment i */
```

---

# 5. Function Guidelines

Every function should:

- Perform one responsibility.
- Validate inputs.
- Avoid duplicate code.
- Return gracefully.
- Keep business logic separate from file operations.

---

# 6. Error Handling

- Never ignore return values.
- Display meaningful error messages.
- Preserve data integrity on failure.

---

# 7. Design Principles

The implementation follows:

- Single Responsibility Principle
- Separation of Concerns
- Low Coupling
- High Cohesion
- Reusability
- Maintainability

---

# 8. Conclusion

Following these coding standards ensures that the code remains readable, maintainable, and consistent throughout the project.