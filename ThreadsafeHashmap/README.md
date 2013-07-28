Basic thread-safe implementation of a hash-map using a mutex lock

* g++ -pthread -o example example.cxx
* ./example <br>
Original Keys: <br>
  (1,1), (3,1), (9,1),  <br>
Thread 1 returns: 0 <br>
Thread 2 returns: 0 <br>
New Keys: <br>
  (2,1), (3,1), (9,1), (200,1),  <br>
