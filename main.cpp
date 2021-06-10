//*****************
//Program Name: Program 14
//Author: Riyya AHmed
//IDE Used: Repl-it
//Program description: Searching analysis
//*****************
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Hash
{
  private:
    int buckets;           // # buckets
    list<int> *hashtable;  // container
  public:
    Hash (int a)           // constructor
    {
      buckets = a;
      hashtable = new list<int>[buckets];
    }     
    int getBuckets(){return buckets;};
    void insert_element (int key)
    {
        //to get the hash index of key
        int indexkey = hashFunction(key);
        hashtable[indexkey].push_back(key);
    }

    // maps values to key
    int hashFunction (int a)
    {  return (a % buckets);  }

    int search_element(int key)
    {
      int count =0;
      // add code for your count of key comparisons
      int indexkey = hashFunction(key);
      list<int>::iterator i = hashtable[indexkey].begin();
      for (; i != hashtable[indexkey].end(); i++)
      {
        count++;
        if (*i == key)
          break;
      }
      return count;
    }

    ~Hash()//destructor
      {  delete [] hashtable;  }
};

//prototype
int pSeqSearch(vector <int> &);
void print(vector <double> &);
int pBinSearch(vector <int> &);
int rSeqSearch(vector <int> &, int,int, int);
int rBinSearch(vector <int> &, int,int, int, int);

const int MAX = 10000, MIN = 100;
int main()
{
  srand(time(0));
  for(int i =1; i <= 5; i++)
  {
    vector <int> v;
    vector <double> keyCount, avg;
    int count, key, sum ;
    switch(i)
    {
      case 1:
      for(int n =2; n <= 8192; n*=2)
      {
        count = 0;
        v.resize(n);
        for(int i =0; i < n;i++)
          v.push_back((rand() % MAX - MIN + 1) + MIN);
        count = pSeqSearch(v);
        keyCount.push_back(count);
        avg.push_back(count/1000);
        v.clear();
      }
      cout << "\nProcedural Sequential Search\n";
      print(avg);
      break;

      case 2:
      for(int n =2; n <= 8192; n*=2)
      {
        for(int i =0; i < n;i++)
          v.push_back((rand() % MAX - MIN + 1) + MIN);
        sort(v.begin(), v.end());
        count = pBinSearch(v);
        keyCount.push_back(count);
        avg.push_back(count/1000);
      }
      cout << "\nProcedural Binary Search\n";
      print(avg);
      break;

      case 3:
        sum =0;
        for(int n =2; n <= 8192; n*=2)
        {
          v.resize(n);
          for(int i =0; i < n;i++)
            v.push_back((rand() % MAX - MIN + 1) + MIN);
          int c =0, i=0;  //{
          for(int s=0; s < 1000;s++)
          {
            key = v[rand() % v.size()];
            count += rSeqSearch(v,key, i, c);
          }
          keyCount.push_back(count);
          avg.push_back(count/1000);
        }
        cout << "\nRecursive Sequential Search\n";
        print(avg);

      case 4:
        for(int n =2; n <= 8192; n*=2)
        {
          int c = 0;
          v.resize(n);
          for(int i =0; i < n;i++)
            v.push_back((rand() % MAX - MIN + 1) + MIN);  //{
          sort(v.begin(), v.end());
          for(int s=0; s < 1000;s++)
          {
            key = v[rand() % v.size()];
            int n= sizeof(v) / sizeof(v[0]);
            count = rBinSearch(v, 0, n- 1, key , c);
            keyCount.push_back(count);
          }
          int sum = 0;
          for (auto v: keyCount)
            sum += v;
          avg.push_back(sum/1000);
        }
        cout << "\n Recursive Binary Search\n";
        print(avg);
        break;

      case 5:
      int r ;
      for(int n =2; n <= 8192; n*=2)
      {
        Hash table(n);
        count =0;
        v.resize(n);
        for(int i =0; i < n;i++)
        {
          r = rand() % (MAX - MIN + 1) + MIN;
          v[i] = r;
          table.insert_element(v[i]);
        }
        for(int s=0; s < 1000;s++)
        {        
          key = rand() % v.size();//1000;
          count += table.search_element(v[key]);
        }
        keyCount.push_back(count);
        avg.push_back(count/1000);
        
      }
      cout << "\nHashing\n";
      print(avg);
      break;
    }
  }
  cout << "\nENDING PROGRAM\n";
  cout << "This is my original work; apart from standard tutoring or class collaboration,\n I neither received help nor copied this code from another source.";

}

//pSeqSearch(): procedural sequential search analysis
//Arguments:v(vector <int>) | Returns: count(int)
int pSeqSearch(vector <int> &v)
{

  int pos, index, searchTerm, count= 0; float avg, eff;
  for(int s=0; s < 1000;s++)
  {
    bool found = false;
    index =0; pos = -1; 
    searchTerm = v[rand() % v.size()];

    while(index < v.size() && !found)
    {
      if(v[index] == searchTerm)
      {
        found = true;
        pos = index;
      }
      index++;
      count++;
    }
  }  
  return count;
}

//pBinSearch(): procedural Binary search analysis
//Arguments:v(vector <int>) | Returns: count(int)
int pBinSearch(vector <int> &v)
{
  int position , first, last, middle, count =0,searchTerm ;
  for(int s=0; s < 1000;s++)
  {
    bool found = false;
    first = 0; last = v.size() - 1;
    position = -1; //index =0;
    searchTerm = v[rand() % v.size()];
    while (first <= last and !found)
    {
      middle = (first + last) / 2;
      if (v[middle] == searchTerm)
      {
        found = true;
        position = middle;
      }
      else if (v[middle] > searchTerm)
        last = middle - 1;
      else
        first = middle + 1;
      count++;
    }
  }
  return count;
}

//rSeqSearch(): recursive sequential search analysis
//Arguments:v(vector <int>), key, size, count(int) | Returns: count(int)
int rSeqSearch(vector <int> &array,int key,int size, int count) 
{
  count++;
  if (size == array.size()-1 ) return count;
  else if(array[size]==key)
    return count;
  else 
    return rSeqSearch(array,key,size+1, count);
  
}

//rBinSearch(): recursive binary search analysis
//Arguments:arr(vector <int>),l,r,x, count(int) | Returns: count(int)
int rBinSearch(vector <int> &arr, int l, int r, int x, int count)
{
  if (r >= l) {
    int mid = l + (r - l) / 2;
    count++;

    // If the element is present at the middle
    // itself
    if (arr[mid] == x)
      return count;
      // return mid;

    // If element is smaller than mid, then
    // it can only be present in left subarray
    if (arr[mid] > x)
      return rBinSearch(arr, l, mid - 1, x, count);

    // Else the element can only be present
    // in right subarray
    return rBinSearch(arr, mid + 1, r, x, count);
  }

  // We reach here when element is not present in array
  return count;
}

//print(): print stats
//Arguments:v(vector <int>) | Returns: nothing
void print(vector <double> &avg)
{
  int i=0;
  double pct, eff;
  for(int n =2; n <= 8192; n*=2)
  {
    pct = 0.0;
    cout << "n = " << n << " | pct = ";
    pct = (avg[i++]/n);
    cout << pct << endl;
  }
}