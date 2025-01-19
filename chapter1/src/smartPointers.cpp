#include <memory>
#include <iostream>

template <typename T>
struct Deleter{
    void operator()(T* ptr) const{
        std::cout << "Used custom deleter at address " << ptr << "\n";
        delete ptr;
    }
};

int main(){
    auto deleter = [](double* ptr){
        std::cout << "Used lambda function custom deleter at address " << ptr << "\n";
        delete ptr;
    };

    std::shared_ptr<double> ptr1(new double(5.3), Deleter<double>());
    std::shared_ptr<double> ptr2(nullptr, deleter);

    std::shared_ptr<double> ptr3(new double (5.3), [](double* ptr){
        std::cout << "Used anonymous lambda function custom deleter at address " << ptr << "\n";
        delete ptr;
    });
    std::shared_ptr ptr4(ptr1);
    std::shared_ptr<double> ptr5(nullptr);
    std::shared_ptr<double> ptr6(ptr2);

    std::cout << "ptr1 shared: " << ptr1.use_count() << "\n"; // 2
    std::cout << "ptr2 shared: " << ptr2.use_count() << "\n"; // 0
    std::cout << "ptr3 shared: " << ptr3.use_count() << "\n"; // 1
    std::cout << "ptr4 shared: " << ptr4.use_count() << "\n"; // 2
    std::cout << "ptr5 shared: " << ptr5.use_count() << "\n"; // 0
}