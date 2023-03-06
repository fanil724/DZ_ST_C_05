#ifndef ARRAY_H
#define ARRAY_H

class Array {
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value;
        NodeStackPtr previous = nullptr;
        NodeStackPtr next = nullptr;

    };


};

#endif //ARRAY_H