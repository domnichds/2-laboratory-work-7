#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <future>

void multiplyThread(const std::vector<float>& data_1, const std::vector<float>& data_2, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "MultiplyThread" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << data_1[i] << " * " << data_2[i] << " = " << data_1[i] * data_2[i] << std::endl;
    }
}

void addThread(const std::vector<float>& data_1, const std::vector<float>& data_2, int n) {
    for (int j = 0; j < n; j++) {
        std::cout << "AddThread" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << data_1[j] << " + " << data_2[j] << " = " << data_1[j] + data_2[j] << std::endl;
    }
}

void randomThread(const std::vector<float>& data, int n) {
    for (int k = 0; k < n; k++) {
        std::cout << "RandomThread" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << data[k] << std::endl;
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 100.0);

    const int n1 = 20, n2 = 30, n3 = 10;

    std::vector<float> multiplyData_1;
    std::vector<float> multiplyData_2;
    for (int i = 0; i < n1; ++i) {
        multiplyData_1.push_back(dist(gen));
        multiplyData_2.push_back(dist(gen));
    }

    std::vector<float> addData_1;
    std::vector<float> addData_2;
    for (int i = 0; i < n2; ++i) {
        addData_1.push_back(dist(gen));
        addData_2.push_back(dist(gen));
    }

    std::vector<float> randomData;
    for (int i = 0; i < n3; ++i) {
        randomData.push_back(dist(gen));
    }
    /*
    std::thread thread1(multiplyThread, std::ref(multiplyData_1), std::ref(multiplyData_2), n1);
    std::thread thread2(addThread, std::ref(addData_1), std::ref(addData_2), n2);
    std::thread thread3(randomThread, std::ref(randomData), n3);

    thread1.join();
    thread2.join();
    thread3.join();
    */
    auto future1 = std::async(std::launch::async, multiplyThread, std::ref(multiplyData_1), std::ref(multiplyData_2), n1);
    auto future2 = std::async(std::launch::async, addThread, std::ref(addData_1), std::ref(addData_2), n2);
    auto future3 = std::async(std::launch::async, randomThread, std::ref(randomData), n3);

    future1.get();
    future2.get();
    future3.get();

    std::cout << "All threads completed." << std::endl;

    return 0;
}