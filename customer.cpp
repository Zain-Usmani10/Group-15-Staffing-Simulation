#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream> // file output
#include <sstream> // for time string parsing
#include <iomanip> // for understanding time string
#include <ctime> // tm struct for time handling
#include <nlohmann/json.hpp> // JSON file type

using namespace std;
using json = nlohmann::json;

unsigned int customerID = 1000;

// Customer class to store all data for each customer
class Customer {
    public: enum class paymentMethod {CARD, CHEQUE, CASH};

    private:

    // The data that will be outputted in 'customer.json' for each customer
        unsigned int id;
        unsigned int arrival_time;
        int item_count;
        string arrival_time_string;
        paymentMethod payment_method;

    // Constructor and getter functions
    public:
        Customer (unsigned int i, int itemCount, paymentMethod m, unsigned int at, string ats) :
        id(i), item_count(itemCount), payment_method(m), arrival_time(at), arrival_time_string(ats)
        {}

        unsigned int getID() {
            return id;
        }
        int getItemCount() {
            return item_count;
        }
        string getMethodString() {
            switch (payment_method) {
                case paymentMethod::CARD:   return "CARD";
                case paymentMethod::CHEQUE: return "CHEQUE";
                case paymentMethod::CASH:   return "CASH";
                default:                    return "NONE";
            }
        }
        string getTimeString() {
            return arrival_time_string;
        }
        unsigned int getTime () {
            return arrival_time;
        }

        // json formatter function
        json to_json() {
            json j;
            j["ID"] = id;
            j["arrival_time_string"] = arrival_time_string;
            j["payment_method"] = getMethodString();
            j["item_count"] = item_count;
            j["arrival_time"] = arrival_time;
            return j;
        }
};

// Parses user input to flag for errors or validation.
// The outputted flag is used as feedback to call function again in case of invalid inputs.
int isValidTime(const string& input, tm& time) {
    std::istringstream stream (input);
    stream >> std::get_time(&time, "%I:%M %p");

    if (stream.fail()) return -1; // means invalid time
    if (time.tm_hour < 8 || time.tm_hour > 19 || time.tm_min < 0 || time.tm_min > 59) return -2; // store closed

    return 0;
}

// converts the std::tm struct "time" into seconds with basic arithmetic
unsigned int convertToSeconds(tm &time) {
    unsigned int seconds;
    seconds = time.tm_hour*3600 + time.tm_min*60 - 28800; // 28600 is 8:00 AM is seconds if we start counting from midnight
    return seconds;
}

// Global function to prompt user to enter a time as a string.
// It then parses the preceding isValidTime function to validate input.
// Finally, the preceding convertToSeconds function converts it to a useful format used for sorting and later calculations
void inputTime (unsigned int &arrival_time, string &t) {
    tm time {};
    cout << "Time of arrival [HH:MM AM/PM]. Example: '08:30 AM': ";
    while (true) {
        getline(cin, t);
        int flag = isValidTime(t, time);
        if (flag == 0) {
            arrival_time = convertToSeconds(time);
            return;
        }
        else if (flag == -1) cout << "Invalid format, please try again. ";
        else if (flag == -2) cout << "Sorry, store is closed! Store hours are 8:00 AM - 8:00 PM. ";
        else cout << "Input not recognized, please try again. ";
    }
}

int main() {
    // Variables for std::cin to be pushed into customer objects
    int number_of_items;
    unsigned int time_of_arrival;
    string time_of_arrival_string;
    string payment_method_string;
    Customer::paymentMethod method_of_payment;

    vector<Customer> customerList;
    char mode;
    bool run = true;

    // Enter customers until user chooses not to.
    while (run) {
        cout << "To enter a customer, press 1. Otherwise, press any key to exit and recieve JSON file: ";
        cin >> mode;
        cin.ignore(1000, '\n');

        switch (mode) {     
            case '1': {
                // User presses 1 and is prompted to enter arrival time, number of items, and payment method.
                cout << "\nCustomer " << customerID - 999 << ":" << endl;
                inputTime(time_of_arrival, time_of_arrival_string);
                cout << "Number of items: ";
                cin >> number_of_items;
                cout << "Payment method (CARD, CHEQUE, or CASH): ";
                while (true) {
                    cin >> payment_method_string;
                    for (size_t i = 0; i < payment_method_string.length(); i++) payment_method_string[i] = toupper(payment_method_string[i]); // Converting all entered characters to upper case for if else comparison. This makes the entry 'case insensitive'
                    if (payment_method_string == "CARD")       {method_of_payment = Customer::paymentMethod::CARD;     break; }
                    if (payment_method_string == "CHEQUE")     {method_of_payment = Customer::paymentMethod::CHEQUE;   break; }
                    if (payment_method_string == "CASH")       {method_of_payment = Customer::paymentMethod::CASH;     break; }
                    cout << "Incorrect! Please try again (CARD, CHEQUE, or CASH): "; 
                }
                customerList.push_back(Customer(customerID++, number_of_items, method_of_payment,time_of_arrival, time_of_arrival_string));
                break;
            }
            // User presses any key and the program exits
            default: {
                run = false;
                break;
            }
        }
    }

    json list = json::array();
    for (size_t i=0; i < customerList.size(); i++) {
        list.push_back(customerList[i].to_json());
    }
    ofstream file("customers.json");
    file << list.dump(2);
    file.close();
    
    cout << "\nTotal number of customers: " << customerList.size() << "\nJSON file ""customer.json"" generated successfully!!!" << endl;

    return 0;
}

/*

Personal Notes:

TODO:
- Add time data-point in Customer class that describes what time customer entered the queue (in seconds) DONE
- Implement input-validation - DONE
- Automate customer entry via loops - DONE
OUTSTANDING:
- Implement a sorting algorithm (most likely merge sort) to sort customers by time of arrival

Note on time data-point:
- Store will be open from 8am to 8pm -> That is 12 hours, which is 43200 seconds
- All time will be kept track of in seconds.
- Seconds can be converted back into readable time for GUI

*/

// cout << "\nCustomer 1:\tID - " << customerList[0].getID() << "\t# of items - " << customerList[0].getItemCount() << "    \tPayment Method - " << customerList[0].getMethodString() << endl;
