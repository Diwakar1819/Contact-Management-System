# Address Book Management System — Testing Strategy

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Testing Strategy |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document describes the testing approach used to verify the correctness, reliability, and robustness of the Address Book Management System.

---

# 2. Testing Objectives

The testing process aims to ensure:

- Functional correctness
- Data integrity
- Input validation
- Reliable file operations
- Stable application behavior

---

# 3. Testing Levels

## Unit Testing

Verify individual functions.

Examples

- validateName()
- validatePhone()
- searchByPhone()

---

## Integration Testing

Verify interaction between modules.

Examples

- Create → Save
- Load → Search
- Edit → Save

---

## System Testing

Verify complete application workflow.

Examples

- Startup
- Menu Navigation
- Contact Management
- File Persistence
- Exit

---

# 4. Test Cases

| Feature | Test |
|----------|------|
| Create Contact | Valid and Invalid Inputs |
| Search Contact | Existing and Non-existing Contact |
| Edit Contact | Valid and Invalid Updates |
| Delete Contact | Existing and Missing Contact |
| List Contacts | Empty and Populated Address Book |
| Save | File Created Successfully |
| Load | Data Loaded Correctly |

---

# 5. Boundary Testing

The following boundary conditions should be verified.

- Empty Address Book
- Maximum Contacts
- Duplicate Phone
- Duplicate Email
- Invalid Menu Option
- Empty Input
- Long Input

---

# 6. Success Criteria

The project is considered tested when:

- All functional requirements pass.
- Invalid inputs are rejected.
- File operations work correctly.
- No crashes occur during normal usage.

---

# 7. Conclusion

Testing ensures that the Address Book Management System behaves correctly under both normal and abnormal operating conditions.