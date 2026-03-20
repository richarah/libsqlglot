#include <libsqlglot/transpiler.h>
#include <libsqlglot/arena.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

int main() {
    std::vector<std::string> crash_files;

    // Find all crash samples
    for (const auto& entry : std::filesystem::directory_iterator("crash_samples")) {
        if (entry.path().extension() == ".sql") {
            crash_files.push_back(entry.path().string());
        }
    }

    std::sort(crash_files.begin(), crash_files.end());

    std::cout << "Testing " << crash_files.size() << " crash samples...\n\n";

    int crashes = 0;
    int handled = 0;

    for (const auto& file : crash_files) {
        std::ifstream in(file);
        std::string sql((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        std::cout << "Test: " << file << "\n";
        std::cout << "SQL: " << sql.substr(0, 60) << (sql.size() > 60 ? "..." : "") << "\n";

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, sql);
            std::cout << "Result: Parsed successfully (ast=" << (ast ? "valid" : "null") << ")\n";
            handled++;
        } catch (const std::exception& e) {
            std::cout << "Result: Exception thrown: " << e.what() << "\n";
            handled++;
        } catch (...) {
            std::cout << "Result: CRASH (unknown exception)\n";
            crashes++;
        }

        std::cout << "\n";
    }

    std::cout << "=================================\n";
    std::cout << "Summary:\n";
    std::cout << "  Total samples: " << crash_files.size() << "\n";
    std::cout << "  Handled gracefully: " << handled << "\n";
    std::cout << "  Crashes: " << crashes << "\n";
    std::cout << "=================================\n";

    return crashes > 0 ? 1 : 0;
}
