#include <iostream>

class SubForwardList {
private:
    struct Node {
        int data;
        Node* next;

        Node(int d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head;

public:
    SubForwardList() : head(nullptr) {}

    // Правило пяти
    ~SubForwardList() {
        clear();
    }

    SubForwardList(const SubForwardList& other) : head(nullptr) {
        Node* cur = other.head;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    SubForwardList& operator=(const SubForwardList& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    SubForwardList(SubForwardList&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    SubForwardList& operator=(SubForwardList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    // Методы
    bool push_back(int d) {
        if (!head) {
            head = new Node(d);
            return true;
        }

        Node* cur = head;
        while (cur->next) {
            cur = cur->next;
        }

        cur->next = new Node(d);
        return true;
    }

    int pop_back() {
        if (!head) {
            return 0;
        }

        if (!head->next) {
            int res = head->data;
            delete head;
            head = nullptr;
            return res;
        }

        Node* cur = head;
        Node* prev = nullptr;

        while (cur->next) {
            prev = cur;
            cur = cur->next;
        }

        int res = cur->data;
        delete cur;
        prev->next = nullptr;
        return res;
    }

    bool push_forward(int d) {
        head = new Node(d, head);
        return true;
    }

    int pop_forward() {
        if (!head) {
            return 0;
        }

        int res = head->data;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return res;
    }

    bool push_where(unsigned int where, int d) {
        if (where == 0) {
            return push_forward(d);
        }

        Node* cur = head;
        Node* prev = nullptr;
        unsigned int cur_index = 0;

        while (cur && cur_index < where) {
            prev = cur;
            cur = cur->next;
            cur_index++;
        }

        if (cur_index != where) {
            return false;
        }

        Node* new_node = new Node(d, cur);
        if (prev) {
            prev->next = new_node;
        }
        return true;
    }

    int erase_where(unsigned int where) {
        if (where == 0) {
            return pop_forward();
        }

        Node* cur = head;
        Node* prev = nullptr;
        unsigned int cur_index = 0;

        while (cur && cur_index < where) {
            prev = cur;
            cur = cur->next;
            cur_index++;
        }

        if (cur_index != where || !cur) {
            return 0;
        }

        int res = cur->data;
        if (prev) {
            prev->next = cur->next;
        }
        delete cur;
        return res;
    }

    unsigned int size() const {
        unsigned int size = 0;
        Node* cur = head;

        while (cur) {
            size++;
            cur = cur->next;
        }

        return size;
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};
