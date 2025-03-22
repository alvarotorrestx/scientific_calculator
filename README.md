# Scientific Calculator

## Overview
This is a **scientific calculator** built using C++ and `wxWidgets`. The application provides an interactive GUI with dynamically created buttons using a **Button Factory**, allowing for a flexible and scalable design.

---

## Features
- **Graphical User Interface (GUI)** built with `wxWidgets`.
- **Dynamic Button Factory** to generate calculator buttons programmatically.
- Supports **basic arithmetic** operations (+, -, *, /, %).
- Implements **scientific functions** such as trigonometry, logarithms, and exponentiation.
- **Error handling** for invalid inputs and edge cases.
- Designed using **Object-Oriented Programming (OOP) principles**.

---

## Screenshots
#### **Default Layout:**
![image](https://github.com/user-attachments/assets/c919d3af-7e07-4106-8769-2c436681dce4)


#### **Trigonometric Function: (Radians)**
![image](https://github.com/user-attachments/assets/4bcfed90-a715-4dc5-8a9d-c44a2a7f3ae2)
![image](https://github.com/user-attachments/assets/acc8224f-ed84-4800-bcfa-dd1d478b430e)


#### **PEMDAS: (Radians)**
![image](https://github.com/user-attachments/assets/6db64a8e-ba4d-47f6-b2c4-d1a2f700a8b8)
![image](https://github.com/user-attachments/assets/186f086a-52d2-4faa-a874-7b15211a9477)



---

## Getting Started

### **Prerequisites**
To build and run this project, ensure you have:
- **C++17 or later** installed.
- **Visual Studio 2022** (or another compatible C++ IDE).
- **Git** for version control.
- **wxWidgets** installed (Follow installation steps below).

---

## **wxWidgets Installation**
To run this project, you must install `wxWidgets`:

1. **Download wxWidgets** from the official site:  
   🔗 [https://www.wxwidgets.org/downloads/](https://www.wxwidgets.org/downloads/)

2. **Extract & Install**:  
   - Unzip the downloaded file.  
   - Move the `wxWidgets` folder to **`C:\wxWidgets`** (recommended).

3. **Build wxWidgets**:  
   - Open **Visual Studio 2022**.
   - Navigate to:  
     ```
     C:\wxWidgets\build\msw\
     ```
   - Open `wx_vc17.sln`.
   - Build the entire solution.

---

## **Setup Instructions**
Once **wxWidgets is installed and built**, follow these steps:

1. **Fork the Repository**:  
   - Click the **"Fork"** button in the top-right corner of the repository page.

2. **Clone Your Fork**:  
   ```bash
   git clone https://github.com/yourusername/scientific_calculator.git
   cd scientific_calculator
   ```
3. Open the Project in Visual Studio:
   Open Scientific_Calculator.sln.

4. Configure Project Settings:

   Navigate to Project Properties
   
   C/C++ → General → Additional Include Directories:
   ```bash
   C:\wxWidgets\include;C:\wxWidgets\include\msvc
   ```
   C/C++ → All Options → Additional Include Directories:
   ```bash
   C:\wxWidgets\include;C:\wxWidgets\include\msvc
   ```

   Linker → General → Additional Library Directories:
   ```bash
   C:\wxWidgets\lib\vc_lib
   ```

   Linker → System:
   Ensure **Subsystem** is set to **Windows (/SUBSYSTEM:WINDOWS)**.

6. Ensure the Build Configuration is Set Correctly:
   Select Win32 Debug mode before building.

7. Build & Run

## **Troubleshooting**
If the application does not compile, check the following:
   - Ensure wxWidgets is installed and built correctly.
   - Double-check project include paths and linker settings.
   - Ensure the app is running in Win32 Debug mode.
   - Try restarting Visual Studio if build issues persist.

## **Notes**
   This repository includes source files only—wxWidgets must be installed separately.

## **License**
This project is licensed under the MIT License.
