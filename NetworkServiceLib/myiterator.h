#ifndef MYITERATOR
#define MYITERATOR
namespace NetworkService {
template <class T> class MyIterator : public std::iterator<std::forward_iterator_tag,T> {
private:
    T *memb;
    uint index;
    MyIterator();
public:
    explicit MyIterator(T *nmemb,uint idx) {
        if(nmemb==nullptr)
            throw std::invalid_argument("Cannot initialize iterator with nullptr");
        memb=nmemb;
        index=idx;
    }

    MyIterator(const MyIterator &it) {
            memb = it.memb;
            index = it.index;
    }

    MyIterator & operator ++() {
        index++;
        return *this;
    }

    MyIterator operator ++(int) {
        MyIterator<T> tmp(*this);
        tmp.index++;
        return tmp;
    }

    MyIterator & operator = (const MyIterator &it) {
        if (this != &it) {
            memb=it.memb;
            index = it.index;
        }
        return *this;
    }

    typename T::indexT & operator *() {
        return dynamic_cast<typename T::indexT &>(memb[index]);
    }
    typename T::indexT * operator ->() {
        return dynamic_cast<typename T::indexT *>(&memb[index]);
    }
    friend bool operator == (MyIterator &lv, MyIterator &rv) {
        return lv.memb == rv.memb && lv.index==rv.index;
    }
    friend bool operator != (MyIterator &lv, MyIterator &rv) {
        return !(lv==rv);
    }
    virtual ~MyIterator();
};
template <class T> class MyConstIterator : public std::iterator<std::forward_iterator_tag,T> {
private:
    const T *memb;
    uint index;
    MyConstIterator();
public:
    explicit MyConstIterator(const T *nmemb,uint idx) {
        if(nmemb==nullptr)
            throw std::invalid_argument("Cannot initialize iterator with nullptr");
        memb=nmemb;
        index=idx;
    }

    MyConstIterator(const MyConstIterator &it) {
            memb = it.memb;
            index = it.index;
    }

    MyConstIterator & operator ++() {
        index++;
        return *this;
    }

    MyConstIterator operator ++(int) {
        MyConstIterator<T> tmp(*this);
        tmp.index++;
        return tmp;
    }

    MyConstIterator & operator = (const MyConstIterator &it) {
        if (this != &it) {
            memb=it.memb;
            index = it.index;
        }
        return *this;
    }

    const typename T::indexT & operator *() {
        return dynamic_cast<const typename T::indexT &>(memb[index]);
    }
    const typename T::indexT * operator ->() {
        return dynamic_cast<const typename T::indexT *>(&memb[index]);
    }
    friend bool operator == (const MyConstIterator &lv, const MyConstIterator &rv) {
        return lv.memb == rv.memb && lv.index==rv.index;
    }
    friend bool operator != (const MyConstIterator &lv, const MyConstIterator &rv) {
        return !(lv==rv);
    }
    virtual ~MyConstIterator();
};
}
#endif // MYITERATOR

