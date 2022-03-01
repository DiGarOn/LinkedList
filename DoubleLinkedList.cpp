#include <iostream>
#include <iterator>

using namespace std;

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
    class ListNode;
    size_type count;
    ListNode *head;
    ListNode *tail;
    void copy(const LinkedList &);//--

public: 
    LinkedList();//
    LinkedList(const LinkedList &);//
    ~LinkedList();//

    explicit LinkedList(size_type);//

    LinkedList& operator =(const LinkedList &);//

    //void assign(size_type, T);
    //void assign(Iter);

    reference front();//
    const_reference front() const;//
    reference back();//
    const_reference back() const;

    //iterator begin();
    //iterator end();

    bool empty() const;//
    size_type size() const;//

    
    void clear();//
    //iterator insert(It, T);
    //iterator insert(It, size_type, T);
    //iterator insert(It, ItFrom, ItLa);

    //iterator erase(It);
    //iterator erase(ItFirst, ItLast);

    void pop_back();//
    void push_back(const T &);//
    void pop_front();//
    void push_front(const T &);//

    //void resize(size_type);
    void swap(LinkedList &);//--
    //friend LinkedList& operator =(const LinkedList &);
};

template<typename T>
class LinkedList<T>::ListNode {
    template<typename T>
    friend class LinkedList;

    template<typename T>
    friend class ListIterator;

    T value;
    ListNode * next;
    ListNode * prev;
public:
    ListNode();//
    ListNode(const T&);//
    //ListNode(const ListNode *)
};

template<typename T>
class LinkedList<T>::ListIterator {
    template<typename T>
    friend struct std::iterator_traits<T>;

    typedef std::ptrdiff_t difference_type;
    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;

    typename LinkedList<T>::ListNode * node;

public:
    ListIterator(typename LinkedList<T>::listNode *n):node(n){}
    bool operator==(const ListIterator & other) const {
        return node == other.node;
    }

    typename LinkedList<T>::reference operator*() {
        return node->value;
    }

    typename LinkedList<T>::const_reference operator*() const {
        return node->value;
    }

    ListIterator operator++() {
        if(node) node = node->next;
        return *this;
    }

    ListIterator operator--() {
        if(node) node = node->prev;
        return *this;
    }
};

template<typename T>
LinkedList<T>::ListNode::ListNode(): value(), next(0), prev(0) {}

template<typename T>
LinkedList<T>::ListNode::ListNode(const T& val): value(val.value), next(val.next), prev(val.prev) {}

template<typename T>
LinkedList<T>::LinkedList(): count(0), head(0), tail(0) {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & val): count(val.count), head(val.head), tail(val.tail) {}

template<typename T>
LinkedList<T>::~LinkedList(){}

template<typename T>
LinkedList<T>::LinkedList(size_type val): count(val), head(0), tail(0) {
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
    if(other.count) {
        ListNode *cur0 = other->prev;
        ListNode *cur1 = new ListNode(other.head);
        ListNode *cur2 = other.head->next;
        head = cur1;
        head->prev = cur0;
        cur0 = head;
        for(count = 1; count < other.count; ++count) {
            cur1->next = new ListNode(cur2);
            cur1->prev = cur0;
            cur0 = cur0->next;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        tail = cur1;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> & other) {
    if(this != &other) copy(other);
    return *this;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return count == 0;
}

template<typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const {
    return count;
}

template<typename T>
void LinkedList<T>::clear() {
    while(count) pop_front();
    head = 0;
    tail = 0;
}

template<typename T>
void LinkedList<T>::pop_back() {
    ListNode *cur = new ListNode(tail);
    tail = cur->prev;
    tail->next = 0;
    delete cur;
    --count;
}   

template<typename T>
void LinkedList<T>::pop_front() {
    ListNode *tmp = new ListNode(head);
    head = tmp->next;
    head -> prev = 0;
    delete tmp;
    --count;
}

template<typename T>
void LinkedList<T>::push_back(const T & n) {
    ListNode * val = new ListNode(n);
    tail->next = val;
    val -> prev = tail;
    tail = val;
    ++count;
}

template<typename T>
void LinkedList<T>::push_front(const T & n) {
    ListNode * val = new ListNode(n);
    head->prev = val;
    val->next = head;
    head = val;
    ++count;
}

template<typename T>
typename LinkedList<T>::reference LinkedList<T>::front() {
    return &head->value;
}

template<typename T>
typename LinkedList<T>::const_reference LinkedList<T>::front() const {
    return &head->value;
}

template<typename T>
typename LinkedList<T>::reference LinkedList<T>::back() {
    return &tail->value;
}

template<typename T>
typename LinkedList<T>::const_reference LinkedList<T>::back() const {
    return &tail->value;
}

//-----------------------------------------------------------------------
template<typename T>
void LinkedList<T>::swap(LinkedList & other) {
    size_type len1 = count;
    size_type len2 = other.count;
    ListNode * cur1 = new ListNode(head);
    ListNode * cur2 = new ListNode(other.head);
    if(len1 < len2) {
        for(size_type i = 0; i < len1; i++) {
            ListNode * cur3 = new ListNode(cur1);
            cur1 = cur2;
            cur2 = cur3;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        tail = cur1;
        for(size_type i = len1; i < len2; i++) {
            push_back(cur2);
            cur2 = cur2->next;
        }
        for(size_type i = len1; i < len2; i++) {
            other.pop_back();
        }
        tail = 
    }
}









int main() {


    return 0;
}
