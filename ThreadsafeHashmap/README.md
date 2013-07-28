Basic thread-safe implementation of a hash-map using a mutex lock

> g++ -pthread -o example example.cxx
> ./example
Original Keys:
  (1,1), (3,1), (9,1), 
Thread 1 returns: 0
Thread 2 returns: 0
New Keys:
  (2,1), (3,1), (9,1), (200,1), 
