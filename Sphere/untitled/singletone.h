#ifndef SINGLETON_H
#define SINGLETON_H


template <typename T>
class Singletone
{
private:
    Singletone();
    Singletone(const Singletone&);
    Singletone(Singletone&&);
    Singletone& operator = (const Singletone&);
    Singletone& operator = (Singletone&&);

    static T *instance;

public:
    ~Singletone();
    static T *GetInstance()
    {
        if (!instance)
        {
            instance = new T;
        }
        return instance;
    }
};

template <typename T>
T* Singletone<T>::instance = nullptr;

#endif // SINGLETON_H
