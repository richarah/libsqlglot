// Copy of fuzz_optimizer with debug output
#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <csignal>

volatile bool running = true;

void signal_handler(int) {
    running = false;
}

class OptimizerFuzzer {
public:
    OptimizerFuzzer() : gen(std::random_device{}()), dist(0, 255) {
        std::cout << "OptimizerFuzzer constructed" << std::endl;
    }

    std::string mutate(const std::string& base) {
        return base + " ";  // Simple mutation for testing
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

int main() {
    std::cout << "Step 1: Setting up signal handlers..." << std::endl;
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    std::cout << "Step 2: Creating fuzzer..." << std::endl;
    OptimizerFuzzer fuzzer;

    std::cout << "Step 3: Initializing corpus..." << std::endl;
    std::vector<std::string> corpus = {
        "SELECT * FROM (SELECT * FROM t) s",
        "SELECT x FROM t WHERE x = x"
    };

    std::cout << "Step 4: Starting fuzzing loop..." << std::endl;
    uint64_t iterations = 0;

    while (running && iterations < 5) {
        std::cout << "Iteration " << iterations << std::endl;
        std::string seed = corpus[iterations % corpus.size()];
        std::string mutated = fuzzer.mutate(seed);

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, mutated);

            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                auto select = static_cast<libsqlglot::SelectStmt*>(ast);
                libsqlglot::Optimizer::qualify_columns(select);
            }
        } catch (...) {
            // Expected
        }

        iterations++;
    }

    std::cout << "Completed " << iterations << " iterations" << std::endl;
    return 0;
}
