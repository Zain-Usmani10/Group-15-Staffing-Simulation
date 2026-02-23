#include "customer.h"
#include <string>

using namespace std;

// Constructor implementation
Customer::Customer(unsigned int i, int itemCount, paymentMethod m, unsigned int at, string ats) :
    id(i), item_count(itemCount), payment_method(m), arrival_time(at), arrival_time_string(ats)
{}

unsigned int Customer::getID() {
    return id;
}

int Customer::getItemCount() {
    return item_count;
}

string Customer::getMethodString() {
    switch (payment_method) {
        case paymentMethod::CARD:   return "CARD";
        case paymentMethod::CHEQUE: return "CHEQUE";
        case paymentMethod::CASH:   return "CASH";
        default:                    return "NONE";
    }
}

string Customer::getTimeString() {
    return arrival_time_string;
}

unsigned int Customer::getTime() {
    return arrival_time;
}

// json formatter function
json Customer::to_json() {
    json j;
    j["ID"] = id;
    j["arrival_time_string"] = arrival_time_string;
    j["payment_method"] = getMethodString();
    j["item_count"] = item_count;
    j["arrival_time"] = arrival_time;
    return j;
}