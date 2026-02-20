#include "hotel.h"


Hotel::Hotel(const std::string& Room_File, const std::string& Reservation_File) : RoomFile(Room_File), ReservationFile(Reservation_File) {}

Hotel::~Hotel() {
    for (Room* room : rooms) {
        delete room;
    }

    for (Reservation* reservation : reservations) {
        delete reservation;
    }
}

void Hotel::loadRoomDatabase() {
    std::ifstream RoomFilename(RoomFile);
    if (!RoomFilename.is_open()) {
        throw std::runtime_error("Failed to open the Room database file.");
    }


        std::string input;
        while (getline(RoomFilename, input)) {
            std::stringstream ss(input);
            std::string str_room, str_booked;
            int roomnum;
            Roomtype r_type;
            Bookingstatus b_status;
            ss >> roomnum >> str_room >> str_booked;
            std::stringstream(str_room) >> r_type;
            std::stringstream(str_booked) >> b_status;
            rooms.push_back(new Room(roomnum, r_type, b_status));
        }

        RoomFilename.close();
        std::cout << "Database successfully loaded." << std::endl;
    


}



// Function to add rooms to the hotel
void Hotel::addRoom() {
    int roomnum;
    std::string str_room, str_booked;
    std::cout << "Enter the room number: ";
    std::cin >> roomnum;
    std::cout << "Enter the roomtype (Single, Deluxe, Suite) :";
    std::cin >> str_room;
    std::cout << "Enter the Booking status (Booked, Available) :";
    std::cin >> str_booked;

    Roomtype type = (str_room == "Single") ? Roomtype::Single :
        (str_room == "Deluxe") ? Roomtype::Deluxe :
        (str_room == "Suite") ? Roomtype::Suite : Roomtype::Single;

    Bookingstatus status = (str_booked == "Booked") ? Bookingstatus::Booked :
        (str_booked == "Available") ? Bookingstatus::Available : Bookingstatus::Available;
    Room* newroom = new Room(roomnum, type, status);
    rooms.push_back(newroom);

    std::cout << "Room successfully added" << std::endl;
    std::cout << "Roomnumber : " << newroom->getRoomNumber() << std::endl
        << "Roomtype : " << newroom->getRoomType() << std::endl
        << "Booking status : " << newroom->getBookingStatus() << std::endl;
    std::ofstream file(RoomFile, std::ios::app);
    if (file.is_open()) {
        file << '\n' << roomnum << " " << type << " " << status;
        file.close();
    }
    else {
        std::cerr << "File: " << RoomFile << " opening is unsuccessful" << std::endl;
    }


}

// Function to display available rooms
void Hotel::displayRoomsAvailability() const {

    std::ifstream RoomFilename(RoomFile);
    if (!RoomFilename.is_open()) {
        std::cerr << "Error opening file: " << RoomFile << std::endl;
        return;
    }


    std::cout << '\n' << "The rooms availability are provided below" << std::endl;
    std::string input;
    while (getline(RoomFilename, input)) {
        std::stringstream ss(input);
        int roomNum;
        std::string str_room, str_booked;

        ss >> roomNum >> str_room >> str_booked;

        Bookingstatus status = (str_booked == "Booked") ? Bookingstatus::Booked : Bookingstatus::Available;

        if (status == Bookingstatus::Booked) {
            std::cout << "RoomnNumber: " << roomNum << "  Roomtype: " << str_room << "  Status : Booked" << std::endl;
        }
    }

        RoomFilename.clear();
        RoomFilename.seekg(0, std::ios::beg);

        while (getline(RoomFilename, input)) {
            std::stringstream ss(input);
            int roomNum;
            std::string str_room, str_booked;

            ss >> roomNum >> str_room >> str_booked;

            Bookingstatus status = (str_booked == "Booked") ? Bookingstatus::Booked : Bookingstatus::Available;

            if (status == Bookingstatus::Available) { 
                std::cout << " RoomnNumber: " << roomNum << "  Roomtype  " << str_room << "  Status : Available" << std::endl;
            }
        }

    }



