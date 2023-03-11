#include <iostream>
#include "Stack.hpp"
#include "TwoStack.hpp"
#include "Police_base.hpp"
#include "ArrayTwo.hpp"

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
    //   StackList2<int> srt({1, 2, 3, 6, 1, 23, 65});
//    srt.print();
//    srt.insert(10,3);
//    srt.print();
//    srt.printreverse();
//    StackList2<int> st({1, 56, 3, 4, 9, 16, 4, 94, 16, 1, 64, 46, 16, 36, 45});
//    st.print();
//    st.printreverse();
//    srt.CloneList(st);
//    srt.print();
//    srt.printreverse();

//задание 4
//    Database base;
//    base.Add(56413);
//    base.Add(53);
//    base.Add(59633);
//    base.Add(5643);
//    base.Add(563);
//    base.Add(58573);
//    base.PrintAll(base.ReturnRoot(), 10);

//задание 3
    ArrayTwo<int> ar(5);
    ar.Add(45);
    ar.Add(43245);
    ar.Add(4234565);
    ar.Add(4521);
    ar.Add(4511);
    ar.Add(987);
    ar.Add(357);

    ArrayTwo<int> arr(5);
    arr.Add(45);
    arr.Add(43245);
    arr.Add(4234565);
    arr.Add(629);
    arr.Add(639);
    arr.Add(169);

    std::cout << ar;
    std::cout << arr;
    ar.Append(arr);
    std::cout << ar.GetSize() << std::endl;
    std::cout << ar;
    arr = ar;
    std::cout << arr;
    std::cout << ar;

}
