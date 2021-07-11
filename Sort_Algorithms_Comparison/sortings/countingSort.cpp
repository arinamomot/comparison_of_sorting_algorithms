//
// Created by arina
//

#include "../sort.hpp"

template<typename T>
class countingSort : public sort<T> {
public:
    countingSort() {
        this->name = "Counting Sort";
    };

    vector<T> sort_elements(vector<T> &elements) {
        vector<T> data = vector<T>(elements);
        data = this->sorting(data);
        return data;
    }

    vector<T> sorting(vector<T> &elements) {
        int size = elements.size();
        int res[size+1];
        T maximum = getMax(elements);
        int max = (int) maximum;
        T minimum = getMin(elements);
        int min = (int) minimum;
        int count[max - min + 1];

        for(int i = 0; i < max - min + 1; i++) count[i] = 0;
        int index = min * (-1);
        for (int i = 0; i < size; i++) count[elements[i] + index]++;
        for (int i = 1; i <= max - min + 1; i++) count[i] += count[i - 1];
        for (int i = size - 1; i >= 0; i--) {
            res[count[elements[i] + index] - 1] = elements[i];
            count[elements[i] + index]--;
        }
        for (int i = 0; i < size; i++) elements[i] = res[i];
        return elements;
    }

    int getMax(vector<T> elements) {
        T max = elements[0];
        for (auto el:elements) {
            if (el > max) max = el;
        }
        return max;
    }

    int getMin(vector<T> elements) {
        T min = elements[0];
        for (auto el:elements) {
            if (el < min) min = el;
        }
        return min;
    }
};