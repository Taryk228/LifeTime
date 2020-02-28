#pragma warning(disable: 4996);
#include<Windows.h>
#include<ctime>
#include<thread>
#include<chrono>
#include<fstream>
#define CreateWindowA
using namespace std;
class Helper{
public:
  char *AlInf[500];
  char timedateUclock(int i){//time date unit clock
    char tim[20]="";
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
    if(i==1){//date
      if(wd==1){
        tim[1]='M';
        tim[2]='o';
        tim[3]='n';
      }
      if(wd==2){
        tim[1]='T';
        tim[2]='u';
        tim[3]='e';
      }
      if(wd==3){
        tim[1]='W';
        tim[2]='e';
        tim[3]='d';
      }
      if(wd==4){
        tim[1]='T';
        tim[2]='h';
        tim[3]='u';
      }
      if(wd==5){
        tim[1]='F';
        tim[2]='r';
        tim[3]='i';
      }
      if(wd==6){
        tim[1]='S';
        tim[2]='a';
        tim[3]='t';
      }
      if(wd==7){
        tim[1]='S';
        tim[2]='u';
        tim[3]='n';
      }
      tim[4]=' ';
      if(md<10){
        tim[5]='0';
        tim[6]=md+48;
        tim[7]=46;
      }else{
        tim[5]=(md/10)+48
        tim[6]=(md%10)+48;
        tim[7]=46;
      }
      if(mo<10){
        tim[8]='0';
        tim[9]=mo+48;
        tim[10]=46;
      }else{
        tim[8]=(mo/10)+48;
        tim[9]=(mo%10)+48;
        tim[10]=46;
      }
      tim[11]=(y/1000)+48;
      tim[12]=(y/100%10)+48;
      tim[13]=(y/10%100)+48;
      tim[14]=(y%1000)+48;
    } else {
      tim[1]=(h/10)+48;
      tim[2]=(h%10)+48;
      tim[3]=59;//':'
      tim[4]=(mi/10)+48;
      tim[5]=(mi%10)+48;
      tim[6]=59;//':'
      tim[7]=(s/10)+48;
      tim[8]=(s%10)+48;
      }
    }
    return tim;
  }
  int ChartoTXT(char i[100]){
    ofstream fout;
    fout.open("i.txt");
    fout.write(i,100);
    four.close();
    return 0;
  }
  char TxttoCHAR(){
    char i[200];
    ifstream fin;
    fin.open("i.txt");
    fin.read(i,200);
    fin.close();
    return i;
  }
  int SecThr(){
    
  }
private:
};
