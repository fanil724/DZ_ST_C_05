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

    };

    Array(size_t size) : count_(0), size_(size), array_(new NodeStack[size_]) {}

    void realocate(size_t new_size) {
        Array<T> ar(new_size);
        for (int i = 0; i < std::min(new_size, size_); i++) {
            ar.Add(GetAt(i));
        }
        delete[] array_;
        array_ = ar.array_;
        size_ = new_size;
    }

    void SetSize(size_t size, size_t grow = 1) {
        if (size > size_) {
            realocate(size_ + grow);
            size_ += grow;
        } else {
            realocate(size);
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
        std::swap(array_, copy.array_);
        return *this;
    }

    Array(Array &&another) noexcept = default;

    ~Array() {
        NodeStackPtr current = array_;
        while (current != nullptr) {
            NodeStackPtr next = current->next;
            delete current;
            current = next;
        }
    }

    void FreeExtra() {
        realocate(count_);
    }

    void RemoveAll() {
        realocate(0);
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
            realocate(count_ + ar.count_);
            for (int i=0;i<ar.count_;i++) {
                Add(ar.GetAt(i));
            }
        }else{
            for (int i=0;i<ar.count_;i++) {
                Add(ar.GetAt(i));
            }
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
    NodeStack *array_;

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