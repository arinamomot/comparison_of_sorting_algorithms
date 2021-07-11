//
// Created by arina
//

#include "../sort.hpp"

template <typename T> class insertionSort : public sort<T> {
public:
    insertionSort() {
        this->name = "Insertion Sort";
    };
    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data);
        return data;
    }

    vector<T> sorting(vector<T> &elements) {
        T key;
        int k;
        for(int i = 1; i < elements.size(); i++) {
            key = elements[i];
            k = i;
            while(k > 0 && elements[k-1] > key) {
                elements[k] = elements[k-1];
                k--;
            }
            elements[k] = key;
        }
        return elements;
    }
};
