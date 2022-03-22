#include <iostream>
#include <iterator>

//#define private public
//#define class struct

using namespace std;

template<typename T>
class LinkedList {
public:
    class Iterator;
    class IteratorRev;

public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type ;
    typedef T* pointer; 
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
    typedef size_t size_type;
    typedef const value_type& const_reference;
    typedef Iterator iterator;

    class ListNode;
    
    size_type count;
    
    ListNode *head;
    ListNode *tail;
    
    void copy(const LinkedList &);

public: 
    LinkedList(): count(0), head(), tail() {}
    LinkedList(const LinkedList & val): count(val.count), head(val.head), tail(val.tail) {}
    ~LinkedList(){}
    explicit LinkedList(size_type);

    LinkedList& operator =(const LinkedList & other) { if(this != &other) copy(other); return *this; }

    void assign(size_type, const value_type &);

    reference front() { return head->value; }                       
    const_reference front() const { return head->value; }
    reference back() { return tail->value; }   
    const_reference back() const { return tail->value; }         

    iterator begin() { return Iterator(head); };
    iterator end() { return Iterator(tail)+1; };
    IteratorRev rbegin() { IteratorRev res(end()-1); return res; }
    IteratorRev rend() { IteratorRev res(begin()-1); return res; }

    bool empty() const { return count == 0; }
    size_type size() const { return count; }

    
    void clear();
    iterator insert(iterator, const value_type &);
    void insert(iterator, size_type, const value_type &);

    iterator erase(iterator);

    void pop_back();
    void push_back(const value_type &);
    void pop_front();
    void push_front(const value_type &);

    void resize(size_type);
    void reverse();
    void swap(LinkedList &);

    friend std::ostream& operator << (std::ostream& out, LinkedList& List) {
        Iterator cur(List.head);

        for (size_t i = 0; i < List.count; i++) {

            out << *cur << " ";
            ++cur;
        }
        return out;
    }
};

template<typename T>
class LinkedList<T>::ListNode {
    friend class LinkedList;
    friend class Iterator;

    T value;
    ListNode * next;
    ListNode * prev;
public:
    ListNode(): value(), next(0), prev(0) {}
    ListNode(const T& val): value(val), next(0), prev(0) {}
    ListNode(const LinkedList<T>::ListNode * val) : value((*val).value), next((*val).next), prev((*val).prev) {}
};

template<typename T>
class LinkedList<T>::Iterator {
public:
    typedef typename LinkedList<T>::ListNode* node;

    friend struct std::iterator_traits<T>;

    node cur;
    node next;
    node prev;
private:
    T flag;

public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
    typedef size_t size_type;
    typedef const value_type& const_reference;
    typedef Iterator iterator;
public:
    Iterator(typename LinkedList<T>::ListNode *n):cur(n), flag(){
        next = cur?cur->next:0; 
        prev = cur?cur->prev:0; 
    }

    bool operator==(const Iterator & other) const { return *this - other ==0; }
    bool operator!=(const Iterator & other) const { return *this - other !=0; }
    bool operator< (const Iterator & other) const { return *this - other < 0; }
    bool operator> (const Iterator & other) const { return *this - other > 0; }
    bool operator>=(const Iterator & other) const { return *this - other >=0; }

    typename LinkedList<T>::reference operator*() { if(cur != nullptr) return cur->value; else return flag; }
    typename LinkedList<T>::const_reference operator*() const { if(cur != nullptr)return cur->value; else return flag; }

    bool IspreBegin() { if(prev == nullptr and cur==0) return true; return false; }
    Iterator operator++() {
        prev=cur; 
        cur=next; 
        next=next?next->next:0;
        return *this;
    }
    Iterator operator--() {
        next = cur; 
        cur = prev; 
        prev = prev?prev->prev:0; 
        return *this;
    }

