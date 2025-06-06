#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <future>
#include <mutex>
#include <string>

std::mutex mtx;

void multiplyThread(const std::string& threadName, const std::vector<float>& data_1, const std::vector<float>& data_2, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << threadName << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        std::cout << data_1[i] << " * " << data_2[i] << " = " << data_1[i] * data_2[i] << std::endl;
    }
}

void addThread(const std::string& threadName, const std::vector<float>& data_1, const std::vector<float>& data_2, int n) {
    for (int j = 0; j < n; j++) {
        std::cout << threadName << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        std::cout << data_1[j] << " + " << data_2[j] << " = " << data_1[j] + data_2[j] << std::endl;
    }
}

void randomThread(const std::string& threadName, const std::vector<float>& data, int n) {
    for (int k = 0; k < n; k++) {
        std::cout << threadName << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
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

    std::thread thread1(multiplyThread, "Multiply Thread", std::ref(multiplyData_1), std::ref(multiplyData_2), n1);
    std::thread thread2(addThread, "Add Thread", std::ref(addData_1), std::ref(addData_2), n2);
    std::thread thread3(randomThread, "Random Thread", std::ref(randomData), n3);

    thread1.join();
    std::cout << "MultiplyThread has completed." << std::endl;
    thread2.join();
    std::cout << "AddThread has completed." << std::endl;
    thread3.join();
    std::cout << "RandomThread has completed." << std::endl;
    std::cout << "All threads completed." << std::endl;
    return 0;
}