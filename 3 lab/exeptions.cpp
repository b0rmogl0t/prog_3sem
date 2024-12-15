#include <iostream>


class VectorException : public std::exception {
private:
    std::string message;

public:
    explicit VectorException(const std::string& msg) : message("VectorException: " + msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class VectorAllocEception : public VectorException {
public:
    explicit VectorAllocEception(const std::string& msg) : VectorException("Memory Allocation Failed: " + msg) {}
};

class VectorEmptyPopback : public VectorException {
public:
    explicit VectorEmptyPopback(const std::string& msg) : VectorException("Empty sybvector pop_back: " + msg) {}
};

class VectorMaxCapacity : public VectorException {
public:
    explicit VectorMaxCapacity(const std::string& msg) : VectorException("Max capacity reached: " + msg) {}
};


struct subvector {
    int* mas;
    unsigned int top;
    unsigned int capacity;

    // Конструктор по умолчанию
    subvector() : mas(nullptr), top(0), capacity(0) {}

    // Деструктор
    ~subvector() {
        clear();
    }

    // Конструктор копирования
    subvector(const subvector& other)
        : mas(nullptr), top(other.top), capacity(other.capacity) {
        if (other.mas) {
            mas = new int[capacity];
            for (unsigned int i = 0; i < top; ++i) {
                mas[i] = other.mas[i];
            }
        }
    }

    // Оператор копирующего присваивания
    subvector& operator=(const subvector& other) {
        if (this == &other) return *this; // Защита от самоприсваивания

        delete[] mas; // Освобождаем старую память

        top = other.top;
        capacity = other.capacity;
        mas = nullptr;
        if (other.mas) {
            mas = new int[capacity];
            for (unsigned int i = 0; i < top; ++i) {
                mas[i] = other.mas[i];
            }
        }
        return *this;
    }

    // Конструктор перемещения
    subvector(subvector&& other) noexcept
        : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr; // Обнуляем источник
        other.top = 0;
        other.capacity = 0;
    }

    // Оператор перемещающего присваивания
    subvector& operator=(subvector&& other) noexcept {
        if (this == &other) return *this; // Защита от самоприсваивания

        delete[] mas; // Освобождаем старую память

        mas = other.mas;
        top = other.top;
        capacity = other.capacity;

        other.mas = nullptr; // Обнуляем источник
        other.top = 0;
        other.capacity = 0;

        return *this;
    }

    bool push_back(int d) {
        try {
            if (capacity == 0) {
                mas = new int[1];
                mas[0] = d;
                capacity = 1;
                top = 1;
                return true;
            }

            if (top < capacity) {
                mas[top++] = d;
                return true;
            }

            if (capacity >= UINT32_MAX) {
                throw VectorMaxCapacity("Cannot push_back when max capacity reached in subvector.");
            } else if (capacity > UINT32_MAX / 2) {
                capacity = UINT32_MAX;
            }
            else {
                capacity *= 2;
            }
            int* tmp = new int[capacity] {};

            for (unsigned int i = 0; i < top; i++) {
                tmp[i] = mas[i];
            }
            tmp[top++] = d;

            delete[] mas;
            mas = tmp;

            return true;
        }
        catch (const std::bad_alloc&) {
            throw VectorAllocEception("Memory allocation failed in push_back");
        }
    }

    int pop_back() {
        if (top == 0) {
            throw VectorEmptyPopback("Cannot pop_back from an empty subvector");
        }
        return mas[--top];
    }

    bool resize(unsigned int new_capacity) {
        try {
            if (capacity == new_capacity) {
                return true;
            }

            if (new_capacity == 0) {
                clear();
                return true;
            }
            int* tmp = new int[new_capacity] {};
            unsigned int last = (new_capacity > top) ? top : new_capacity;

            for (unsigned int i = 0; i < last; i++) {
                tmp[i] = mas[i];
            }

            delete[] mas;
            mas = tmp;
            capacity = new_capacity;
            top = last;

            return true;
        }
        catch (const std::bad_alloc&) {
            throw VectorAllocEception("Memory allocation failed in resize");
        }
    }

    void shrink_to_fit() {
        resize(top);
    }

    void clear() {
        delete[] mas;
        mas = nullptr;
        top = 0;
        capacity = 0;
    }
};

int main() {
    try {
        subvector sv;

        sv.push_back(10);
        sv.push_back(20);
        std::cout << "Added elements successfully.\n";

        std::cout << "Last element: " << sv.pop_back() << std::endl;

        sv.pop_back();
        sv.pop_back(); // Выкинет ошибку

        std::cout << UINT32_MAX << std::endl;

        int step = 0;
        while (true) { // Выкинет ошибку рано или поздно
            sv.push_back(1);
        }
    }
    catch (const VectorEmptyPopback& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const VectorAllocEception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const VectorMaxCapacity& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const VectorException& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
