#ifndef HEAP_H
#define HEAP_H

#include <vector>

using namespace std;

template<typename T,typename K>
class Heap
{
private:
    vector<T> value;
    vector<K> key;
    int order;

public:
    Heap(int ord);

    enum{minheap = 0,maxheap = 1};

    void push(T val,K ky);
    K top_key();
    T top_value();
    void pop();
    void clear();
    int size();
};

template<typename T,typename K>
Heap<T, K>::Heap(int ord):order(ord)
{
    T t;
    K k;
    value.push_back(t);
    key.push_back(k);
}

template<typename T,typename K>
void Heap<T, K>::push(T val, K ky)
{
    value.push_back(val);
    key.push_back(ky);
    T tv;
    K tk;
    for (int j = key.size()-1; j > 1; j /= 2)
    {
        if(order == minheap)
        {
            if (key[j] < key[j / 2])
            {
                tv = value[j];
                value[j] = value[j / 2];
                value[j / 2] = tv;

                tk = key[j];
                key[j] = key[j / 2];
                key[j / 2] = tk;
            }
            else
                break;
        }
        else if(order == maxheap)
        {
            if (key[j] > key[j / 2])
            {
                tv = value[j];
                value[j] = value[j / 2];
                value[j / 2] = tv;

                tk = key[j];
                key[j] = key[j / 2];
                key[j / 2] = tk;
            }
            else
                break;
        }
    }

}
template<typename T,typename K>
K Heap<T, K>::top_key()
{
    return key[1];
}
template<typename T,typename K>
T Heap<T, K>::top_value()
{
    return value[1];
}
template<typename T,typename K>
void Heap<T, K>::pop()
{
    T tv;
    K tk;
    key[1] = key[key.size()-1];
    key.pop_back();
    value[1] = value[value.size()-1];
    value.pop_back();
    for (int j = 1; j <= (key.size()-1) / 2; j *= 2)
    {
        if(order == minheap)
        {
            if (key[j * 2] > key[j * 2 + 1])
            {
                tk = key[j];
                key[j] = key[j * 2 + 1];
                key[j * 2 + 1] = tk;

                tv = value[j];
                value[j] = value[j * 2 + 1];
                value[j * 2 + 1] = tv;
            }
            else
            {
                tk = key[j];
                key[j] = key[j * 2];
                key[j * 2] = tk;

                tv = value[j];
                value[j] = value[j * 2];
                value[j * 2] = tv;
            }
        }
        else if(order == maxheap)
        {
            if (key[j * 2] > key[j * 2 + 1])
            {
                tk = key[j];
                key[j] = key[j * 2 + 1];
                key[j * 2 + 1] = tk;

                tv = value[j];
                value[j] = value[j * 2 + 1];
                value[j * 2 + 1] = tv;
            }
            else
            {
                tk = key[j];
                key[j] = key[j * 2];
                key[j * 2] = tk;

                tv = value[j];
                value[j] = value[j * 2];
                value[j * 2] = tv;
            }
        }
    }
}

template<typename T,typename K>
void Heap<T,K>::clear()
{
    key.clear();
    value.clear();
    T t;
    K k;
    value.push_back(t);
    key.push_back(k);
}
template<typename T,typename K>
int Heap<T,K>::size()
{
    return key.size()-1;
}



#endif // HEAP_H
