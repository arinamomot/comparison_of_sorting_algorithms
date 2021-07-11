//
// Created by arina
//

#include "../sort.hpp"

template<typename T>
class mergeSort : public sort<T> {
public:
    mergeSort() {
        this->name = "Merge Sort";
    };

    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data);
        return data;
    }

    vector<T> sorting(vector<T> &elements) {
        int size = elements.size();
        if (size > 1) {
            int middle = elements.size()/2;
            vector<T> left(elements.begin(),elements.begin()+middle);
            vector<T> right(elements.begin()+middle,elements.begin()+size);

            left = sorting(left);
            right = sorting(right);

            int i = 0,j = 0 ,k = 0;
            while ((i < left.size()) && (j < right.size())) {
                if (left[i] < right[j]) {
                    elements[k]=left[i];
                    i++;
                } else {
                    elements[k] = right[j];
                    j++;
                }
                k++;
            }

            while (i < left.size()) {
                elements[k] = left[i];
                i++;
                k++;
            }

            while (j < right.size()) {
                elements[k]=right[j];
                j++;
                k++;
            }
        }
        return elements;
    }
};