#ifndef _NODE_HH_
#define _NODE_HH_

#include <variant>
#include <string>
#include <vector>

enum class NodeType {
    Number,
    String,
    Boolean,

    Symbol,     // function or argument name
    List,       // quote (1 2 3) or '(1, 2, 3)


    // (define variable expression)
    // (define (function-name parameter1 parameter2 ...) 
    //     optional_body
    //     ...
    //     final_body
    // )
    Definition,

    // (lambda (parameter1 parameter2 ...)
    //     optional_body
    //     ...
    //     final_body
    //    )
    Lambda,
};

struct Node {
    NodeType type;
    std::variant<double, std::string, bool, std::vector<std::unique_ptr<Node>>> value;

    Node(NodeType type, std::variant<double, std::string, bool, std::vector<std::unique_ptr<Node>>> value)
        : type(type), value(std::move(value)) {}
};

#endif // !_NODE_HH_
