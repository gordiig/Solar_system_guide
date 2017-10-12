#include "singletone.h"

template <typename T>
Singletone<T>::~Singletone()
{
    if (instance)
    {
        delete instance;
    }
}
