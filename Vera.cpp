#include <utility>
#include <iostream>

#define A cout << "here"

using namespace std;

template <typename T > class LinkedList {
public:
    typedef size_t size_type;
    typedef T value_type;
    typedef  value_type& reference;
    typedef const value_type& const_reference;
    class Iterator;
    class IteratorRev;
    class ListNode;

private:

    size_type count;

    ListNode* head;
    ListNode* tail;

public:
    typedef typename  LinkedList::Iterator iterator;
    //typedef typename  IteratorRev iterator;
    LinkedList();
    LinkedList(const LinkedList&);
    ~LinkedList() {
        clear();
    };

    explicit LinkedList(size_type);
    LinkedList<T>& operator= (const LinkedList<T>&);

    
    reference front(){ return head->value; }
    const_reference front() const { return head->value; }
    reference back() { return tail->value; }
    const_reference back() const { return tail->value; }
    //void assign(size_type, T);
    //void assign(Inter, );
    //iterator insert(It);
    //iterator insert(It, size_type, T);
    //iterator insert( It, Itfrom, It);
    iterator begin() { return iterator(head);}
    iterator end() { iterator it(tail); return it; }
    bool empty() const;
    size_type size() const;
    void clear();
    void pop_back();
    void erase(iterator);
    void erase(iterator, iterator);
    void push_back(const T);
    void pop_front();
    void push_front(const T);
    void resize(size_type);
    void swap(LinkedList&);
    void copy(const LinkedList&);
    value_type operator [] (const int n);
    value_type operator [] (iterator t);

    friend std::ostream& operator << (std::ostream& out, LinkedList& List) {
        std::cout << "operator<<";
        Iterator cur(List.head);

        for (size_t i = 0; i < List.count; i++) {

            out << *cur << " ";
            ++cur;
        }
        return out;
    }

};
template <typename T > class LinkedList<T>::ListNode {
    friend class LinkedList;
    ListNode* next;
    ListNode* prev;
    value_type value;
public:
    ListNode();
    ListNode(const T & value);
    ListNode(const ListNode * );
    ListNode(ListNode* prev_a, const T value_a, ListNode* next_a) : prev(prev_a), value(value_a), next(next_a) {}
    ListNode(ListNode* prev_a, ListNode* next_a) : prev(prev_a), next(next_a) {}
    // bool operator!=(const ListNode& it) const { return value != it.value; };
    // bool operator==(const ListNode& it) const { return value == it.value; };
    // bool operator<(const ListNode& it) const { return value < it.value; };
    // bool operator>(const ListNode& it) const { return value > it.value; };
    // friend bool operator==(const ListNode& c_1, const ListNode& c_2) { return c_1.value == c_2.value; }
    // friend bool operator!=(const ListNode& c_1, const ListNode& c_2) { return !(c_1 == c_2); }

};

