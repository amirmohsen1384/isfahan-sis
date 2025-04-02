#include <iostream>
#include <random>
#include <stdexcept>
#include <QDataStream>

template<typename T>
class CircularQueue {
public:
    CircularQueue();
    ~CircularQueue();

    inline size_t count() const {
        return _length;
    }

    inline bool isFull() const {
        return _length == maximumSize();
    }
    inline bool isEmpty() const {
        return _length == 0;
    }

    T& dequeue();
    void enqueue(T const& data);

    template<typename R>
    friend QDataStream& operator<<(QDataStream &stream, const CircularQueue<R> &data);

    template<typename R>
    friend QDataStream& operator>>(QDataStream &stream, CircularQueue<R> &data);

protected:
    inline virtual size_t maximumSize() const {
        return 128;
    }

private:
    T* _container = nullptr;
    int _length;
    int _front;
    int _rear;
};

template <typename T>
CircularQueue<T>::CircularQueue()
{
    _container = new T[maximumSize()];
    _front = _length = 0;
    _rear = _front - 1;
}

template <typename T>
CircularQueue<T>::~CircularQueue()
{
    delete _container;
}

template <typename T>
T &CircularQueue<T>::dequeue()
{
    if(isEmpty()) {
        throw std::runtime_error("The queue cannot return any elements.");
    }
    size_t index = (_front++ % maximumSize());
    _length--;
    return _container[index];
}

template <typename T>
void CircularQueue<T>::enqueue(T const &data)
{
    if(isFull()) {
        throw std::runtime_error("The queue cannot accept more elements.");
    }
    size_t index = (++_rear % maximumSize());
    _container[index] = data;
    _length++;
}

template<typename R>
QDataStream& operator<<(QDataStream &stream, const CircularQueue<R> &data)
{
    stream << data._length;
    stream << data._front;
    stream << data._rear;
    for(int i = 0; i < data._length; ++i) {
        stream << data._container[i];
    }
    return stream;
}

template<typename R>
QDataStream& operator>>(QDataStream &stream, CircularQueue<R> &data)
{
    stream >> data._length;
    stream >> data._front;
    stream >> data._rear;
    for(int i = 0; i < data._length; ++i) {
        stream >> data._container[i];
    }
    return stream;
}
