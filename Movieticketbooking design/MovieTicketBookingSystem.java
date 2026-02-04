import java.util.*;

/* Movie Class */
class Movie {
    String movieId;
    String title;
    String genre;
    int duration;

    Movie(String movieId, String title, String genre, int duration) {
        this.movieId = movieId;
        this.title = title;
        this.genre = genre;
        this.duration = duration;
    }
}

/* Seat Class */
class Seat {
    String seatNumber;
    boolean isBooked;

    Seat(String seatNumber) {
        this.seatNumber = seatNumber;
        this.isBooked = false;
    }

    boolean bookSeat() {
        if (!isBooked) {
            isBooked = true;
            return true;
        }
        return false;
    }
}

/* Screen Class (Composition) */
class Screen {
    String screenId;
    List<Seat> seats = new ArrayList<>();

    Screen(String screenId, int seatCount) {
        this.screenId = screenId;
        for (int i = 1; i <= seatCount; i++) {
            seats.add(new Seat("S" + i));
        }
    }

    Seat getSeatByNumber(String seatNo) {
        for (Seat seat : seats) {
            if (seat.seatNumber.equalsIgnoreCase(seatNo))
                return seat;
        }
        return null;
    }
}

/* Theatre Class (Aggregation) */
class Theatre {
    String theatreId;
    String location;
    List<Screen> screens = new ArrayList<>();

    Theatre(String theatreId, String location) {
        this.theatreId = theatreId;
        this.location = location;
    }

    void addScreen(Screen screen) {
        screens.add(screen);
    }
}

/* Show Class (Association) */
class Show {
    String showId;
    String showTime;
    Movie movie;
    Screen screen;

    Show(String showId, String showTime, Movie movie, Screen screen) {
        this.showId = showId;
        this.showTime = showTime;
        this.movie = movie;
        this.screen = screen;
    }
}

/* Customer Class */
class Customer {
    String customerId;
    String name;
    String phone;

    Customer(String customerId, String name, String phone) {
        this.customerId = customerId;
        this.name = name;
        this.phone = phone;
    }
}

/* Booking Class */
class Booking {
    String bookingId;
    double totalAmount;
    Customer customer;
    Show show;
    List<Seat> bookedSeats = new ArrayList<>();

    Booking(String bookingId, Customer customer, Show show) {
        this.bookingId = bookingId;
        this.customer = customer;
        this.show = show;
    }

    void addSeat(Seat seat) {
        bookedSeats.add(seat);
        totalAmount += 150;
    }

    void displayTicket() {
        System.out.println("\n🎟 BOOKING CONFIRMATION");
        System.out.println("Booking ID : " + bookingId);
        System.out.println("Customer   : " + customer.name);
        System.out.println("Movie      : " + show.movie.title);
        System.out.println("Show Time  : " + show.showTime);
        System.out.print("Seats      : ");
        for (Seat s : bookedSeats)
            System.out.print(s.seatNumber + " ");
        System.out.println("\nTotal Amt  : ₹" + totalAmount);
    }
}

/* Main Class */
public class MovieTicketBookingSystem {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        Movie movie = new Movie("M01", "Avengers", "Sci-Fi", 148);
        Screen screen = new Screen("Screen1", 10);

        Theatre theatre = new Theatre("T01", "Chandigarh");
        theatre.addScreen(screen);

        Show show = new Show("SH01", "7:00 PM", movie, screen);

        System.out.print("Enter Customer Name: ");
        String name = sc.nextLine();
        Customer customer = new Customer("C01", name, "9999999999");

        Booking booking = new Booking("B001", customer, show);

        System.out.println("\n🎬 Movie: " + movie.title);
        System.out.println("Show Time: " + show.showTime);

        System.out.println("\nAvailable Seats:");
        for (Seat seat : screen.seats) {
            if (!seat.isBooked)
                System.out.print(seat.seatNumber + " ");
        }

        System.out.print("\n\nHow many seats do you want to book? ");
        int count = sc.nextInt();

        for (int i = 0; i < count; i++) {
            System.out.print("Enter seat number: ");
            String seatNo = sc.next();

            Seat seat = screen.getSeatByNumber(seatNo);
            if (seat != null && seat.bookSeat()) {
                booking.addSeat(seat);
                System.out.println(seatNo + " booked successfully");
            } else {
                System.out.println("Seat not available!");
            }
        }

        booking.displayTicket();
        sc.close();
    }
}
