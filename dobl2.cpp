#include <iostream>
#include <iterator>
#include <vector>
#include <bits/stdc++.h>
// #include "test.cpp"

#define private public
#define class struct

using namespace std;

#define A cout << "here" << endl;

template<typename T>
class LinkedList {
public:
    class ListIterator;
    class ReverseIterator;
// private:
//     typedef ListIterator _iterator;

//     typedef size_t size_type;
//     typedef T value_type;
//     typedef value_type& reference;
//     typedef const value_type& const_reference;
//     typedef value_type* pointer;
//     typedef const value_type* const_pointer;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;
    using size_type = size_t;
    using const_reference = const value_type&;
    using _iterator = ListIterator;


    class ListNode;
    
    size_type count;
    
    ListNode *head;
    ListNode *tail;
    
    void copy(const LinkedList &);//                        copy() - check

public: 
    LinkedList();//                                         constructor() - check
    LinkedList(const LinkedList &);//                       constructor() - check
    ~LinkedList();//                                        destructor()

    explicit LinkedList(size_type);//                       constructor() - check

    LinkedList& operator =(const LinkedList &);//           operator = - check 

    void assign(size_type, const value_type &);//           assign - check
    //void assign(Iter);//                                    x

    reference front();//                                    front() - check
    const_reference front() const;//                        front() - check
    reference back();//                                     back() - cehck
    const_reference back() const;//                         back() - check 

    _iterator begin();//                                     begin() - check 
    _iterator end();//                                       end() - check
    ReverseIterator rbegin();//                            x
    ReverseIterator rend();//                              x

    bool empty() const;//                                   empty() - check
    size_type size() const;//                               size() - check

    
    void clear();//                                         clear() - check
    _iterator insert(_iterator, const value_type &);//        insert - check
    void insert(_iterator, size_type, const value_type &);// insert - check
    //void insert(_iterator, _iterator, _iterator);//          не буду реализовывать 

    _iterator erase(_iterator);//                                   erase - check
    _iterator erase(_iterator, _iterator);//                      x

    void pop_back();//                                      pop_back() - check
    void push_back(const value_type &);//                            push_back() - check 
    void pop_front();//                                     pop_front() - check 
    void push_front(const value_type &);//                           push_front() - check

    void resize(size_type);//                               x
    void reverse();
    void swap(LinkedList &);//                              x

    void Print(); // - check 
    ListNode * GetPrev(ListNode *);// GetPrev - check
    ListNode * GetNext(ListNode *);// GetNext - check
    // friend void swap(typename LinkedList<T>::ListIterator, typename LinkedList<T>::ListIterator);
};

template<typename T>
class LinkedList<T>::ListNode {
    //template<typename T>
    friend class LinkedList;

    //template<typename T>
    friend class ListIterator;

    T value;
    ListNode * next;
    ListNode * prev;
public:
    ListNode();//
    ListNode(const T&);//
    ListNode(const ListNode *); //
};

template<typename T>
class LinkedList<T>::ListIterator {
    //template<typename It>
    friend struct std::iterator_traits<T>;

    // using difference_type = std::ptrdiff_t;
    // using value_type = typename LinkedList<T>::value_type;
    // using pointer = typename LinkedList<T>::value_type*;
    // using reference = typename LinkedList<T>::value_type&;
    // using iterator_category = std::forward_iterator_tag;
    typename LinkedList<T>::ListNode * node;
    typename LinkedList<T>::ListNode * next;
    typename LinkedList<T>::ListNode * prev;
public:
    void check()const{
        assert(prev?prev->next==node:1);
        assert(node?node->next==next:1);
        assert(node?node->prev==prev:1);
        assert(next?next->prev==node:1);
    }
private:
    T flag;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;
    using size_type = size_t;
    using const_reference = const value_type&;
    using _iterator = ListIterator;

    using orginal_type=LinkedList<T>;

    bool target;
/*
    typedef std::ptrdiff_t difference_type;
    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
*/
    //сделать флаг для реверса
public:
    ListIterator(typename LinkedList<T>::ListNode *n):node(n), flag(), target(1) {
        next = node?node->next:0; 
        prev = node?node->prev:0; 
        check();
    }

