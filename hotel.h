#pragma once

#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "reservation.h"
#include "room.h"

class Hotel
{
    private:
        std::vector<Room*> rooms;
        std::vector<Reservation*> reservations;
        std::string RoomFile;
        std::string ReservationFile;

public:
    Hotel(const std::string& Room_File, const std::string& Reservation_File);

    void loadRoomDatabase();

    void loadReservationDatabase();

    //Destructor
    ~Hotel();

    // Add a new room to the hotel
    void addRoom();

    // A function to display the rooms available for booking
    void displayRoomsAvailability() const;

    // Book a reservation for a given room
    void MakeReservation();

    double CheckRoomPrices(const Room& room, const date& checkin, const date& checkout) ;

    Room* SelectRoom();

    void processReservationPayment(Reservation* reservation, const std::string& paymentMethod, double Amount);

    void saveRoomDatabase();

    void checkout(int Reservation_ID);

    bool isLeapYear(int year);

    int daysInMonth(int month, int year);

    int dateToDays(const date& date);

    int daysBetween(const date& checkin, const date& checkout);
    
};

#endif /*HOTEL_H*/

