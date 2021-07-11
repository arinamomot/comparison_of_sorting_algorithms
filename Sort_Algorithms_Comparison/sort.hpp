//
// Created by arina on 26.10.2020.
//

#ifndef SEMESTRALNI_PRACE_SORT_HPP
#define SEMESTRALNI_PRACE_SORT_HPP

#include <iostream>
#include <vector>

using namespace std;

template<class T>
class sort {
protected:
    string name;
    vector<T> elements;
public:
    sort() = default;

    explicit sort(const vector<T> &elements) {
        this->elements = elements;
    }

    ~sort() {
        elements.clear();
    };

    void set_elements(vector<T> &elements) {
        this->elements = elements;
    }

    vector<T> sort_elements() {
        elements = sort_elements(elements);
    };

    virtual vector<T> sort_elements(vector<T> &elements) {

    };
};


#endif //SEMESTRALNI_PRACE_SORT_HPP
