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

// Insertion sort
// an efficient algorithm for sorting a small number of elements.
void isort1(T x[], int n)
{
  int i,j;
  for(i = 0; i < n; ++i)
  {
    for(j = i; j > 0 && x[j-1] > x[j]; --j)
    {
      swap(x[j-1],x[j]);
    }
  }
}

void isort2(T x[], int n)
{
  int i,j;
  for(i = 0; i < n; ++i)
  {
    for(j = i; j > 0 && x[j-1] > x[j]; --j)
    {
      T key = x[j];
      x[j] = x[j-1];
      x[j-1] = key;
    }
  }
}

void isort3(T x[], int n)
{
  int i,j;
  for(i = 0; i < n; ++i)
  {
    T key = x[i];
    for(j = i; j > 0 && x[j-1] > key; --j)
    {
      x[j] = x[j-1];
    }
    x[j] = key;
  }
}

// Bubblesort is a popular, but inefficient, sorting algorithm. 
// It works by repeatedly swapping adjacent elements that are out of order.
void bsort1(T x[], int n)
{
	int i,j;
	for (i = 0; i< n; ++i)
	{
    // move the minimum to left
		for (j = n-1; j > i; --j)
		{
			if (x[j-1] > x[j])
			{
				swap(x[j-1],x[j]);
			}
		}
	}
}

void bsort2(T x[], int n)
{
  int i, j, k;
	for(i = n-1; i > 0; i = k)       // ѭ����û�бȽϷ�Χ
	{
		for(j = 0, k = 0; j < i; ++j)  // ÿ��Ԥ��k=0��ѭ��ɨ������k
		{
			if(x[j] > x[j+1])            // ��С��������
			{
				swap(x[j+1],x[j]);
				k = j;                     // ��������³�λ�ã�k���涼�ź�����
			}
		}
	}

}


// The quicksort 
void qsort1(T x[], int low, int high)
{
	int i, j, base;

	if( low < high )
	{
    i = low;
    j = high;
    base = x[low];                    // low��Ϊ��׼��

    while(i < j)
    {
      while(i < j && x[j] > base)     // ���ұߵ�ֻҪ�Ȼ�׼�����Է����ұ�
      {
        j--;
      }

      if(i < j)
      {
        swap(x[i],x[j]);              // �����ѭ���˳���ʾ: ���ֱȻ�׼��С��������������ߵ�(С)��
      }

      while(i < j && x[i] <= base)    // ����ߵ�ֻҪС�ڵ��ڻ�׼���������
      {
        i++;
      }

      if(i < j)
      {
        swap(x[i],x[j]);              // �����ѭ���˳���ʾ: ���ֱȻ�׼���������������ұ߸�(��)��
      }
    }

    //a[i] = base;                    // һ��ɨ����󣬷ŵ��ʵ�λ��

    qsort1(x,low, i-1);
    qsort1(x,i+1, high);
	}

}

void qsort2(T x[], int low, int high)
{
	int i, j, base;

	if( low < high )
	{
    i = low;
    j = high;
    base = x[low];                    // low��Ϊ��׼��

    while( i< j )
    {
      while( i < j && x[j] > base )   // ���ұߵ�ֻҪ�Ȼ�׼�����Է����ұ�
      {
        j--;
      }

      if( i < j )
      {
        x[i] = x[j];                  // �����ѭ���˳���ʾ: ���ֱȻ�׼��С�������ƶ�����ߵ�(С)��
        i++;                          // ����һ��λ�ã����Դ�Ϊ��׼��
      }

      while( i < j && x[i] <= base )  // ����ߵ�ֻҪС�ڵ��ڻ�׼���������
      {
        i++;
      }

      if( i < j )
      {
        x[j] = x[i];                  // �����ѭ���˳���ʾ: ���ֱȻ�׼���������ƶ����ұ߸�(��)��
        j--;                          // ǰ��һ��λ��
      }
    }

    x[i] = base;                      // һ��ɨ����󣬷ŵ��ʵ�λ��

    qsort2(x,low, i-1);
    qsort2(x,i+1, high);
	}

}


int main()
{
  int x1[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x2[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x3[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x4[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x5[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x6[8] = {49, 38, 65, 97, 76, 13, 27, 49};
  int x7[8] = {49, 38, 65, 97, 76, 13, 27, 49};

  isort1(x1, sizeof(x1)/sizeof(x1[0]));
  printAarray(x1, 8);

  isort1(x2, sizeof(x2)/sizeof(x2[0]));
  printAarray(x2, 8);

  isort1(x3, sizeof(x3)/sizeof(x3[0]));
  printAarray(x3, 8);
  
  bsort1(x4, sizeof(x4)/sizeof(x4[0]));
  printAarray(x4, 8);
  
  bsort2(x5, sizeof(x5)/sizeof(x5[0]));
  printAarray(x5, 8);
  
  qsort1(x6, 0, 7);
  printAarray(x6, 8);
  
  qsort2(x7, 0, 7);
  printAarray(x7, 8);
  return 0;
}