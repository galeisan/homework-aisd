#include <iostream>
#include <vector>

using namespace std;

typedef double dataType;	// Тип информации узлов дерева

struct Node {				// Звено дерева
    dataType data;			// Информация в узлах дерева
    Node *farLeft;			// Указатель на крайнее левое звено
    Node *left;				// Указатель на левое звено
    Node *right;			// Указатель на правое звено
    Node *farRight;			// Указатели на крайнее правое звено
};

class Tree {				// Класс четверичного дерева
private:
    Node *root;				// Корень дерева (в секции private, так как пользователю не нужен)

    /* Вспомогательные рекурсивные функции,
    принимающие в качестве параметра узел дерева */
    int _numOfTree(dataType, dataType);			// Функция определения номера поддерева, куда добавлять новый элемент.
    // Зависит от того, во сколько раз больше или меньше добавляемое число, чем предок
    void _add(Node*&, dataType);				// Рекурсивное добавление нового элемента
    void _clear(Node*&);						// Рекурсивная очистка дерева
    void _toArray(Node*, vector<dataType>&);	// Рекурсивная создания vector<valueType> по элементам дерева обходом Корень-Левый-Правый
    void _count(Node*, int&);					// Рекурсивный подсчет количества элементов
    bool _isExist(Node*, dataType);				// Проверка, содержится ли заданный элемент в дереве
    Node *_findMin(Node*);						// Нахождение указателя на минимальный элемента дерева
    Node *_findMax(Node*);						// Нахождение указателя на максимальный элемент дерева
    void _print(Node*);							// Рекурсивный вывод на экран всех элементов в строчку обходом Левый-Корень-Правый
    void _printByTree(Node*, int h = 2);		// Рекурсивный вывод дерева на экран в древовидном виде, повернутом на 90 градусов против часовой стрелки

public:
    /* Конструкторы и деструктор */
    Tree();					// Конструктор по умолчанию
    Tree(dataType);			// Конструктор с параметром, инициализирует максимальное число потомков каждого узла
    Tree(Tree&); 			// Конструктор копии
    ~Tree();				// Деструктор

    /* Основные методы класса */
    void add(dataType);					// Функция добавления нового числа в дерево
    void clear();						// Функция очистки дерева
    void copy(Tree&);					// Функция копирования дерева
    void erase(dataType);				// Функция удаления из дерева элементов с заданным значением
    void print();						// Вывод на экран всех элементов в строчку обходом Левый-Корень-Правый
    void printByTree(int h = 2);		// Вывод дерева на экран в древовидном виде, повернутом на 90 градусов против часовой стрелки

    /* Дополняющие методы класса */
    void loadFromArray(vector<dataType>);	// Функция создания дерева по элементам вектора
    vector<dataType> toArray();				// Функция создания вектора по элементам дерева
    bool isExist(dataType);					// Функция проверки, содержится ли заданный элемент в дереве
    int count();							// Функция подсчета числа элементов дерева
    dataType min();							// Функция нахождения минимального значения элементов дерева
    dataType max();							// Функция нахождения максимального значения элементов дерева

    friend ostream &operator<<(ostream&, Tree); // Перегруженная операция '<<' вывода элементов дерева в поток
};
