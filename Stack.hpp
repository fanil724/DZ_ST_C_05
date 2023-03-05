#ifndef STACK_H
#define STACK_H

template<typename T>
class StackList {
public:
    struct NodeStack;
    using NodeStackPtr = NodeStack *;

    struct NodeStack {
        T value;
        NodeStackPtr next = nullptr;

        NodeStack(T value) {
            this->value = std::move(value);
            next = nullptr;
        }

        NodeStack(T value, NodeStackPtr next) {
            this->value = std::move(value);
            this->next = next;
        }
    };

    StackList() : size_(0), first_node_(nullptr),
                  last_node_(&first_node_) {};

    StackList(std::initializer_list<T> list)
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

    StackList &operator=(StackList &src) {
        StackList(src).swap(*this);
        return *this;
    }

    void swap(StackList &src) {
        std::swap(size_, src.size_);
        std::swap(last_node_, src.last_node_);
        std::swap(first_node_, src.first_node_);
    }

    StackList(StackList &&another) noexcept = default;

    ~StackList() {
        NodeStackPtr current = first_node_.next;
        while (current != nullptr) {
            NodeStackPtr next = current->next;
            delete current;
            current = next;
        }
    }

    void add(T value) {
        last_node_->next = new NodeStack(std::move(value));
        last_node_ = last_node_->next;
        size_++;
    }

    void insert(T value, size_t index) {
        NodeStackPtr current = get(index);
        *current = NodeStack(value, new NodeStack(std::move(*current)));
        size_++;
    }

    void pop(size_t index) {
        size_--;
        if (index == 0) {
            first_node_ = std::move(*first_node_.next);
            return;
        }
        NodeStackPtr node = get(index - 1);
        if (index == size_) {
            delete node->next;
            last_node_ = node;
            return;
        }
        NodeStackPtr todelete = node->next;
        node->next = node->next->next;
        delete todelete;
    }

    T &operator[](size_t index) {
        return get(index)->value;
    }

    bool is_equal(T value, StackList<T> &another) {
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

    NodeStack &CloneList(StackList<T> &another) {
        for (int i = size_ - 1; i > 0; i--) {
            pop(i);
        }
        first_node_.value = another.first_node_.value;
        NodeStackPtr anoth{&another.first_node_};
        NodeStackPtr current{anoth->next};
        while (current != another.last_node_->next) {
            add(current->value);
            current = current->next;
        }
        return first_node_;
    }

    NodeStack &operator+(StackList<T> &another) {
        NodeStackPtr current{&another.first_node_};
        while (current != another.last_node_->next) {
            add(current->value);
            current = current->next;
        }
        return first_node_;
    }

    NodeStack &operator*(StackList<T> &another) {
        for (int i = 0; i < size_; i++) {
            if (!is_equal(get(i)->value, another)) {
                if (i != size_ - 1) {
                    pop(i);
                    i--;
                }
            }
        }
        return first_node_;
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

#endif //STACK_H