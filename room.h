#pragma once

#ifndef ROOM_H
#define ROOM_H
#include<istream>
#include<ostream>
#include<fstream>
#include<iostream>
#include<string>



enum class Roomtype {
    Single,
    Deluxe,
    Suite
};

enum class Bookingstatus {
    Booked,
    Available
};

//Declaration of stream extraction operators
std::istream& operator>>(std::istream& is, Roomtype& rt);
std::istream& operator>>(std::istream& is, Bookingstatus& bs);


// Declarations of stream insertion operators
std::ostream& operator<<(std::ostream& os, const Roomtype& rt);
std::ostream& operator<<(std::ostream& os, const Bookingstatus& bs);


class Room
{
private:
    int RoomNumber;
    Roomtype type;
    Bookingstatus status;

public:
    Room(int roomnum, Roomtype typee, Bookingstatus statuss);

    int getRoomNumber() const;

    Roomtype getRoomType() const;

    Bookingstatus getBookingStatus() const;

    void changeBookingStatus(Bookingstatus newStatus);

    void saveRoom(std::ofstream& file) const;

};
#endif /*ROOM_H*/