    Iterator operator+=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            prev=cur; 
            cur=next; 
            next=next?next->next:0;
        }
        return *this;
    }
    Iterator operator-=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            next = cur; 
            cur = prev; 
            prev = prev?prev->prev:0; 
        }
        return *this;
    }
    Iterator&operator+=(long n) {
        if (n<0){
            *this-=size_t(-n);
        }else{
            *this+=size_t(n);
        }
        return *this;
    }
    Iterator&operator-=(long n){ return *this+=(-n); }

    Iterator operator+(long n) {
        Iterator q=*this;
        q+=n;
        return q;
    }
    Iterator operator-(long n) {
        Iterator q=*this;
        q-=n;
        return q;
    }
    
    T&operator[](long value) { return *(*this+value); }

    friend ptrdiff_t operator-(Iterator q,Iterator w) {
        ptrdiff_t count_q = 0;
        ptrdiff_t count_w = 0;
        while(!q.IspreBegin()) {
            count_q++;
            --q;
        }
        while(!w.IspreBegin()) {
            count_w++;
            --w;
        }
        return (count_q - count_w);
    }
};

template<typename T>
class LinkedList<T>::IteratorRev {
private:
    T flag;
public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
    typedef size_t size_type;
    typedef const value_type& const_reference;
    typedef Iterator iterator;

    typedef LinkedList<T> orginal_type;

    LinkedList<T>::Iterator It;
public:
    IteratorRev(typename LinkedList<T>::Iterator it):It(it) {}

    bool operator==(const IteratorRev & other) const { return *this - other ==0; return *this - other ==0; }
    bool operator!=(const IteratorRev & other) const { return *this - other !=0; return *this - other !=0; }
    bool operator< (const IteratorRev & other) const { return *this - other < 0; return *this - other > 0; }
    bool operator> (const IteratorRev & other) const { return *this - other > 0; return *this - other < 0; }
    bool operator<=(const IteratorRev & other) const { return *this - other <=0; return *this - other >=0; }
    bool operator>=(const IteratorRev & other) const { return *this - other >=0; return *this - other <=0; }

    typename LinkedList<T>::reference operator*() { return *It; }
    typename LinkedList<T>::const_reference operator*() const { return *It; }

    IteratorRev operator++() { --It; return *this; }
    IteratorRev operator--() { ++It; return *this; }

    IteratorRev operator+=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            --It;
        }
        return *this;
    }
    IteratorRev operator-=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            ++It;
        }
        return *this;
    }
    IteratorRev&operator+=(long n) {
        if (n<0){
            *this-=size_t(-n);
        }else{
            *this+=size_t(n);
        }
        return *this;
    }
    IteratorRev&operator-=(long n){ return *this+=(-n); }

    IteratorRev operator+(long n) {
        IteratorRev q=*this;
        q+=n;
        return q;
    }
    IteratorRev operator-(long n) {
        IteratorRev q=*this;
        q-=n;
        return q;
    }
    T&operator[](long value) { return *(this->It-value); }
    friend ptrdiff_t operator-(IteratorRev q,IteratorRev w) { return (w.It - q.It); }
};

template<typename T>
LinkedList<T>::LinkedList(size_type val): count(val), head(), tail() {
    if(count) {
        ListNode * cur = new ListNode;
        head = cur;
        ListNode * cur1;
        cur1 = head;
        head -> prev = nullptr;
        for(size_type i = 1; i < count; i++) {
            cur->next = new ListNode;
            cur = cur->next;
            cur->prev = cur1;
            cur1 = cur;
        }
        tail = cur;
        tail->next = nullptr;
    }
}


template<typename T>
void LinkedList<T>::copy(const LinkedList & other){
    if(other.count) {
        ListNode *cur1 = other.head;
        while(cur1) {
            push_back(cur1->value);
            cur1 = cur1->next;
        }
    }
}

template<typename T>
void LinkedList<T>::clear() {
    while(count) { pop_front(); }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if( !tail->prev ) {
        delete tail;
        count = 0;
        tail = nullptr;
        head = nullptr;
        return;
    }
    ListNode *cur = new ListNode(tail);
    tail = cur->prev;
    tail->next = 0;
    delete cur;
    --count;
}   

template<typename T>
void LinkedList<T>::pop_front() {
    if(!head->next) {
        delete head;
        count = 0;
        head = 0;
        tail = 0;
        return;   
    }
    ListNode *tmp = new ListNode(head);
    head = tmp->next;
    head -> prev = 0;
    delete tmp;
    --count;
}

