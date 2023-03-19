//
// Created by xuxinyu on 23-3-18.
//

#ifndef MYWEBSERVER_HEAP_TIMER_H
#define MYWEBSERVER_HEAP_TIMER_H

#include <queue>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <arpa/inet.h>
#include <functional>
#include <cassert>
#include <chrono>

typedef std::function<void()> TimeoutCallBack;
typedef std::chrono::high_resolution_clock Clock;   // 表示实现提供的拥有最小计次周期的时钟
typedef std::chrono::milliseconds MS;               // 毫秒
typedef Clock::time_point TimeStamp;                // 表示一个时间点

struct TimerNode {
    int id;
    TimeStamp expires;  // 过期时间
    TimeoutCallBack cb; // 超时回调函数
    bool operator<(const TimerNode& t) const {    // 重载<符号，用于堆排序使用
        return expires < t.expires;
    }
};

class HeapTimer {
public:
    HeapTimer() { heap_.reserve(64); }

    ~HeapTimer() { clear(); }

    void adjust(int id, int newExpires);

    void add(int id, int timeOut, const TimeoutCallBack& cb);

    void clear();

    void tick();

    void pop();

    int GetNextTick();

private:
    void del_(size_t i);    // 删除节点

    void siftup_(size_t i);     // 上虑操作

    bool siftdown_(size_t index, size_t n);     // 下虑操作

    void SwapNode_(size_t i, size_t j);     // 交换节点

    std::vector<TimerNode> heap_;           // 小顶堆是完全二叉树，可以用数组管理元素

    std::unordered_map<int, size_t> ref_;   // 存放节点在数组中对应位置，保证查询时间复杂度O(1)
};

#endif //MYWEBSERVER_HEAP_TIMER_H
