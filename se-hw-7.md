# 7-5
![](https://gh.qwqwq.com.cn/stephen-zeng/img/master/202411290038024.png)
```cpp
#include <bits/stdc++.h>
using namespace std;

class Shape {
    
};

class Rectangle 
: public Shape {
    public:
        int getArea() {
            return x * y;
        }
        void setA(const int& x, const int& y) {
            this->x = x;
            this->y = y;
        }

    private:
        int x;
        int y;
};

class Circle
: public Shape {
    public:
        double getArea() {
            return 3.14 * r * r;
        }
        void setR(const int& r) {
            this->r = r;
        }
    
    private:
        int r;
};

class Square
: public Rectangle {
    public:
        void setX(const int& x) {
            setA(x, x);
        }
};

int main() {
    Square square;
    int n;
    cin>>n;
    square.setX(n);
    cout<<square.getArea()<<endl;
    return 0;
}
```

```
输入：3
输出：9
```

# 7-11
![](https://gh.qwqwq.com.cn/stephen-zeng/img/master/20241129003909.png)
```cpp
#include <bits/stdc++.h>
using namespace std;

class BaseClass {
    public:
        void fn1(){cout<<"BC1"<<endl;}
        void fn2(){cout<<"BC2"<<endl;}
};

class DerivedClass
: public BaseClass {
    public:
        void fn1(){cout<<"DC1"<<endl;}
        void fn2(){cout<<"DC2"<<endl;}
};

int main() {
    DerivedClass* dc = new DerivedClass();
    BaseClass* bc = dc;
    dc->fn1();
    dc->fn2();
    bc->fn1();
    bc->fn2();
    return 0;
}
```

```
输出：
DC1
DC2
BC1
BC2
```