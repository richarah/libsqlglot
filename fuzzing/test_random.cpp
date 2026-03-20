#include <iostream>
#include <random>

int main() {
    std::cout << "Test 1: Creating std::random_device..." << std::endl;
    try {
        std::random_device rd;
        std::cout << "random_device created" << std::endl;

        std::cout << "Test 2: Getting random number..." << std::endl;
        auto seed = rd();
        std::cout << "Seed: " << seed << std::endl;

        std::cout << "Test 3: Creating mt19937..." << std::endl;
        std::mt19937 gen(seed);
        std::cout << "mt19937 created" << std::endl;

        std::cout << "Test 4: Creating distribution..." << std::endl;
        std::uniform_int_distribution<> dist(0, 255);
        std::cout << "distribution created" << std::endl;

        std::cout << "Test 5: Generating random number..." << std::endl;
        int num = dist(gen);
        std::cout << "Random number: " << num << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "All random tests passed!" << std::endl;
    return 0;
}
