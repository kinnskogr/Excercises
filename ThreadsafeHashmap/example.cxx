#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "hashmap.h"

#include <list>

HashMapRWSafe<int, int> local_hashmap;

void *modify_hashmap_1( void *ptr );
void *modify_hashmap_2( void *ptr );

main()
{
  
  local_hashmap.put(1, 1);
  local_hashmap.put(3, 1);
  local_hashmap.put(9, 1);

  std::list<int> keys = local_hashmap.keys();

  printf("Original Keys:\n  %s\n", local_hashmap.print().c_str());

  pthread_t thread1, thread2;
  int  iret1, iret2;

  iret1 = pthread_create( &thread1, NULL, modify_hashmap_1, (void*) NULL);
  iret2 = pthread_create( &thread2, NULL, modify_hashmap_2, (void*) NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  
  printf("Thread 1 returns: %d\n",iret1);
  printf("Thread 2 returns: %d\n",iret2);
  
  printf("New Keys:\n  %s\n", local_hashmap.print().c_str());
  exit(0);
  }

void *modify_hashmap_1( void *ptr )
{
  local_hashmap.put(2,1);
}

void *modify_hashmap_2( void *ptr )
{
  local_hashmap.del(1);
  local_hashmap.put(200,1);
}



