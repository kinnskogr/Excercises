#include <pthread.h>
#include <assert.h>
#include <pthread.h>
#include <vector>
#include <list>
#include <string>
#include <sstream>

//----------------------------------------------------
// Pair-like container for keys and values
//----------------------------------------------------
template<typename Keys, typename Vals> class Mapped {
 public:
 Mapped(Keys k, Vals v) : key(k), val(v) {};
  Keys key;
  Vals val;
  bool operator<(Mapped<Keys, Vals> & comp) {return key < comp.key; }
  bool operator>(Mapped<Keys, Vals> & comp) {return key > comp.key; }
  bool operator<=(Mapped<Keys, Vals> & comp) {return key <= comp.key; }
  bool operator>=(Mapped<Keys, Vals> & comp) {return key >= comp.key; }
  
};

//----------------------------------------------------
// HashMap base class, not thread safe
//----------------------------------------------------
template<typename Keys, typename Vals> class HashMap {
 public:
  
  HashMap(int m = 100) : mod(m) { map.resize(mod); };
  bool put(Keys const & k, Vals const &v);           // Insert key/values (fails if key is already present)
  bool set(Keys const & k, Vals const &v);           // Update value (fails if key is not yet present)
  Vals get(Keys const & k);                          // Return value (fails if key is not present)
  bool del(Keys const & k);                          // Remove key/value (fails if key is not present)
  int  hash(Keys const & k) {return int(k) % mod; }; // Dummy hashing function assuming key can be cast to an integer
  std::list<Keys> keys();                            // Return a list of stored keys
  std::string print();                               // Write a string representation of the key/value pairs

 protected:
  const int mod;
  std::vector< std::list<Mapped<Keys, Vals> > > map;
  
};

template<typename Keys, typename Vals> bool HashMap<Keys, Vals>::put(Keys const & k, Vals const & v)  {
  int h = hash(k);
  for (typename std::list<Mapped<Keys, Vals> >::iterator it = map[h].begin(), it_end = map[h].end(); it != it_end; ++it) {
    if (it->key == k)
      assert(0);
  }
  map[h].push_back(Mapped<Keys, Vals>(k, v));
  return true;
}

template<typename Keys, typename Vals> bool HashMap<Keys, Vals>::set(Keys const & k, Vals const & v)  {
  int h = hash(k);
  for (typename std::list<Mapped<Keys, Vals> >::iterator it = map[h].begin(), it_end = map[h].end(); it != it_end; ++it) {
    if (it->key == k) {
      it->val = v;
      return true;
    }
  }
  assert(0);
}

template<typename Keys, typename Vals> Vals HashMap<Keys, Vals>::get(Keys const & k)  {
  int h = hash(k);
  for (typename std::list<Mapped<Keys, Vals> >::iterator it = map[h].begin(), it_end = map[h].end(); it != it_end; ++it) {
    if (it->key == k)
      return it->val;
  }
  assert(0);
}

template<typename Keys, typename Vals> bool HashMap<Keys, Vals>::del(Keys const & k)  {
  int h = hash(k);
  for (typename std::list<Mapped<Keys, Vals> >::iterator it = map[h].begin(), it_end = map[h].end(); it != it_end; ++it) {
    if (it->key == k) {
      map[h].erase(it);
      return true;
    }
  }
  assert(0);
}

template<typename Keys, typename Vals> std::list<Keys> HashMap<Keys, Vals>::keys() {
  std::list<Keys> keys;
  for (typename std::vector< std::list<Mapped<Keys, Vals> > >::iterator v_it = map.begin(), v_it_end = map.end(); v_it != v_it_end; ++v_it) {
    for (typename std::list<Mapped<Keys, Vals> >::iterator l_it = v_it->begin(), l_it_end = v_it->end(); l_it != l_it_end; ++l_it) {
      keys.push_back(l_it->key);
    }
  }
  return keys;
}

template<typename Keys, typename Vals> std::string HashMap<Keys, Vals>::print() {
  std::list<Keys> all_keys = keys();
  all_keys.sort();
  std::stringstream ss;
  for (typename std::list<Keys>::iterator it = all_keys.begin(), it_end = all_keys.end(); it != it_end; ++it) {
    ss << "(" << *it << "," << get(*it) << "), ";
  }

  return ss.str();

}


//----------------------------------------------------
// Modify the base type such that writing operations
// are thread safe
//----------------------------------------------------
template<typename Keys, typename Vals> class HashMapWSafe : public HashMap<Keys, Vals> {
 public:
  HashMapWSafe(int m = 100) : HashMap<Keys,Vals>::HashMap(m), rw_mutex(PTHREAD_MUTEX_INITIALIZER) { };
  bool put(Keys const & k, Vals const &v);           // Insert key/values (fails if key is already present)
  bool set(Keys const & k, Vals const &v);           // Update value (fails if key is not yet present)
  bool del(Keys const & k);                          // Remove key/value (fails if key is not present)

 private:
  pthread_mutex_t rw_mutex;

};

template<typename Keys, typename Vals> bool HashMapWSafe<Keys, Vals>::put(Keys const & k, Vals const & v)  {
  pthread_mutex_lock(&rw_mutex);
  bool output = HashMap<Keys,Vals>::put(k, v);
  pthread_mutex_unlock(&rw_mutex);
  return output;
}

template<typename Keys, typename Vals> bool HashMapWSafe<Keys, Vals>::set(Keys const & k, Vals const & v)  {
  pthread_mutex_lock(&rw_mutex);
  bool output = HashMap<Keys,Vals>::set(k, v);
  pthread_mutex_unlock(&rw_mutex);
  return output;
}

template<typename Keys, typename Vals> bool HashMapWSafe<Keys, Vals>::del(Keys const & k)  {
  pthread_mutex_lock(&rw_mutex);
  bool output = HashMap<Keys,Vals>::del(k);
  pthread_mutex_unlock(&rw_mutex);
  return output;
}
