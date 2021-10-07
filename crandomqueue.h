#ifndef CRANDOMQUEUE_H
#define CRANDOMQUEUE_H
#include <QVector>

template<typename T>
class CRandomQueue
{
    QVector<T> mArray;
public:
    CRandomQueue() {}
    void append(T aData) {
        mArray.append(aData);
    }
    bool isEmpty() {
        return mArray.isEmpty();
    }
    void clear() {
        mArray.empty();
    }
    T get() {
        int pos = qrand() % mArray.size();
        T tmp = mArray[pos];
        mArray[pos] = mArray.back();
        mArray.back() = tmp;
        return mArray.back();
    }
    T pop() {
        T buf = get();
        mArray.pop_back();
        return buf;
    }
};

#endif // CRANDOMQUEUE_H
