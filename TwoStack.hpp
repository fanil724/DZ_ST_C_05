#ifndef TWOSTACK_H
#define TWOSTACK_H


template<typename T>
class StackList2 {
public:
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value;
        NodeStackPtr previous = nullptr;
        NodeStackPtr next = nullptr;

        NodeStack(T value) {
            this->value = std::move(value);
            next = nullptr;
            previous = nullptr;
        }

        NodeStack(T value, NodeStackPtr next) {
            this->value = std::move(value);
            this->next = next;
        }
    };

    StackList2() : size_(0), first_node_(nullptr),
                   last_node_(&first_node_) {};

    StackList2(std::initializer_list<T> list)
            : first_node_(0),
              last_node_(&first_node_),
              size_(0) {
        const T *begin = list.begin();
        last_node_->value = std::move(*begin);
        ++begin;
        for (; begin != list.end(); ++begin) {
            add(*begin);
        }
    }

    StackList2 &operator=(StackList2 &src) {
        StackList(src).swap(*this);
        return *this;
    }

    void swap(StackList2 &src) {
        std::swap(size_, src.size_);
        std::swap(last_node_, src.last_node_);
        std::swap(first_node_, src.first_node_);
    }

    StackList2(StackList2 &&another) noexcept = default;

    ~StackList2() {
        NodeStackPtr current = first_node_.next;
        while (current != nullptr) {
            NodeStackPtr next = current->next;
            delete current;
            current = next;
        }
    }

    void add(T value) {
        NodeStackPtr temp = last_node_;
        last_node_->next = new NodeStack(std::move(value));
        last_node_ = last_node_->next;
        last_node_->previous = temp;
        size_++;
    }

    void insert(T value, size_t index) {
        NodeStackPtr current = get(index);
        NodeStackPtr node = new NodeStack(value);
        NodeStackPtr temp = current->previous;
        current->previous = node;
        node->next = current;
        temp->next = node;
        node->previous = temp;
        size_++;
    }

    void pop(size_t index) {
        if (index == 0) {
            NodeStackPtr todelete = &first_node_;
            todelete = todelete->next;
            todelete->previous = nullptr;
            first_node_ = *todelete;
            size_--;
            return;
        }
        NodeStackPtr node = get(index - 1);
        if (index == size_) {
            node->next = nullptr;
            last_node_ = node;
            size_--;
            return;
        } else {
            NodeStackPtr todelete = node->next;
            node->next = node->next->next;
            node = node->next;
            node->previous = node->previous->previous;
            delete todelete;
            size_--;
        }
    }

    T &operator[](size_t index) {
        return get(index)->value;
    }

    bool is_equal(T value, StackList2<T> &another) {
        for (int i = 0; i < another.size_ - 1; i++) {
            if (value == another[i]) {
                return true;
            }
        }
        return false;
    }


    void print() {
        std::cout << "Size:" << size_ << std::endl;
        NodeStackPtr current = &first_node_;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void printreverse() {
        std::cout << "Size:" << size_ << std::endl;
        NodeStackPtr current = last_node_;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->previous;
        }
        std::cout << std::endl;
    }

    NodeStack &CloneList(StackList2<T> &another) {
        for (int i = size_; i > 0; i--) {
            pop(i);
        }
        NodeStackPtr anoth{&another.first_node_};
        NodeStackPtr current{anoth->next};
        while (current != another.last_node_->next) {
            add(current->value);
            current = current->next;
        }
        return first_node_;
    }

    NodeStack &operator+(StackList2<T> &another) {
        NodeStackPtr current{&another.first_node_};
        while (current != another.last_node_->next) {
            add(current->value);
            current = current->next;
        }
        return first_node_;
    }

    NodeStack &operator*(StackList2<T> &another) {
        for (int i = 0; i < size_; i++) {
            if (!is_equal(get(i)->value, another)) {
                if (i != size_ - 1) {
                    pop(i);
                    i--;
                }
            }
            return first_node_;
        }
    }

    friend ::std::ostream &operator<<(std::ostream &out, StackList2<T> &st) {
        NodeStackPtr current = &st.first_node_;
        while (current != nullptr) {
            out << current->value << " ";
            current = current->next;
        }
        out << std::endl;
        return out;
    }

private:
    size_t size_ = 0;
    NodeStack first_node_;
    NodeStackPtr last_node_{&first_node_};

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


#endif //TWOSTACK_H