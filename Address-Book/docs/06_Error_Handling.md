# Address Book Management System — Error Handling Strategy

---

## Document Information

| Field | Value |
|--------|-------|
| Project | Address Book Management System |
| Document | Error Handling Strategy |
| Version | 1.0 |
| Sprint | Sprint 0 |
| Status | Final |

---

# 1. Purpose

This document defines the error handling strategy for the Address Book Management System.

The objective is to ensure that invalid operations are detected early, appropriate feedback is provided to the user, and the integrity of the Address Book is always maintained.

---

# 2. Error Handling Philosophy

The system follows these principles:

- Detect errors as early as possible.
- Never store invalid data.
- Preserve existing data.
- Display meaningful error messages.
- Recover gracefully whenever possible.
- Avoid abrupt program termination.

---

# 3. Error Categories

| Category | Description |
|----------|-------------|
| Input Errors | Invalid user input |
| Validation Errors | Invalid contact information |
| Duplicate Errors | Duplicate phone/email |
| Search Errors | Contact not found |
| File Errors | File open/read/write failures |
| System Errors | Address book full or unexpected failures |

---

# 4. Error Handling Matrix

| Error | Cause | System Response |
|--------|------|----------------|
| Invalid Menu Choice | Unsupported option | Display error and return to menu |
| Invalid Name | Invalid characters | Prompt user again |
| Invalid Phone | Wrong format | Prompt user again |
| Invalid Email | Incorrect format | Prompt user again |
| Duplicate Phone | Already exists | Reject entry |
| Duplicate Email | Already exists | Reject entry |
| Contact Not Found | Search failed | Inform user |
| Empty Address Book | No contacts available | Display message |
| Address Book Full | Maximum limit reached | Reject new contact |
| File Open Failure | File unavailable | Display error |
| File Read Failure | Corrupted file | Abort loading |
| File Write Failure | Storage error | Notify user |

---

# 5. Recovery Strategy

Whenever an error occurs, the system follows this sequence.

```

```text
Detect Error
      │
      ▼
Display Error Message
      │
      ▼
Discard Invalid Operation
      │
      ▼
Return to Safe State
      │
      ▼
Continue Execution
```

```markdown
---

# 6. Data Protection Rules

The application shall never:

- Store partially validated data.
- Modify existing contacts before validation.
- Reduce contactCount incorrectly.
- Continue file operations after fatal file errors.

---

# 7. Error Message Guidelines

Error messages should:

- Clearly describe the problem.
- Suggest corrective action where appropriate.
- Avoid exposing implementation details.

Example

ERROR: Phone number must contain exactly 10 digits.

instead of

ERROR 103

---

# 8. Key Design Decisions

| Decision | Reason |
|----------|--------|
| Validate before processing | Prevent invalid state |
| Abort invalid operations | Maintain data integrity |
| Clear user feedback | Improve usability |
| Graceful recovery | Prevent application crashes |

---

# 9. Conclusion

The error handling strategy ensures that the application remains reliable, predictable, and user-friendly while protecting the integrity of stored contact information.