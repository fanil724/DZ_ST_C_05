#include <iostream>
#include "Stack.hpp"
#include "TwoStack.hpp"

int main() {
    //задание 1
//    StackList<int> s({1, 5, 6, 9, 4, 6, 49, 90, 56, 16, 56});
//    s.print();
//    StackList<int> w({1, 56, 9, 46, 6, 454, 46, 16});
//    w.print();
//    w.CloneList(s);
//    w.print();
//    s * w;
//    s.print();

//задание 2
    StackList2<int> srt({1, 2, 3, 6, 1, 23, 65});
//    srt.print();
//    srt.insert(10,3);
    srt.print();
    srt.printreverse();
    StackList2<int> st({1, 56, 3, 4, 9, 16, 4, 94, 16, 1, 64, 46, 16, 36, 45});
    st.print();
    st.printreverse();
    srt.CloneList(st);
    srt.print();
    srt.printreverse();
}
