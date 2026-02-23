#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Customer class to store all data for each customer
class Customer {
public: 
    enum class paymentMethod { CARD, CHEQUE, CASH };

private:
    // The data that will be outputted in 'customer.json' for each customer
    unsigned int id;
    unsigned int arrival_time;
    int item_count;
    std::string arrival_time_string;
    paymentMethod payment_method;

public:
    // Constructor and getter functions
    Customer(unsigned int i, int itemCount, paymentMethod m, unsigned int at, std::string ats);

    unsigned int getID();
    int getItemCount();
    std::string getMethodString();
    std::string getTimeString();
    unsigned int getTime();

    // json formatter function
    json to_json();
};

#endif