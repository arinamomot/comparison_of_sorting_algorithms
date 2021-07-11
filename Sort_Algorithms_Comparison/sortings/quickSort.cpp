//
// Created by arina
//
#include "../sort.hpp"

template <typename T> class quickSort : public sort<T> {
public:
    quickSort() {
        this->name = "Quick Sort";
    };
    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data, 0, data.size()- 1);
        return data;
    }

    vector<T> sorting(vector<T> &elements, int start, int end) {
        if(start < end){
            int pivot = partition(elements, start, end);
            sorting(elements ,start, pivot-1);
            sorting(elements ,pivot+ 1, end);
        }
        return elements;
    }

    void swap(T *first, T *second) {
        T tmp = *first;
        *first = *second;
        *second = tmp;
    }

    int partition(vector<T> &elements, int start, int end) {
        T pivot = elements[end];
        int i = start-1;
        for (int j= start; j < end; j++){
            if (elements[j] <= pivot){
                i++;
                swap(&elements[i], &elements[j]);
            }
        }
        i++;
        swap(&elements[i], &elements[end]);
        return i;
    }
};