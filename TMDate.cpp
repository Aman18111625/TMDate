#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace std;

class TMDate
{
private:
int DayOfMonth;
int Month;
int Year;
int dayNumber;
int isLeapYear(int );
void toDayNumber();
void FromDayNumber();
void isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y);
public:
//constructor methods
TMDate();
TMDate (const char *dateString);
TMDate(const TMDate &other);
TMDate & operator=(const TMDate &other);
virtual ~TMDate();
//non constructor methods
int getDayOfMonth();
int getMonth();
int getYear();
int getDayOfWeek();
void getMonthString(char *monthString);
void getMonthShortString(char *monthShortString);
void getDayOfWeekString(char *dayOfWeekString);
void getDayOfWeekShortString(char *dayOfWeekShortString);
int isLeapYear();
//operator methods
TMDate & operator=(const char *dateString);
void operator+=(int );
void operator-=(int );
TMDate operator+(int);
TMDate operator-(int);
int operator <(const TMDate &other);
int operator >(const TMDate &other);
int operator <=(const TMDate &other);
int operator >=(const TMDate &other);
int operator ==(const TMDate &other);
int operator !=(const TMDate &other);
};

TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
DayOfMonth=now->tm_mday;
Month=now->tm_mon+1;
Year=now->tm_year+1900;
this->toDayNumber();
}

TMDate::~TMDate()
{
//do nothing
}

TMDate::TMDate (const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->DayOfMonth=d;
this->Month=m;
this->Year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->DayOfMonth=0;
this->Month=0;
this->Year=0;
}
}

TMDate::TMDate(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->DayOfMonth=other.DayOfMonth;
this->Month=other.Month;
this->Year=other.Year;
}

TMDate & TMDate::operator=(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->DayOfMonth=other.DayOfMonth;
this->Month=other.Month;
this->Year=other.Year;
return *this;
}

TMDate & TMDate::operator=(const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->DayOfMonth=d;
this->Month=m;
this->Year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->DayOfMonth=0;
this->Month=0;
this->Year=0;
}
return *this;
}

int TMDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}

void TMDate::FromDayNumber()
{
if(this->dayNumber<=0) 
{
this->DayOfMonth=0;
this->Month=0;
this->Year=0;
return ;
}
int x=this->dayNumber;
int d,m,y;
int daysInYear;
int daysInMonth;
y=1901;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(x<=daysInYear) break;
x=x-daysInYear;
y=y+1;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(x<=daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
d=x;
/*
//phase-1
cout<<d<<","<<m<<","<<y<<endl;
*/
//phase-2
this->DayOfMonth=d;
this->Month=m;
this->Year=y;
}

void TMDate::toDayNumber()
{
int x=0;
int y=1901;
int m;
while(y<this->Year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y)) mth[1]=29;
int ep=this->Month-2;
m=0;
while(m<=ep)
{
x=x+mth[m];
m++;
}
x=x+this->DayOfMonth;
this->dayNumber=x;
}

int TMDate::getDayOfMonth()
{
return this->DayOfMonth;
}

int TMDate::getMonth()
{
return this->Month;
}

int TMDate::getYear()
{
return this->Year;
}

ostream & operator<< (ostream &o,TMDate &tmDate)
{
o<<tmDate.getDayOfMonth()<<" "<<tmDate.getMonth()<<" "<<tmDate.getYear();
return o;
}

void TMDate::operator+=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber+=days;
this->FromDayNumber();
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0) return ;
if(days>this->dayNumber) return ;
this->dayNumber-=days;
this->FromDayNumber();
}

TMDate TMDate::operator+(int days)
{
if(this->dayNumber==0) return "00/00/0000";
TMDate date;
date.dayNumber=this->dayNumber+10;
date.FromDayNumber();
return date;
}

TMDate TMDate::operator-(int days)
{
if(this->dayNumber==0) return "00/00/0000";
TMDate date;
date.dayNumber=this->dayNumber-10;
date.FromDayNumber();
return date;
}

