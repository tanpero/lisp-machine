#include <iostream>
#include <string>
#include <vector>

// 函数用于显示帮助信息
void showHelp() {
    std::cout << "Usage: monde [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help            Show this help message and exit.\n";
    std::cout << "  -v, --version         Show version information and exit.\n";
}

void showVersion() {
    std::cout << "Monde - Version 1.0.0" << std::endl;
}


void evaluateCommand(const std::string& command) {
    std::cout << "You entered: " << command << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args;


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            showHelp();
            return 0;
        }
        else if (arg == "-v" || arg == "--version") {
            showVersion();
            return 0;
        }
        else {
            args.push_back(arg);
        }
    }


    if (!args.empty()) {
        std::cout << "Command line arguments:" << std::endl;
        for (const auto& arg : args) {
            std::cout << arg << std::endl;
        }
    }


    std::string line;
    std::cout << "Monde - Interaction (type 'exit' to quit)" << std::endl;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        }

        evaluateCommand(line);
    }

    return 0;
}