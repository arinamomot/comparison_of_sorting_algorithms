//
// Created by arina
//

#include "../sort.hpp"

template <typename T> class selectionSort : public sort<T> {
public:
    selectionSort() {
        this->name = "Selection Sort";
    };
    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data);
        return data;
    }

    vector<T> sorting(vector<T> &elements) {
        int size = elements.size();

        for (int i = 0; i < size-1; i++) {
            int min = i;
            for (int j = i+1; j < size; j++)
                if (elements[j] < elements[min]) min = j;
            swap(&elements[min], &elements[i]);
        }
        return elements;
    }

    void swap(T *first, T *second) {
        T tmp = *first;
        *first = *second;
        *second = tmp;
    }
};

