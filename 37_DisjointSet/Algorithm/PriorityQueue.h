#pragma once
#include <vector>
using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
    void push(const T& data)
    {
        // 우선 힙 구조를 만들어 줍니다.
        heap.push_back(data);

        // 부모와 경쟁을 시작합니다.
        int now = static_cast<int>(heap.size()) - 1;

        while (now > 0) // 루트 전까지 반복합니다.
        {
            // 부모 노드와 비교합니다.
            int next = (now - 1) / 2; // 부모 노드 index
            //if (heap[now] < heap[next])
            //    break;
            if (predicate(heap[now], heap[next]))
                break;

            // 부모 노드와 데이터를 교환합니다.
            swap(heap[now], heap[next]);
            now = next;
        }
    }

    void pop()
    {
        // 자식 노드를 루트로 옮깁니다.
        heap[0] = heap.back();
        heap.pop_back();

        // 자식들과 경쟁을 시작합니다.
        int now = 0;
        while (true)
        {
            int left = 2 * now + 1; // 왼쪽 자식 index
            int right = 2 * now + 2; // 오른쪽 자식 index

            // 리프에 도달한 경우 종료합니다.
            if (left >= heap.size())
                break;


            int next = now;

            // 왼쪽 자식과 비교합니다.
            //if (heap[next] < heap[left])
            //    next = left;
            if (predicate(heap[next], heap[left]))
                next = left;

            // 둘 중 승자를 오른쪽과 비교합니다.
            //if (right < heap.size() && heap[next] < heap[right])
            //    next = right;
            if (right < heap.size() && predicate(heap[next], heap[right]))
                next = right;


            // 이동하지 않는 경우 종료합니다.
            if (next == now)
                break;

            // 자식 노드와 데이터를 교환합니다.
            swap(heap[now], heap[next]);
            now = next;
        }
    }

    T& top()
    {
        return heap[0];
    }

    bool empty()
    {
        return heap.empty();
    }

private:
    Container heap = {};
    Predicate predicate = {};
};