// libFuzzer target for SQL parser
// Compile: clang++ -fsanitize=fuzzer,address -I../include fuzz_parser.cpp -o fuzz_parser
// Run: ./fuzz_parser -max_len=10000 -timeout=10

#include <libsqlglot/parser.h>
#include <libsqlglot/arena.h>
#include <cstdint>
#include <cstddef>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    // Convert input to string
    std::string sql(reinterpret_cast<const char*>(data), size);

    // Try to parse it
    try {
        libsqlglot::Arena arena;
        libsqlglot::Parser parser(arena, sql);
        parser.parse();
    } catch (...) {
        // Expected - invalid SQL should throw
        // Fuzzer is looking for crashes, not exceptions
    }

    return 0;  // Non-zero return is reserved for future use
}
