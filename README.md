# Railway Ticket Reservation System (C++ DSA Project)

A console-based Railway Ticket Reservation System written in C++ that demonstrates practical applications of core Data Structures and Algorithms.

## Data Structures Used
- **Array of Structs (`Train`)**: Stores train numbers, routes (Lahore–Karachi, Islamabad–Lahore, Peshawar–Rawalpindi, Quetta–Multan), and available seat counts.
- **Singly Linked List (`Passenger`)**: Dynamically stores active passenger bookings and supports insertion and deletion on cancellation.
- **Queue (`std::queue`)**: Manages the waiting list in First-In, First-Out (FIFO) order when seats are full.
- **Stack (`std::stack`)**: Tracks cancelled ticket IDs in Last-In, First-Out (LIFO) order.
- **Binary Search Tree (`TreeNode`)**: Indexes booked tickets by `ticketID` for fast search operations.

## Features
- View trains and remaining seat availability
- Book tickets and assign seat numbers (or add passengers to the waiting list)
- Cancel tickets by Ticket ID and track cancelled IDs
- Search passengers by Ticket ID using a BST
- Display active passengers, waiting list, and cancelled tickets

## How to Compile and Run
```bash
g++ -std=c++17 main.cpp -o railway_system
./railway_system