int TMDate::operator <(const TMDate &other)
{
return this->dayNumber<other.dayNumber;
}
int TMDate::operator >(const TMDate &other)
{
return this->dayNumber>other.dayNumber;
}
int TMDate::operator <=(const TMDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int TMDate::operator >=(const TMDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int TMDate::operator ==(const TMDate &other)
{
return this->dayNumber==other.dayNumber;
}
int TMDate::operator !=(const TMDate &other)
{
return this->dayNumber!=other.dayNumber;
}


void TMDate::getMonthString(char *monthString)
{
if(this->dayNumber==0)
{
*monthString='\0';
return ;
}
if(this->Month==1) strcpy(monthString,"January");
else if(this->Month==2) strcpy(monthString,"February");
else if(this->Month==3) strcpy(monthString,"March");
else if(this->Month==4) strcpy(monthString,"April");
else if(this->Month==5) strcpy(monthString,"May");
else if(this->Month==6) strcpy(monthString,"June");
else if(this->Month==7) strcpy(monthString,"July");
else if(this->Month==8) strcpy(monthString,"August");
else if(this->Month==9) strcpy(monthString,"September");
else if(this->Month==10) strcpy(monthString,"October");
else if(this->Month==11) strcpy(monthString,"November");
else strcpy(monthString,"December");
}

void TMDate::getMonthShortString(char *monthShortString)
{
if(this->dayNumber==0)
{
*monthShortString='\0';
return ;
}
if(this->Month==1) strcpy(monthShortString,"Jan");
else if(this->Month==2) strcpy(monthShortString,"Feb");
else if(this->Month==3) strcpy(monthShortString,"Mar");
else if(this->Month==4) strcpy(monthShortString,"Apr");
else if(this->Month==5) strcpy(monthShortString,"May");
else if(this->Month==6) strcpy(monthShortString,"Jun");
else if(this->Month==7) strcpy(monthShortString,"Jul");
else if(this->Month==8) strcpy(monthShortString,"Aug");
else if(this->Month==9) strcpy(monthShortString,"Sep");
else if(this->Month==10) strcpy(monthShortString,"Oct");
else if(this->Month==11) strcpy(monthShortString,"Nov");
else strcpy(monthShortString,"Dec");
}

int TMDate::getDayOfWeek()
{
if(this->dayNumber==0) return 0;
int leftDays=this->dayNumber%7;
int dow=2+leftDays; //2(Mondays) as 1/1/1901 is Tue(3)
if(dow>7) dow=dow%7;
return dow;
}

void TMDate::getDayOfWeekString(char *dayOfWeekString)
{
if(this->dayNumber==0) 
{
*dayOfWeekString='\0';
return ;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekString,"Sunday");
else if(dow==2) strcpy(dayOfWeekString,"Monday");
else if(dow==3) strcpy(dayOfWeekString,"Tuesday");
else if(dow==4) strcpy(dayOfWeekString,"Wednesday");
else if(dow==5) strcpy(dayOfWeekString,"Thursday");
else if(dow==6) strcpy(dayOfWeekString,"Friday");
else strcpy(dayOfWeekString,"Saturday");
}
void TMDate::getDayOfWeekShortString(char *dayOfWeekShortString)
{
if(this->dayNumber==0) 
{
*dayOfWeekShortString='\0';
return ;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekShortString,"Sun");
else if(dow==2) strcpy(dayOfWeekShortString,"Mon");
else if(dow==3) strcpy(dayOfWeekShortString,"Tue");
else if(dow==4) strcpy(dayOfWeekShortString,"Wed");
else if(dow==5) strcpy(dayOfWeekShortString,"Thu");
else if(dow==6) strcpy(dayOfWeekShortString,"Fri");
else strcpy(dayOfWeekShortString,"Sat");
}

int TMDate::isLeapYear()
{
if(this->dayNumber==0) return 0;
if(this->Year%400==0) return 1;
else if(this->Year%100==0 ) return 0;
else if(this->Year%4==0) return 1;
else return 0;
}


void TMDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy,i,r;
int sepIndex1,sepIndex2;
char sep;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
*isValid=0;
if(dateString==NULL) return ;
int x=strlen(dateString);
if(x<8 || x>10) return ;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2]=='-')) return ;
if(dateString[1]=='/' || dateString[1]=='-') sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57)  return ;
if(sepIndex1==2 &&( dateString[1]<48 || dateString[1]>57)) return ;
if(sepIndex1==1) 
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return ;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return ;
if(sepIndex2==i+2 &&(dateString[i+1]<48 || dateString[i+1]>57)) return ;
if(sepIndex2==i+1)
{
mm=dateString[i]-48;
}
else
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return ;
i=sepIndex2+1;
yy=0;
r=0;
while(r<=3)
{
if(dateString[i+r]<48 ||dateString[i+r]>57 )return ;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1901) return ;
if(yy%400==0) mth[1]=29;
else if(yy%100) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1 || dd>mth[mm-1]) return ;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}


int main()
{
TMDate date1="8/6/2021";
cout<<date1.getDayOfWeek()<<endl;
char a[21];
date1.getDayOfWeekString(a);
cout<<a<<endl;
date1.getDayOfWeekShortString(a);
cout<<a<<endl;
date1="30/06/2021";
cout<<date1<<endl;
TMDate date2;
date2=date1+10;
cout<<date2<<endl;
TMDate date3;
date3=date1-10;
cout<<date3<<endl;

return 0;
}


/*
//TestCase-3
int main()
{
TMDate date1="12/12/2020";
TMDate date2="10/12/2020";
TMDate date3="12/12/2020";
cout<<(date1==date2)<<endl;
cout<<(date1==date3)<<endl;
cout<<(date1<=date3)<<endl;
cout<<(date1<=date2)<<endl;
cout<<(date1>=date3)<<endl;
cout<<(date1>=date2)<<endl;
cout<<(date1!=date3)<<endl;
cout<<(date1>date2)<<endl;
cout<<(date1<date3)<<endl;
TMDate date4=date2;
cout<<date4<<endl;
TMDate date5;
date5=date1;
cout<<date5<<endl;
char a[11];
date1.getMonthString(a);
cout<<a<<endl;
date2.getMonthShortString(a);
cout<<a<<endl;
return 0;
}
*/

/*
//TestCase-2
int main()
{
TMDate date;
cout<<date<<endl;
date+=100;
cout<<date<<endl;
date-=100;
cout<<date<<endl;

TMDate date1;
date1="30/12/1901";
date1+=1;
cout<<date1<<endl;

TMDate date2="10/12/2020";
cout<<date2<<endl;
date2+=24;
cout<<date2<<endl;
date2-=2;
cout<<date2<<endl;

return 0;
}
*/

/*
//TestCase-1
int main()
{
TMDate date;
cout<<date<<endl;
cout<<date.getDayNumber()<<endl;
date.FromDayNumber();
return 0;
}
*/