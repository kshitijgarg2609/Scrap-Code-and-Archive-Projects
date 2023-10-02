String zeroAppend(int,int);
int digit2(char,char);
int digit3(char,char,char);
unsigned long digitTime(String);

String zeroAppend(int a,int b)
{
  String tmp="";
  int i;
  char c;
  for(i=1;i<=b;i++)
  {
    c=(char)((a%10)+'0');
    tmp=c+tmp;
    a/=10;
  }
  return tmp;
}

int digit2(char a,char b)
{
  return (((a-'0')*10)+(b-'0'));
}

int digit3(char a,char b,char c)
{
  return (((a-'0')*100)+((b-'0')*10)+(c-'0'));
}

unsigned long digitTime(String a)
{
  unsigned long sum=0;
  int tlen=a.length();
  int i;
  unsigned long multiplier=1;
  for(i=tlen-1;i>=0;i--)
  {
    sum+=(a.charAt(i)-'0')*multiplier;
    multiplier*=10;
  }
  return sum;
}
