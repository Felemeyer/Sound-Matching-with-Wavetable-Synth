#include <iostream>  //output to console
#include <string>    //C++ string data type;
#include <cstring>   //functions for C-style strings char arr[] (strcpy,strcmp,strcat,strlen...)
#include <vector>    //vector data structure; at(i),erase(itPos),insert(itPos,val), push_back, pop_back
#include <map>       //map data type; size, clear, empty ,begin ,end, at(key), contains
#include <set>       //data structure that stores only keys
#include <queue>     //a FIFO (first-in, first-out) data structure; front,back,push,pop
#include <stack>     //a LIFO data structure; empty, size, back, push_back, pop
#include <algorithm> //e.g. count(itS,itE,val), find(itS,itE,val),sort(itS,itE), min_element(itS,itE)
#include <iterator>  //functions: begin,end,size,empty,data,advance,distance,next,prev
#include <fstream>   //read or write files; open, getline, get, ignore, close
#include <chrono>    //time measuring, e.g ::steady_clock::now(), ::duration<double>

#define NEWLINE '\n' // define Constant
#define MAXIMUM 3

using namespace std; // use the standard namespace

// declare functions
int randomInt();
bool checkExist(vector<int> arr, int val);

// declare global variables
int number = 4; // static if only for this file
int *numberPtr = &number;
vector<string> words = {"Hello", "World"};
map<std::string, int> pairs{
    {"CPU", 10},
    {"GPU", 15},
    {"RAM", 20},
};

// declare types
struct Books
{
    char title[50]; // strcpy to specify
    char author[50];
    int book_id;
};

class myClass
{
    // private
public:
    myClass(int val) // Constructor
    {
        varOne = val;
        objectCount++;
    };
    myClass(const myClass &obj); // copy constructor
    ~myClass();                  // Destructor
    void assignValue(int val);
    friend void printValue(myClass obj);
    void printValue() { cout << varOne; };
    void operator=(const myClass &obj) { varOne = obj.varOne; };
    int compare(myClass obj) { return this->varOne > obj.varOne; }; // need arrow simce this is a pointer
    myClass operator-()                                             // overloading negation
    {
        varOne = -varOne;
        return myClass(varOne);
    };
    static int objectCount; // cout << myClass::objectCount;

private:
    int varOne;

protected:
    int varTwo; // derived classes can access
};

void myClass::assignValue(int val)
{
    varOne = val;
}

void printValue(myClass obj)
{
    cout << obj.varOne;
}

class derivedClass : public myClass //, public class (multiple inheritance)
{
public:
    int timesTen()
    {
        return varTwo * 10;
    }
};

int myClass::objectCount = 0;

template <typename T>
inline T const &Max(T const &a, T const &b)
{
    return a < b ? b : a;
}

// Main Function
int main()
{
    struct Books BookOne;
    myClass anObj(5);
    int anyNumber;
    // an array with 5 rows and 2 columns.
    int a[5][2] = {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}};

    myClass *ptrObj = &anObj;
    ptrObj->printValue();

    cout << "Type in a number: ";
    cin >> anyNumber;

    pairs["CPU"] = 25;

    time_t now = time(0);
    char *dt = ctime(&now); // convert now to string form

    int var[3] = {10, 100, 200};
    int *ptr;
    ptr = &var[3 - 1]; // last adress of array

    for (string str : words)
    {
        cout << str << " ";
    }

    try
    {
        if (anyNumber == 0)
        {
            throw "Division by zero condition!";
        }
    }
    catch (const char &msg) // catches thrown exceptions
    {
        cout << msg;
    }

    return 0;
}

// initialize functions
int randomInt()
{
    srand((unsigned)time(NULL));
    number = rand() % 10; // 0-9
    return number;
}
bool checkExist(vector<int> arr, int val)
{
    bool exist = false;
    exist = find(arr.begin(), arr.end(), val) != arr.end();
    return exist;
}
