#  Bus Reservation System

A console-based C++ project that simulates a bus reservation system. It allows users to manage buses, book and cancel tickets, maintain a waiting list using queues, and track cancelled seats using stacks.

---

##  Features

* Add new buses with seat and fare details
* Display all available buses
* Book tickets (adds to waiting list if the bus is full)
* Cancel tickets (fills the seat with a waiting passenger if available)
* View passenger list for a specific bus
* File reading functionality to display bus data from `bus.txt`
* Uses Stack (for cancelled seats) and Queue (for waiting list) data structures

##  Technologies Used

* **Language:** C++
* **Concepts:** Object-Oriented Programming (OOP), File Handling, Linked Lists, Stack, Queue
* **IDE:** Any C++ supported IDE (e.g., Code::Blocks, Visual Studio, etc.)

---

##  Project Structure

```bash
├── main.cpp         # Main code file
├── bus.txt          # Bus details file (read-only display at program start)
```

---

##  How to Run

1. Make sure you have a C++ compiler installed (e.g., `g++`).
2. Compile the code:

   ```bash
   g++ main.cpp -o bus_system
   ```
3. Run the executable:

   ```bash
   ./bus_system
   ```
4. Follow the on-screen menu to interact with the system.

---

##  Sample `bus.txt` Format

```
Bus No: B123
From: City A
To: City B
Seats: 40
Fare: $10
```

---

##  Notes

* Cancelled tickets immediately allocate seats to passengers in the waiting list.
* You can customize the `bus.txt` file to pre-load or display existing buses.
* All data is stored in memory; no database or file persistence is used beyond display.
