#include <iostream>

struct subvector {
    int *mas;
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
        if (capacity == 0) {
            mas = new int[1]{d};
            capacity = 1;
            top = 1;
            return true;
        }

        if (top < capacity) {
            mas[top++] = d;
            return true;
        }

        capacity *= 2;
        int* tmp = new int[capacity]{};
        for (unsigned int i = 0; i < top; i++) {
            tmp[i] = mas[i];
        }
        tmp[top++] = d;
        delete[] mas;
        mas = tmp;
        return true;
    }

    int pop_back() {
        if (top == 0) {
            return 0;
        }
        return mas[--top];
    }

    bool resize(unsigned int new_capacity) {
        if (capacity == new_capacity) {
            return true;
        }

        if (new_capacity == 0) {
            clear();
            return true;
        }

        int* tmp = new int[new_capacity]{};
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
    subvector sv;
    sv.push_back(10);
    sv.push_back(20);
    subvector sv_copy = sv;  // Копирующий конструктор
    subvector sv_moved = std::move(sv);  // Перемещающий конструктор

    std::cout << "Last element in copied subvector: " << sv_copy.pop_back() << std::endl;
    std::cout << "Last element in moved subvector: " << sv_moved.pop_back() << std::endl;
    return 0;
}
