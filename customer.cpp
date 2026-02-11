#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

unsigned int customerID = 1000;

class Customer {
    public: enum class paymentMethod {CARD, CHEQUE, CASH};

    private:
        unsigned int id;
        int item_count;
        paymentMethod payment_method;

    public:
    Customer (unsigned int i, int itemCount, paymentMethod m) : id(i), item_count(itemCount), payment_method(m) {}
    unsigned int getID() {
        return id;
    }
    int getItemCount() {
        return item_count;
    }
    paymentMethod getPaymentMethod() {
        return payment_method;
    }
    string getMethodString() {
        switch (payment_method) {
            case paymentMethod::CARD:   return "CARD";
            case paymentMethod::CHEQUE: return "CHEQUE";
            case paymentMethod::CASH:   return "CASH";
            default:                    return "NONE";
        }
    }

    json to_json() {
        json j;
        j["ID"] = id;
        j["item_count"] = item_count;
        j["payment_method"] = getMethodString();
        return j;
    }
};

int main() {
    int i1, i2;
    string c1, c2;
    Customer::paymentMethod C1, C2;

    cout << "Please enter the number of item of the first customer: ";
    cin >> i1;
    cout << "Please enter the payment method (CARD, CHEQUE, or CASH) of the first customer: ";
    while (true) {
        cin >> c1;
        for (int i = 0; i < c1.length(); i++) {
            c1[i] = toupper(c1[i]);
        }
        if (c1 == "CARD")       {C1 = Customer::paymentMethod::CARD;     break; }
        if (c1 == "CHEQUE")     {C1 = Customer::paymentMethod::CHEQUE;   break; }
        if (c1 == "CASH")       {C1 = Customer::paymentMethod::CASH;     break; }
        cout << "Incorrect! Please try again (CARD, CHEQUE, or CASH): "; 
    }

    cout << "Please enter the number of item of the second customer: ";
    cin >> i2;
    cout << "Please enter the payment method (CARD, CHEQUE, or CASH) of the second customer: ";
    while (true) {
        cin >> c2;
        for (int i = 0; i < c2.length(); i++) {
            c2[i] = toupper(c2[i]);
        }
        if (c2 == "CARD")       {C2 = Customer::paymentMethod::CARD;     break; }
        if (c2 == "CHEQUE")     {C2 = Customer::paymentMethod::CHEQUE;   break; }
        if (c2 == "CASH")       {C2 = Customer::paymentMethod::CASH;     break; }
        cout << "Incorrect! Please try again (CARD, CHEQUE, or CASH): "; 
    }

    vector<Customer> customerList;
    customerList.push_back(Customer(customerID++, i1, C1));
    customerList.push_back(Customer(customerID++, i2, C2));

    cout << "\nCustomer 1:\tID - " << customerList[0].getID() << "\t# of items - " << customerList[0].getItemCount() << "    \tPayment Method - " << customerList[0].getMethodString() << endl;
    cout << "Customer 2:\tID - " << customerList[1].getID() << "\t# of items - " << customerList[1].getItemCount() << "    \tPayment Method - " << customerList[1].getMethodString() << endl;

    json list = json::array();
    list.push_back(customerList[0].to_json());
    list.push_back(customerList[1].to_json());

    ofstream file("customers.json");
    file << list.dump(2);
    file.close();

    cout << "\nJSON file ""customer.json"" generated successfully!!!\n" << endl;

    return 0;
}

/*

Personal Notes:

TODO:
- Add time data-point in Customer class that describes what time customer entered the queue (in seconds)
- Implement some type of sort algorithm to sort customers by time of arrival
- Implement input-validation
- Automate customer entry via loops

Note on time variable:
- Store will be open from 8am to 8pm. -> That is 12 hours, which is 43200 seconds
- All time will be kept track of in seconds.
- Seconds can be converted back into readable time for GUI

*/