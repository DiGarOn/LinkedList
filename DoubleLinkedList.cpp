#include <iostream>
#include <iterator>

using namespace std;

#define A cout << "here" << endl;

template<typename T>
class LinkedList {
public:
    class ListIterator;
private:
    typedef ListIterator iterator;

    typedef size_t size_type;
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

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

    //void assign(size_type, const value_type &);//                            x
    //void assign(Iter);//                                    x

    reference front();//                                    front() - check
    const_reference front() const;//                        front() - check
    reference back();//                                     back() - cehck
    const_reference back() const;//                         back() - check 

    iterator begin();//                                     begin() - check 
    iterator end();//                                       end() - check
    //reverse iterator rbegin();//                            x
    //reverse iterator rend();//                              x

    bool empty() const;//                                   empty() - check
    size_type size() const;//                               size() - check

    
    void clear();//                                         clear() - check
    iterator insert(iterator, const value_type &);//        insert
    void insert(iterator, size_type, const value_type &);// insert
    //void insert(iterator, iterator, iterator);//          не буду реализовывать 

    iterator erase(iterator);//                                   erase
    iterator erase(iterator, iterator);//                      x

    void pop_back();//                                      pop_back() - check
    void push_back(const value_type &);//                            push_back() - check 
    void pop_front();//                                     pop_front() - check 
    void push_front(const value_type &);//                           push_front() - check

    //void resize(size_type);//                               x
    void swap(LinkedList &);//                              x

    void Print(); // - check 
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
    //template<typename T>
    friend struct std::iterator_traits<T>;

    typedef std::ptrdiff_t difference_type;
    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;

    typename LinkedList<T>::ListNode * node;

public:
    ListIterator(typename LinkedList<T>::ListNode *n):node(n){}

    bool operator==(const ListIterator & other) const { return node == other.node; }
    bool operator!=(const ListIterator & other) const { return node != other.node; } 
    bool operator<(const ListIterator & other) const { return node < other.node; }
    bool operator>(const ListIterator & other) const { return node > other.node; }
    bool operator<=(const ListIterator & other) const { return !(node > other.node); }
    bool operator>=(const ListIterator & other) const { return !(node < other.node); }

    typename LinkedList<T>::reference operator*() { return node->value; }
    typename LinkedList<T>::const_reference operator*() const { return node->value; }

    ListIterator operator++() {
        if(node) node = node->next;
        return *this;
    }
    ListIterator operator--() {
        if(node) node = node->prev;
        return *this;
    }

    ListIterator operator+=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            if(node) node = node->next;
            else exit(0);
        }
        return *this;
    }
    ListIterator operator-=(size_type n) {
        for(size_type i = 0; i < n; i++) {
            if(node) node = node->prev;
            else exit(0);
        }
        return *this;
    }

    ListIterator operator+(size_type n) {
        ListIterator It = new ListIterator(node);
        for(size_type i = 0; i < n; i++) {
            if(node) ++It;
            else exit(0);
        }
        return It;
    }
    ListIterator operator-(size_type n) {
        ListIterator It = new ListIterator(node);
        for(size_type i = 0; i < n; i++) {
            if(node) --It;
            else exit(0);
        }
        return It;
    }
    ListIterator operator[](int value) {
        int flag = value > 0 ? 1 : -1;
        for(size_type i = 0; i < flag*value; i++) {
            if(flag) { if(node) node = node->next; } 
            else { if(node) node = node->prev; }
        }
        return *this;
    }
};

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
        tail->next = nullptr;
        head->prev = nullptr;
        head->next = nullptr; 
    } else {
        tail->next = val;
        val->prev = tail;
        tail = val;
        tail->next = nullptr; 
    }
    ++count;
}

template<typename T>
void LinkedList<T>::push_front(const T & n) {
    ListNode * val = new ListNode(n);
    if( !head ) {
        head = val;
        tail = head;
        tail->prev = nullptr;
        tail->next = nullptr;
        head->prev = nullptr;
        head->next = nullptr; 
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
typename LinkedList<value_type>::iterator LinkedList<value_type>::insert(LinkedList<value_type>::iterator It, const value_type & val) {
    ListNode * node = new ListNode(val);
    ListNode * pr = It.node->prev;
    ListNode * ne = It.node;
    pr->next = node;
    node->prev = pr;
    node->next = ne;
    ne->prev = node;
    return iterator(node);
}

template<typename value_type>
void LinkedList<value_type>::insert(LinkedList<value_type>::iterator It, size_type n, const value_type & val) {
    if(n == 0) return;
    ListNode * node = new ListNode(val);
    ListNode * pr = *(--It);
    ListNode * ne = *(It);
    pr->next = node;
    node->prev = pr;
    for(size_type i = 1; i < n; i++) {
        ListNode * node1 = new ListNode(val);
        node->next = node1;
        node1->prev = node;
        node = node->next;
    }
    node->next = ne;
    ne->prev = node;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator It) {
    if(It == begin()) {
        ListNode * cur = It.node->next;
        delete head;
        head = cur;
        head->prev = nullptr;
        return iterator(head);
    } else if(It.node == tail) {
        ListNode * cur = tail->prev;
        delete tail;
        tail = cur;
        tail->next = nullptr;
        return iterator(tail);
    } else {
        ListNode * pr = It.node->prev;
        ListNode * ne = It.node->next;
        delete It.node;
        pr->next = ne;
        ne->prev = pr;
        return iterator(ne);
    }
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator firstIt, LinkedList<T>::iterator secondIt) {
    ListNode * pr = firstIt.node->prev;
    ListNode * ne = secondIt.node->next;
    ListNode * cur = firstIt.node;
    while(cur->next != ne) {

    }

}

template<typename T>
void LinkedList<T>::Print() {
    LinkedList<T>::ListIterator b = begin();
    while(b != end()) {
        cout << *b << endl;
        ++b;
    }
}

//push's and pop's working 

int main() {
    LinkedList<int> mylist;

    mylist.push_back(4);
    mylist.push_front(3);
    
    LinkedList<int> secondlist;
    mylist.Print();
    cout << "\n_________________________________________\n";
    mylist.insert(mylist.begin(), 1);
    mylist.Print();


    return 0;
}
