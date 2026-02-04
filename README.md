# System_Design

## Overview
This repo contains a small set of C++, Java, and static web files for software design practice.

## Files
- 2nd.cpp: Simple C++ source file.
- MovieTicketBookingSystem.java: Java program with related classes (`Booking`, `Customer`, `Movie`, `Screen`, `Seat`, `Show`, `Theater`/`Theatre`).
- index.html, script.js, style.css: Static web page assets.

## Build & Run

### C++ (Windows, MinGW)
Use the existing VS Code task or run manually:

```powershell
g++ -g 2nd.cpp -o 2nd.exe
./2nd.exe
```

### Java
Compile all classes and run the main program:

```powershell
javac *.java
java MovieTicketBookingSystem
```

### Web
Open index.html in your browser (no server required).

## Notes
- Build outputs (e.g., `*.class`, `*.exe`, `.vscode/`) are ignored via `.gitignore`.
- If any binaries were previously committed, they have been untracked in a later commit.
