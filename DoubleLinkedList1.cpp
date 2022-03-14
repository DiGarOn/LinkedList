#include <iostream>
#include <iterator>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "test.cpp"

using namespace std;

#define A cout << "here" << endl;

template<typename T>
class LinkedList {
public:
    class ListIterator;
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
    using iterator_category = std::output_iterator_tag;
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
    _iterator rbegin();//                            x
    _iterator rend();//                              x

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

    //void resize(size_type);//                               x
    void swap(LinkedList &);//                              x

    void Print(); // - check 
    ListNode * GetPrev(ListNode *);// GetPrev - check
    ListNode * GetNext(ListNode *);// GetNext - check
    friend void swap(typename LinkedList<T>::ListIterator, typename LinkedList<T>::ListIterator);
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
    T flag;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;
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
    ListIterator(typename LinkedList<T>::ListNode *n):node(n), flag(), target(1){}

    bool operator==(const ListIterator & other) const { return *this - other == 0; }
    bool operator!=(const ListIterator & other) const { return !(*this == other); } 
    bool operator<(const ListIterator & other) const { if(target)return *this - other < 0; else return *this - other > 0; }
    bool operator>(const ListIterator & other) const { if(target)return *this - other > 0; else return *this - other < 0; }
    bool operator<=(const ListIterator & other) const { if(target)return !(node > other.node); else return !(node < other.node); }
    bool operator>=(const ListIterator & other) const { if(target)return !(node < other.node); else return !(node > other.node); }

    typename LinkedList<T>::reference operator*() { if(node != nullptr) return node->value; else return flag; }
    typename LinkedList<T>::const_reference operator*() const { if(node != nullptr)return node->value; else return flag; }

    bool IsZero() {
        if(!node) return true;
        return false;
    }

    bool IsBegin() {
        if(node) if(node->prev == nullptr) return true;
        return false;
    }

    LinkedList<T>::ListNode* GetNode() {
        if(node) return node;
        else return flag;
    }

    ListIterator operator++() {
        if(node)  {
            if(target)node = node->next;
            else node = node->prev;
        }
        return *this;
    }
    ListIterator operator--() {
        if(node) {
            if(target)node = node->prev;
            else node = node->next;
        }
        return *this;
    }

    ListIterator operator+=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            if(node){
                if(target)node = node->next;
                else node = node->prev;
            }
            else exit(0);
        }
        return *this;
    }
    ListIterator operator-=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            if(node) {
                if(target)node = node->prev;
                else node = node->next;
            }
            else exit(0);
        }
        return *this;
    }

    ListIterator operator+(size_type n) { //    x
        for(size_type i = 0; i < n; i++) {
            if(node){
                if(target)node = node->next;
                else node = node->prev;
            }
            else exit(0);
        }
        return *this;
    }
    ListIterator operator-(size_type n) { //    x
        for(size_type i = 0; i < n; i++) {
            if(node) {
                if(target) node = node->prev;
                else node = node->next;
            }
            else exit(0);
        }
        return *this;
    }
    ListIterator operator[](int value) {
        int fl = value > 0 ? 1 : -1;
        for(size_type i = 0; i < flag*value; i++) {
            if(fl) { 
                if(node) {
                    if(target)node = node->next;
                    else node = node->prev; 
                }
            }

            else { 
                if(node) {
                    if(target)node = node->prev;
                    else node = node->next; 
                }
            }
        }
        return *this;
    }
};

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
        using T=typename TT::orginal_type;
        //if(q.IsZero() || w.IsZero()) return 0;
        ptrdiff_t count_q = 0;
        ptrdiff_t count_w = 0;
        while(!q.IsZero()) {
            count_q++;
            --q;
        }
        while(!w.IsZero()) {
            count_w++;
            --w;
        }
        return (count_q - count_w);
        //else return (count_w - count_q);
}
/*
template<typename T>
void swap(typename LinkedList<T>::ListIterator& f, typename LinkedList<T>::ListIterator& s) {
    typename LinkedList<T>::ListIterator f_pr = --f;
    typename LinkedList<T>::ListIterator f_ne = ++f;
    typename LinkedList<T>::ListIterator s_pr = --s;
    typename LinkedList<T>::ListIterator s_ne = ++s;
    

}
*/
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
        ListNode * after_tail = new ListNode;
        tail->next = after_tail;
        after_tail->prev = tail;
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
    if( !tail ) { exit(0); }
    if( !tail->prev ) {
        delete tail;
        count = 0;
        return;
    }
    ListNode *cur = new ListNode(tail);
    tail = cur->prev;
    tail->next = 0;
    delete cur;
    --count;
    ListNode * after_tail = new ListNode;
    tail->next = after_tail;
    after_tail->prev = tail;
}   

