#include <iostream>

using namespace std;

typedef char ItemType;

bool IsOpen(char symbol);
bool IsClosed(char symbol);
bool Matches(char symbol, char openSymbol);


bool IsOpen(char symbol)
{
    if ((symbol == '(') || (symbol == '{') || (symbol == '[') || (symbol == '/*'))
        return true;
    else
        return false;
}

bool IsClosed(char symbol)
{
    if ((symbol == ')') || (symbol == '}') || (symbol == ']') || (symbol == '*/'))
        return true;
    else
        return false;
}

bool Matches(char symbol, char openSymbol)
{
    return (((openSymbol == '(') && symbol == ')')
        || ((openSymbol == '{') && symbol == '}')
        || ((openSymbol == '[') && symbol == ']')
        || ((openSymbol == '/*') && symbol == '*/'));

}

class FullStack
{};

class EmptyStack
{};

class StackType
{
public:
    StackType();
    bool IsEmpty() const;
    bool IsFull() const;
    void Push(ItemType item);
    void Pop();
    ItemType Top() const;
private:
    int top;
    ItemType items[500];
};

StackType::StackType()
{
    top = -1;
}

bool StackType::IsEmpty() const
{
    return (top == -1);
}

bool StackType::IsFull() const
{
    return (top == 500-1);
}

void StackType::Push(ItemType newItem)
{
    if (IsFull())
        throw FullStack();
    top++;
    items[top] = newItem;
}

void StackType::Pop()
{
    if(IsEmpty())
        throw EmptyStack();
    top--;
}

ItemType StackType::Top() const
{
    if (IsEmpty())
        throw EmptyStack();
    return items[top];
}


int main()
{
    char symbol;
    StackType stack;
    bool balanced = true;
    char openSymbol;

    cout << "Enter an expression and press return." << endl;
    cin.get(symbol);
    while (symbol != '\n' && balanced)
    {
        if (IsOpen(symbol))
            stack.Push(symbol);
        else if (IsClosed(symbol))
        {
            if (stack.IsEmpty())
                balanced = false;
            else
            {
                openSymbol = stack.Top();
                stack.Pop();
                balanced = Matches(symbol, openSymbol);
            }
        }
        cin.get(symbol);
    }
    if (!stack.IsEmpty())
        balanced = false;
    if (balanced)
        cout << "Expression is well formed."  << endl;
    else
        cout << "Expression is not well formed." << endl;

    return 0;
}
