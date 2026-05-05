#include <iostream>
#include <vector>
#include <string>
using namespace std;



class Movie {
protected:
    string title;
    int duration;

public:
    virtual double getPrice() = 0;

    void setTitle(string t) { title = t; }
    void setDuration(int d) { duration = d; }

    string getTitle() { return title; }
    int getDuration() { return duration; }

    virtual string getType() = 0;
};

class RegularMovie : public Movie {
    double basePrice = 150.0;
public:
    double getPrice() override { return basePrice; }
    string getType() override { return "Regular"; }
};

class IMAXMovie : public Movie {
    double basePrice = 300.0;
public:
    double getPrice() override { return basePrice; }
    string getType() override { return "IMAX"; }
};



class MovieFactory {
public:
    virtual Movie* createMovie(string title, int duration) = 0;
};

class RegularMovieFactory : public MovieFactory {
public:
    Movie* createMovie(string title, int duration) override {
        RegularMovie* movie = new RegularMovie();
        movie->setTitle(title);
        movie->setDuration(duration);
        return movie;
    }
};

class IMAXMovieFactory : public MovieFactory {
public:
    Movie* createMovie(string title, int duration) override {
        IMAXMovie* movie = new IMAXMovie();
        movie->setTitle(title);
        movie->setDuration(duration);
        return movie;
    }
};

class MovieFactoryProducer {
public:
    static MovieFactory* getFactory(string type) {
        if (type == "regular") return new RegularMovieFactory();
        if (type == "imax") return new IMAXMovieFactory();
        throw invalid_argument("Invalid movie type");
    }
};



class ShowObserver {
public:
    virtual void update(string message) = 0;
};

class User : public ShowObserver {
    string name, email;
public:
    User(string n, string e) : name(n), email(e) {}

    void update(string message) override {
        cout << "[User Notification] " << name
             << " (" << email << "): " << message << endl;
    }
};

class TheaterManager : public ShowObserver {
public:
    void update(string message) override {
        cout << "[Manager Alert] " << message << endl;
    }
};



class Seat {
    string seatId;
    bool isAvailable;

public:
    Seat(string id) {
        seatId = id;
        isAvailable = true;
    }

    string getSeatId() { return seatId; }

    bool bookSeat() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false;
    }
};



class Show {
    string showId;
    Movie* movie;
    string time;
    vector<Seat> seats;
    vector<ShowObserver*> observers;

public:
    Show(string id, Movie* m, string t) {
        showId = id;
        movie = m;
        time = t;

        for (int i = 1; i <= 10; i++) {
            seats.push_back(Seat("A" + to_string(i)));
        }
    }

    void addObserver(ShowObserver* obs) {
        observers.push_back(obs);
    }

    void notifyObservers(string msg) {
        for (auto obs : observers) {
            obs->update(msg);
        }
    }

    bool bookSeat(string seatId) {
        for (auto &seat : seats) {
            if (seat.getSeatId() == seatId) {
                if (seat.bookSeat()) {
                    notifyObservers("Seat " + seatId + " booked successfully");
                    return true;
                }
            }
        }
        return false;
    }

    Movie* getMovie() { return movie; }
    string getTime() { return time; }
};


class PaymentStrategy {
public:
    virtual bool pay(double amount) = 0;
    virtual string getMethod() = 0;
};

class CreditCardPayment : public PaymentStrategy {
    string cardNumber;
public:
    CreditCardPayment(string num) : cardNumber(num) {}

    bool pay(double amount) override {
        cout << "Paying Rs." << amount
             << " using Credit Card (****"
             << cardNumber.substr(cardNumber.size()-4) << ")\n";
        return true;
    }

    string getMethod() override {
        return "Credit Card";
    }
};

class UPIPayment : public PaymentStrategy {
    string upiId;
public:
    UPIPayment(string id) : upiId(id) {}

    bool pay(double amount) override {
        cout << "Paying Rs." << amount
             << " using UPI (" << upiId << ")\n";
        return true;
    }

    string getMethod() override {
        return "UPI";
    }
};



class Booking {
    Show* show;
    vector<string> seats;
    PaymentStrategy* payment;

public:
    Booking(Show* s, vector<string> st, PaymentStrategy* p)
        : show(s), seats(st), payment(p) {}

    bool confirmBooking() {
        double total = 0;

        cout << "\n=====================================\n";
        cout << "        BOOKING IN PROGRESS\n";
        cout << "=====================================\n";

        for (string seat : seats) {
            cout << "\nBooking Seat: " << seat << endl;

            if (show->bookSeat(seat)) {
                total += show->getMovie()->getPrice();
            } else {
                cout << "Seat already booked!\n";
            }
        }

        cout << "\n-------------------------------------\n";
        cout << "             PAYMENT\n";
        cout << "-------------------------------------\n";

        if (payment->pay(total)) {
            cout << "\n=====================================\n";
            cout << "          BOOKING CONFIRMED\n";
            cout << "=====================================\n";

            cout << "Movie      : " << show->getMovie()->getTitle()
                 << " (" << show->getMovie()->getType() << ")\n";
            cout << "Show Time  : " << show->getTime() << endl;

            cout << "Seats      : ";
            for (auto s : seats) cout << s << " ";
            cout << endl;

            cout << "Total      : Rs." << total << endl;
            cout << "Payment    : " << payment->getMethod() << endl;

            cout << "=====================================\n";
            cout << "Enjoy your movie!\n";
            cout << "=====================================\n";

            return true;
        }

        return false;
    }
};



int main() {

    cout << "=====================================\n";
    cout << "   MOVIE TICKET BOOKING SYSTEM\n";
    cout << "=====================================\n";

    MovieFactory* factory = MovieFactoryProducer::getFactory("imax");
    Movie* movie = factory->createMovie("Dune: Part Two", 166);

    cout << "\nMovie Created: " << movie->getTitle()
         << " (" << movie->getType() << ") - "
         << movie->getDuration() << " mins\n";

    Show show("S001", movie, "20:30");

    User user("Shashank", "shashank@email.com");
    TheaterManager manager;

    show.addObserver(&user);
    show.addObserver(&manager);

    vector<string> seats = {"A1", "A2"};

    PaymentStrategy* payment = new CreditCardPayment("1234567812345678");

    Booking booking(&show, seats, payment);

    booking.confirmBooking();

    return 0;
}