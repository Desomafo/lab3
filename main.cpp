#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

struct apartmentCardIndex {
    struct apartment {
        int rooms, floor;
        double area;
        string address;
        apartment *prev, *next;
    };

    apartment *head, *tail, *notUpdatedTail;

    fstream dbase;

    apartmentCardIndex() {
        tail = NULL;
        head = NULL;
        notUpdatedTail = NULL;
        dbase.open("database.txt", ios::app | ios::in |ios::out);
        open();
    }

    ~apartmentCardIndex() {
        dbase.close();
    }

    void apartmentsOutput() {
        apartment *current = new apartment;
        while (current != NULL) {
            cout << current->rooms << " " << current->floor << " " << current->area << " " << current->address << endl;
            current = current->next;
        }
    }

    void exchangeRequest() {
        cout << "Enter characteristics of your apartment:" << endl;
        cout << "rooms/floor/area/address" << endl;

        apartment *newApartment = new apartment;
        cin >> newApartment->rooms;
        cin >> newApartment->floor;
        cin >> newApartment->area;
        cin >> newApartment->address;

        apartmentSearch(newApartment);
    }

    void apartmentSearch(apartment *desiredApatrment){
        apartment *current = head;
        while (current->next != NULL) {
            if (current->rooms == desiredApatrment->rooms && current->floor == desiredApatrment->floor && (abs(current->area - desiredApatrment->area)/(current->area + desiredApatrment->area)/2*100) <= 10) {
                cout << "Was found a suitable apartment at" << current->address << endl;
                cout << "Processing the exchange..." << endl;
                current->address == desiredApatrment->address;
                current->area == desiredApatrment->area;
                cout << "Successful exchange.";
                apartmentsOutput();
                break;
            }
        }
        cout << "No apartment was found. Yours apartment will be added to the database./n";
        tail->next = desiredApatrment;
        desiredApatrment->prev = tail;
        tail = desiredApatrment;
        apartmentsOutput();
    }

    void open() {
        if (dbase.is_open()) {
            string line;
            size_t pos = 0;
            size_t new_pos;
            apartment *newApartment = new apartment;
            while ( getline (dbase, line) ) {
                newApartment->prev = tail;
                new_pos = line.find(' ', pos);
                newApartment->rooms = stoi(line.substr(pos, new_pos));
                pos = new_pos;
                new_pos = line.find(' ', pos);
                newApartment->floor = stoi(line.substr(pos, new_pos));
                pos = new_pos;
                new_pos = line.find(' ', pos);
                newApartment->area = stod(line.substr(pos, new_pos));
                newApartment->address = line.substr(new_pos);
                if (head == NULL) {
                    head = newApartment;
                    tail = newApartment;
                    notUpdatedTail = newApartment;
                    head->prev = NULL;
                } else {
                    tail->next = newApartment;
                    notUpdatedTail->next = newApartment;
                    newApartment->prev = tail;
                    tail = newApartment;
                    notUpdatedTail = newApartment;
                }
                newApartment = new apartment;
            }
        } else cout << "Unable to open file";
    }

    void save() {
        if (dbase.is_open()) {
           if (notUpdatedTail->next != NULL) {
                while (notUpdatedTail->next != NULL) {
                    dbase << endl << notUpdatedTail->rooms << " " << notUpdatedTail->floor << " " << notUpdatedTail->area << " " << notUpdatedTail->address;
                    notUpdatedTail = notUpdatedTail->next;
                }
           }
        } else cout << "Unable to open file";
    }
};

int main() {
    apartmentCardIndex mine;
    mine.open();
    mine.exchangeRequest();
    mine.save();
    return 0;
}
