#include <iostream>
using namespace std;
struct element
{
    int x;
    element *next;
};

struct List
{
    List() : head_(NULL) {}
    ~List()
    {
        while (head_ != NULL)
        {
            element *temp = head_->next;
            delete head_;
            head_ = temp;
        }
    }
    void Add(int x)
    {
        element *temp = new element;
        temp->x = x;
        cout << head_ << endl;
        temp->next = head_;
        head_ = temp;
        cout << head_ << endl;
    }
    void Show()
    {
        element *temp = head_;
        while(temp != NULL)
        {
            cout << temp << " " << temp->next << " " << temp->x << endl ;
            temp = temp->next;
        }
        cout << endl;
    }
    void Reverse()
    {
        element *current, *next, *previous = NULL;
        current = head_;
        while(current)
        {
            cout << current << " " << next  << " " << previous << endl;
            next = current->next;
            current->next = previous;;
            previous = current;
            current = next;
            cout << current << " " << next  << " " << previous << endl;
        }
        head_ = previous;
    }
    void reverseList()
    {
        element *d = NULL;
        for (element *a = head_, *b; a != NULL; a = b)
        {
            b = a->next;
            a->next = d;
            d = a;
        }
        head_ = d;
    }
private:
    element *head_;
};



int main()
{
    cout << "Hello World!" << endl;

    List newList;
    newList.Add(1);
    newList.Add(2);
    newList.Add(3);
    cout << endl;
    newList.Show();
    newList.reverseList();//a = head_, d = NULL, c == a->next/// then while(a) b <- c <- d <- a <- b
    newList.Show();

    return 0;
}
