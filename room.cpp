#include "room.h"

// Definition of stream extraction operator for Roomtype
std::istream& operator>>(std::istream& is, Roomtype& rt) {
    std::string str;
    is >> str;
    if (str == "Single") rt = Roomtype::Single;
    else if (str == "Deluxe") rt = Roomtype::Deluxe;
    else if (str == "Suite") rt = Roomtype::Suite;
    else is.setstate(std::ios_base::failbit);
    return is;
}

// Definition of stream extraction operator for Bookingstatus
std::istream& operator>>(std::istream& is, Bookingstatus& bs) {
    std::string str;
    is >> str;
    if (str == "Available") bs = Bookingstatus::Available;
    else if (str == "Booked") bs = Bookingstatus::Booked;
    else is.setstate(std::ios_base::failbit);
    return is;
}

// Stream insertion operator for Roomtype
std::ostream& operator<<(std::ostream& os, const Roomtype& rt) {
    switch (rt) {
    case Roomtype::Single:
        os << "Single";
        break;
    case Roomtype::Deluxe:
        os << "Deluxe";
        break;
    case Roomtype::Suite:
        os << "Suite";
        break;
        // Handle more room types as needed
    default:
        os << "Unknown Roomtype";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Bookingstatus& bs) {
    switch (bs) {
    case Bookingstatus::Booked:
        os << "Booked";
        break;
    case Bookingstatus::Available:
        os << "Available";
        break;

        // Handle more booking statuses as needed
    default:
        os << "Unknown Bookingstatus";
        break;
    }
    return os;
}


Room::Room(int roomnum, Roomtype typee, Bookingstatus statuss) :
    RoomNumber(roomnum), type(typee), status(statuss) {}

int Room::getRoomNumber()const
{
    return RoomNumber;
}

Roomtype Room::getRoomType()const
{
    return type;
}

Bookingstatus Room::getBookingStatus()const
{
    return status;
}

void Room::changeBookingStatus(Bookingstatus newStatus) {
    status = newStatus;
}

void Room::saveRoom(std::ofstream& file) const {
    
    if (file.is_open()) {
        file << RoomNumber << " " << type << " " << status << '\n';
    }
    else {
        std::cerr << "Error: File stream is not open." << std::endl;
    }
}

