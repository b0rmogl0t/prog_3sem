#include <iostream>
#include <deque>
#include <string>
#include <vector>


template <typename T, typename Container = std::deque<T>>
class stack {
private:
    Container container_;

public:
    void push(const T& value) {
        container_.push_back(value);
    }

    void pop() {
        if (!container_.empty()) {
            container_.pop_back();
        }
    }

    T top() const {
        return container_.back();
    }

    bool empty() const {
        return container_.empty();
    }

    std::size_t size() const {
        return container_.size();
    }
};


template <>
class stack<char, std::string> {
private:
    std::string container_;

public:
    void push(char value) {
        container_ += value;
    }

    void pop() {
        if (!container_.empty()) {
            container_.pop_back();
        }
    }

    char top() const {
        return container_.back();
    }

    bool empty() const {
        return container_.empty();
    }

    std::size_t size() const {
        return container_.size();
    }
};


int main() {
    stack<int> s1;

    stack<double, std::vector<double>> s2;

    stack<char, std::string> s3;

    s3.push('a');

    s1.push(0);
    s2.push(3.14);
    s2.push(2.718);
    s2.pop();

    std::cout << s1.top() << " " << s2.top() << " " << s3.top() << std::endl;


    return 0;
}