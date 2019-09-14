//зов воз взо зво овз

//string str1,str2;
//"зов","взо"
//"апал","апавп"
#include <string>
using namespace std;

bool isAnagram (string str1, string str2)
{
    //TO Multiset and compare

    return true;
}

//---------------------------------

 //а  ->   b  ->  c . ......

 struct element
 {
     int value;
     element *next;
 };

 struct List
 {
     element *head_;
 };

 int main()
 {
     List newList;
    //k element from the end
     element *temp = newList.head_;
     element *tempK = newList.head_;
     int k = 3, i = 0;
     while(temp)
     {
         temp = temp->next;
         i++;
         if(i >= k)
             tempK = tempK->next;
     }

    return 0;
 }
