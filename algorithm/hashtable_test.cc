#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int kHashtableSize = 10;
const int kMultiplier    = 31;

struct Hashtable
{
  string name;
  int  value;
  Hashtable *next;        // in chain
};

Hashtable *symtab[kHashtableSize];      // a symbol table

void hashtable_init()
{
  memset(symtab, 0x0, sizeof(symtab));
}

Hashtable * hashtable_create(const string &name, int value, int hashval)
{
  Hashtable * h = NULL;
  h = new Hashtable;
  if(h != NULL)
  {
    h->name    = name;
    h->value   = value;
    h->next    = symtab[hashval];
    symtab[hashval]  = h;
  }
  return h;
}

// hash: compute hash value of string
unsigned int hash(const string &str)
{
  unsigned int h = 0;
  unsigned char *p = NULL;

  for(p = (unsigned char *) str.c_str(); *p != '\0'; ++p)
  {
    h = kMultiplier *h + *p;
  }

  return h % kHashtableSize;
  
}

// hashtable_search: find name in symtable, with optional create
Hashtable * hashtable_search(const string &name, int value, bool create)
{
  unsigned int h = 0;
  Hashtable *bucket = NULL;

  h = hash(name);

  for(bucket = symtab[h]; bucket != NULL; bucket = bucket->next)
  {
    if(name.compare(bucket->name) == 0)
    {
      return bucket;
    }
  }

  if(create)
  {
    bucket = hashtable_create(name, value, h);
  }

  return bucket;
}


void hashtable_destroy()
{
  Hashtable *bucket = NULL;
  Hashtable *tmp = NULL;
  for(int i = 0; i < kHashtableSize; ++i)
  {
    bucket = symtab[i];
    while(bucket != NULL)
    {
      tmp = bucket;
      bucket = bucket->next;
      delete tmp;
    }
  }
}

void pinrtBuckets(unsigned int h)
{
  int n = 0;
  Hashtable *bucket = symtab[h];
  while(bucket != NULL)
  {
    cout << "name  = "<< bucket->name << endl;
    cout << "value = "<< bucket->value << endl;
    bucket = bucket->next;
    n++;
  }

  if(n != 0)
  {
    cout << "bucket[" << h << "] has " << n << " elems." << endl;
    cout << endl;
  }
}

int main(int argc, char **argv)
{
  hashtable_init();

  hashtable_search("Cesar", 1, true);
  hashtable_search("Zanetti", 4, true);
  hashtable_search("Sneijder", 10, true);
  hashtable_search("Milito", 22, true);
  hashtable_search("Cassano", 99, true);

  for(int i = 0; i < kHashtableSize; ++i)
  {
    pinrtBuckets(i);
  }

  hashtable_search("Nagatomo", 55, true);
  hashtable_search("Guarin", 14, true);
  hashtable_search("Cambiasso", 19, true);
  hashtable_search("Coutinho", 7, true);
  hashtable_search("Palacio", 8, true);

  for(int i = 0; i < kHashtableSize; ++i)
  {
    pinrtBuckets(i);
  }

  hashtable_search("Smiley", 0x263A, true);
  hashtable_search("Aacute", 0x00c1, true);
  hashtable_search("Zeta", 0x03b6, true);
  hashtable_search("Aelig", 0x00C6, true);
  hashtable_search("Acirc", 0x00c2, true);

  for(int i = 0; i < kHashtableSize; ++i)
  {
    pinrtBuckets(i);
  }
  
  hashtable_destroy();
}
