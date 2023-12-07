#ifndef LockfreeQueue_H
#define LockfreeQueue_H

#include <vector>
#include <atomic>

template <typename T>
class LockfreeQueue {
private:
    std::vector<T> data_;
    std::atomic<int> front_ = {0};
    std::atomic<int> back_ = {0};
    std::atomic<int> write_ = {0};
    int capacity_;
    
public:
    LockfreeQueue<T>(int capacity=8) : capacity_(capacity), data_(std::vector<T>(capacity)){}
    
    bool MultiplePush(const T val) {
        int write, back;

        do {
            write = write_.load(std::memory_order_relaxed); //L1
            if((write + 1) % capacity_ == front_.load(std::memory_order_acquire)) //L2 
                return false;
        }while(!write_.compare_exchange_strong(write, (write + 1) % capacity_, std::memory_order_relaxed)); //L3

        data_[write] =  val; //L4

        do {
            back = write;
        }while(!back_.compare_exchange_strong(back, (back + 1) % capacity_ , std::memory_order_release)); //L5

        return true;
    }
    
    bool MultiplePop(T& val) {
        int front;
        do {
            front = front_.load(std::memory_order_relaxed); //L6
            if(front == back_.load(std::memory_order_acquire)) //L7
                return false;
            val = data_[front]; //L8
        }while(!front_.compare_exchange_strong(front, (front + 1) % capacity_, std::memory_order_release)); //L9
        
        return true;
    }

    bool empty(){
        int front;
        front = front_.load(std::memory_order_relaxed); 
        if(front == back_.load(std::memory_order_acquire)) 
            return true;       
        else
            return false;
    }
};
#endif