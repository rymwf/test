#include <cstdio>
#include <stdexcept>

template <class T>
class Iterator
{
public:
    virtual void first() = 0;
    virtual void next() = 0;
};

template <class T>
class linearList
{
public:
    //    class Iterator : public IteratorBase<T>
    //    {
    //    public:
    //        virtual void first() = 0;
    //        virtual void next() = 0;
    //    };
    virtual ~linearList() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int index) const = 0;
    virtual void insert(int index, const T &ele) = 0;
    virtual void insert(int index, T &&ele) = 0;
    virtual void push_back(const T &ele) = 0;
    virtual void push_back(T &&ele) = 0;
    virtual void erase(int index) = 0;
};

template <class T>
class arrayList : public linearList<T>
{
    T *ele_ = nullptr;
    int capacity_ = 0;
    int size_ = 0;
    int newCapacity()
    {
        return 2 * capacity_ + 1;
    }
    void changeCapacity()
    {
        int temp = newCapacity();
        T *newEle = new T[temp];
        for (int i = 0; i < capacity_; ++i)
        {
            newEle[i] = ele_[i];
        }
        delete[] ele_;
        ele_ = newEle;
        capacity_ = temp;
    }

public:
    arrayList() {}
    arrayList(const arrayList<T> &other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        ele_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i)
        {
            ele_[i] = other.ele_[i];
        }
    }
    arrayList(arrayList<T> &&other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        ele_ = other.ele_;
        other.ele_ = nullptr;
        //        *ele=std::move(*other.ele_);
    }
    ~arrayList()
    {
        delete[] ele_;
        ele_ = nullptr;
    }
    bool empty() const override { return size_ == 0; }
    int size() const override { return size_; }
    T &get(int index) const override { return ele_[index]; }
    void push_back(const T &ele)
    {
        if (size_ == capacity_)
            changeCapacity();
        ele_[size_] = ele;
        size_++;
    }
    void push_back(T &&ele) override
    {
        if (size_ == capacity_)
            changeCapacity();
        ele_[size_] = std::move(ele);
        size_++;
    }
    void insert(int index, const T &ele) override
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("out fo range");
        if (size_ == capacity_)
            changeCapacity();
        for (int i = size_; i > index; --i)
        {
            ele_[i] = ele_[i - 1];
        }
        ele_[index] = ele;
        size_++;
    }
    void insert(int index, T &&ele) override
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("out fo range");
        if (size_ == capacity_)
            changeCapacity();
        for (int i = size_; i > index; --i)
        {
            ele_[i] = ele_[i - 1];
        }
        ele_[index] = std::move(ele);
        size_++;
    }
    void erase(int index) override
    {
        if (index < 0 || index >= capacity_)
            throw std::out_of_range("out fo range");
    }
};

template <class T>
class ArrayListIterator : public Iterator<T>
{
    const arrayList<T> *list_;
    int current_ = 0;

public:
    ArrayListIterator(arrayList<T> *list) : list_(list) {}
    void first() override
    {
        current_ = 0;
    }
    void next() override
    {
        current_++;
    }
    bool IsDone()
    {
        return current_ >= list_->size();
    }
    T &CurrentItem()
    {
        if (IsDone())
            throw std::out_of_range("out of range");
        return list_->get(current_);
    }
};
int main()
{
    auto a = arrayList<int>();
    a.push_back(2);
    a.push_back(4);
    auto it = ArrayListIterator<int>(&a);
    for (it.first(); !it.IsDone(); it.next())
        printf("%d ", it.CurrentItem());

    return 0;
}