#include <pthread.h>

void* thread_routine(void *arg) {
  int errflag;

  //  как-то код

  //  попробовать отсоединить себя
  errflag = pthread_detach(pthread_self());
  
  //  проверить, удался ли вызов detach
  if(errflag != 0) {
    //что-то делаем
  }
  
  //  штатно завершить поток
  return arg;
}


int main(int argc, char *argv[])
{
  int errflag;
  pthread_t thread;
  
  //  создать и запустить поток
  errflag = pthread_create(&thread, NULL, thread_routine, NULL);
  
  //  проверить запуск потока
  if(errflag != 0) {
    // ...
  }

  //  завершить другой поток pthread_cancel(...);

  return EXIT_SUCCESS; // либо pthread_exit(); - если надо завершить main, но оставить процесс выполняться
}