template<typename T>
void LinkedList<T>::push_back(const T & n) {
    ListNode * val = new ListNode(n);
    if(!tail) {
        tail = val;
        head = tail;
    } else {
        tail->next = val;
        val->prev = tail;
        tail = val;
    }
    ++count;
}

template<typename T>
void LinkedList<T>::push_front(const T & n) {
    ListNode * val = new ListNode(n);
    if( !head ) {
        head = val;
        tail = val;
    } else {
        head->prev = val;
        val->next = head;
        head = val;
    }
    head->prev = nullptr;
    ++count;
}

template<typename T>
void LinkedList<T>::swap(LinkedList & other) {
    LinkedList<T> a;
    a.copy(other);
    other = *this;
    *this  = a;
}

template <typename value_type>
typename LinkedList<value_type>::iterator LinkedList<value_type>::insert(LinkedList<value_type>::iterator It, const value_type & val) {
    ListNode * cur = It.cur;
    if(cur == head) {
        push_front(val);
        return iterator(head);
    }
    if(cur == tail->next) {
        push_back(val);
        return iterator(tail);
    }
    ListNode * pr = cur->prev;
    ListNode * new_cur = new ListNode(val);
    pr->next = new_cur;
    new_cur->prev = pr;
    new_cur->next = cur;
    cur->prev = new_cur;
    count++;
    return iterator(new_cur);
}

template<typename value_type>
void LinkedList<value_type>::insert(LinkedList<value_type>::iterator It, size_type n, const value_type & val) {
    ListNode * cur = It.cur;
    if(cur == head) {
        for(size_type i = 0; i < n; i++) {
            push_front(val);
        }
        return;
    }
    if(cur == tail->next) {
        
        iterator res = iterator(cur);
        for(size_type i = 0; i < n; i++) {
            push_back(val);
        }
        return;
    } else {
        iterator res = iterator(cur);
        ListNode * pr = cur->prev;
        for(size_type i = 0; i < n; i++) {
            
            ListNode * new_cur = new ListNode(val);
            pr->next = new_cur;
            new_cur->prev = pr;
            pr = pr->next;
        }
        pr->next = cur;
        cur->prev = pr;
        count += n;
    }
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator It) {
    ListNode * cur = It.cur;
    while(iterator(cur) != It) { cur = cur->next; }
    if(cur == head) {
        pop_front();
        return iterator(head);
    } else if(cur == tail) {
        pop_back();
        return iterator(tail);
    } else {
        ListNode * pr = cur->prev;
        ListNode * ne = cur->next;
        delete cur;
        pr->next = ne;
        ne->prev = pr;
        count--;
        return iterator(ne);
    }
}

template<typename T>
void LinkedList<T>::assign(size_type n, const value_type & val) {
    clear();
    for(size_type i = 0; i < n; i++) {
        push_back(val);
    }
}

template<typename T>
void LinkedList<T>::resize(size_type n) {
    while(n < size()) { pop_back(); }
    while(n > size()) { push_back(T());}
}

template<typename T>
void LinkedList<T>::reverse() {
    if(!count) return;
    auto q=begin();
    auto w=end()-1;
    while ((q!=w) && (q+1!=w)){
        auto t=*q;
        *q=*w;
        *w=t;
        ++q;
        --w;
    }
}

int main() {
    LinkedList<int> a;
    a.push_back(12);
    a.push_back(28);
    a.push_back(3);
    a.push_back(48);
    a.push_front(4);
    a.push_back(8);
    a.push_front(7);
    a.insert(a.begin()+4, 8);
    a.push_back(126);
    cout << a;
    cout << "\n_________________________________________\n";
    
    sort(a.begin(), a.end());
    cout << a;
    cout << "\n______________________________________________\n";
    
    sort(a.rbegin(), a.rend());
    cout << a;
    cout << "\n______________________________________________\n";
    
    a.insert(find(a.begin(), a.end(), 7),16);
    cout << a << endl;

    LinkedList<int> b;
    b.push_back(5);
    a.swap(b);
    cout << a << endl;
    cout << b;
    return 0;
}
