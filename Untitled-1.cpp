#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <memory>

using namespace std;

class Passenger {
private:
    string name;
    string contact;
    int userID;
    int trainNumber;

public:
    Passenger(const string& n, const string& c, int id, int trainNum) : name(n), contact(c), userID(id), trainNumber(trainNum) {}

    string getName() const {
        return name;
    }

    string getContact() const {
        return contact;
    }

    int getUserID() const {
        return userID;
    }

    int getTrainNumber() const {
        return trainNumber;
    }
};

class Train {
private:
    int trainNumber;
    string source;
    string destination;
    string departureTime;
    int totalSeats;
    int availableSeats;

public:
    Train(int tNumber, const string& src, const string& dest, const string& depTime, int total, int avail)
        : trainNumber(tNumber), source(src), destination(dest), departureTime(depTime), totalSeats(total), availableSeats(avail) {}

    int getTrainNumber() const {
        return trainNumber;
    }

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    string getDepartureTime() const {
        return departureTime;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    int getAvailableSeats() const {
        return availableSeats;
    }

    void bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            cout << "Seat booked successfully!\n";
        } else {
            cout << "Sorry, no seats available on this train.\n";
        }
    }

    void cancelSeat() {
        if (availableSeats < totalSeats) {
            availableSeats++;
            cout << "Reservation canceled successfully.\n";
        } else {
            cout << "No reservations to cancel.\n";
        }
    }

    void displayInfo() const {
        cout << "Train Number: " << trainNumber << ", Source: " << source
             << ", Destination: " << destination << ", Departure Time: " << departureTime
             << ", Total Seats: " << totalSeats << ", Available Seats: " << availableSeats << endl;
    }
};

class ReservationSystem {
private:
    vector<Train> trains;
    unordered_map<int, unique_ptr<Passenger>> passengers;
    int nextUserID;

public:
    ReservationSystem() : nextUserID(1) {}

    void addTrain(const Train& train) {
        trains.push_back(train);
    }

    void displayTrainSchedules() const {
        cout << "\nTrain Schedules:\n";
        for (const auto& train : trains) {
            train.displayInfo();
        }
    }

    void checkAvailability(int trainNumber) const {
        auto it = find_if(trains.begin(), trains.end(), [&](const Train& train) {
            return train.getTrainNumber() == trainNumber;
        });

        if (it != trains.end()) {
            cout << "Available seats for Train " << trainNumber << ": " << it->getAvailableSeats() << endl;
        } else {
            cout << "Train not found.\n";
        }
    }

    void bookTicket(int trainNumber, const string& name, const string& contact) {
        auto it = find_if(trains.begin(), trains.end(), [&](const Train& train) {
            return train.getTrainNumber() == trainNumber;
        });

        if (it != trains.end()) {
            if (it->getAvailableSeats() > 0) {
                int userID = nextUserID++;
                passengers[userID] = make_unique<Passenger>(name, contact, userID, trainNumber);
                it->bookSeat();
                cout << "Your User ID is: " << userID << endl;
            } else {
                cout << "Sorry, no seats available on this train.\n";
            }
        } else {
            cout << "Train not found.\n";
        }
    }

    void cancelBooking(int userID) {
        auto it = passengers.find(userID);
        if (it != passengers.end()) {
            passengers.erase(it);
            cout << "Reservation canceled successfully.\n";
        } else {
            cout << "User ID not found.\n";
        }
    }

    void displayBookingStatus(int userID) const {
        auto it = passengers.find(userID);
        if (it != passengers.end()) {
            cout << "Booking status for User ID " << userID << ":\n";
            cout << "Name: " << it->second->getName() << ", Contact: " << it->second->getContact() 
                 << ", Train Number: " << it->second->getTrainNumber() << endl;
        } else {
            cout << "User ID not found.\n";
        }
    }
};

int main() {
    ReservationSystem system;

    // Add some sample trains
    system.addTrain(Train(101, "Guwahati", "Silchar", "10:00 AM", 100, 100));
    system.addTrain(Train(102, "Silchar", "Guwahati", "12:00 PM", 120, 100));
    system.addTrain(Train(103, "Guwahati", "Nalbari", "2:00 PM", 80, 80));

    while (true) {
        cout << "\n--- Train Reservation System ---\n";
        cout << "1. View Train Schedules\n";
        cout << "2. Check Seat Availability\n";
        cout << "3. Book Ticket\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Check Booking Status\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayTrainSchedules();
                break;
            case 2: {
                int trainNumber;
                cout << "Enter Train Number: ";
                cin >> trainNumber;
                system.checkAvailability(trainNumber);
                break;
            }
            case 3: {
                int trainNumber;
                string name, contact;
                cout << "Enter Train Number: ";
                cin >> trainNumber;
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter your contact: ";
                cin >> contact;
                system.bookTicket(trainNumber, name, contact);
                break;
            }
            case 4: {
                int userID;
                cout << "Enter your User ID: ";
                cin >> userID;
                system.cancelBooking(userID);
                break;
            }
            case 5: {
                int userID;
                cout << "Enter your User ID: ";
                cin >> userID;
                system.displayBookingStatus(userID);
                break;
            }
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}