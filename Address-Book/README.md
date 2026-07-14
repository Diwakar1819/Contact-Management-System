# 📖 Address Book Management System

A robust, console-based address book application implemented in standard, portable C. It features structured modular programming, custom input validation, duplicate prevention, and persistent file-based database persistence.

---

## Features Overview

| Feature | Description |
| :-- | :--- |
| **✨ Create Contact** | Interactive contact insertion with active field validation. |
| **🔍 Case-Insensitive Search** | Search by name, phone, or email. Handles duplicate name entries gracefully. |
| **✏️ Edit Contact** | Modify name, phone, or email of existing records securely. |
| **❌ Delete Contact** | Confirm and remove records dynamically from memory. |
| **📋 List Contacts** | Outputs formatted records of all saved contacts. |
| **💾 CSV Persistence** | File operations load contacts on startup and persist updates on exit. |

---

## 🛡️ Input Validation & Constraints

| Field | Validation Rules / Constraints | Error Handled |
| :--- | :--- | :--- |
| **Name** | Only alphabetical characters, spaces, and `.` allowed. Cannot be empty. | Empty/Invalid Character |
| **Phone** | Must contain exactly 10 numerical digits. Must be unique. | Empty/Invalid Length/Non-Digit/Duplicate |
| **Email** | Must contain exactly one `@` and at least one `.` after `@`. Must be unique. | Empty/Invalid Format/Duplicate |

---

## 🛠️ Project Directory Tree

The source code separates application execution, interface declarations, core logic, validation helper functions, and storage logic:

```text
Address-Book/
├── data/
│   └── contacts.csv        # Persistent database file (CSV)
├── include/
│   ├── contact.h           # Structure definition and core function prototypes
│   ├── contact_helper.h    # Prototypes for validation, display, and search subroutines
│   └── file.h              # File I/O function declarations
├── src/
│   ├── contact.c           # High-level contact operations (CRUD flow)
│   ├── contact_helper.c    # Low-level input checks & string helpers (C standard library only)
│   ├── file.c              # CSV file loading and saving routines
│   └── main.c              # Main application loop and menu router
├── test/
│   └── TestCases.md        # Comprehensive 25-case testing matrix
├── docs/
│   └── 10_Running_guide    # Compilation and running instructions
├── README.md               # User guide and project details
└── .gitignore              # Configured Git ignore rules
```

---

## 🚀 How to Run the Project

### 1. Compilation
Navigate to the project root directory (`Address-Book`) and compile the program using `gcc`:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/contact.c src/contact_helper.c src/file.c -o addressbook
```

> [!NOTE]  
> The compilation command uses `-Wall` and `-Wextra` flags to enforce clean code without warnings.

### 2. Running the Application
Execute the compiled binary from the project root:

```bash
./addressbook
```

---

## 🧪 Testing

The system has been verified against a matrix of **25 testing scenarios** defined in `test/TestCases.md`.

*   **Robustness:** Correctly handles buffer overflows on inputs, clearing trailing newlines, and cleaning input streams to prevent infinite loop bugs on type mismatches.
*   **Portability:** Swapped POSIX-specific functions (like `strcasecmp`) with standard C alternatives (`tolower` + `strcmp`) to make it fully portable across Windows, Mac, and Linux platforms.