void Hotel::loadReservationDatabase() {
    std::ifstream Reservation_File(ReservationFile);
    if (Reservation_File.is_open()) {
        std::string input;
        while (getline(Reservation_File, input)) {
            std::stringstream ss(input);
            std::string str_room, str_booked;
            int Reservation_ID, RoomNum;
            std::string guest_Name, Contact_Info;
            date checkin, checkout;
            
            ss >> Reservation_ID >> guest_Name >> Contact_Info >> checkin >> checkout >> RoomNum;

            reservations.push_back(new Reservation(Reservation_ID, guest_Name, Contact_Info, checkin, checkout, RoomNum));
        }

        Reservation_File.close();
        std::cout << "Database successfully loaded." << std::endl;
    }

    else {
        std::cerr << "Failed to open the Reservation database file." << std::endl;
    }
}
// Function to make a reservation
void Hotel::MakeReservation() {
    int Reservation_ID;
    std::string guest_Name, Contact_info;
    date checkin, checkout;
    std::cout << "Enter your reservation ID : ";
    std::cin >> Reservation_ID;
    std::cout << "Enter you name : ";
    std::cin >> guest_Name;
    std::cout << "Enter contact info, preferable phone number or email address: ";
    std::cin >> Contact_info;
    std::cout << "Input your checkin date in the format DD MM YYYY :";
    std::cin >> checkin.day >> checkin.month >> checkin.year;
    std::cout << "Input your checkout date in the format DD MM YYYY :";
    std::cin >> checkout.day >> checkout.month >> checkout.year;

    //Select a room for reservation
    Room* selectedRoom = SelectRoom();
    if (selectedRoom->getRoomNumber() == 0) {
        std::cerr << "Error: Room selection failed." << std::endl;
        return;
    }


    if (isDateValid(checkin, checkout)) {

        //Calculate the total price
        double totalPrice = CheckRoomPrices(*selectedRoom, checkin, checkout);

        Reservation* newreservation = new Reservation(Reservation_ID, guest_Name, Contact_info, checkin, checkout, selectedRoom->getRoomNumber());
        reservations.push_back(newreservation);

        std::string paymentMethod;
        std::cout << ".....Proceed to make payment....." << std::endl;
        std::cout << "Enter your Payment method : (Creditcard, Debitcard, Cash) : ";
        std::cin >> paymentMethod;
        processReservationPayment(newreservation, paymentMethod, totalPrice);
        std::cout << "Reservation successfully made." << std::endl;

        // Change the booking status of the selected room to Booked
        selectedRoom->changeBookingStatus(Bookingstatus::Booked);

        std::cout << '\n' << "Your Reservation details is displayed below " << std::endl;
        std::cout << "Reservation ID : " << newreservation->getReservationID() << std::endl
                    << "guestName : " << newreservation->getGuestName() << std::endl
                    << "Contact Info : " << newreservation->getContactInfo() << std::endl
                    << "Check in date : " << newreservation->getCheckinDate() << std::endl
                    << "Checkout date : " << newreservation->getCheckoutDate() << std::endl
                    << "Room number : " << selectedRoom->getRoomNumber() << std::endl
                    << "Total Price: " << totalPrice << std::endl;

        std::ofstream file(ReservationFile, std::ios::app);


        if (file.is_open()) {
            file << '\n' << Reservation_ID << " " << guest_Name << " " << Contact_info << " " << checkin << " " << checkout << " " << selectedRoom->getRoomNumber() << " " << totalPrice;
            file.close();
        }

        else {
            std::cerr << "File: " << ReservationFile << " opening is unsuccessful" << std::endl;
        }

        // Save the updated room status to the room database file
        saveRoomDatabase();
    }
    else {
        std::cerr << "Error: Checkout date must be later than checkin date." << std::endl;
    }

   
}

void Hotel::saveRoomDatabase() {
    std::ofstream file(RoomFile);
    if (file.is_open()) {
        for (const auto& room : rooms) {
            room->saveRoom(file);
        }
        file.close();
    }
    else {
        std::cerr << "Error: Could not open room database file for writing." << std::endl;
    }
}

Room* Hotel::SelectRoom() {
    // Display available rooms to the user
    displayRoomsAvailability();

    // Prompt the user to select a room
    int roomNumber;
    std::cout << "Enter the room number you want to reserve: ";
    std::cin >> roomNumber;

    // Find the selected room in the list of available rooms
    for (Room* roomPtr : rooms) {
        if (roomPtr->getRoomNumber() == roomNumber && roomPtr->getBookingStatus() == Bookingstatus::Available) {
            return roomPtr; // Return the pointer to the selected room
        }
    }

    // If the room number entered by the user is not valid or not available,
    throw std::runtime_error("Invalid room number or room not available.");
}

void Hotel::checkout(int Reservation_ID) {
    try {
        // Search for the reservation with the provided ID
        Reservation* targetReservation = nullptr;
        for (size_t i = 0; i < reservations.size(); ++i) {
            if (reservations[i]->getReservationID() == Reservation_ID) {
                targetReservation = reservations[i];
                break;
            }
        }

        // If the reservation with the provided ID is not found, throw an exception
        if (targetReservation == nullptr) {
            throw std::runtime_error("Reservation with the provided ID not found.");
        }

        // Get the room associated with the reservation
        Room* targetRoom = nullptr;
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i]->getRoomNumber() == targetReservation->getRoomNumber()) {
                targetRoom = rooms[i];
                break;
            }
        }

        // If the room associated with the reservation is not found, throw an exception
        if (targetRoom == nullptr) {
            throw std::runtime_error("Room associated with the reservation not found.");
        }

        // Change the booking status of the room to Available
        targetRoom->changeBookingStatus(Bookingstatus::Available);
        std::cout << "Checkout successful. Room " << targetRoom->getRoomNumber() << " is now available." << std::endl;

        // Save the updated room status to the room database file
        saveRoomDatabase();

        // Remove the reservation from the list and deallocate memory
        delete targetReservation;
        reservations.erase(std::remove(reservations.begin(), reservations.end(), targetReservation), reservations.end());
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}



void Hotel::processReservationPayment(Reservation* reservation, const std::string& paymentMethod, double Amount) {
    reservation->processPayment(paymentMethod, Amount);
    std::cout << "Payment successful for reservation ID: " << reservation->getReservationID() << std::endl;
}



double Hotel::CheckRoomPrices(const Room& room, const date& checkin, const date& checkout)
{
    double price = 0;
    switch (room.getRoomType())
    {
        case Roomtype::Single :
            price = 5000;
            break;

        case Roomtype::Deluxe :
            price = 10000;
            break;

        case Roomtype::Suite :
            price = 20000;
            break;
        default:
            price = 5000;
            break;
    }
    int numberOfDays = daysBetween(checkin, checkout);

    return price * numberOfDays;
}

bool Hotel::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Hotel::daysInMonth(int month, int year) {
    switch (month) {
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 31;
    }
}

int Hotel::dateToDays(const date& date) {
    int days = date.day;

    for (int m = 1; m < date.month; ++m) {
        days += daysInMonth(m, date.year);
    }

    for (int y = 1; y < date.year; ++y) {
        days += isLeapYear(y) ? 366 : 365;
    }

    return days;
}

int Hotel::daysBetween(const date& checkin, const date& checkout) {
    int checkinDays = dateToDays(checkin);
    int checkoutDays = dateToDays(checkout);
    return checkoutDays - checkinDays;
}