template<typename T>
void LinkedList<T>::pop_front() {
    if(!head) { exit(0); }
    if(!head->next) {
        delete head;
        count = 0;
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
        tail->prev = nullptr;
        head->prev = nullptr;
        head->next = nullptr; 
    } else {
        tail->next = val;
        val->prev = tail;
        tail = val;
    }
    ++count;
    ListNode * after_tail = new ListNode;
    tail->next = after_tail;
    after_tail->prev = tail;
}

template<typename T>
void LinkedList<T>::push_front(const T & n) {
    ListNode * val = new ListNode(n);
    if( !head ) {
        head = val;
        tail = head;
        tail->prev = nullptr;
        head->prev = nullptr;
        head->next = nullptr; 
        ListNode * after_tail = new ListNode;
        tail->next = after_tail;
        after_tail->prev = tail;
    } else {
        head->prev = val;
        val->next = head;
        head = val;
        head->prev = nullptr;
    }
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
    size_type len1 = count;
    size_type len2 = other.count;
    ListNode * cur1 = new ListNode(head);
    ListNode * cur2 = new ListNode(other.head);
    while(cur1 -> next && cur2->next) {
        ListNode * cur3 = cur1;

    }
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::begin() {
    return ListIterator(head);
}

template<typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::end() {
    return ListIterator(tail->next);
}

template <typename value_type>
typename LinkedList<value_type>::_iterator LinkedList<value_type>::insert(LinkedList<value_type>::_iterator It, const value_type & val) {
    count++;
    ListNode * cur = head;
    while(_iterator(cur) != It) { cur = cur->next; }
    if(cur == head) {
        ListNode * new_head = new ListNode(val);
        new_head->prev = nullptr;
        new_head->next = cur;
        cur->prev = new_head;
        head = new_head;
        return _iterator(head);
    }
    if(cur == tail) {
        ListNode * new_tail = new ListNode(val);
        ListNode * pr = GetPrev(tail);
        new_tail->prev = pr;
        pr->next = new_tail;
        new_tail->next = tail;
        tail->prev = new_tail;
        _iterator res = _iterator(new_tail);
        //ListNode * after_tail = new ListNode;
        //tail->next = after_tail;
        //after_tail->prev = tail;
        //cout << ": " << *(--res) << "| " << *(res) << " |" << " :" << *(++res) << endl;
        return res;
    }
    ListNode * pr = GetPrev(cur);
    ListNode * new_cur = new ListNode(val);
    pr->next = new_cur;
    new_cur->prev = pr;
    new_cur->next = cur;
    cur->prev = new_cur;
    return _iterator(new_cur);

}

template<typename value_type>
void LinkedList<value_type>::insert(LinkedList<value_type>::_iterator It, size_type n, const value_type & val) {
    ListNode * cur = head;
    count += n;
    while(_iterator(cur) != It) { cur = cur->next; }
    if(cur == head) {
        for(size_type i = 0; i < n; i++) {
            ListNode * new_head = new ListNode(val);
            new_head->prev = nullptr;
            new_head->next = cur;
            cur->prev = new_head;
            head = new_head;
        }
        //return _iterator(head);
    }
    if(cur == tail) {
        
        _iterator res = _iterator(cur);
        for(size_type i = 0; i < n; i++) {
            ListNode * new_tail = new ListNode(val);
            new_tail->prev = tail;
            tail->next = new_tail;
            new_tail->next = nullptr;
            tail = new_tail;
        }
        ListNode * after_tail = new ListNode;
        tail->next = after_tail;
        after_tail->prev = tail;
        //return res;
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
    }
    //return res;
}

template<typename T>
typename LinkedList<T>::_iterator LinkedList<T>::erase(LinkedList<T>::_iterator It) {
    ListNode * cur = head;
    count--;
    while(_iterator(cur) != It) { cur = cur->next; }
    if(cur == head) {
        ListNode * cur = cur->next;
        delete head;
        head = cur;
        head->prev = nullptr;
        return _iterator(head);
    } else if(cur == tail) {
        ListNode * cur = tail->prev;
        delete tail;
        tail = cur;
        ListNode * after_tail = new ListNode;
        tail->next = after_tail;
        after_tail->prev = tail;
        return _iterator(tail);
    } else {
        ListNode * pr = cur->prev;
        ListNode * ne = cur->next;
        delete cur;
        pr->next = ne;
        ne->prev = pr;
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
    while(b != end()) {
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
typename LinkedList<T>::_iterator LinkedList<T>::rbegin() {
    ListIterator res = end();
    res.target = 0;
    return res;
}

template<typename T>
typename LinkedList<T>::_iterator LinkedList<T>::rend() {
    ListIterator res = begin();
    res.target = 0;
    return res;
}

//push's and pop's working 

template<typename T>
void check(T q,T e){
	vector<T> a;
	for (auto w=q;w!=e;++w){
		a.push_back(w);
	}
	a.push_back(e);
	for (size_t w=0;w<a.size();++w){
		for (size_t e=0;e<a.size();++e){
			assert(a[w]-a[e]==w-e);
			assert(w>=e or  a[w]<a[e]);
			assert(w<=e or  a[w]>a[e]);
			assert(w==e or a[w]!=a[e]);
			assert(w>e  or a[w]<=a[e]);
			assert(w<e  or a[w]>=a[e]);
			assert(w!=e or a[w]==a[e]);
			assert(a[w]+(e-w)==a[e]);
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


template <typename Y>
void ___mergesort(Y qb,Y qe,pointer<vector<typename Y::value_type>> _a=nullptr){
	using T=typename Y::value_type;
	// using T=vector<decltype(qb[0])>;
	// T*a=(T*)_a;
	if (qe-qb<2){
		return;
	}
	bool outs=0;
	if (!_a){
		// a=new T[qe-qb];
		_a=vector<T>(qe-qb);
		outs=1;
	}
	vector<T>&a=*_a;
	___mergesort(qb,qb+(qe-qb)/2,_a);
	___mergesort(qb+(qe-qb)/2,qe,_a);
	size_t asize=0;
	size_t lp=0;
	size_t rp=(qe-qb)/2;
	while (lp<(qe-qb)/2 or rp<(qe-qb)){
		if (lp==(qe-qb)/2){
			a[asize++]=qb[rp++];
		}else
		if (rp==(qe-qb)){
			a[asize++]=qb[lp++];
		}else
		if (qb[lp]>qb[rp]){
			a[asize++]=qb[rp++];
		}else{
			a[asize++]=qb[lp++];
		}
	}
	for (size_t w=0;w<asize;++w){
		qb[w]=a[w];
	}
	if (outs){
		// delete a;
	}
}

int main() {
    LinkedList<int> mylist;

    mylist.push_back(4);
    mylist.push_front(3);
    
    //LinkedList<int> secondlist;
    //mylist.Print();
    //cout << "\n_________________________________________\n";
    //cout << *(++mylist.begin());
    mylist.insert(mylist.end()-1, 1);
    //cout << "--edn: " << *(--mylist.end()) << endl;
    mylist.insert(mylist.end()-1, 2, 5);
    mylist.insert(mylist.begin(), 4, 7);

    //reverse(mylist.begin(), mylist.end());
    check(mylist.begin(), mylist.end());
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
    //sort(++mylist.rbegin(), mylist.rend());
    //mylist.Print();
    return 0;
}
