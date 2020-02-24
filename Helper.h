#include<Windows.h>
#include<ctime>
#include<thread>
#include<chrono>
#include<fstream>
#define CreateWindowA
using namespace std;
class Helper{
public:
  int timedate&clock(){
    int y,mo,md,wd,h,mi,s;
    time_t t;
    time(NULL);
    tm *t_m;
    t_m=localtime(&t);
    y=t_m->tm_year+1900;
    mo=t_m->tm_mon+1;
    md=t_m->tm_mday;
    wd=t_m->tm_wday;
    h=t_m->tm_hour;
    mi=t_m->tm_min;
    s=t_m->tm_sec;
//Надо подумать!!!Как это вывести?
  }
private:
};
