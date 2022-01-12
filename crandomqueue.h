#ifndef CRANDOMQUEUE_H
#define CRANDOMQUEUE_H
#include <QVector>
#include <QQueue>
#include <QDebug>

template<typename T>
class CRandomQueue
{
    QVector<T> mArray;
    QQueue<T> mBufferQueue;
public:
    CRandomQueue() {}
    void append(T aData) {
        mBufferQueue.append(aData);
        //mArray.append(aData);
    }
    bool isEmpty() {
        return mArray.isEmpty() && mBufferQueue.isEmpty();
    }
    void clear() {
        mArray.clear();
        mBufferQueue.clear();
    }
    int getSize() {
        return mArray.size() + mBufferQueue.size();
    }
    T get() {
        maintain();
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
    void forceMove() {
        while (!mBufferQueue.isEmpty()) {
            mArray.append(mBufferQueue.front());
            mBufferQueue.pop_front();
        }
        return;
    }
private:
    void maintain() {
        while (mArray.size() < mBufferQueue.size() * 2) {
            qDebug() << "Maintain:" << mArray.size() << mBufferQueue.size();
            mArray.append(mBufferQueue.front());
            mBufferQueue.pop_front();
        }
        return;
    }
};

#endif // CRANDOMQUEUE_H
