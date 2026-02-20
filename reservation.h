#pragma once

#ifndef RESERVATION_H
#define RESERVATION_H

#include<string>
#include<iostream>

struct date {
    int day;
    int month;
    int year;

    // Friend function for stream extraction
    friend std::istream& operator>>(std::istream& is, date& dt);
    friend std::ostream& operator<<(std::ostream& os, const date& dt);
};

bool isDateValid(const date& checkin, const date& checkout);

// Reservation class representing a reservation in the hotel
class Reservation {
private:
    int reservationID;
    std::string guestName;
    std::string contactinfo;
    date checkindate;
    date checkoutdate;
    int RoomNumber;
    double amount;
    std::string paymentmethod;
    bool isPaid;
    

public:
    Reservation(int reservation_ID, std::string guest_Name, std::string contact_info, date checkin, date checkout, int RoomNum);

    int getReservationID() const;

    int getRoomNumber() const;

    std::string getGuestName() const;

    std::string getContactInfo() const;

    date getCheckinDate() const;

    date getCheckoutDate() const;  

    void processPayment(const std::string& method, double amount);
};

#endif /*RESERVATION_H*/