    bool operator==(const ListIterator & other) const {check();other.check(); if(target)return *this - other ==0; return *this - other ==0; }
    bool operator!=(const ListIterator & other) const {check();other.check(); if(target)return *this - other !=0; return *this - other !=0; }
    bool operator< (const ListIterator & other) const {check();other.check(); if(target)return *this - other < 0; return *this - other > 0; }
    bool operator> (const ListIterator & other) const {check();other.check(); if(target)return *this - other > 0; return *this - other < 0; }
    bool operator<=(const ListIterator & other) const {check();other.check(); if(target)return *this - other <=0; return *this - other >=0; }
    bool operator>=(const ListIterator & other) const {check();other.check(); if(target)return *this - other >=0; return *this - other <=0; }

    typename LinkedList<T>::reference operator*() {check(); if(node != nullptr) return node->value; else return flag; }
    typename LinkedList<T>::const_reference operator*() const {check(); if(node != nullptr)return node->value; else return flag; }

    bool IspreBegin() {
        // ic(*this)
        check();
        // auto g=this[150];
        assert(node or next or prev);
        if(prev == nullptr and node==0) return true;
        return false;
    }
/*
    LinkedList<T>::ListNode* GetNode() {
        if(node) return node;
        else return flag;
    }
*/
    ListIterator operator++() {
        check();
        if(target) {prev=node; node=next; next=next?next->next:0; }
        else { next = node; node = prev; prev = prev?prev->prev:0; }
        check();
        return *this;
    }
    ListIterator operator--() {
        check();
        if(target){ next = node; node = prev; prev = prev?prev->prev:0; }
        else {prev=node; node=next; next=next?next->next:0; }
        check();
        return *this;
    }

    ListIterator operator+=(size_type n) {
        check();
        for(size_type i = 0; i < n; i++) {
            if(target){prev=node; node=next; next=next?next->next:0; }
            else { next = node; node = prev; prev = prev?prev->prev:0; }
        }
        check();
        return *this;
    }
    ListIterator operator-=(size_type n) {
        check();
        for(size_type i = 0; i < n; i++) {
            if(target){ next = node; node = prev; prev = prev?prev->prev:0; }
            else {prev=node; node=next; next=next?next->next:0; }
        }
        check();
        return *this;
    }
    ListIterator&operator+=(long n) {
        check();
        if (n<0){
            *this-=size_t(-n);
        }else{
            *this+=size_t(n);
        }
        check();
        return *this;
    }
    ListIterator&operator-=(long n){
        check();
        return *this+=(-n);
    }

    ListIterator operator+(long n) {
        check();
        auto q=*this;
        q+=n;
        check();
        return q;
    }
    ListIterator operator-(long n) {
        check();
        auto q=*this;
        q-=n;
        check();
        return q;
    }
    T&operator[](long value) {
        check();
        return *(*this+value);
    }
    friend typename LinkedList<value_type>::_iterator LinkedList<value_type>::insert(LinkedList<value_type>::_iterator, const value_type &);
    friend void LinkedList<value_type>::insert(LinkedList<value_type>::_iterator, size_type, const value_type &);
    friend typename LinkedList<T>::_iterator LinkedList<T>::erase(LinkedList<T>::_iterator);
};

template<typename T>
class LinkedList<T>::ReverseIterator {
    //template<typename It>
    //friend struct std::iterator_traits<T>;

    // using difference_type = std::ptrdiff_t;
    // using value_type = typename LinkedList<T>::value_type;
    // using pointer = typename LinkedList<T>::value_type*;
    // using reference = typename LinkedList<T>::value_type&;
    // using iterator_category = std::forward_iterator_tag;
private:
    T flag;
public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;
    using size_type = size_t;
    using const_reference = const value_type&;
    using _iterator = ListIterator;

    using orginal_type=LinkedList<T>;

    LinkedList<T>::ListIterator It;

    void check()const{
        It.check();
    }
/*
    typedef std::ptrdiff_t difference_type;
    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
*/
    //сделать флаг для реверса
public:
    ReverseIterator(typename LinkedList<T>::ListIterator it):It(it) {}

