#ifndef MYVECTOR
#define MYVECTOR
namespace NetworkService {
template<typename T> class MyVector {
private:
    T *array;
    size_t nmemb;
    size_t maxmemb;
public:
    MyVector(): array(nullptr), nmemb(0),maxmemb(0) {}
    MyVector(const MyVector &mv) {
        array = (T *)calloc(mv.nmemb,sizeof(T));
        if(!array)
            throw std::bad_alloc();
        array = (T *)memcpy(array,mv.array,mv.nmemb*sizeof(T));
        nmemb=mv.nmemb;
        maxmemb=mv.nmemb;
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
        free(array);
    }
    MyVector & operator = (const MyVector &mv) {
        if(this == &mv)
            return *this;
        nmemb=mv.nmemb;
        maxmemb=mv.nmemb;
        array = (T *)calloc(nmemb,sizeof(T));
        if(!array)
            throw std::bad_alloc();
        array = (T *)memcpy(array,mv.array,mv.nmemb*sizeof(T));
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
        array = (T *)calloc(maxmemb,sizeof(T));
        if(!array)
            throw std::bad_alloc();
        this->maxmemb=maxmemb;
    }
    void push_back(T item) {
        if (nmemb==maxmemb) {
            size_t _maxmemb= 2*maxmemb+1;
            T *_array = (T *)calloc(_maxmemb,sizeof(T));
            while(_array==nullptr && _maxmemb>=maxmemb+1)
                _array = (T *)calloc(--_maxmemb,sizeof(T));
            if(_array==nullptr)
                throw std::bad_alloc();
            if(array!=nullptr) {
                _array=(T *)memcpy(_array,array,nmemb*sizeof(T));
                T *tmp = array;
                array = _array;
                free(tmp);
            } else {
                array = _array;
            }
            maxmemb=_maxmemb;
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
        uint startindex = &(*iter)-array;
        T item = *iter;
        for(uint i=startindex;i<nmemb-1;i++)
            array[i]=array[i+1];
        array[nmemb-1]=item;
        nmemb--;
    }
    void shrink_to_fit() {
        T *_array = (T *)realloc(array,nmemb*sizeof(T));
        if(_array==nullptr)
            throw std::bad_alloc();
        array=_array;
        maxmemb=nmemb;
    }
    T & back (){
       return array[nmemb-1];
    }
};
}
#endif // MYVECTOR
