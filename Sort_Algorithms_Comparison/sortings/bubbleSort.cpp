//
// Created by arina
//

#include "../sort.hpp"

template<typename T>
class bubbleSort : public sort<T> {
public:
    bubbleSort() {
        this->name = "Bubble Sort";
    };

    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data);
        return data;
    }

    vector<T> sorting(vector<T> &elements) {
        int size = elements.size();
        bool swapped;
        for (int i = 0; i < size-1; i++) {
            swapped = false;
            for (int j = 0; j < size-i-1; j++) {
                if (elements[j] > elements[j+1]) {
                    swap(&elements[j], &elements[j+1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        return elements;
    }

    void swap(T *first, T *second) {
        T tmp = *first;
        *first = *second;
        *second = tmp;
    }
};