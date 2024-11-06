#include "lexer.hh"
#include "mman.h"

















int main() {

    auto tokens = Lexer(R"((define f x (x))
    (+ "Hello" -1.5)
)").tokenize();

    for (auto t : tokens) std::cout << t.value << "\n";

    return 0;
}