    bool operator==(const ReverseIterator & other) const {check();other.check(); return *this - other ==0; return *this - other ==0; }
    bool operator!=(const ReverseIterator & other) const {check();other.check(); return *this - other !=0; return *this - other !=0; }
    bool operator< (const ReverseIterator & other) const {check();other.check(); return *this - other < 0; return *this - other > 0; }
    bool operator> (const ReverseIterator & other) const {check();other.check(); return *this - other > 0; return *this - other < 0; }
    bool operator<=(const ReverseIterator & other) const {check();other.check(); return *this - other <=0; return *this - other >=0; }
    bool operator>=(const ReverseIterator & other) const {check();other.check(); return *this - other >=0; return *this - other <=0; }

    typename LinkedList<T>::reference operator*() { return *It; }
    typename LinkedList<T>::const_reference operator*() const { return *It; }

    ReverseIterator operator++() {
        --It;
        return *this;
    }
    ReverseIterator operator--() {
        ++It;
        return *this;
    }

    ReverseIterator operator+=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            --It;
        }
        return *this;
    }
    ReverseIterator operator-=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            ++It;
        }
        return *this;
    }
    ReverseIterator&operator+=(long n) {
        if (n<0){
            *this-=size_t(-n);
        }else{
            *this+=size_t(n);
        }
        return *this;
    }
    ReverseIterator&operator-=(long n){
        return *this+=(-n);
    }

    ReverseIterator operator+(long n) {
        auto q=*this;
        q+=n;
        return q;
    }
    ReverseIterator operator-(long n) {
        auto q=*this;
        q-=n;
        return q;
    }
    T&operator[](long value) {
        return *(this->It-value);
    }
    //friend typename LinkedList<value_type>::_iterator LinkedList<value_type>::insert(LinkedList<value_type>::_iterator, const value_type &);
    //friend void LinkedList<value_type>::insert(LinkedList<value_type>::_iterator, size_type, const value_type &);
    //friend typename LinkedList<T>::_iterator LinkedList<T>::erase(LinkedList<T>::_iterator);
};



template<typename TT>
auto to_str(TT q) ->
    enable_if_t<
        is_same_v<
            typename
            LinkedList<typename TT::value_type>::ListIterator,
            TT
        >,
        decltype(vector({q.prev,q.node,q.next}))
    >{
        using T=typename TT::orginal_type;
        return vector({q.prev,q.node,q.next});
}

template<typename TT>
auto to_str(TT q) ->
    enable_if_t<
        is_same_v<
            typename
            LinkedList<typename TT::value_type>::ReverseIterator,
            TT
        >,
        decltype(vector({q.It.prev,q.It.node,q.It.next}))
    >{
        using T=typename TT::orginal_type;
        return vector({q.It.prev,q.It.node,q.It.next});
}

template<typename TT>
auto operator-(TT q,TT w) ->
    enable_if_t<
        is_same_v<
            typename
            LinkedList<typename TT::value_type>::ReverseIterator,
            TT
        >,
        ptrdiff_t
    >{
    q.check();w.check();
    
        using T=typename TT::orginal_type;
        
        return (w.It - q.It);
        //else return (count_w - count_q);
}


template<typename TT>
auto operator-(TT q,TT w) ->
    enable_if_t<
        is_same_v<
            typename
            LinkedList<typename TT::value_type>::ListIterator,
            TT
        >,
        ptrdiff_t
    >{
        // ic(q,w)
    q.check();w.check();
        using T=typename TT::orginal_type;
        //if(q.IsZero() || w.IsZero()) return 0;
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
        //else return (count_w - count_q);
}

template<typename T>
LinkedList<T>::ListNode::ListNode(): value(), next(0), prev(0) {}

template<typename T>
LinkedList<T>::ListNode::ListNode(const T& val): value(val), next(0), prev(0) {}

template<typename T>
LinkedList<T>::ListNode::ListNode(const LinkedList<T>::ListNode * val) : value((*val).value), next((*val).next), prev((*val).prev) {}

template<typename T>
LinkedList<T>::LinkedList(): count(0), head(), tail() {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & val): count(val.count), head(val.head), tail(val.tail) {}

template<typename T>
LinkedList<T>::~LinkedList(){}

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
    clear();
    if(other.count) {
        ListNode *cur1 = other.head;
        while(cur1) {
            push_back(cur1->value);
            cur1 = cur1->next;
        }
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> & other) {
    if(this != &other) copy(other);
    return *this;
}

