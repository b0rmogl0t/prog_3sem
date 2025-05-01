#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>


bool key(int a, int b) {
    return a < b;
}

class ComparatorClass {
public:
    bool operator()(char a, char b) {
        return a < b;
    }
};

template <typename iter>
void print(iter first, iter last) {
    for (auto i = first; i < last; i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}


template <typename RandomAccessIterator, typename Compare>
void merge(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, Compare comp) {
    int length = std::distance(first, last);

    std::vector<std::decay_t<decltype(*first)>> tmp(length);

    auto it = tmp.begin();

    RandomAccessIterator m1 = first, m2 = mid;

    while (m1 < mid && m2 < last) {
        if (comp(*m1, *m2)) {
            std::iter_swap(m1, it);
            m1++;
        } else {
            std::iter_swap(m2, it);
            m2++;
        }
        it++;
    }

    while (m1 < mid) {
        std::iter_swap(m1, it);
        m1++;
        it++;
    }
    while (m2 < last) {
        std::iter_swap(m2, it);
        m2++;
        it++;
    }

    std::move(tmp.begin(), tmp.end(), first);
}

template <typename RandomAccessIterator, typename Compare>
void sortt(RandomAccessIterator first, RandomAccessIterator last, Compare comp = key) {
    int length = std::distance(first, last);
    if (length <= 1) {
        return;
    }


    RandomAccessIterator mid = first + length / 2;

    sort(first, mid, comp);
    sort(mid, last, comp);

    merge(first, mid, last, comp);
}



int main() {
    const int length = 1000000;

    std::vector<int> v(length);


    std::srand(std::time(0));
    std::generate(v.begin(), v.end(), []() { return std::rand() % 10000; });
    
    std::deque<int> d(v.begin(), v.end());
    std::list<int> l(v.begin(), v.end());


    auto start = std::chrono::high_resolution_clock::now();
    sortt(v.begin(), v.end(), key);
    auto end = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "vector sort time: " << t1.count() / 1000.0 << " s" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    sortt(d.begin(), d.end(), [](int a, int b) { return a < b; });
    end = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "deque sort time:  " << t2.count() / 1000.0 << " s" << std::endl;
    
    ComparatorClass comp;
    std::string s;
    for (int i = 0; i < length; i++) {
        s += (char) (std::rand() % 128);
    }

    start = std::chrono::high_resolution_clock::now();
    sortt(s.begin(), s.end(), comp);
    end = std::chrono::high_resolution_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "string sort time: " << t3.count() / 1000.0 << " s" << std::endl;

    // Will not compile
    // start = std::chrono::high_resolution_clock::now();
    // sortt(l.begin(), l.end(), key);
    // end = std::chrono::high_resolution_clock::now();
    // auto t4 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // std::cout << "list sort time:   " << t4.count() / 1000.0 << " s" << std::endl;

    return 0;
}