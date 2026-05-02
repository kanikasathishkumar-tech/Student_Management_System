# 🎓 Student Management System

A console-based **Student Management System** written in **C++** that efficiently manages student records using file handling and a menu-driven interface.


# 📋 Features

- ➕ **Add** new student records
- 📋 **Display** all students in a formatted table
- 🔍 **Search** for a student by ID
- ✏️ **Update** existing student information
- 🗑️ **Delete** student records (with confirmation)
- 📊 **Statistics** — total count, average/highest/lowest GPA
- 💾 **Persistent storage** via file handling (`students.dat`)

---

## 🛠️ Tech Stack

- **Language:** C++
- **Compiler:** G++ (MinGW / GCC)
- **Storage:** CSV-based flat file (`students.dat`)
- **IDE:** Any — VS Code recommended

---

## 🚀 Getting Started

### Prerequisites

- G++ compiler installed ([MinGW for Windows](https://winlibs.com))
- VS Code (optional but recommended)

### Clone the Repository

```bash
git clone https://github.com/your-username/student-management-system.git
cd student-management-system
```

### Compile

```bash
g++ student_management.cpp -o sms
```

### Run

```bash
# Linux / macOS
./sms

# Windows
sms.exe
```

---

## 📂 Project Structure

```
student-management-system/
├── student_management.cpp   # Main source file
├── students.dat             # Auto-generated data file (created on first run)
└── README.md
```

---

## 🖥️ Menu Options

```
=======================================================
             STUDENT MANAGEMENT SYSTEM
=======================================================

  1. Add Student
  2. Display All Students
  3. Search Student by ID
  4. Update Student
  5. Delete Student
  6. Show Statistics
  0. Exit
```

---

## 📦 Data Fields

| Field   | Type   | Description              |
|---------|--------|--------------------------|
| ID      | int    | Unique student identifier |
| Name    | string | Full name                 |
| Age     | int    | Student age               |
| Course  | string | Enrolled course/program   |
| GPA     | float  | Grade point average (0–4.0) |

---

## 💡 How It Works

- All records are stored in `students.dat` as comma-separated values
- The file is loaded into memory at the start of each operation
- After every add/update/delete, the file is rewritten with updated data
- Input validation is applied for all fields (ID uniqueness, GPA range, age, etc.)

---

## 📸 Sample Output

```
=======================================================
                  ALL STUDENTS
=======================================================

ID    Name                  Age   Course            GPA
----------------------------------------------------------
1     Alice Johnson         20    Computer Science  3.85
2     Bob Smith             22    Mathematics       3.40
3     Carol White           21    Physics           3.90

Total records: 3
```

---

