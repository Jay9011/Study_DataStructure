#pragma once
#include <vector>
using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
    void push(const T& data)
    {
        // �켱 �� ������ ����� �ݴϴ�.
        heap.push_back(data);

        // �θ�� ������ �����մϴ�.
        int now = static_cast<int>(heap.size()) - 1;

        while (now > 0) // ��Ʈ ������ �ݺ��մϴ�.
        {
            // �θ� ���� ���մϴ�.
            int next = (now - 1) / 2; // �θ� ��� index
            //if (heap[now] < heap[next])
            //    break;
            if (predicate(heap[now], heap[next]))
                break;

            // �θ� ���� �����͸� ��ȯ�մϴ�.
            swap(heap[now], heap[next]);
            now = next;
        }
    }

    void pop()
    {
        // �ڽ� ��带 ��Ʈ�� �ű�ϴ�.
        heap[0] = heap.back();
        heap.pop_back();

        // �ڽĵ�� ������ �����մϴ�.
        int now = 0;
        while (true)
        {
            int left = 2 * now + 1; // ���� �ڽ� index
            int right = 2 * now + 2; // ������ �ڽ� index

            // ������ ������ ��� �����մϴ�.
            if (left >= heap.size())
                break;


            int next = now;

            // ���� �ڽİ� ���մϴ�.
            //if (heap[next] < heap[left])
            //    next = left;
            if (predicate(heap[next], heap[left]))
                next = left;

            // �� �� ���ڸ� �����ʰ� ���մϴ�.
            //if (right < heap.size() && heap[next] < heap[right])
            //    next = right;
            if (right < heap.size() && predicate(heap[next], heap[right]))
                next = right;


            // �̵����� �ʴ� ��� �����մϴ�.
            if (next == now)
                break;

            // �ڽ� ���� �����͸� ��ȯ�մϴ�.
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