//ËÚÂ‡ÚÓ 
template <typename T> class LinkedList<T>::Iterator {      
public:
    friend class LinkedList;

    template <class Iter> friend struct iterator_traits;
    typedef std::ptrdiff_t difference_type;
    typedef typename  LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::reference reference;
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename LinkedList<T>::ListNode* node;
    node cur;
    node next;
    node prev;
public:
    Iterator() = default;
    Iterator(node head) :cur(head) {
        next = cur ? cur->next : 0;
        prev = cur ? cur->prev : 0;
    }
    Iterator(const Iterator& it) {
        *this = it;
    };
    ~Iterator() = default;

    Iterator& operator++()
    {
        prev = cur;
        cur = next;
        next = next ? next->next: 0;
        return *this;
    }
    Iterator& operator--()
    {
        next = cur;
        cur = prev;
        prev = prev ? prev->prev : 0;
        
        return *this;
    }
    /* Iterator operator++(int)
    {
        //std::cout << cur;
        Iterator temp(cur);
        if (cur->next != nullptr)cur = cur->next;
        return temp;
    }
    Iterator operator--(int)
    {
        Iterator temp(cur);
        cur = cur->prev;
        return temp;
    }
    */

    Iterator operator += (size_type n) {
        for (size_type i = 0; i < n; ++i) {
            prev = cur;
            cur = next;
            next = next ? next->next : 0;
        }
        return *this;
    };
    Iterator operator -= ( size_type n) {
        for (size_type i = 0; i < n; ++i) {
            next = cur;
            cur = prev;
            prev = prev ? prev->prev : 0;
        }
        return *this;
    };
    Iterator operator += ( int n) {
        if (n < 0) { *this -= size_type(-n); }
        else { *this += size_type(n); }
        return *this;
    };
    Iterator operator -= ( int n) {
        return *this+=(-n);
    };

    Iterator operator - ( int n) {
        Iterator tmp = *this;
        tmp -= n;
        return tmp;
    };
    Iterator operator+( int n) {
        Iterator tmp = *this;
        tmp += n;
        return tmp;

    };
    friend Iterator operator+(difference_type n, const Iterator& it) {
        return (it + n);
    };

    bool operator!=(const Iterator& it) const { return (*this - it) != 0; }
    bool operator==(const Iterator& it) const { return (*this - it) == 0; }
    bool operator<(const Iterator& it) const { return (*this - it) < 0; }
    bool operator>(const Iterator& it) const { return (*this - it) > 0; }
    bool operator>=(const Iterator& it) const { return !(*this < it); }
    bool operator<=(const Iterator& it) const { return !(*this > it); }
    
    bool is_pre_begin() {
        if ((prev == nullptr) && (cur == 0)) return true;
        else return false;
    }
    Iterator operator = ( Iterator it) {
        cur = it.cur;
        next = it.next;
        prev = it.prev;
        return *this;
    };
    LinkedList<T>::reference operator* () { return cur->value; };

    friend std::ostream& operator << (std::ostream& out, Iterator& it) {
        std::cout << "operator<<";
        out << *it;
        return out;
    }

    LinkedList<T>::reference operator [] (int n) {
        return *(*this + n);
    }

    LinkedList<T>::reference operator* () const { if (cur) return (cur->value);
    //else 
    }
    LinkedList<T>::value_type* operator ->() { return *this; }

    //operator Iterator() const { return Iterator(cur); }

    void swap( Iterator& it) {
        T tmp= cur->value;
    
        cur->value = it.cur->value;
        it.cur->value = tmp;
        std::cout << tmp << '\t';
    };
};
//ËÚÂ‡ÚÓ rev 
// Ô‡Ï‡„ËÚÂ ˇ ÛÒÚ‡Î¸, ˇ ·ÓÎ¸¯Â ÌÂ ÏÓ„ÛÛÛ


// ÍÓÌÒÚÛÍÚÓ ÔÓ ÛÏÓÎ˜‡ÌË˛ 
//template <typename T > LinkedList<T>::LinkedList(): count(0), head(0), tail (0) {}
//template <typename T > LinkedList<T>::~LinkedlList()


template <typename T > void LinkedList<T>::copy(const LinkedList<T>& other) {
    if (other.count) {
        ListNode* cur1 = new ListNode(other.head);
        ListNode* cur2 = new ListNode(other.head->next);
        head = cur1;
        for (count = 1; count < other.count; ++count) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        tail = cur1;
    }
}
// ÍÓÌÒÚÛÍÚÓ ÍÓÔËÓ‚‡ÌËˇ 
template <typename T > LinkedList<T>::LinkedList(const LinkedList& other) {
    copy(other);
}

template <typename T > LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != other) copy(other);
    return *this;
}

template <typename T > LinkedList<T>::LinkedList(size_type count) : count(count), head(0), tail(110) {
    if (count) {
        ListNode* cur1 = new ListNode;
        ListNode* cur2 = new ListNode;
        head = cur1;
        for (size_type i = 1; i < count; ++i) {
            cur1->next = new ListNode;
            cur2 = cur1;
            cur1 = cur1->next;
            cur1->prev = cur2;

        }
        tail = cur1;
    }
}

template <typename T > bool LinkedList<T>::empty() const {
    return this == 0;
}

template <typename T>  size_t  LinkedList<T>::size() const {
    return count;
}

template <typename T> void LinkedList<T>::clear() {

    while (head != nullptr)
    {
        ListNode* tmpNewHead = head->next;
        delete head;
        head = tmpNewHead;
    }
    tail = nullptr;
    count = 0;
}

template <typename T> void LinkedList<T>::pop_front() {

    if (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        count--;
    }
}

template <typename T> void LinkedList<T>::pop_back() {
    ListNode* tmp = tail;
    tail = tmp->prew;
    head->next = tmp->next;
    delete tmp;
    --count;
}

template <typename T> void LinkedList<T>::swap(LinkedList<T>& other) {
    ListNode* h = head;
    head = other.head;
    other.head = h;
    ListNode* t = tail;
    tail = other.tail;
    other.tail = t;
    size_type c = count;
    count = other.count;
    other.count = c;
}

