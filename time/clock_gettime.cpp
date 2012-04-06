#include <sys/time.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){

  struct timespec ts1;
  struct timespec ts2;
  struct timespec res;
  struct timespec prec;

  clock_getres(CLOCK_REALTIME, &prec);
  cout << prec.tv_sec << " " << res.tv_nsec << endl;

  clock_gettime(CLOCK_REALTIME, &ts1);
  sleep(1);
  clock_gettime(CLOCK_REALTIME, &ts2);

  res.tv_sec = ts2.tv_sec - ts1.tv_sec;
  res.tv_nsec= ts2.tv_nsec- ts1.tv_nsec;

  cout << res.tv_sec << " " << res.tv_nsec << endl;

  return 0;
}

