#ifndef POLICE_BASE_H
#define POLICE_BASE_H

struct violation {
    char *violat;
    violation *next;
};

struct node {
    int number;
    node *parent;
    node *left;
    node *right;

    violation *head;
    violation *tail;
};

class Database {
public:
    Database() {
        base = NULL;
        size_ = 0;
    };

    ~Database() {
        DeleteAll(base);
    };

    void Add(int value) {
        node *temp = new node;
        temp->number = value;
        temp->left = temp->right = temp->parent = NULL;

        if (!base) {
            base = temp;
        } else {
            node *tmp1 = base;
            node *tmp2 = NULL;

            while (tmp1) {
                tmp2 = tmp1;
                if (value < tmp1->number)
                    tmp1 = tmp1->left;
                else if (value > tmp1->number)
                    tmp1 = tmp1->right;
                else
                    break;
            }
            if (value < tmp2->number) {
                tmp2->left = temp;
                temp->parent = tmp2;
            } else if (value > tmp2->number) {
                tmp2->right = temp;
                temp->parent = tmp2;
            } else
                std::cout << "keys are equal\n";
        }
    };

    void PrintAll(node *temp, int value) {
        if (temp) {
            PrintAll(temp->left, value + 1);
            std::cout << "Number of the car: " << temp->number << std::endl;
            std::cout << "Violation: " << std::endl;
            PrintAll(temp->right, value + 1);
        }
    };

    void PrintNumber(int num) {
        if (base) {
            node *temp = base;
            int k = 0;
            while (temp) {
                if (num == temp->number) {
                    k = 0;
                    break;
                }
                if (num < temp->number) {
                    ++k;
                    temp = temp->left;
                } else if (num > temp->number) {
                    ++k;
                    temp = temp->right;
                }
            }
            if (k == 0) {
                std::cout << "Number of the car: " << temp->number << std::endl;
                std::cout << "Violation: " << std::endl;
            } else
                std::cout << "There is no car with this number in the database\n";

        }
    };

    node *ReturnRoot() {
        return base;
    };

    void DeleteAll(node *temp) {
        if (temp) {
            DeleteAll(temp->left);
            DeleteAll(temp->right);
        }
        delete temp;
    };

private:
    size_t size_;
    node *base;
};

#endif //POLICE_BASE_H