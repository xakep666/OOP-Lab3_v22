#ifndef MYITERATOR
#define MYITERATOR
namespace NetworkService {
template <class T> class MyIterator {
private:
    int index;
public:
    MyIterator();
    MyIterator(const MyIterator &);
    MyIterator operator ++();
    MyIterator operator --();
    MyIterator & operator = (const MyIterator &);
    T * operator *();
    T * operator ->();
    friend bool operator == (MyIterator &lv, MyIterator &rv);
    friend bool operator != (MyIterator &lv, MyIterator &rv);
    virtual ~MyIterator();
};
}
#endif // MYITERATOR