template <typename T> void LinkedList<T>::resize(size_type size) {
    ListNode* cur1, * cur2;
    if ((count == 0) && (size > 0)) {
        head = new ListNode;
        count = 1;
        cur1 = head;
        for (size_type i = count; i < size; ++i) {
            cur1->next = new ListNode;
            cur2 = cur1;
            cur1 = cur1->next;
            cur1->prev = cur2;
        }
    }
    else {
        if (size == 0) clear();
        if (size <= count) {

            cur1 = tail;
            for (size_type i = 0; i < (count - size) + 1; ++i) {
                cur2 = cur1->prev;
                delete (cur1);
                cur1 = cur2;
            }
            tail->prev = cur1->prev;
        }
        else {
            cur1 = tail;
            for (size_type i = count; i < size; ++i) {
                cur1->next = new ListNode;
                cur2 = cur1;
                cur1 = cur1->next;
                cur1->prew = cur2;
            }
            tail = cur1;
        }
    }
    count = size;
}

template <typename T> void LinkedList<T>::push_back(T value_a)
{

    ListNode* newNode = new(std::nothrow) ListNode(value_a);
    if (newNode != nullptr)
    {
        if (head == nullptr)
        {
            head = tail = newNode;
            head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;

        }
    }

    ++count;
    //std::cout << "push_back " << value_a << newNode->next <<"\n";
}
template <typename T> void LinkedList<T>::push_front(const T value_a)
{
    head->prew = new ListNode;
    ListNode* er = head;
    head = head->prev;
    head->next = er;
    head->value = value_a;
    count++;
}

template <typename T> void LinkedList<T>::erase(Iterator position)
{
    if (position.cur != head && position.cur != tail->prev)
    {
        position.cur->prev->next = position.cur->next;
        position.cur->next->prev = position.cur->prev;
        delete position.cur;
        count--;
    }
    else if (position.cur == head)
    {
        this->pop_front();
    }
    else
    {
        this->pop_back();
    }
}
template <typename T> void LinkedList<T>::erase(Iterator begin_pos, const Iterator end_pos)
{
    while (begin_pos != end_pos)
    {
        this->erase(begin_pos++);
    }
}

template<typename TT>
ptrdiff_t operator-(TT q,TT w) {
    ptrdiff_t count_q = 0;
    ptrdiff_t count_w = 0;
    while(!q.is_pre_begin()) {
        count_q++;
        --q;
    }
    while(!w.is_pre_begin()) {
        count_w++;
        --w;
    }
    return (count_q - count_w);
}

template<typename T>
LinkedList<T>::ListNode::ListNode(const LinkedList<T>::ListNode * val) : value((*val).value), next((*val).next), prev((*val).prev) {}

template<typename T>
LinkedList<T>::ListNode::ListNode(): value(), next(0), prev(0) {}

template<typename T>
LinkedList<T>::ListNode::ListNode(const T& val): value(val), next(0), prev(0) {}

template<typename T>
LinkedList<T>::LinkedList() : count(0), head(0), tail(0){}

template<typename T>
typename LinkedList<T>::value_type LinkedList<T>::operator [] (LinkedList<T>::iterator t) {
    A << endl;
    iterator i = begin();
    A;
    while((i != end()) &&(i != t)) ++i;
    A;
    if(i == end()) exit(0);
    A;   
    return *i;
}

template<typename T>
typename LinkedList<T>::value_type LinkedList<T>::operator [] (const int n) {
    Iterator cur(this->begin());
    return *(cur + n);
}

int main()
{
    LinkedList<int> sr;
    sr.push_back(4);
    sr.push_back(5);
    sr.push_back(3);
    sr.push_back(4);
    sr.push_back(6);
    sr.push_back(1);
    std::cout << sr << '\n';
    //LinkedList<int>::Iterator It1(sr.begin());;
    // LinkedList<int>::Iterator It2 = LinkedList<int>::Iterator(sr.tail(), sr);
    //std::cout << sr[1] << '\t' << sr[3] <<'\n';
    A << endl;
    sr.begin()+=1;
    //cout << sr.begin()[0];
    //cout << sr[sr.begin()+2];
    //cout << ((sr.end()-sr.begin()) == sr.size());
    //std::cout << sr[std::find(sr.begin(), sr.end(), 5)];


    //std::sort(sr.begin(), sr.end());

    //std::cout << sr;
}
