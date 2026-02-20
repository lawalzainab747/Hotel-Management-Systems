
#include "reservation.h"

// Define the stream extraction operator for date
std::istream& operator>>(std::istream& is, date& dt) {
    char separator; // To read the separator characters (e.g., '/')
    is >> dt.day >> separator >> dt.month >> separator >> dt.year;
    return is;
}

// Define the stream insertion operator for date
std::ostream& operator<<(std::ostream& os, const date& dt) {
    os << dt.day << '/' << dt.month << '/' << dt.year;
    return os;
}

// Function to compare two dates
bool isDateValid(const date& checkin, const date& checkout) {
    if (checkout.year > checkin.year) {
        return true;
    }
    else if (checkout.year == checkin.year) {
        if (checkout.month > checkin.month) {
            return true;
        }
        else if (checkout.month == checkin.month) {
            return checkout.day > checkin.day;
        }
    }
    return false;
}


Reservation::Reservation(int reservation_ID, std::string guest_Name, std::string contact_info, date checkin, date checkout, int RoomNum)
    : reservationID(reservation_ID), guestName(guest_Name), contactinfo(contact_info), checkindate(checkin), checkoutdate(checkout), RoomNumber(RoomNum), amount(0.0), paymentmethod(""),isPaid(false) {}

int Reservation::getReservationID() const
{
    return reservationID;
}

int Reservation::getRoomNumber() const
{
    return RoomNumber;
}

std::string Reservation::getGuestName() const
{
    return guestName;
}

std::string Reservation::getContactInfo() const
{
    return contactinfo;
}

date Reservation::getCheckinDate() const
{
    return checkindate;
}

date Reservation::getCheckoutDate() const
{
    return checkoutdate;
}

void Reservation::processPayment(const std::string& method, double Amount) {
    std::cout << "Processing payment of " << Amount << "HUF using " << method << std::endl;
    paymentmethod = method;
    amount = Amount;
    isPaid = true;
}
