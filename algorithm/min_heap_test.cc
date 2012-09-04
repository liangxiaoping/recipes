#include <iostream>

using namespace std;

typedef int T;

void printAarray(T x[], int n)
{
  for (int i = 0; i < n; ++i)
  {
    cout << x[i] << " ";
  }

  cout << endl;
}

void swap(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

// pre n > 0 && minHeap[1,n-1]
// post heap[1,n]
// O(logn)
void min_heap_shift_up(T h[], int n)
{
  int i,parent;
  
  i = n;
  while(1)
  {
    if(i == 1)
      break;
    
    parent = i/2;
    if(h[parent] <= h[i])
      break;
    
    swap(h[parent], h[i]);
    i = parent;
  }
}

// pre n >= 0 && minHeap[2,n]
// post heap[1,n]
// O(logn)
void min_heap_shift_down(T h[], int n)
{
  int i,minChild;
  
  i = 1;
  while(1)
  {
    minChild = 2*i;

    if(minChild > n)
      break;

    // find the lesser child of i
    if((minChild+1) <= n && h[minChild+1] < h[minChild])
      minChild++;

    if(h[i] <= h[minChild])
      break;

    swap(h[minChild],h[i]);

    i = minChild;
  }
}


// O(nlogn)
// h[1] >= h[2] >= ... >= h[n]
void heapsort(T h[], int n)
{
  int i;

  // make heap
  // O(logn) * (n-1)
  for(i = 2; i <= n; ++i)
  {
    min_heap_shift_up(h,i);
  }
  
  cout << "After shift up" << endl;
  printAarray(h+1,n);

  // sorting
  // O(logn) * (n-1)
  for(i = n; i >= 2; --i)
  {
    swap(h[1],h[i]);
    min_heap_shift_down(h, i-1);
  }
  
  cout << "After shift down" << endl;
  printAarray(h+1,n);
}

// priority_queue
class priqueue
{
 public:
  priqueue(int maxs)
  {
    maxsize = maxs;
    x = new T[maxsize+1]; // we do not use x_[0]
    num = 0;
  }
  
  ~priqueue() { delete[] x; }
  
  void push(const T & t)
  {
    num++;
    x[num] = t;
    min_heap_shift_up(x, num);
  }
  
  T pop()
  {
    T t  = x[1];
    x[1] = x[num];
    num--;
    min_heap_shift_down(x, num);
    return t;
  }

  bool empty() { return num == 0; }
  int size() { return num; }

  void print() { printAarray(x+1, num);}
 private:
  int num;
  int maxsize;
  T *x;
};

int main(int argc, char ** argv)
{
  int x1[8+1] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
  heapsort(x1, 8);

  priqueue pq(8);
  pq.push(49);
  pq.push(38);
  pq.push(65);
  pq.push(97);
  pq.push(76);
  pq.push(13);
  pq.push(27);
  pq.push(49);

  cout << "pq.size() = " << pq.size() << endl;
  pq.print();

  while(!pq.empty())
  {
    cout << pq.pop() << " ";
  }
  cout << endl;
}
