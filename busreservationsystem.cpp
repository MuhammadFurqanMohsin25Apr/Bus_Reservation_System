#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

void displayBusFile() {
    ifstream file("bus.txt");
    if (!file) {
        cerr << "Error: Could not open bus.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

class Stack {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Queue {
private:
    struct Node {
        void* data;
        Node* next;
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(void* value) {
        Node* newNode = new Node{value, nullptr};
        if (rear != nullptr) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
    }

    void* dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        void* value = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class PassengerNode {
public:
    string name;
    int age;
    string gender;
    string contactNumber;
    PassengerNode* next;

    PassengerNode(string n, int a, string g, string contact)
        : name(n), age(a), gender(g), contactNumber(contact), next(nullptr) {}
};

class Bus {
private:
    string busNumber;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double ticketPrice;
    PassengerNode* passengerList;
    Stack cancelledSeats;
    Queue waitingList;

public:
    Bus(string number, string src, string dest, int seats, double price)
        : busNumber(number), source(src), destination(dest),
          totalSeats(seats), availableSeats(seats), ticketPrice(price), passengerList(nullptr) {}

    bool bookTicket(string name, int age, string gender, string contact) {
        if (availableSeats > 0) {
            PassengerNode* newPassenger = new PassengerNode(name, age, gender, contact);
            if (passengerList == nullptr) {
                passengerList = newPassenger;
            } else {
                PassengerNode* temp = passengerList;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newPassenger;
            }
            availableSeats--;
            return true;
        } else {
            PassengerNode* waitingPassenger = new PassengerNode(name, age, gender, contact);
            waitingList.enqueue(waitingPassenger);
            return false;
        }
    }

    bool cancelTicket(string name) {
        PassengerNode* current = passengerList;
        PassengerNode* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                if (prev == nullptr) {
                    passengerList = current->next;
                } else {
                    prev->next = current->next;
                }

                availableSeats++;
                cancelledSeats.push(1);


                if (!waitingList.isEmpty()) {
                    PassengerNode* waitingPassenger = static_cast<PassengerNode*>(waitingList.dequeue());
                    bookTicket(waitingPassenger->name, waitingPassenger->age,
                               waitingPassenger->gender, waitingPassenger->contactNumber);
                }

                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void displayPassengers() {
        PassengerNode* current = passengerList;
        cout << "\n===== Passenger List =====" << endl;
        while (current != nullptr) {
            cout << "Name: " << current->name << endl;
            cout << "Age: " << current->age << endl;
            cout << "Gender: " << current->gender << endl;
            cout << "Contact: " << current->contactNumber << endl;
            cout << "------------------------" << endl;
            current = current->next;
        }
    }

    string getBusNumber() { return busNumber; }
    string getSource() { return source; }
    string getDestination() { return destination; }
    int getAvailableSeats() { return availableSeats; }
    double getTicketPrice() { return ticketPrice; }
};


class BusReservationSystem {
private:
    vector<Bus*> busList;

public:
    void addBus(string number, string source, string destination, int seats, double price) {
        Bus* newBus = new Bus(number, source, destination, seats, price);
        busList.push_back(newBus);
    }

    void displayAvailableBuses() {
        cout << "\n===== Available Buses =====" << endl;
        for (Bus* bus : busList) {
            cout << "Bus Number: " << bus->getBusNumber() << endl;
            cout << "Source: " << bus->getSource() << endl;
            cout << "Destination: " << bus->getDestination() << endl;
            cout << "Available Seats: " << bus->getAvailableSeats() << endl;
            cout << "Ticket Price: $" << bus->getTicketPrice() << endl;
            cout << "------------------------" << endl;
        }
    }

    Bus* findBus(string busNumber) {
        for (Bus* bus : busList) {
            if (bus->getBusNumber() == busNumber) {
                return bus;
            }
        }
        return nullptr;
    }

    void mainMenu() {
        int choice;
        do {
            cout << "\n===== Bus Reservation System =====" << endl;
            cout << "1. Add New Bus" << endl;
            cout << "2. Display Available Buses" << endl;
            cout << "3. Book Ticket" << endl;
            cout << "4. Cancel Ticket" << endl;
            cout << "5. View Passengers" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addBusMenu(); break;
                case 2: displayAvailableBuses(); break;
                case 3: bookTicketMenu(); break;
                case 4: cancelTicketMenu(); break;
                case 5: viewPassengersMenu(); break;
                case 6: cout << "Thank you for using Bus Reservation System!" << endl;
                        break;
                default: cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 6);
    }

    void addBusMenu() {
        string number, source, destination;
        int seats;
        double price;

        cout << "\nEnter Bus Number: ";
        cin >> number;
        cout << "Enter Source: ";
        cin >> source;
        cout << "Enter Destination: ";
        cin >> destination;
        cout << "Enter Total Seats: ";
        cin >> seats;
        cout << "Enter Ticket Price: ";
        cin >> price;

        addBus(number, source, destination, seats, price);
        cout << "Bus added successfully!" << endl;
    }

    void bookTicketMenu() {
        displayAvailableBuses();
        string busNumber, name, gender, contact;
        int age;

        cout << "\nEnter Bus Number: ";
        cin >> busNumber;

        Bus* selectedBus = findBus(busNumber);
        if (selectedBus) {
            cout << "Enter Passenger Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Enter Contact Number: ";
            cin >> contact;

            if (selectedBus->bookTicket(name, age, gender, contact)) {
                cout << "Ticket booked successfully!" << endl;
            } else {
                cout << "Bus is full. Added to waiting list." << endl;
            }
        } else {
            cout << "Bus not found!" << endl;
        }
    }

    void cancelTicketMenu() {
        string busNumber, name;
        cout << "\nEnter Bus Number: ";
        cin >> busNumber;
        cout << "Enter Passenger Name: ";
        cin >> name;

        Bus* selectedBus = findBus(busNumber);
        if (selectedBus) {
            if (selectedBus->cancelTicket(name)) {
                cout << "Ticket cancelled successfully!" << endl;
            } else {
                cout << "Passenger not found!" << endl;
            }
        } else {
            cout << "Bus not found!" << endl;
        }
    }

    void viewPassengersMenu() {
        string busNumber;
        cout << "\nEnter Bus Number: ";
        cin >> busNumber;

        Bus* selectedBus = findBus(busNumber);
        if (selectedBus) {
            selectedBus->displayPassengers();
        } else {
            cout << "Bus not found!" << endl;
        }
    }

    ~BusReservationSystem() {
        for (Bus* bus : busList) {
            delete bus;
        }
    }
};


int main() {
    
    displayBusFile();
    BusReservationSystem brs;
    brs.mainMenu();
    return 0;
}
