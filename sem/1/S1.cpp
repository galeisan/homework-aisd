// Дерево квадрантов
// Задача: нахождение ближайшей к координате точки

#include <iostream>
#include <cmath>
using namespace std;

// Используется для хранения координат точки
struct Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

// Объекты, которые мы хотим сохранить в дереве квадрантов
struct Node
{
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};

// Основной класс дерева квадрантов
class Quad
{
    // Границы координат этого узла
    Point topLeft;
    Point botRight;

    // Содержит подробную информацию об узле
    Node *n;

    // Дочерние узлы
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;

public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
    }
    Quad(Point topL, Point botR)
    {
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
    }
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
};

// Вставка узла в дерево
void Quad::insert(Node *node)
{
    if (node == NULL)
        return;

    // Не содержит его
    if (!inBoundary(node->pos))
        return;

    // Мы находимся в квадрате единичной площади
    // Мы не можем разделить этот квад дальше
    if (abs(topLeft.x - botRight.x) <= 1 &&
        abs(topLeft.y - botRight.y) <= 1)
    {
        if (n == NULL)
            n = node;
        return;
    }

    if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
    {
        // Указывает topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                        Point(topLeft.x, topLeft.y),
                        Point((topLeft.x + botRight.x) / 2,
                              (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }

            // Указывает botLeftTree
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                        Point(topLeft.x,
                              (topLeft.y + botRight.y) / 2),
                        Point((topLeft.x + botRight.x) / 2,
                              botRight.y));
            botLeftTree->insert(node);
        }
    }
    else
    {
        // Указывает topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                        Point((topLeft.x + botRight.x) / 2,
                              topLeft.y),
                        Point(botRight.x,
                              (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }

            // Указывает botRightTree
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                        Point((topLeft.x + botRight.x) / 2,
                              (topLeft.y + botRight.y) / 2),
                        Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}

// Ищем узел в дереве
Node* Quad::search(Point p)
{
    // Текущий квад не может содержать его
    if (!inBoundary(p))
        return NULL;

    // Мы находимся в квадрате единичной длины
    //  Мы не можем разделить этот квад дальше
    if (n != NULL)
        return n;

    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        // Указывает topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }

            // Указывает botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Указывает topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }

            // Указывает botRightTree
        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};

// Проверить, содержит ли текущее дерево квадрантов точку
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x &&
            p.x <= botRight.x &&
            p.y >= topLeft.y &&
            p.y <= botRight.y);
}

// main
int main()
{
    Quad center(Point(0, 0), Point(8, 8));
    Node a(Point(1, 1), 1);
    Node b(Point(2, 5), 2);
    Node c(Point(7, 6), 3);
    center.insert(&a);
    center.insert(&b);
    center.insert(&c);
    cout << "Node a: " <<
         center.search(Point(1, 1))->data << "\n";
    cout << "Node b: " <<
         center.search(Point(2, 5))->data << "\n";
    cout << "Node c: " <<
         center.search(Point(7, 6))->data << "\n";
    cout << "Non-existing node: "
         << center.search(Point(5, 5));
    return 0;
}
