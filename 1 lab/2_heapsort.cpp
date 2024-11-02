#include <iostream>
#include <chrono>
#include <cstdlib> // для rand()
using namespace std;
using namespace std::chrono;


//строим кучу для индекса
void heapify(int* arr, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // если левый потомок больше максимального элемента меняем индексы
    if (l < n && *(arr + l) > *(arr + largest))
        largest = l;
    
    //если правый потомок больше максимального элемента меняем индексы
    if (r < n && *(arr + r) > *(arr + largest))
        largest = r;

    //если максимальный эл-т не в корне меняем его
    if (largest != i){
        int swtch = *(arr + i);
        *(arr + i) = *(arr + largest);
        *(arr + largest) = swtch;

    //делаем кучу из измененного поддерева
    heapify(arr, n, largest);

    }

}


void heapssort(int* arr, int n){
    for (int i = n / 2 - 1; i > 0; i--){
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--){
        int swtch = *(arr);
        *(arr) = *(arr + i);
        *(arr + i) = swtch;

        heapify(arr, i, 0);
    }
}

void generateRandomArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; 
    }
}

// Функция для измерения времени работы алгоритма сортировки
void testHeapSort(int size) {
    int* arr = new int[size];
    generateRandomArray(arr, size);

    auto start = std::chrono::high_resolution_clock::now(); // Старт таймера

    heapssort(arr, size); // Выполнение сортировки

    auto end = std::chrono::high_resolution_clock::now();   // Конец таймера

    std::chrono::duration<double> duration = end - start;
    std::cout << "Array size: " << size << " - Time taken: " << duration.count() << " seconds" << std::endl;

    delete[] arr;
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел

    // Тестируем сортировку на разных размерах массива
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 500000};
    
    for (int size : sizes) {
        testHeapSort(size);
    }

    return 0;
}
