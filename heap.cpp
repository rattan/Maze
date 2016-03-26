//#include "heap.h"

//template<typename T,typename K>
//Heap<T, K>::Heap(int ord):order(ord)
//{
//        value.push_back(new T);
//        key.push_back(new K);
//}

//template<typename T,typename K>
//void Heap<T, K>::push(T val, K ky)
//{
//    value.push_back(val);
//    key.push_back(ky);
//    T &tv;
//    K &tk;
//    for (int j = key.size(); j > 1; j /= 2)
//    {
//        if(order == minheap)
//        {
//            if (key[j] < key[j / 2])
//            {
//                tv = value[j];
//                value[j] = value[j / 2];
//                value[j / 2] = tv;

//                tk = key[j];
//                key[j] = key[j / 2];
//                key[j / 2] = tk;
//            }
//            else
//                break;
//        }
//        else if(order == maxheap)
//        {
//            if (key[j] > key[j / 2])
//            {
//                tv = value[j];
//                value[j] = value[j / 2];
//                value[j / 2] = tv;

//                tk = key[j];
//                key[j] = key[j / 2];
//                key[j / 2] = tk;
//            }
//            else
//                break;
//        }
//    }

//}
//template<typename T,typename K>
//K Heap<T, K>::top_key()
//{
//    return key[1];
//}
//template<typename T,typename K>
//T Heap<T, K>::top_value()
//{
//    return value[1];
//}
//template<typename T,typename K>
//void Heap<T, K>::pop()
//{
//    T &tv;
//    K &tk;
//    key[1] = key[key.size()-1];
//    key.pop_back();
//    for (int j = 1; j <= key.size() / 2; j *= 2)
//    {
//        if(order == minheap)
//        {
//            if (key[j * 2] > key[j * 2 + 1])
//            {
//                tk = key[j];
//                key[j] = key[j * 2 + 1];
//                key[j * 2 + 1] = tk;

//                tv = value[j];
//                value[j] = value[j * 2 + 1];
//                value[j * 2 + 1] = tv;
//            }
//            else
//            {
//                tk = key[j];
//                key[j] = key[j * 2];
//                key[j * 2] = tk;

//                tv = value[j];
//                value[j] = value[j * 2];
//                value[j * 2] = tv;
//            }
//        }
//        else if(order == maxheap)
//        {
//            if (key[j * 2] > key[j * 2 + 1])
//            {
//                tk = key[j];
//                key[j] = key[j * 2 + 1];
//                key[j * 2 + 1] = tk;

//                tv = value[j];
//                value[j] = value[j * 2 + 1];
//                value[j * 2 + 1] = tv;
//            }
//            else
//            {
//                tk = key[j];
//                key[j] = key[j * 2];
//                key[j * 2] = tk;

//                tv = value[j];
//                value[j] = value[j * 2];
//                value[j * 2] = tv;
//            }
//        }
//    }
//}

//template<typename T,typename K>
//void Heap::clear()
//{
//    key.clear();
//    value.clear();
//    key.push_back(new K);
//    value.push_back(new T);
//}

