#include <memory>
#include <iostream>

struct Point{
    Point() : x(0.0), y(0.0) {}
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    double x, y;
};

// 2 (a)
class C1{
private:
    std::shared_ptr<double> d;
public:
    C1(std::shared_ptr<double> value) : d(value) {}
    virtual ~C1() { std::cout << "C1 destructor\n";}

    void print() const { std::cout << "Value " << *d; }
};

class C2{
private:
    std::shared_ptr<double> d;
public:
    C2(std::shared_ptr<double> value) : d(value) {}
    virtual ~C2() { std::cout << "C2 destructor\n";}
    void print() const { std::cout << "Value " << *d; }
};

int main(){
    // 1 (a), (b)
    try{
        std::unique_ptr<double> d = std::make_unique<double>(1.0);
        std::unique_ptr<Point> pt = std::make_unique<Point>(1.0, 2.0);

        // Dereference and call member functions
        *d = 2.0;
        pt->x = 3.0; // Modify x coordinate
        pt->y = 3.0; // Modify y coordinate
        //throw -1;
    }
    catch(int& exception){
        std::cout << "Error, but memory is cleaned up in smart pointer destructor" << "\n";
    }

    // 1 (c)
    {
        int* ptr = new int(0);
        std::unique_ptr<int> uniquePtr1(ptr);
        std::unique_ptr<int> uniquePtr2(ptr); 
        uniquePtr2.release();     
    } // If multiple unique_ptrs are initialised to the same ptr without releasing there is a double free

    { // Doesn't compile because assignment is deleted (must be moved)
        //std::unique_ptr<int> ptr1 = std::make_unique<int>(0);
        //std::unique_ptr<int> ptr2 = ptr1;
    }

    {
        std::unique_ptr<int> ptr1 = std::make_unique<int>(0);
        std::unique_ptr<int> ptr2 = std::move(ptr1);
    }

    // 2 (b)
    std::shared_ptr<double> ptr = std::make_shared<double>(1.0);
    {
        C1 c1(ptr);
        C2 c2(ptr);
        std::cout << "Number of shared owners of ptr: " << ptr.use_count() << "\n";
    }
    std::cout << "Number of shared owners of ptr: " << ptr.use_count() << "\n";

    // 2 (d)
    {
        std::shared_ptr<double> sp1 = std::make_shared<double>(1.0);
        std::shared_ptr<double> sp2 = std::move(sp1);
        std::cout << "sp1 is the unique owner of a resource: " << std::boolalpha << sp1.unique() << "\n";
        std::cout << "sp2 is the unique owner of a resource: " << std::boolalpha << sp2.unique() << "\n";
        std::swap(sp1, sp2);
        sp2.reset();
    }

    {
        // Define auto_ptr pointers instead of raw pointers
        std::unique_ptr <double> d(new double (1.0));
        // Dereference
        *d = 2.0;
        // Change ownership of auto_ptr
        // (after assignment, d is undefined)
        std::unique_ptr <double> d2 = std::move(d);
        *d2 = 3.0;
        std::cout << "Auto values: " << *d.get() << ", " << *d2.get();
    }
}