template<typename T>
bool LinkedList<T>::empty() const { return count == 0; }

template<typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const { return count; }

template<typename T>
void LinkedList<T>::clear() {
    while(count) { pop_front(); }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void LinkedList<T>::pop_back() {
    assert( tail!=0 );
    if( !tail->prev ) {
        //cout << "tail->value: " << tail->value << endl;
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
    assert( head!=0 );
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
    
    //cout << "tail: " << tail->value << endl;
    //cout << (tail==0) << endl;
    ++count;
}

template<typename T>
void LinkedList<T>::push_front(const T & n) {
    ListNode * val = new ListNode(n);
    if( !head ) {
        head = val;
        tail = val;
    } else {
        //ListNode * val = new ListNode(n);
        head->prev = val;
        val->next = head;
        head = val;
    }
    head->prev = nullptr;
    ++count;
}

template<typename T>
typename LinkedList<T>::reference LinkedList<T>::front() {
    return head->value;
}

template<typename T>
typename LinkedList<T>::const_reference LinkedList<T>::front() const {
    return head->value;
}

template<typename T>
typename LinkedList<T>::reference LinkedList<T>::back() {
    return tail->value;
}

template<typename T>
typename LinkedList<T>::const_reference LinkedList<T>::back() const {
    return tail->value;
}

//--------------------------------------------------------------------------------------swap()
template<typename T>
void LinkedList<T>::swap(LinkedList & other) {
    LinkedList<T> a = other;
    other = *this;
    *this  = a;
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::begin() {
    return ListIterator(head);
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::end() {
    return ListIterator(tail)+1;
}

template <typename value_type>
typename LinkedList<value_type>::_iterator LinkedList<value_type>::insert(LinkedList<value_type>::_iterator It, const value_type & val) {
    It.check();
    assert(this->begin().IsBegin());
    ListNode * cur = It.node;
    if(cur == head) {
        push_front(val);
        return _iterator(head);
    }
    if(cur == tail->next) {
        push_back(val);
        return _iterator(tail);
    }
    ListNode * pr = cur->prev;
    ListNode * new_cur = new ListNode(val);
    pr->next = new_cur;
    new_cur->prev = pr;
    new_cur->next = cur;
    cur->prev = new_cur;
    count++;
    return _iterator(new_cur);

}

template<typename value_type>
void LinkedList<value_type>::insert(LinkedList<value_type>::_iterator It, size_type n, const value_type & val) {
    It.check();
    assert(this->begin().IsBegin());
    ListNode * cur = It.node;
    if(cur == head) {
        for(size_type i = 0; i < n; i++) {
            push_front(val);
        }
        return;
    }
    if(cur == tail->next) {
        
        _iterator res = _iterator(cur);
        for(size_type i = 0; i < n; i++) {
            push_back(val);
        }
        return;
    } else {
        _iterator res = _iterator(cur);
        ListNode * pr = GetPrev(cur);
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
typename LinkedList<T>::_iterator LinkedList<T>::erase(LinkedList<T>::_iterator It) {
    It.check();
    assert(this->begin().IsBegin());
    ListNode * cur = It.node;
    assert(cur != tail->next);
    while(_iterator(cur) != It) { cur = cur->next; }
    if(cur == head) {
        pop_front();
        return _iterator(head);
    } else if(cur == tail) {
        pop_back();
        return _iterator(tail);
    } else {
        ListNode * pr = cur->prev;
        ListNode * ne = cur->next;
        delete cur;
        pr->next = ne;
        ne->prev = pr;
        count--;
        return _iterator(ne);
    }
}
/*
template<typename T>
typename LinkedList<T>::_iterator LinkedList<T>::erase(LinkedList<T>::_iterator firstIt, LinkedList<T>::_iterator secondIt) {
    ListNode * pr = firstIt.node->prev;
    ListNode * ne = secondIt.node->next;
    ListNode * cur = firstIt.node;
    while(cur->next != ne) {

    }

}
*/
template<typename T>
void LinkedList<T>::Print() {
    LinkedList<T>::ListIterator b = begin();
    if(!count) return;
    while(b != end()) {
        b.check();
        cout << *b << endl;
        ++b;
    }
}

template<typename T>
typename LinkedList<T>::ListNode * LinkedList<T>::GetPrev(ListNode * cur) {
    return cur->prev;
}

template<typename T>
typename LinkedList<T>::ListNode * LinkedList<T>::GetNext(ListNode * cur) {
    return cur->next;
}

template<typename T>
void LinkedList<T>::assign(size_type n, const value_type & val) {
    clear();
    for(size_type i = 0; i < n; i++) {
        push_back(val);
    }
}

template<typename T> 
typename LinkedList<T>::ReverseIterator LinkedList<T>::rbegin() {
    ReverseIterator res(end()-1);
    return res;
}


template<typename T>
typename LinkedList<T>::ReverseIterator LinkedList<T>::rend() {
    ReverseIterator res(begin()-1);
    return res;
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
    while (q!=w){
        auto t=*q;
        *q=*w;
        *w=t;
        ++q;
        --w;
    }
    // ListIterator f = begin();
    // ListIterator s = --end();
    // if(f==s) return;
    // ListNode * a = f.node;
    // ListNode * b = s.node;
    // head = b;
    // head->prev = 0;
    // head->next = b->prev;
    // tail = a;
    // tail->next = 0;
    // tail->prev = a->next;
    // f.prev = 0;
    // f.next = 
    // ++f;
    // ++s;
    // while(f < s) {
    //     ListNode * a = f.node;
    //     ListNode * b = s.node;
    //     ListNode * a_pr = a->prev;
    //     ListNode * a_ne = a->next;
    //     ListNode * b_pr = b->prev;
    //     ListNode * b_ne = b->next;
    //     a_pr->next = b;
    //     b->next = a_ne;
    //     a_ne->prev = b; 
    //     b->prev = a_pr;
    //     b_pr->next = a;
    //     a->next = b_ne;
    //     b_ne->prev = a; 
    //     b->prev = b_pr;
    //     ++f;
    //     --s;
    // }
}

//push's and pop's working 
/*
template<typename T>
void check(T q,T e){
	vector<T> a;
	for (auto w=q;w!=e;++w){
        w.check();
		a.push_back(w);
	}
    e.check();
	a.push_back(e);
	for (int w=0;w<a.size();++w){
		for (int e=0;e<a.size();++e){
            cout << w << " " << e << endl;
            //cout << *a[w] << " " << *a[e] << endl;
            cout << "1) " << (a[w]-a[e]) << " " << (w-e) << endl;   
			assert(a[w]-a[e]==w-e);
            cout << "2) " << (w>=e) << " " << (a[w]<a[e]) << endl;
			assert(w>=e or  a[w]<a[e]);
            cout <<"3) " << (w<=e) << " " << (a[w]>a[e]) << endl;
			assert(w<=e or  a[w]>a[e]);
            cout <<"4) " << (w==e) << " " << (a[w]!=a[e]) << endl;
			assert(w==e or a[w]!=a[e]);
            cout <<"5) " << (w>e) << " " << (a[w]<=a[e]) << endl;
			assert(w>e  or a[w]<=a[e]);
            cout <<"6) " << (w<e) << " " << (a[w]>=a[e]) << endl;
			assert(w<e  or a[w]>=a[e]);
            cout <<"7) " << (w!=e) << " " << (a[w]==a[e]) << endl;
			assert(w!=e or a[w]==a[e]);
            cout <<"8) " << *(a[w]+(e-w)) << " " << *(a[e]) << endl;
            // ic(a[w],w,e,a.size(),e-w,a[w]+(e-w),a[w]+1,a[e])
            // ic(a)
			assert(a[w]+(e-w)==a[e]);
            cout <<"9) " << *(a[w]-(w-e)) << " " << *(a[e]) << endl;
			assert(a[w]-(w-e)==a[e]);
		}
	}
	auto s=a;
	s.clear();
	for (auto w=e;w!=q;--w){
		s.push_back(w);
	}
	s.push_back(q);
	reverse(s.begin(),s.end());
	assert(a==s);
}
*/
void ch(LinkedList<int> & a, vector<int> & b) {
    for(int i = 0; i < a.size(); i++) {
        //cout << a.begin()[i] << " " << b[i] << endl; 
        assert(a.begin()[i] == b[i]);
    }
    assert(*(a.begin()) == *(b.begin()));
    assert(*(--a.end()) == *(--b.end()));
    assert(*(a.rbegin()) == *(b.rbegin()));
    assert(*(--a.rend()) == *(--b.rend()));
    assert(*(a.rbegin()) == *(a.end()-1));
    assert(*(a.rend()) == *(a.begin()-1));
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < a.size(); i++) {
        //cout << a.begin()[i] << " " << b[i] << endl; 
        assert(a.begin()[i] == b[i]);
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    for(int i = 0; i < a.size(); i++) {
        cout << a.begin()[i] << " " << b[i] << endl; 
        //assert(a.begin()[i] == b[i]);
    }
}


int main() {
    LinkedList<int> a;
    //a.assign(3,3);
    // a.push_back(5);
    // a.push_front(4);
    // //a.pop_front();
    //a.pop_back();
    //sort(a.begin(), a.end());
    // a.insert(a.end(),3, 1);
    // a.erase(a.end()-1);
    // a.resize(a.size()-1);
    // a.resize(a.size()+1);
    // a.Print();
    a.push_back(1);
    a.push_back(4);
    a.push_back(6);
    a.push_back(63);
    a.push_back(5);
    a.push_back(7);
    a.push_back(8);
    a.push_back(4);
    a.push_back(6);
    a.push_front(10);

    //cout << "\n_________________________________________\n";
    //sort(a.rbegin(), a.rend());
    a.Print();
    cout << "\n_________________________________________\n";
    a.reverse();
    a.Print();
    cout << "\n_________________________________________\n";
    // ___mergesort(a.rbegin(),a.rend());
    // assert(0);


    // for (auto w=a.rbegin();w!=a.rend();++w){
    //     ic(w-a.rbegin(),a.rend()-w)
    // }


    // auto q=a.begin();
    // for (size_t w=0;w<8;++w){
    //     ++q;
    // }
    // assert(q-8==a.begin());

    // assert(a.rbegin()+8+(-8)==a.rbegin());


    // auto q=a.begin();
    // auto w=q;
    // ++w;
    // assert(q<w);

    a.Print();
    cout << "\n______________________________________________\n";
    LinkedList<int> b;
    b.push_back(5);
    //a.swap(b);
    //b = a;
    a.reverse();
    a.Print();
    //ch(a,b);
    //cout << *(--b.end()) << " " << *(b.rbegin()) << endl;
    //cout << *(b.begin()) << " " << *(--b.rend()) << endl;
/*
    cout << endl;
    sort(b.rbegin(), b.rend());
    for(int i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << endl;
*/
    //cout << *(--a.end()) << " " << *(a.rbegin()) << endl;
    //cout << *(a.begin()) << " " << *(--a.rend()) << endl;


    //LinkedList<int> b(a);
    //b.Print();
    //cout << "\n_________________________________________\n";
    //mylist.push_back(4);
    //check(mylist.begin(),mylist.end());
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //mylist.push_front(3);
    
    //LinkedList<int> secondlist;
    //mylist.Print();
    //cout << *(++mylist.begin());
    //mylist.insert(mylist.end()-1, 1);
    
    //cout << "--edn: " << *(--mylist.end()) << endl;
    //mylist.insert(mylist.end()-1, 2, 5);
    //mylist.insert(mylist.begin(), 2, 7);

    //mylist.Print();

    // ic(mylist.rbegin())
    //sort(mylist.rbegin(), mylist.rend());


    // check(mylist.begin(), mylist.end());
    //check(mylist.begin(), mylist.end());
    //cout << "--edn: " << *(--mylist.end()) << endl;
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //cout << "find: " << *(find(mylist.begin(), mylist.end(), 1)) << endl;
    //cout << *mylist.begin();
    //cout << *mylist.end();
    //cout << mylist.end() - mylist.begin() << " : " << mylist.size() << endl;
    //if(mylist.end() == mylist.end()) cout << "yes";
    //sort(mylist.begin(), mylist.end());
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //mylist.reverse();

    //mylist.resize(4);
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //mylist.resize(6);
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //sort(++mylist.rbegin(), mylist.rend());
    //mylist.Print();
    return 0;
}
