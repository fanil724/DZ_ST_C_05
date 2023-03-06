#ifndef ARRAY_H
#define ARRAY_H


template<typename T>
class Array {
public:
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value;
        NodeStackPtr previous = nullptr;
        NodeStackPtr next = nullptr;

        NodeStack(T value_, NodeStackPtr previous_, NodeStackPtr next_)
                : value(value_), previous(previous_), next(next_) {}

        NodeStack(const NodeStack &another)
                : NodeStack(another.value, another.previous, another.next) {}

        NodeStack &operator=(const NodeStack &another) {
            if (&another == this)
                return *this;
            NodeStack copy(another);
            std::swap(value, copy.value);
            std::swap(previous, copy.previous);
            std::swap(next, copy.next);
            return *this;
        };
    };


    Array(size_t size) : count_(0), size_(size), array_(new NodeStack[size]{}) {}

    T *realocate(T arr[], size_t size, size_t new_size) {
        T *ar = new T[new_size];
        for (int i = 0; i < std::min(new_size, size); i++) {
            ar[i] = arr[i];
        }
        delete[] arr;
        return ar;
    }

    void SetSize(size_t size, size_t grow = 1) {
        if (size > size_) {
            realocate(array_, size_, size_ + grow);
            size_ += grow;
        } else {
            realocate(array_, size_, size);
            size_ = size;
        }
    }

    Array(const Array &another)
            : Array(another.array_, another.GetSize(), another.GetUpperBound()) {}

    Array &operator=(const Array &another) {
        if (&another == this)
            return *this;
        Array copy(another);
        std::swap(count_, copy.count_);
        std::swap(size_, copy.size_);
        std::swap(array_, copy.pointer_);
        return *this;
    }

    void FreeExtra() {
        realocate(array_, size_, count_);
    }

    void RemoveAll() {
        realocate(array_, size_, 0);
        count_ = 0;
        size_ = 0;
    }

    size_t &GetSize() {
        return size_;
    }

    const size_t &GetUpperBound() const {
        return count_;
    }

    T &operator[](size_t index) {
        return get(index)->value;
    }

    T &GetAt(size_t index) {
        return array_[index];
    }

    void SetAt(size_t index, T value) {
        array_[index] = value;
    }

    void Add(T value) {
        if (count_ == 0) {
            SetAt(0, value);
            count_++;
        } else if (count_ <= size_) {
            SetAt(count_ + 1, value);
            array_[count_ + 1].previous = &array_[count_];
            count_++;
        } else {
            SetSize(size_);
            SetAt(count_ + 1, value);
            count_++;
        }
    }

    bool IsEmpty() {
        if (count_ == 0)
            return true;
        return false;
    }

    friend ::std::ostream &operator<<(std::ostream &out, Array<T> &st) {
        NodeStackPtr current = st.array_;
        while (current != nullptr) {
            out << current->value << " ";
            current = current->next;
        }
        out << std::endl;
        return out;
    }

private:
    size_t count_;
    size_t size_;
    NodeStack *array_;

    NodeStackPtr get(size_t index) {
        NodeStackPtr current{&array_};
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