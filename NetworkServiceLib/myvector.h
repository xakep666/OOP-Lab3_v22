#ifndef MYVECTOR
#define MYVECTOR
namespace NetworkService {
template<typename T> class MyVector {
private:
    T *array;
    size_t nmemb;
    size_t maxmemb;
    static void _copy(T *dst, const T *src, size_t membstocopy) {
        if(dst==nullptr || src==nullptr)
            throw std::invalid_argument("Cannot copy from/to nullptr");
        for(size_t i=0;i<membstocopy;i++)
            dst[i]=src[i];
    }

public:
    MyVector(): array(nullptr), nmemb(0),maxmemb(0) {}
    MyVector(const MyVector &mv) {
        nmemb=mv.nmemb;
        maxmemb=mv.nmemb;
        array = new T[nmemb];
        if (mv.array!=nullptr)
            _copy(array,mv.array,nmemb);
    }
    MyVector(MyVector &&mv) {
        array=mv.array;
        nmemb=mv.nmemb;
        maxmemb=mv.maxmemb;
        mv.array=nullptr;
        mv.nmemb=0;
        mv.maxmemb=0;
    }
    virtual ~MyVector() {
        delete [] array;
    }
    MyVector & operator = (const MyVector &mv) {
        if(this == &mv)
            return *this;
        nmemb=mv.nmemb;
        maxmemb=mv.nmemb;
        array = new T[nmemb];
        if(mv.array!=nullptr)
            _copy(array,mv.array,nmemb);
        return *this;
    }
    MyVector & operator = (MyVector &&mv) {
        if(this == &mv)
            return *this;
        array=mv.array;
        nmemb=mv.nmemb;
        maxmemb=mv.maxmemb;
        mv.array=nullptr;
        mv.nmemb=0;
        mv.maxmemb=0;
        return *this;
    }
    void reserve(size_t maxmemb) {
        T *_array = new T[maxmemb];
        if(array!=nullptr) {
            _copy(_array,array,maxmemb);
            delete [] array;
        }
        array=_array;
        this->maxmemb=maxmemb;
        this->nmemb=maxmemb;
    }
    void push_back(T item) {
        if (nmemb==maxmemb) {
            size_t _maxmemb = 2*maxmemb+1;
            for(;;) {
                try {
                    T *_array = new T[_maxmemb];
                    if(array!=nullptr)
                        _copy(_array,array,maxmemb);
                    array=_array;
                    maxmemb=_maxmemb;
                } catch (std::bad_alloc &ba) {
                    if(_maxmemb>maxmemb+1)
                        throw ba;
                    _maxmemb--;
                    continue;
                }
                break;
            }
        }
        array[nmemb++]=item;
    }
    size_t size() const {
        return nmemb;
    }
    T & operator [] (uint index) {
        if(index>=nmemb)
            throw std::invalid_argument("Index ("+std::to_string(index)+
                                        ") is greater then number of items ("+std::to_string(nmemb)+")");
        return array[index];
    }

    const T & operator [] (uint index) const {
        if(index>=nmemb)
            throw std::invalid_argument("Index ("+std::to_string(index)+
                                        ") is greater then number of items ("+std::to_string(nmemb)+")");
        return array[index];
    }
    typedef T indexT;
    friend class MyIterator<MyVector>;
    friend class MyConstIterator<MyVector>;
    typedef MyIterator<MyVector> Iterator;
    typedef MyConstIterator<MyVector> ConstIterator;
    Iterator begin() {
        return Iterator(this,0);
    }
    ConstIterator cbegin() const{
        return ConstIterator(this,0);
    }
    Iterator end() {
        return Iterator(this,nmemb);
    }
    ConstIterator cend() const {
        return ConstIterator(this,nmemb);
    }
    void erase(Iterator iter) {
        uint startindex = iter.getIndex();
        for(uint i=startindex;i<nmemb-1;i++)
            array[i]=array[i+1];
        nmemb--;
    }
    void eraseAll() {
        if(std::is_destructible<T>::value)
            for(uint i=0;i<nmemb;i++)
                array[i].~T();
        nmemb=0;
    }

    void shrink_to_fit() {
        T *_array=nullptr;
        if (nmemb>0) {
            _array = new T[nmemb];
            _copy(_array,array,nmemb);
        }
        delete [] array;
        array=_array;
        maxmemb=nmemb;
    }
    T & back (){
       return array[nmemb-1];
    }
    const T & back() const{
        return array[nmemb-1];
    }
};
}
#endif // MYVECTOR
