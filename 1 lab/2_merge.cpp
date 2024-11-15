#include <iostream>
#include <chrono>
#include <cstdlib> // для rand()
using namespace std;
using namespace std::chrono;


void mergeArrays(int* left, int leftSize, int* right, int rightSize, int* arr) {
    int i = 0, j = 0, k = 0;

    // два подмассивов в один
    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // копируем оставшиеся элементы из левого подмассива
    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    // копируем оставшиеся элементы из правого подмассива
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

// функция сортировки слиянием
void mergeSort(int* arr, int size) {
    if (size < 2) {
        return; 
    }

    int mid = size / 2;

    // Создаем временные подмассивы для левой и правой частей
    int* left = new int[mid];
    int* right = new int[size - mid];

    // Копируем элементы в подмассивы
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    // сортируем левую и правую части
    mergeSort(left, mid);
    mergeSort(right, size - mid);

    // сливаем отсортированные части
    mergeArrays(left, mid, right, size - mid, arr);

    delete[] left;
    delete[] right;
}

void fillArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
}

// Функция для тестирования сортировки и записи результата в файл
void testMergeSort(int size, ofstream& file) {
    int* arr = new int[size];
    fillArray(arr, size);

    auto start = high_resolution_clock::now();
    mergeSort(arr, size);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    file << size << " " << duration.count() << endl; // Запись в файл
    cout << "Array size: " << size << ", Time taken: " << duration.count() << " ms" << endl;

    delete[] arr;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    ofstream file("merge_sort_results.txt"); // Открываем файл для записи

    int start_size = 1000;   // Начальный размер массива
    int step = 2000;         // Шаг увеличения размера
    int num_tests = 20;      // Количество тестов

    for (int i = 0; i < num_tests; i++) {
        int size = start_size + i * step;
        testMergeSort(size, file);
    }

    file.close(); // Закрываем файл
    return 0;
}
