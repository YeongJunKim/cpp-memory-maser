#include <iostream>
#include <memory>

class unique_basic
{
private:
    int A;
    int B;
    int C;
    int value;
public:
    unique_basic(int _A, int _B, int _C) : A(_A), B(_B), C(_C) {}
    ~unique_basic(){}
    void setValue(int _val){value = _val;}
    int getValue(){return value;}
    void printA(){std::cout << "A: " << A << std::endl;}
    void printB(){std::cout << "B: " << B << std::endl;}
    void printC(){std::cout << "C: " << C << std::endl;}
};

void f1(std::unique_ptr<unique_basic> _uptr) //값으로 받을때
{
    std::cout << __func__ << std::endl;
    _uptr->printA();
}

void f2(const std::unique_ptr<unique_basic> &_uptr) //참조로 받을때
{
    std::cout << __func__ << std::endl;
    // const로 받으면 "공유" 된다. 따라서 여기서 사용은 불가능하다.
    // _uptr->printB();
}

void f3(std::unique_ptr<unique_basic> &&_uptr) // raw value로 받을때
{
    std::cout << __func__ << std::endl;
}

void f4(std::unique_ptr<unique_basic> &&_uptr) // raw value로 받고 move시킬때
{
    std::unique_ptr<unique_basic> a = std::move(_uptr);
    std::cout << "value: " << a->getValue() << std::endl;
}

int main(void)
{
    // nullptr 처럼 선언이 가능하다
    std::unique_ptr<unique_basic> uptr1;
    // 일반적인 사용법
    std::unique_ptr<unique_basic> uptr2{new unique_basic(10,30,40)};
    std::unique_ptr<unique_basic> uptr3 = std::make_unique<unique_basic>(1,2,3);

    // raw 포인터를 unique_ptr로 관리하려면
    unique_basic *rptr1 = new unique_basic(10,20,30);
    std::unique_ptr<unique_basic> uptr4(rptr1);
    
    unique_basic *rptr2 = new unique_basic(20,30,100);
    std::unique_ptr<unique_basic> uptr5;
    uptr5.reset(rptr2);
    
    uptr3->printA();
    unique_basic* pa = nullptr;
    pa = uptr3.get();
    pa->printB();

    // unique_ptr(const unique_ptr&) = delete;
    // f1(ua);
    // rvalue로 넘겨야 한다.
    f1(std::move(uptr3));

    // 함수로 ua 자원을 넘겼기 때문에 ua를 여기서는 사용 불가능하다.
    // ua->printB();
    uptr3 = std::make_unique<unique_basic>(3,2,1);

    f2(uptr3);

    uptr3->setValue(10);
    std::cout << "value: " << uptr3->getValue() << std::endl;

    f3(std::move(uptr3));

    f4(std::move(uptr3));

    std::cout << "value: " << uptr3->getValue() << std::endl;
    // std::cout << ua.get() << std::endl;
    // f4(std::move(ua));
}