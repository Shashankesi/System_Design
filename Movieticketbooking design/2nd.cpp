#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* ================= Movie Entity ================= */
class Movie {
public:
    string movieId;
    string title;
    string genre;
    int duration;

    Movie(string id, string t, string g, int d) {
        movieId = id;
        title = t;
        genre = g;
        duration = d;
    }
};

/* ================= Seat Entity ================= */
class Seat {
public:
    string seatNumber;
    bool isBooked;

    Seat(string num) {
        seatNumber = num;
        isBooked = false;
    }

    bool bookSeat() {
        if (!isBooked) {
            isBooked = true;
            return true;
        }
        return false;
    }
};

/* ================= Screen Entity (Composition) ================= */
class Screen {
public:
    string screenId;
    vector<Seat> seats;

    Screen(string id, int seatCount) {
        screenId = id;
        for (int i = 1; i <= seatCount; i++) {
            seats.push_back(Seat("S" + to_string(i)));
        }
    }

    Seat* getSeat(string seatNo) {
        for (auto &seat : seats) {
            if (seat.seatNumber == seatNo)
                return &seat;
        }
        return nullptr;
    }
};

/* ================= Theatre Entity (Aggregation) ================= */
class Theatre {
public:
    string theatreId;
    string location;
    vector<Screen*> screens;

    Theatre(string id, string loc) {
        theatreId = id;
        location = loc;
    }

    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }
};

/* ================= Show Entity (Association) ================= */
class Show {
public:
    string showId;
    string showTime;
    Movie* movie;
    Screen* screen;

    Show(string id, string time, Movie* m, Screen* s) {
        showId = id;
        showTime = time;
        movie = m;
        screen = s;
    }
};

/* ================= Customer Entity ================= */
class Customer {
public:
    string customerId;
    string name;
    string phone;

    Customer(string id, string n, string p) {
        customerId = id;
        name = n;
        phone = p;
    }
};

/* ================= Booking Entity (Association) ================= */
class Booking {
public:
    string bookingId;
    double totalAmount;
    Customer* customer;
    Show* show;
    vector<Seat*> bookedSeats;

    Booking(string id, Customer* c, Show* s) {
        bookingId = id;
        customer = c;
        show = s;
        totalAmount = 0;
    }

    void addSeat(Seat* seat) {
        bookedSeats.push_back(seat);
        totalAmount += 150; // price per seat
    }

    void displayTicket() {
        cout << "\n🎟 BOOKING CONFIRMATION\n";
        cout << "Booking ID : " << bookingId << endl;
        cout << "Customer   : " << customer->name << endl;
        cout << "Movie      : " << show->movie->title << endl;
        cout << "Show Time  : " << show->showTime << endl;
        cout << "Seats      : ";
        for (auto seat : bookedSeats)
            cout << seat->seatNumber << " ";
        cout << "\nTotal Amt  : ₹" << totalAmount << endl;
    }
};

/* ================= Main Function ================= */
int main() {

    Movie movie("M01", "Avengers", "PVR", 148);

    Screen screen("Screen1", 10);
    Theatre theatre("T01", "Chandigarh");
    theatre.addScreen(&screen);

    Show show("SH01", "7:00 PM", &movie, &screen);

    string cname;
    cout << "Enter customer name: ";
    getline(cin, cname);

    Customer customer("C01", cname, "6201460006");
    Booking booking("B001", &customer, &show);

    cout << "\n🎬 Movie: " << movie.title;
    cout << "\n⏰ Show Time: " << show.showTime << endl;

    cout << "\nAvailable Seats:\n";
    for (auto &seat : screen.seats) {
        if (!seat.isBooked)
            cout << seat.seatNumber << " ";
    }

    int count;
    cout << "\n\nHow many seats do you want to book? ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        string seatNo;
        cout << "Enter seat number: ";
        cin >> seatNo;

        Seat* seat = screen.getSeat(seatNo);
        if (seat != nullptr && seat->bookSeat()) {
            booking.addSeat(seat);
            cout << seatNo << " booked successfully\n";
        } else {
            cout << "Seat not available\n";
        }
    }

    booking.displayTicket();
    return 0;
}
