## 0. 简介

有时候我们在面对通用代码时候，经常会尝试着创建多个示例函数来对一个函数多次赋值，这样会损耗很多的内存空间，这对于代码来说是不利的。而单例模式可以很好的解决这个问题。但是实现一个实用的单例模式来说，这个并不容易。

## 1. 单例函数

### 1. 饿汉模式

饿汉模式 是指单例实例在类装载时就构建，并被立即执行初始化:

```
public class Test {
        private Test() {
        }
        public static Test instance = new Test();// 直接对Test构造函数进行实例化
        public Test getInstance() {
                return instance;
        }
}
```

优点：

1.线程安全
2.在类加载的同时已经创建好一个静态对象，调用时反应速度快

缺点

资源效率不高，可能getInstance()永远不会执行到，但执行该类的其他静态方法或者加载了该类（class.forName)，那么这个实例仍然初始化 。如果类是多态的, 那静态成员变量初始化顺序还是没保证，下面我们将详细解释这个问题.

例如：有两个单例模式的类 ASingleton 和 BSingleton, 某天你想在 BSingleton 的构造函数中使用 ASingleton 实例, 这就出问题了. 因为 BSingleton m_pInstance 静态对象可能先 ASingleton 一步调用初始化构造函数, 结果 ASingleton::getInstance() 返回的就是一个未初始化的内存区域, 程序还没跑就直接崩掉.

### 1.2 懒汉模式

懒汉式是指：单例实例在第一次被使用时构建，但延迟初始化：

```
class Test {
        private Test() {
        }
        public static Test instance = null;
        public static Test getInstance() {
                if (instance == null) {
              //多个线程判断instance都为null时，在执行new操作时多线程会出现重复情况
                        instance = new Test();
                }
                return instance;
        }
}
```

优点：
避免了饿汉式的那种在没有用到的情况下创建事例，资源利用率高，不执行getInstance()就不会被实例，可以执行该类的其他静态方法。
缺点：
懒汉式在单个线程中没有问题，但多个线程同事访问的时候就可能同事创建多个实例，而且这多个实例不是同一个对象，虽然后面创建的实例会覆盖先创建的实例，但是还是会存在拿到不同对象的情况。解决这个问题的办法就是加锁synchonized，第一次加载时不够快，多线程使用不必要的同步开销大。



### 1.3 双重模式

```
class Test {
        private Test() {
        }
        public static Test instance = null;

        public static Test getInstance() {
                if (instance == null) {
                        synchronized (Test.class) {
                                if (instance == null) {
                                        instance = new Test();
                                }
                        }
                }
                return instance;
        }
}
```

优点
资源利用率高，不执行getInstance()就不被实例，可以执行该类其他静态方法
缺点
第一次加载时反应不快



### 1.4 静态内部类

```
class Test {
        private Test() {
        }
        public static Test instance = null;

        public static Test getInstance() {
                if (instance == null) {
                        synchronized (Test.class) {
                                if (instance == null) {
                                        instance = new Test();
                                }
                        }
                }
                return instance;
        }
}
```

优点
资源利用率高，不执行getInstance()就不被实例，可以执行该类其他静态方法
缺点
第一次加载时反应不快



### 1.5 总结：
一般采用饿汉式，若对资源十分在意可以采用静态内部类，不建议采用懒汉式及双重检测 。



## 2 . 设计一款完美的单例模式

这里我们选择静态内部类+模板类的组合方法来有效的对多线程程序进行单例模式设计

### 2.1 Best Practices

网络上存在一些简单的单例模式方法，这里先对一种简单的易懂的单例模式进行解释：

```
#include <iostream>
#include <cassert>

class Singleton
{
public:
    static Singleton& Instance()
    {
        // https://blog.csdn.net/qq_34637408/article/details/71189382
        static Singleton instance; // 静态实例化：
        return instance;
    }
public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
private:
    Singleton() = default;
    ~Singleton() = default;
};

int main()
{
    auto& a = Singleton::Instance(); //实例化
    auto& b = Singleton::Instance();
    assert(&a == &b);

    return 0;
}
```

### 2.2 Best Practices + Template

```
#ifndef CSingleton_hpp
#define CSingleton_hpp

#include <stdio.h>
#include <pthread.h>
#include <memory>

class CSinGuard {
public:
    CSinGuard() { m_lGrdCnt = 0; pthread_mutex_init(&m_cs, nullptr); }
    ~CSinGuard() { pthread_mutex_destroy(&m_cs); }

    int IsGuarded() const { return (m_lGrdCnt > 0); }

public:
    class CGuard {
    public:
        CGuard(CSinGuard& rg):m_rg(rg) { m_rg.Guard(); };
        ~CGuard() { m_rg.Unguard(); }

    private:
        CSinGuard& m_rg;
    };

private:
    void Guard() { pthread_mutex_lock(&m_cs); m_lGrdCnt++; }    //引用+1
    void Unguard() { m_lGrdCnt--; pthread_mutex_unlock(&m_cs); }    //引用-1

    friend class CSinGuard::CGuard;

private:
    pthread_mutex_t m_cs;   //线程锁
    long m_lGrdCnt;     //引用计数
};

template <class T>
class CSingleton
{
public:
    static inline T* Instance();
    static inline void Release();

private:
    CSingleton(void) {}
    virtual ~CSingleton(void) {}
    CSingleton(const CSingleton&) {}
    CSingleton & operator= (const CSingleton &) {}

    static std::unique_ptr<T> m_Instance; //智能指针，会自动释放
    static CSinGuard m_sg;   //单例安全锁
};

//声明单例(对象)模板
template <class T>
std::unique_ptr<T> CSingleton<T>::m_Instance;

//声明单例对象安全锁模板
template <class T>
CSinGuard CSingleton<T>::m_sg;

//获取单例
template <class T>
inline T* CSingleton<T>::GetInstance()
{
    if (m_Instance.get() == nullptr) {
        CSinGuard::CGuard gd(m_sg);      //上锁，防止多线程同时访问
        if (m_Instance.get() == nullptr) {
            m_Instance.reset(new T);// 使用std::unique_ptr<T>.reset实例化.和上文的static Test instance = new Test();类似
        }
    }

    return m_Instance.get();
}

//释放单例
template <class T>
inline void CSingleton<T>::Release()
{
    CSinGuard::CGuard gd(m_sg);
    m_Instance.release();
}

#endif /* CSingleton_hpp */
```

### 2.3 使用方法

```
/**
#define DECLARE_SINGLETON_CLASS(Type) \
friend class std::unique_ptr<Type>; \
friend class CSingleton<Type>; \
static Type* Instance() { Type *shareClass = CSingleton<Type>::Instance(); return shareClass; } \
static void Release() { \
    Type *shareClass = CSingleton<Type>::Instance(); \
    if (shareClass) { \
        delete shareClass; \
        shareClass = nullptr; \
    } \
    CSingleton<Type>::Release(); \
}\**/

#include “CSingleton.hpp”
DECLARE_SINGLETON_CLASS(CLASS NAME);
class CThreadPool
{
public:
    CThreadPool();
    virtual ~CThreadPool();
    DECLARE_SINGLETON_CLASS(CThreadPool);

    void TestSingleton();
    void ReadTestSingleton();
};

void CThreadPool::TestSingleton() {
    printf("It is address:%p", this); 
}

void CThreadPool::ReadTestSingleton() {
    CThreadPool::Instance()->TestSingleton();
    CThreadPool::Release();
}
```

