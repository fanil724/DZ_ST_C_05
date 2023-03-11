#ifndef ARRAY_H
#define ARRAY_H

#include <utility>

template<typename T>
class ArrayTwo {
public:
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value = NULL;
        NodeStackPtr previous = nullptr;
        NodeStackPtr next = nullptr;
    };

    ArrayTwo(size_t size) {
        for (int i = 0; i < size - 1; i++) {
            add();
        }
    };

    ~ArrayTwo() {
        NodeStackPtr current = first_node_.next;
        while (current != nullptr) {
            NodeStackPtr next = current->next;
            delete current;
            current = next;
        }
    }

    const size_t &GetSize() const {
        return size_;
    }

    const size_t &GetUpperBound() const {
        return count_;
    }

    void SetSize(size_t size, size_t grow = 1) {
        if (size > size_) {
            for (int i = 0; i < grow; i++) {
                add();
            }
        } else {
            NodeStackPtr current = get(size);
            while (current != nullptr) {
                NodeStackPtr next = current->next;
                delete current;
                current = next;
            }
            last_node_ = get(size - 1);
            last_node_->next = nullptr;
            size_ = size;
        }
    }

    void FreeExtra() {
        SetSize(count_);
    }

    void RemoveAll() {
        count_ = 0;
        size_ = 1;
        SetSize(size_);
    }


    T &operator[](size_t index) {
        return get(index)->value;
    }

    T &GetAt(size_t index) {
        return get(index)->value;
    }

    void SetAt(size_t index, T value) {
        if (index > count_)
            throw std::out_of_range("index is out of boundaries");
        GetAt(index) = value;
    }


    void Append(ArrayTwo<T> &ar) {
        if (size_ < (count_ + ar.count_)) {
            SetSize(size_, count_ + ar.count_);
        }
        for (int i = 0; i < ar.count_; i++) {
            Add(ar[i]);
        }
    }

    void Add(T value) {
        if (count_ == size_) {
            SetSize(size_ + 5, 5);
        }

        GetAt(count_) = value;
        count_++;
    }

    void InsertAt(size_t index, T value) {
        if (count_ == size_) {
            SetSize(size_, 5);
        }
        Add(value);
        NodeStackPtr current = last_node_->previous->previous;
        int count = count_;
        while (index != count) {
            std::swap(current->value, current->previous->value);
            current = current->previous;
            count--;
        }

        count_++;
    }

    void RemoveAt(size_t index) {
        NodeStackPtr current = get(index);
        current->value = NULL;
        while (index != count_ - 1) {
            std::swap(current->value, current->next->value);
            current = current->next;
            index++;
        }
    }

    void operator=(ArrayTwo<T> &ar) {
        int count = ar.count_;
        if (size_ < ar.size_) {
            SetSize(ar.size_, (ar.size_ - size_));
            count_ = ar.count_;
            for (int i = 0; i < count; i++) {
                SetAt(i, ar[i]);
            }
        } else {
            SetSize(count);
            for (int i = 0; i < count; i++) {
                SetAt(i, ar[i]);
            }
            count_ = ar.count_;
        }
    }

    bool IsEmpty() {
        if (count_ == 0)
            return true;
        return false;
    }

    void GetData() {
        std::cout << &first_node_;
    }

    void printRevers() {
        NodeStackPtr current = last_node_;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->previous;
        }
        std::cout << std::endl;
    }

    friend ::std::ostream &operator<<(std::ostream &out, ArrayTwo<T> &st) {
        NodeStackPtr current = &st.first_node_;
        while (current != nullptr) {
            out << current->value << " ";
            current = current->next;
        }
        out << std::endl;
        return out;
    }

private:
    size_t count_ = 0;
    size_t size_ = 1;
    NodeStack first_node_;
    NodeStackPtr last_node_{&first_node_};

    void add() {
        NodeStackPtr temp = last_node_;
        last_node_->next = new NodeStack();
        last_node_ = last_node_->next;
        last_node_->previous = temp;
        size_++;
    }

    NodeStackPtr get(size_t index) {
        NodeStackPtr current{&first_node_};
        size_t count = 0;
        while (count != index) {
            if (current == nullptr)
                throw std::out_of_range("index is out of boundaries");
            count++;
            current = current->next;
        }
        return current;
    }
};


#endif //ARRAY_H