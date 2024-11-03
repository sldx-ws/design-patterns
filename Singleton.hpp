// 饿汉模式
template <class T>
class Singleton
{
public:
    static T& getInstance()
    {
        if (nullptr == inst)
            inst = new T();

        return inst;
    }
private:
    static T* inst;
};
// 只要通过 Singleton 这个包装类来使用 T 对象
// 则一个进程中只有一个 T 对象的实例、



// 懒汉模式
template <class T>
class Singleton
{
public:
    static T* getInstance()
    {
        return &data;
    }

private:
    static T data;
};
// 存在线程不安全
// 第一次调用 GetInstance 的时候, 如果两个线程同时调用, 可能会创建出两份 T 对象的实例
// 但是后续再次调用, 就没有问题了



// 懒汉模式（线程安全版）
template <class T>
class Singleton
{
public:
    static T* getInstance()
    {
        if (nullptr == inst)  // 双重判定空指针, 降低锁冲突的概率, 提高性能
        {
            m.lock();  // 使用互斥锁, 保证多线程情况下也只调用一次 new
            if (nullptr == inst)
            {
                inst = new T();
            }
            m.unlock();
        }

        return inst;
    }
private:
    volatile static T* inst;  // 需要设置 volatile 关键字, 否则可能被编译器优化
    static std::mutex m;
};