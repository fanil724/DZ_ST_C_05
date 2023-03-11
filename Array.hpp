#ifndef ARRAY_H
#define ARRAY_H

#include <utility>

template<typename T>
class Array {
public:
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value;
        NodeStackPtr previous = nullptr;
        NodeStackPtr next = nullptr;
    };

    Array(size_t size) : count_(0), size_(size), array_(new NodeStack[size_]) {}

    Array(const Array &another)
            : Array(another.size()) {}

    Array &operator=(const Array &another) {
        if (&another == this)
            return *this;
        Array copy(another);
        std::swap(size_, copy.size_);
        std::swap(count_, copy.count_);
        std::swap(array_, copy.array_);
        return *this;
    }

    Array(Array &&another) noexcept
            : size_(std::exchange(another.size_, 0ull)),
              count_(std::exchange(another.count_, 0ull)),
              array_(std::exchange(another.array_, nullptr)) {}

    Array &operator=(Array &&another) noexcept {
        if (&another == this)
            return *this;
        delete[] array_;
        count_ = std::exchange(another.count_, 0ull);
        size_ = std::exchange(another.size_, 0ull);
        array_ = std::exchange(another.array_, nullptr);

        return *this;
    }

    void SetSize(size_t size, size_t grow = 1) {
        if (size > size_) {
            realloc(array_, size_ + grow);
            size_ += grow;
        } else {
            realloc(array_, size);
            size_ = size;
        }
    }


    ~Array() {
        delete[] array_;
    }

    void FreeExtra() {
        realloc(array_, count_);
    }

    void RemoveAll() {
        realloc(array_, 0);
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
        return get(index)->value;
    }

    void SetAt(size_t index, T value) {
        GetAt(index) = value;
    }

    void Add(T value) {
        if (count_ == 0) {
            array_->value = value;
            count_++;
        } else if (count_ <= size_) {
            array_[count_ - 1].next = &array_[count_];
            array_[count_].value = value;
            array_[count_].previous = &array_[count_ - 1];
            count_++;
        } else {
            SetSize(size_);
            array_[count_ - 1].next = &array_[count_];
            array_[count_].value = value;
            array_[count_].previous = &array_[count_ - 1];
            count_++;
        }
    }

    void Append(Array<T> &ar) {
        if ((count_ + ar.count_) > size_) {
            realloc(array_,count_ + ar.count_);
            for (int i = 0; i < ar.count_; i++) {
                Add(ar.GetAt(i));
            }
        } else {
            for (int i = 0; i < ar.count_; i++) {
                Add(ar.GetAt(i));
            }
        }
    }

    void InsertAt(size_t index, T value) {
        if (index > count_) {
            Add(value);
        } else if (index < count_) {
            Add(value);
            for (int i = index; index < count_; i++) {
                std::swap(array_[i], array_[i + 1]);
            }
        }
    }

    void RemoveAt(size_t index) {
        if (index == count_) {
            FreeExtra(index);
        } else {
            for (int i = index; index < count_; i++) {
                std::swap(array_[i], array_[i + 1]);
            }
            FreeExtra(count_ - 1);
        }
    }

    bool IsEmpty() {
        if (count_ == 0)
            return true;
        return false;
    }

    void GetData() {
        std::cout << &array_;
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
    NodeStackPtr array_;
    NodeStackPtr get(size_t index) {
        NodeStackPtr current{array_};
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