#include <atomic> // 引入原子操作的头文件
#include <thread> // 引入线程的头文件

class spinlock { // 定义一个自旋锁的类
    std::atomic_flag flag = ATOMIC_FLAG_INIT; // 定义一个原子标志，初始为假
public:
    void lock() { // 定义获取锁的方法
        while (flag.test_and_set(std::memory_order_acquire)); // 循环测试并设置标志，如果标志为真，表示锁被占用，继续循环；如果标志为假，表示锁空闲，设置标志为真，并跳出循环。这里使用内存顺序为获取，表示获取锁后，后续的读操作不能被重排到前面。
    }
    void unlock() { // 定义释放锁的方法
        flag.clear(std::memory_order_release); // 清除标志，设置为假，表示锁空闲。这里使用内存顺序为释放，表示释放锁前，前面的写操作不能被重排到后面。
    }
};
