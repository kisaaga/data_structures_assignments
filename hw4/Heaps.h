#include <iostream> 
using namespace std;

// Heap capacity 
#define MAX_HEAP_SIZE (512) 

// exchange a and b 
template <class Comparable>
inline
void change(Comparable& a, Comparable& b)
{
    Comparable aux = a;
    a = b;
    b = aux;
}

// Greater and Smaller are used as comparators 
template <class Comparable>
bool Greater(Comparable a, Comparable b)
{
    return a > b;
}

template <class Comparable>
bool Smaller(Comparable a, Comparable b)
{
    return a < b;
}

// Heap implementation
template <class Comparable>
class Heap
{
public:
    // Initializes heap array and comparator required 
    // in heapification 
    Heap(Comparable itemnotfound, Comparable* b, bool (*c)(Comparable, Comparable)) :ITEM_NOT_FOUND(itemnotfound), A(b), comp(c)
    {
        heapSize = 0;
    }

    // Destructor
    virtual ~Heap()
    {
        if (A)
        {
            delete[] A;
        }
    }

    virtual bool Insert(Comparable x) = 0;
    virtual Comparable  GetTop() = 0;
    virtual Comparable  ExtractTop() = 0;
    virtual int  GetCount() = 0;

protected:
    Comparable ITEM_NOT_FOUND;

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * (i + 1);
    }

    int parent(int i)
    {
        if (i <= 0)
        {
            return -1;
        }

        return (i - 1) / 2;
    }

    // Heap array 
    Comparable* A;
    // Comparator 
    bool  (*comp)(Comparable, Comparable);
    // Heap size 
    int   heapSize;

    // Returns top element of heap data structure 
    Comparable top()
    {
        Comparable max = ITEM_NOT_FOUND; 

        if (heapSize > 0)
        {
            max = A[0];
        }

        return max;
    }

    // Returns number of elements in heap 
    int count()
    {
        return heapSize ;
    }

    // Heapification
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int child = i;
        if (l < count() && comp(A[l] , A[i])) {
            child = l;
        }
        if (r < count() && comp(A[r] , A[child])) {
            child = r;
        }

        if (child != i) {
            change(A[i], A[child]);
            heapify(child);
        }
    }

    // Deletes root of heap 
    Comparable deleteTop()
    {
        if (count() <= 0) {
            return ITEM_NOT_FOUND;
        }
        else if (count() == 1) {
            heapSize--;
            return A[0];
        }
        Comparable root = A[0];
        A[0] = A[count() - 1];
        heapSize--;
        heapify(0);
        return root;
    }
};

// Specilization of Heap to define MaxHeap 
template <class Comparable>
class MaxHeap : public Heap<Comparable> // bunu Heap<int> yapýnca düzeliyo ama ??
{
private:

public:
    MaxHeap(Comparable inf) : Heap<Comparable>(inf, new Comparable[MAX_HEAP_SIZE], &Greater) {  }

    ~MaxHeap() { }

    // Wrapper to return root of Max Heap 
    Comparable GetTop()
    {
        return this->top();
    }

    // Wrapper to delete and return root of Max Heap 
    Comparable ExtractTop()
    {
        return this->deleteTop();
    }

    // Wrapper to return # elements of Max Heap 
    int  GetCount()
    {
        return this->count();
    }

    bool Insert(Comparable x) {

        if (this->count() == MAX_HEAP_SIZE) {
            return false;
        }
        this->A[this->count()] = x;
        this->heapSize++;
        int i = this->count() - 1;
        while (i != 0 && this->A[this->parent(i)] < this->A[i]) {
            change(this->A[this->parent(i)], this->A[i]);
            i = this->parent(i);
        }
        return true;
    }
};

// Specilization of Heap to define MinHeap 
template <class Comparable>
class MinHeap : public Heap<Comparable>
{
private:

public:

    MinHeap(Comparable inf) : Heap<Comparable>(inf, new Comparable[MAX_HEAP_SIZE], &Smaller) { }

    ~MinHeap() { }

    // Wrapper to return root of Min Heap 
    Comparable GetTop()
    {
        return this->top();
    }

    // Wrapper to delete and return root of Min Heap 
    Comparable ExtractTop()
    {
        return this->deleteTop();
    }

    // Wrapper to return # elements of Min Heap 
    int  GetCount()
    {
        return this->count();
    }

    bool Insert(Comparable x) {

        if (this->count() == MAX_HEAP_SIZE) {
            return false;
        }
        this->A[this->count()] = x;
        this->heapSize++;
        int i = this->count() - 1;
        while (i != 0 && this->A[this->parent(i)] > this->A[i]) {
            change(this->A[this->parent(i)], this->A[i]);
            i = this->parent(i);
        }
        return true;
    }
};