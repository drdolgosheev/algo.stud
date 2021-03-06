#include  "hashset.h"

using namespace std;

template<class key_type, class hash_func, class key_equal>
const int HashSet<key_type,hash_func,key_equal>::num_primes = 25;


template<class key_type, class hash_func, class key_equal>
const unsigned long HashSet<key_type,hash_func,key_equal>::prime_list[] = 
        {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
         196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
         50331653, 100663319, 201326611, 402653189, 805306457};


template<class key_type, class hash_func, class key_equal>
bool HashSet<key_type,hash_func,key_equal>::search(const key_type& k) {

    int p = hf(k) % table_size();

    while ((*ht)[p].used && !((*ht)[p].flag)) {
        if (eq((*ht)[p].key, k)) {       // equality predicate for key_type
            return true;
        }
        p++;
        if (p == table_size()) {
            p = 0;  // wrap around to beginning
        }
    }

    return false;
}

template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::remove(const key_type& k)
{

    // TODO: complete...
    if(search(k))
    {
        int i = hf(k) % table_size();
        while(i != table_size())
        {
            if (eq((*ht)[i].key, k) && (*ht)[i].used)
            {
                (*ht)[i].used = false;
                (*ht)[i].flag = true;
                entries--;
                return;
            }
            i++;
            if (i == table_size()) {
                i = 0;  // wrap around to beginning
            }
        }
    }
}


template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::insert(const key_type& k)
{

    if (load_factor() > .7) {
        resize();
    }

    int place = hf(k) % table_size();

    while(place < table_size())
    {
        if ((*ht)[place].used)
            place++;
        else
            break;
    }

    if(place >= table_size())
        place--;

    if(!(*ht)[place].used)
    {
        (*ht)[place].key = k;
        entries++;
        (*ht)[place].used = true;
    }
    else
    {
        place = 0;
        while(place < table_size())
            if((*ht)[place].used)
                place++;
            else
                break;
        if(!(*ht)[place].used)
        {
            (*ht)[place].key = k;
            entries++;
            (*ht)[place].used = true;
        }
    }
    // TODO: complete...
    
}

template<class key_type, class hash_func, class key_equal>
int HashSet<key_type,hash_func,key_equal>::resize() {

    if (prime == num_primes - 1) {
        cerr << "maximal table size reached, aborting ... " << endl;
        exit(2);
    }

    int mm = prime_list[prime];
    prime++;
    int m = prime_list[prime];
    vector<Entry>* ptr = new vector<Entry>(m);

    int i = 0;
    while(i < mm)
    {
        if((*ht)[i].used)
        {
            (*ptr)[i].key = (*ht)[i].key;
            (*ptr)[i].used = true;
        }
        i++;
    }

    delete ht;
    ht = ptr;
    return mm;
    // TODO: complete...
    
}
