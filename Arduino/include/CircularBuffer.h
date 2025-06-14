#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <cstddef>



template  <typename T, size_t Size>

class CircularBuffer {
    public:
        CircularBuffer() {};

        void push(T input) {
            if(full){
                sum-=data[head];
            }
            sum+=input;
            data[head] = input;
            head = (head+1) % Size; 
            if(head == 0){
                full = true;
            }
        }

        T get(size_t index) const {
            if (!full && index >= head) return data[0]; // basic safeguard
            size_t realIndex = (head + index) % Size;
            return data[realIndex];
        }

        T back() const {
            return data[head];
        }

        T get_average() const {
            if(full){
                return sum / 15;
            } else {
                return sum / head;
            }
            
        }

    private:
        size_t head = 0;
        bool full = false;
        T data[Size];
        float sum = 0;

};

#endif