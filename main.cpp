#include "hotel.h"
#include <iostream>
#include <string>

int main() {
    Hotel hotel("RoomDatabase.txt", "ReservationDatabase.txt");

    hotel.loadRoomDatabase();
    hotel.loadReservationDatabase();

    int choice;
    do {
        std::cout << "_________________________________________";
        std::cout << "\nWelcome to my Hotel Management System" << std::endl;
        std::cout << "1. Add Room" << std::endl;
        std::cout << "2. Display Rooms Availability" << std::endl;
        std::cout << "3. Make reservation" << std::endl;
        std::cout << "4. Check out" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                hotel.addRoom();
                break;
            }
            case 2: {
                hotel.displayRoomsAvailability();
                break;
            }
            case 3: {
                hotel.MakeReservation();
                break;
            }
            case 4: {
                int Reservation_ID;
                std::cout << "Enter your reservation ID to check out of the room: ";
                std::cin >> Reservation_ID;
                hotel.checkout(Reservation_ID);
                break;
            }

            case 5:
                std::cout << "Exiting..." << std::endl;
            break;

            default:
                std::cerr << "Invalid choice! Please enter a number between 1 and 5." << std::endl;
        }
    } while (choice != 5);
    return 0;
}