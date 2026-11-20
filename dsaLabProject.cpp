
/*
 * ============================================================================
 * Project: Railway Ticket Reservation System (C++ DSA Project)
 * Description: A console-based Railway Reservation System written in C++ that
 *              demonstrates practical applications of core Data Structures and
 *              Algorithms.
 *
 * Data Structures Used:
 * - Array of Structs (Train): Stores train numbers, routes (Lahore-Karachi,
 *   Islamabad-Lahore, Peshawar-Rawalpindi, Quetta-Multan), and available seat
 *   counts.
 * - Singly Linked List (Passenger): Dynamically stores active passenger
 *   bookings and supports insertion and deletion on cancellation.
 * - Queue (std::queue): Manages the waiting list in First-In, First-Out
 *   (FIFO) order when seats are full.
 * - Stack (std::stack): Tracks cancelled ticket IDs in Last-In, First-Out
 *   (LIFO) order.
 * - Binary Search Tree (TreeNode): Indexes booked tickets by ticketID for
 *   fast search operations.
 *
 * Features:
 * - View trains and remaining seat availability
 * - Book tickets and assign seat numbers (or add passengers to the waiting list)
 * - Cancel tickets by Ticket ID and track cancelled IDs
 * - Search passengers by Ticket ID using a BST
 * - Display active passengers, waiting list, and cancelled tickets
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int NUM_TRAINS = 4;
const int SEATS = 5;

// ================== ARRAY OF STRUCTS (TRAINS) ==================
struct Train {
    int trainNo;
    string source, destination;
    int availableSeats;
};

Train trains[NUM_TRAINS] = {
    {101, "Lahore", "Karachi", SEATS},
    {102, "Islamabad", "Lahore", SEATS},
    {103, "Peshawar", "Rawalpindi", SEATS},
    {104, "Quetta", "Multan", SEATS}
};

// ================== LINKED LIST (ACTIVE PASSENGERS) ==================
struct Passenger {
    int ticketID;
    string name;
    int age;
    int trainNo;
    int seatNo;
    Passenger* next;
};

Passenger* head = NULL;
int ticketCounter = 1000;

// ================== QUEUE (FIFO WAITING LIST) ==================
queue<string> waitingList;

// ================== STACK (LIFO CANCELLED TICKETS) ==================
stack<int> cancelledTickets;

// ================== BINARY SEARCH TREE (TICKET LOOKUP) ==================
struct TreeNode {
    int ticketID;
    string name;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* root = NULL;

TreeNode* insert(TreeNode* node, int id, string name) {
    if (node == NULL) {
        TreeNode* temp = new TreeNode;
        temp->ticketID = id;
        temp->name = name;
        temp->left = temp->right = NULL;
        return temp;
    }

    if (id < node->ticketID)
        node->left = insert(node->left, id, name);
    else
        node->right = insert(node->right, id, name);

    return node;
}

TreeNode* search(TreeNode* node, int id) {
    if (node == NULL || node->ticketID == id)
        return node;

    if (id < node->ticketID)
        return search(node->left, id);

    return search(node->right, id);
}

void inorder(TreeNode* node) {
    if (node == NULL) return;

    inorder(node->left);
    cout << node->ticketID << " - " << node->name << endl;
    inorder(node->right);
}

int findTrain(int tno) {
    for (int i = 0; i < NUM_TRAINS; i++) {
        if (trains[i].trainNo == tno)
            return i;
    }
    return -1;
}

void bookTicket() {
    string name;
    int age, trainNo;

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Train No: ";
    cin >> trainNo;

    int idx = findTrain(trainNo);

    if (idx == -1) {
        cout << "Invalid Train!\n";
        return;
    }

    if (trains[idx].availableSeats > 0) {

        Passenger* newNode = new Passenger;
        newNode->ticketID = ++ticketCounter;
        newNode->name = name;
        newNode->age = age;
        newNode->trainNo = trainNo;
        newNode->seatNo = SEATS - trains[idx].availableSeats + 1;
        newNode->next = head;
        head = newNode;

        trains[idx].availableSeats--;

        root = insert(root, newNode->ticketID, name);

        cout << "Booked! Ticket ID: " << newNode->ticketID << endl;
        cout << "Seat No: " << newNode->seatNo << endl;

    } else {
        waitingList.push(name);
        cout << "No seats! Added to waiting list.\n";
    }
}

void cancelTicket() {
    int id;
    cout << "Enter Ticket ID: ";
    cin >> id;

    Passenger* temp = head;
    Passenger* prev = NULL;

    while (temp != NULL) {
        if (temp->ticketID == id) {

            int idx = findTrain(temp->trainNo);
            trains[idx].availableSeats++;

            cancelledTickets.push(id);

            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            delete temp;

            cout << "Cancelled Successfully!\n";

            if (!waitingList.empty()) {
                cout << "Promoted from waiting: " << waitingList.front() << endl;
                waitingList.pop();
            }

            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Ticket not found!\n";
}

void displayPassengers() {
    Passenger* temp = head;

    if (!temp) {
        cout << "No bookings.\n";
        return;
    }

    while (temp) {
        cout << temp->ticketID << " | "
             << temp->name << " | "
             << temp->trainNo << " | Seat "
             << temp->seatNo << endl;

        temp = temp->next;
    }
}

void searchPassenger() {
    int id;
    cout << "Enter Ticket ID: ";
    cin >> id;

    TreeNode* res = search(root, id);

    if (res)
        cout << "Found: " << res->ticketID << " " << res->name << endl;
    else
        cout << "Not Found!\n";
}

void showWaiting() {
    queue<string> temp = waitingList;

    cout << "Waiting List:\n";
    while (!temp.empty()) {
        cout << temp.front() << endl;
        temp.pop();
    }
}

void showCancelled() {
    stack<int> temp = cancelledTickets;

    cout << "Cancelled Tickets:\n";
    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}

void showTrains() {
    for (int i = 0; i < NUM_TRAINS; i++) {
        cout << trains[i].trainNo << " | "
             << trains[i].source << " -> "
             << trains[i].destination
             << " | Seats: " << trains[i].availableSeats << endl;
    }
}

int main() {
    int ch;

    do {
        cout << " RAILWAY SYSTEM" << endl;
        cout << "1. View Trains\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. Search (BST)\n";
        cout << "5. Display Passengers\n";
        cout << "6. Waiting List\n";
        cout << "7. Cancelled Tickets\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                showTrains();
            }
            break;
            case 2: {
                bookTicket();
            }
            break;
            case 3: {
                cancelTicket();
            }
            break;
            case 4: {
                searchPassenger();
            }
            break;
            case 5: {
                displayPassengers();
            }
            break;
            case 6: {
                showWaiting();
            }
            break;
            case 7: {
                showCancelled();
            }
            break;
        }

    } while (ch != 8);

    return 0;
}
