# 🏨 **Hotel Room Booking System**

> **Mini‑Project in C (File‑I/O, Structs & Menus)**

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)
2. [Objectives](#objectives)
3. [Tech Stack & Concepts](#tech-stack--concepts)
4. [Data Files (File‑I/O)](#data-files-file-io)
5. [Core Data Structures](#core-data-structures)
6. [Feature Matrix](#feature-matrix)
7. [System Workflows](#system-workflows)
8. [Build & Run Guide](#build--run-guide)
9. [Sample Seed Files](#sample-seed-files)
10. [Future Improvements](#future-improvements)
11. [Credits](#credits)

---

## 📖 Project Overview

A command‑line **Hotel Room Booking System** that demonstrates how **C fundamentals**—arrays, structs, loops, conditionals, functions, and persistent **file I/O**—can be woven together into a role‑based mini application.

*Two personas* drive the system:

* **Admin** 🛠 (manages rooms, monitors revenue, reads feedback)
* **Customer** 🛌 (books, cancels, rates stay)

> ✨ **Why it matters:** It turns textbook C topics into a practical, real‑world scenario—reinforcing memory management, input validation, and modular design.

---

## 🎯 Objectives

* **Design** an intuitive, menu‑driven room‑booking workflow.
* **Enforce** role‑based access (Admin vs Customer).
* **Persist** all critical entities using plain‑text files.
* **Showcase** best practices: input sanitation, struct‑based modeling, and crash‑resistant saves.

---

## 🛠 Tech Stack & Concepts

| Layer             | Details                                                                                                                                                             |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Language**      | C (C11 standard)                                                                                                                                                    |
| **Compiler**      | GCC / MinGW / Clang / MSVC (cross‑platform)                                                                                                                         |
| **Editor**        | VS Code (with C/C++ extension)                                                                                                                                      |
| **Core Concepts** | ‑ Arrays & Structs  ‑ Functions & Modular headers ‑ Loops & Conditionals  ‑ File I/O (`fopen`, `fprintf`, `fscanf`)  ‑ Input buffer sanitation (`getchar`, `fgets`) |

---

## 🗄 Data Files (File‑I/O)

| File            | Purpose                      | Format Example                        |
| --------------- | ---------------------------- | ------------------------------------- |
| `users.txt`     | Registered user credentials  | `john john123` (email password)       |
| `rooms.txt`     | Room master data + occupancy | `1 101 0` (id roomNo isBooked)        |
| `customers.txt` | All active bookings          | `Alice,3,4,104,2,7000.00,Great stay!` |
| `earnings.txt`  | Rolling grand‑total revenue  | `35000.00`                            |

> 📝  *All files are rewritten atomically after each mutating action—guaranteeing consistency even after a crash.*

---

## 🧩 Core Data Structures

```c
#define SINGLE 1
#define DOUBLE 2

typedef struct {
    char email[50];
    char password[50];
} User;

typedef struct {
    int id;
    int number;
    int isBooked;   // 0 = vacant, 1 = booked
} Room;

typedef struct {
    char  name[50];
    int   nights;
    int   roomID;
    int   roomNo;
    int   roomType;     // SINGLE | DOUBLE
    int   hasDiscount;  // bool
    float bill;
    char  feedback[200];
} Customer;
```

---

## 🗺 Feature Matrix

### 🔧 Admin Capabilities

| # | Feature                    | Description                                                      |
| - | -------------------------- | ---------------------------------------------------------------- |
| 1 | **Login**                  | Hard‑coded credentials (`admin / 1234`).                         |
| 2 | **Add Room**               | Create new room records on the fly; persisted to `rooms.txt`.    |
| 3 | **View Bookings**          | List every active customer with room, nights, cost.              |
| 4 | **View Vacant Rooms**      | Live inventory filtered where `isBooked == 0`.                   |
| 5 | **Show Earnings**          | Rolling totals + per‑customer break‑down (reads `earnings.txt`). |
| 6 | **View Feedback**          | Reads comments stored in `customers.txt`.                        |
| 7 | **Reset Rooms (Optional)** | Set all `isBooked` to 0—useful for maintenance.                  |

### 🧳 Customer Capabilities

| # | Feature             | Description                                                   |
| - | ------------------- | ------------------------------------------------------------- |
| 1 | **View Room Types** | Prices (Single 2000 PKR / Double 3500 PKR).                   |
| 2 | **Book Room**       | Prompt for name, type, nights, discount code (`NEWYEAR2025`). |
| 3 | **Receive Receipt** | Auto‑formatted summary with bill.                             |
| 4 | **Cancel Booking**  | Provide booking name + Room ID to roll back.                  |
| 5 | **Give Feedback**   | Leave comments post‑stay; stored for admin review.            |

---

## 🔄 System Workflows

```text
Customer Flow            Admin Flow
──────────────           ────────────
1. View rooms            1. Login
2. Book → receipt        2. Add / reset rooms
3. Payment               3. Monitor bookings
4. (Option) Cancel       4. View feedback, earnings
5. (Option) Feedback     5. Logout
```

---

## ⚙️ Build & Run Guide

```bash
# Compile (Linux / macOS)
$ gcc HotelManagementSystem_FileIO_Full.c -o hotel

# Compile (Windows | MinGW)
> gcc HotelManagementSystem_FileIO_Full.c -o hotel.exe

# Run
$ ./hotel   # or hotel.exe on Windows
```

> **Tip:** Ensure `users.txt`, `rooms.txt`, `customers.txt`, and `earnings.txt` sit in the **same directory** as the executable.

---

## 📦 Sample Seed Files

```txt
# rooms.txt (20 vacant rooms)
1 101 0
2 102 0
...
20 210 0

# users.txt (starter users)
abd 123
ahmad 1233

# customers.txt (empty initially)

# earnings.txt
0.00
```

Feel free to copy‑paste these to bootstrap testing.

---

## 🚀 Future Improvements

* **Date‑stamped bookings** (struct tm for check‑in/out).
* **CSV export** for analytics.
* **Password hashing** instead of plain‑text.
* **Room categories** (Deluxe, Suite) with tiered pricing.
* **Concurrency control** (file locks) for multi‑user CLI sessions.

---

## 🙌 Credits

* **Developer:** *M Abdullah Ameen*
* **Instructor / Course:** *PF CC-112 – Spring Semester 2025*
* **IDE:** VS Code


