#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

struct apartmentCardIndex {
    struct apartment {
        int rooms, floor, area;
        string adress;
        apartment *prev, *next;
    };

    apartment *head, *tail;

    fstream dbase;

    apartmentCardIndex() {
        tail = NULL;
        head = NULL;
        dbase.open("dbase.txt", ios::app | ios::in |ios::out);
        open();
    }

    ~apartmentCardIndex() {
        dbase.close();
    }

    void init(int number) {
    }

    void exchangeRequest(apartment *newApartment) {

    }

    void apartmentSearch(apartment *desiredApatrment){

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
                cout << line << endl;
                newApartment->rooms = stoi(line.substr(pos, new_pos));
                pos = new_pos;
                new_pos = line.find(' ', pos);
                newApartment->floor = stoi(line.substr(pos, new_pos));
                pos = new_pos;
                new_pos = line.find(' ', pos);
                newApartment->area = stoi(line.substr(pos, new_pos));
                newApartment->adress = line.substr(new_pos);
                if (head == NULL) {
                    head = newApartment;
                    tail = newApartment;
                    head->prev = NULL;
                } else {
                    tail->next = newApartment;
                    newApartment->prev = tail;
                    tail = newApartment;
                }
                newApartment = new apartment;
            }
        } else cout << "Unable to open file";
    }

    void save() {
        if (dbase.is_open()) {
            dbase << "This is a line.\n";
            dbase << "This is another line.\n";
        } else cout << "Unable to open file";
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
