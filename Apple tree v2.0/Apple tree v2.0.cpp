// Apple tree v2.0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Apple 
{
public:
    Apple(int weight) : weight(weight), left(nullptr), right(nullptr), parent(nullptr) {}

    int getWeight() const
    {
        return weight;
    }

    void setWeight(int newWeight) 
    {
        weight = newWeight;
    }

    bool operator==(const Apple& other) const
    {
        return weight == other.weight;
    }

    bool operator!=(const Apple& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Apple& other) const 
    {
        return weight < other.weight;
    }

    bool operator<=(const Apple& other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator>(const Apple& other) const 
    {
        return weight > other.weight;
    }

    bool operator>=(const Apple& other) const 
    {
        return (*this > other) || (*this == other);
    }

    Apple* left;
    Apple* right;
    Apple* parent;

private:
    int weight;
};

class Tree
{
public:
    Tree() : root(nullptr) {}

    void insert(const Apple& apple) 
    {
        root = insertRecursive(root, nullptr, apple);
    }

    void print() const 
    {
        printInOrder(root);
    }

    Apple* search(int weight) const
    {
        return searchRecursive(root, weight);
    }

    Apple* minimum() const 
    {
        return minimumRecursive(root);
    }

    Apple* maximum() const 
    {
        return maximumRecursive(root);
    }

    Apple* getNext(const Apple& apple) const 
    {
        return getNextRecursive(root, apple);
    }

    Apple* getPrevious(const Apple& apple) const 
    {
        return getPreviousRecursive(root, apple);
    }

    void remove(const Apple& apple) 
    {
        root = removeRecursive(root, nullptr, apple);
    }

private:
    Apple* root;

    Apple* insertRecursive(Apple* current, Apple* parent, const Apple& apple)
    {
        if (current == nullptr)
        {
            Apple* newNode = new Apple(apple.getWeight());
            newNode->parent = parent;
            return newNode;
        }

        if (apple < *current) 
        {
            current->left = insertRecursive(current->left, current, apple);
        }
        else
        {
            current->right = insertRecursive(current->right, current, apple);
        }

        return current;
    }

    void printInOrder(const Apple* current) const
    {
        if (current != nullptr) 
        {
            printInOrder(current->left);
            cout << "Apple with weight " << current->getWeight() << "g\n";
            printInOrder(current->right);
        }
    }

    Apple* searchRecursive(Apple* current, int weight) const 
    {
        if (current == nullptr || current->getWeight() == weight)
        {
            return current;
        }

        if (weight < current->getWeight()) 
        {
            return searchRecursive(current->left, weight);
        }
        else 
        {
            return searchRecursive(current->right, weight);
        }
    }

    Apple* minimumRecursive(Apple* current) const 
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        while (current->left != nullptr) 
        {
            current = current->left;
        }

        return current;
    }

    Apple* maximumRecursive(Apple* current) const 
    {
        if (current == nullptr) 
        {
            return nullptr;
        }

        while (current->right != nullptr) 
        {
            current = current->right;
        }

        return current;
    }

    Apple* getNextRecursive(Apple* root, const Apple& apple) const 
    {
        Apple* current = searchRecursive(root, apple.getWeight());
        if (current == nullptr) 
        {
            return nullptr;
        }

        if (current->right != nullptr)
        {
            return minimumRecursive(current->right);
        }

        Apple* parent = current->parent;
        while (parent != nullptr && current == parent->right) 
        {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }

    Apple* getPreviousRecursive(Apple* root, const Apple& apple) const 
    {
        Apple* current = searchRecursive(root, apple.getWeight());
        if (current == nullptr)
        {
            return nullptr;
        }

        if (current->left != nullptr) 
        {
            return maximumRecursive(current->left);
        }

        Apple* parent = current->parent;
        while (parent != nullptr && current == parent->left)
        {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }

    Apple* removeRecursive(Apple* current, Apple* parent, const Apple& apple) 
    {
        if (current == nullptr) 
        {
            return current;
        }

        if (apple < *current) 
        {
            current->left = removeRecursive(current->left, current, apple);
        }
        else if (apple > *current)
        {
            current->right = removeRecursive(current->right, current, apple);
        }
        else 
        {
            if (current->left == nullptr) 
            {
                Apple* temp = current->right;
                if (temp)
                {
                    temp->parent = parent;
                }
                delete current;
                return temp;
            }
            else if (current->right == nullptr)
            {
                Apple* temp = current->left;
                if (temp)
                {
                    temp->parent = parent;
                }
                delete current;
                return temp;
            }

            Apple* temp = minimumRecursive(current->right);
            current->setWeight(temp->getWeight());
            current->right = removeRecursive(current->right, current, *temp);
        }
        return current;
    }
};

int main()
{
    
    srand(time(0));

    Tree tree;
    for (int i = 0; i < 20; ++i) 
    {
        int randomWeight = std::rand() % 151 + 50; 
        Apple apple(randomWeight);
        tree.insert(apple);
    }

    cout << "Apples on the tree:\n";
    tree.print();

    int searchWeight = 120;
    Apple* foundApple = tree.search(searchWeight);
    if (foundApple)
    {
        cout << "Apple with weight " << searchWeight << "g found in the tree.\n";
    }
    else
    {
        cout << "Apple with weight " << searchWeight << "g not found in the tree.\n";
    }

    Apple* minApple = tree.minimum();
    if (minApple) 
    {
        cout << "Minimum apple weight: " << minApple->getWeight() << "g\n";
    }

    Apple* maxApple = tree.maximum();
    if (maxApple)
    {
        cout << "Maximum apple weight: " << maxApple->getWeight() << "g\n";
    }

    int removeWeight = 150;
    tree.remove(Apple(removeWeight));
    cout << "After removing apple with weight " << removeWeight << "g:\n";
    tree.print();

    return 0;
}
