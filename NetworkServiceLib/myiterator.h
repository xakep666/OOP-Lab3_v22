#ifndef MYITERATOR
#define MYITERATOR
namespace NetworkService {
template <class T> class MyIterator : public std::iterator<std::forward_iterator_tag,T> {
private:
    T *memb;
    uint index;
public:
    MyIterator() : memb(nullptr),index(0) {}
    explicit MyIterator(T *nmemb,uint idx) : memb(nmemb),index(idx) {}

    MyIterator(const MyIterator &it) {
            memb = it.memb;
            index = it.index;
    }

    MyIterator & operator ++() {
        index++;
        return *this;
    }
    MyIterator & operator = (const MyIterator &it) {
        if (this != &it) {
            memb=it.memb;
            index = it.index;
        }
        return *this;
    }

    T * operator *() {
        return memb ? memb[index] : nullptr;
    }
    T * operator ->() {
        return memb ? memb[index] : nullptr;
    }
    friend bool operator == (MyIterator &lv, MyIterator &rv) {
        return lv.memb == rv.memb && lv.index==rv.index;
    }
    friend bool operator != (MyIterator &lv, MyIterator &rv) {
        return lv.memb != rv.memb && lv.index==rv.index;
    }
    virtual ~MyIterator();
};
}
#endif // MYITERATOR

