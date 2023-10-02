int l;
char c;
int a;
int i;

void setup() {
Serial.begin(9600);
}

void loop()
{
  String rec;
  rec=rmsg();
  if(rec!="")
  {
    l=rec.length();
    Serial.println("Check length");
    Serial.println(l);
    for(i=0;i<l;i++)
    {
      c=rec.charAt(i);
      a=c;
      Serial.println(a);
    }
  }
}

String rmsg()
{
  String rec="";
  int x;
  if(Serial.available()>0)
  {
  rec=Serial.readString();
  x=rec.lastIndexOf('\n');
  if(x!=-1)
  {
    Serial.println(x);
    Serial.println("check");
    rec=rec.substring(0,x+1);
  }
  }
  return rec; 
}
