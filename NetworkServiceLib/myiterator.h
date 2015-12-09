#ifndef MYITERATOR
#define MYITERATOR
/*!
 * \file
 * \brief Файл, содержащий шаблонных классов MyIterator, MyConstIterator
 */
namespace NetworkService {
/*!
 * \brief Шаблонный класс итератора
 *
 * Первый параметр шаблона - класс, к которому прикрепляется итератор
 * Для корректной работы требуется следующее:
 * - Переопределенный тип indexT (тип, возвращаемый оператором [])
 * - Перегруженный оператор []
 */
template <class T> class MyIterator : public std::iterator<std::forward_iterator_tag,T> {
private:
    T *memb; ///<Указатель на итерируемый объект
    uint index; ///<Индекс текущего элемента
    MyIterator(); ///<Отключение создания через пустой конструктор для предотвращения обращения к nullptr
public:
    /*!
     * \brief Инициализирующий конструктор
     * \param nmemb Указатель на итерируемый объект
     * \param idx Индекс
     * \throw invalid_argument, если в качетсве указателя передан nullptr
     */
    explicit MyIterator(T *nmemb,uint idx) {
        if(nmemb==nullptr)
            throw std::invalid_argument("Cannot initialize iterator with nullptr");
        memb=nmemb;
        index=idx;
    }

    /*!
     * \brief Копирующий конструктор
     * \param it Исходный объект
     */
    MyIterator(const MyIterator &it) {
            memb = it.memb;
            index = it.index;
    }

    /*!
     * \brief Увеличение индекса на 1 (постфиксный оператор)
     */
    MyIterator & operator ++() {
        index++;
        return *this;
    }

    /*!
     * \brief Увеличение индекса на 1 (префиксный оператор)
     * Используется создание временного объекта итератора
     */
    MyIterator operator ++(int) {
        MyIterator<T> tmp(*this);
        tmp.index++;
        return tmp;
    }

    /*!
     * \brief Получение итератора добавлением к индексу
     * \param toadd Число, добавляемое к текущему индексу
     * \return Новый объект итератора с измененным индексом
     */
    MyIterator operator +(int toadd) {
        MyIterator<T> tmp(*this);
        tmp.index+=toadd;
        return tmp;
    }

    /*!
     * \brief Копирующий оператор присваивания
     *
     * Оператор присваивания, копирующий объект итератора.
     * Корректно обрабатывает присваивание самому себе
     */
    MyIterator & operator = (const MyIterator &it) {
        if (this != &it) {
            memb=it.memb;
            index = it.index;
        }
        return *this;
    }

    /*!
     * \brief Разыменовывание (обращение к элементу итерируемого объекта по индексу)
     * \return Ссылка на объект
     *
     * Разыменовывание с использованием перегруженного оператора [] с последующим динамическим приведением типа
     */
    typename T::indexT & operator *() {
        return dynamic_cast<typename T::indexT &>(memb[index]);
    }
    /*!
     * \brief Доступ к членам объекта, создающего коллекцию
     * \return Указатель на объект, создающий коллекцию
     *
     * Получение указателя на элемент коллекции с помощью перегруженного оператора [] с последующим динамическим приведением типа
     */
    typename T::indexT * operator ->() {
        return dynamic_cast<typename T::indexT *>(&memb[index]);
    }
    /*!
     * \brief Равенство двух итераторов
     * \param lv Итератор слева от знака ==
     * \param rv Итератор справа от знака ==
     * \return true, если итераторы равны, false в противном случае
     *
     * Итераторы считаются равными, если у них совпадают указатели на итерируемый объект и индексы
     */
    friend bool operator == (MyIterator &lv, MyIterator &rv) {
        return lv.memb == rv.memb && lv.index==rv.index;
    }
    /*!
     * \brief Неравенство двух итераторов
     * \param lv Итератор слева от знака ==
     * \param rv Итератор справа от знака ==
     * \return true, если итераторы неравны, false в противном случае
     *
     * Обращение результата оператора ==
     */
    friend bool operator != (MyIterator &lv, MyIterator &rv) {
        return !(lv==rv);
    }
    virtual ~MyIterator() {
    }
};
/*!
 * \brief Шаблонный класс итератора
 *
 * Первый параметр шаблона - класс, к которому прикрепляется итератор
 * Для корректной работы требуется следующее:
 * - Переопределенный тип indexT (тип, возвращаемый оператором [])
 * - Перегруженный оператор []
 * Отличается от обычного итератора тем, что не позволяет изменять значение элемента, на который он указывает
 */
template <class T> class MyConstIterator : public std::iterator<std::forward_iterator_tag,T> {
private:
    const T *memb; ///<Константный указатель на итерируемый объект
    uint index; ///<Индекс текущего элемента
    MyConstIterator(); ///<Отключение создания через пустой конструктор для предотвращения обращения к nullptr
public:
    /*!
     * \brief Инициализирующий конструктор
     * \param nmemb Указатель на итерируемый объект
     * \param idx Индекс
     * \throw invalid_argument, если в качетсве указателя передан nullptr
     */
    explicit MyConstIterator(const T *nmemb,uint idx) {
        if(nmemb==nullptr)
            throw std::invalid_argument("Cannot initialize iterator with nullptr");
        memb=nmemb;
        index=idx;
    }

    /*!
     * \brief Копирующий конструктор
     * \param it Исходный объект
     */
    MyConstIterator(const MyConstIterator &it) {
            memb = it.memb;
            index = it.index;
    }

    /*!
     * \brief Увеличение индекса на 1 (постфиксный оператор)
     */
    MyConstIterator & operator ++() {
        index++;
        return *this;
    }

    /*!
     * \brief Увеличение индекса на 1 (префиксный оператор)
     *
     * Используется создание временного объекта итератора
     */
    MyConstIterator operator ++(int) {
        MyConstIterator<T> tmp(*this);
        tmp.index++;
        return tmp;
    }

    /*!
     * \brief Получение итератора добавлением к индексу
     * \param toadd Число, добавляемое к текущему индексу
     * \return Новый объект итератора с измененным индексом
     */
    MyConstIterator operator +(int toadd) {
        MyConstIterator<T> tmp(*this);
        tmp.index+=toadd;
        return tmp;
    }

    /*!
     * \brief Копирующий оператор присваивания
     *
     * Оператор присваивания, копирующий объект итератора.
     * Корректно обрабатывает присваивание самому себе
     */
    MyConstIterator & operator = (const MyConstIterator &it) {
        if (this != &it) {
            memb=it.memb;
            index = it.index;
        }
        return *this;
    }

    /*!
     * \brief Разыменовывание (обращение к элементу итерируемого объекта по индексу)
     * \return Константная ссылка на объект
     *
     * Разыменовывание с использованием перегруженного оператора [] с последующим динамическим приведением типа
     */
    const typename T::indexT & operator *() {
        return dynamic_cast<const typename T::indexT &>(memb[index]);
    }

    /*!
     * \brief Доступ к членам объекта, создающего коллекцию
     * \return Константный указатель на объект, создающий коллекцию
     *
     * Получение указателя на элемент коллекции с помощью перегруженного оператора [] с последующим динамическим приведением типа
     */
    const typename T::indexT * operator ->() {
        return dynamic_cast<const typename T::indexT *>(&memb[index]);
    }
    /*!
     * \brief Равенство двух итераторов
     * \param lv Итератор слева от знака ==
     * \param rv Итератор справа от знака ==
     * \return true, если итераторы равны, false в противном случае
     *
     * Итераторы считаются равными, если у них совпадают указатели на итерируемый объект и индексы
     */
    friend bool operator == (const MyConstIterator &lv, const MyConstIterator &rv) {
        return lv.memb == rv.memb && lv.index==rv.index;
    }
    /*!
     * \brief Неравенство двух итераторов
     * \param lv Итератор слева от знака ==
     * \param rv Итератор справа от знака ==
     * \return true, если итераторы неравны, false в противном случае
     *
     * Обращение результата оператора ==
     */
    friend bool operator != (const MyConstIterator &lv, const MyConstIterator &rv) {
        return !(lv==rv);
    }
    virtual ~MyConstIterator(){
    }
};
}
#endif // MYITERATOR

