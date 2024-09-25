#include <iostream>
#include <string>

struct Passenger {
    std::string name;
    int passportNumber;
    int seatNumber;
    Passenger* next; 

    Passenger(std::string n, int passNo, int seat) : name(n), passportNumber(passNo), seatNumber(seat), next(NULL) 
	{}
};

struct Flight {
    int flightNumber;
    std::string departure;
    std::string destination;
    std::string date;
    std::string time;
    Passenger* passengerList;  
    Flight* left;  
    Flight* right; 

    Flight(int fNo, std::string dep, std::string dest, std::string d, std::string t) 
        : flightNumber(fNo), departure(dep), destination(dest), date(d), time(t), 
          passengerList(NULL), left(NULL), right(NULL) {}
};

class FlightBST {
public:
    Flight* root;

    FlightBST() : root(NULL) {}

    
    Flight* insertFlight(Flight* node, int flightNumber, std::string departure, std::string destination, std::string date, std::string time) {
        if (!node) {
            return new Flight(flightNumber, departure, destination, date, time);
        }
        if (flightNumber < node->flightNumber)
            node->left = insertFlight(node->left, flightNumber, departure, destination, date, time);
        else if (flightNumber > node->flightNumber)
            node->right = insertFlight(node->right, flightNumber, departure, destination, date, time);
        
        return node;
    }

    
    Flight* searchFlight(Flight* node, int flightNumber) {
        if (!node || node->flightNumber == flightNumber)
            return node;
        if (flightNumber < node->flightNumber)
            return searchFlight(node->left, flightNumber);
        else
            return searchFlight(node->right, flightNumber);
    }

    
    Flight* findMin(Flight* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    
    Flight* deleteFlight(Flight* node, int flightNumber) {
        if (!node) return node;

        if (flightNumber < node->flightNumber) {
            node->left = deleteFlight(node->left, flightNumber);
        } else if (flightNumber > node->flightNumber) {
            node->right = deleteFlight(node->right, flightNumber);
        } else {
            if (!node->left) {
                Flight* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Flight* temp = node->left;
                delete node;
                return temp;
            }

            Flight* temp = findMin(node->right);
            node->flightNumber = temp->flightNumber;
            node->right = deleteFlight(node->right, temp->flightNumber);
        }

        return node;
    }
};


void addPassenger(Flight* flight, std::string name, int passportNumber, int seatNumber) {
    Passenger* newPassenger = new Passenger(name, passportNumber, seatNumber);
    
    if (!flight->passengerList) {
        flight->passengerList = newPassenger;
    } else {
        Passenger* temp = flight->passengerList;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newPassenger;
    }
    std::cout << "Passenger added successfully.\n";
}

void removePassenger(Flight* flight, int passportNumber) {
    Passenger* temp = flight->passengerList;
    Passenger* prev = NULL;

    if (temp != NULL && temp->passportNumber == passportNumber) {
        flight->passengerList = temp->next;
        delete temp;
        std::cout << "Passenger removed successfully.\n";
        return;
    }

    while (temp != NULL && temp->passportNumber != passportNumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        std::cout << "Passenger not found.\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    std::cout << "Passenger removed successfully.\n";
}


void displayFlightDetails(Flight* flight) {
    if (flight) {
        std::cout << "Flight Number: " << flight->flightNumber << std::endl;
        std::cout << "Departure: " << flight->departure << std::endl;
        std::cout << "Destination: " << flight->destination << std::endl;
        std::cout << "Date: " << flight->date << std::endl;
        std::cout << "Time: " << flight->time << std::endl;
        std::cout << "Passengers: \n";

        Passenger* temp = flight->passengerList;
        while (temp) {
            std::cout << "Passenger Name: " << temp->name << ", Passport: " << temp->passportNumber << ", Seat: " << temp->seatNumber << std::endl;
            temp = temp->next;
        }
    } else {
        std::cout << "Flight not found.\n";
    }
}

int main() {
    FlightBST flightSystem;

    flightSystem.root = flightSystem.insertFlight(flightSystem.root, 101, "New York", "Los Angeles", "2024-09-25", "10:00 AM");
    flightSystem.root = flightSystem.insertFlight(flightSystem.root, 102, "Chicago", "Miami", "2024-09-26", "2:00 PM");

    
    Flight* flight = flightSystem.searchFlight(flightSystem.root, 101);
    if (flight) {
        addPassenger(flight, "John Doe", 12345, 12);
        addPassenger(flight, "Jane Smith", 67890, 15);
    }

    
    displayFlightDetails(flight);


    removePassenger(flight, 12345);


    displayFlightDetails(flight);

    
    flightSystem.root = flightSystem.deleteFlight(flightSystem.root, 102);
    std::cout << "Flight 102 deleted.\n";

    return 0;
}

