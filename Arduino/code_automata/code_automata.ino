void setup()
{
  Serial.begin(115200);
}

void loop()
{
  
}

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  if(m.equals(""))
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  if(validate(a))
  {
    Serial.println(a+" is valid");
  }
  else
  {
    Serial.println(a+" is not valid");
  }
}

boolean validate(String a)
{
  String arr[6];
  arr[0]="";
  arr[1]="";
  arr[2]="";
  arr[3]="";
  arr[4]="";
  arr[5]="";
  int indx=0;
  boolean stat=false;
  char c,l;
  arr[0]+=a.charAt(0);
  l=a.charAt(0);
  for(int i=1;i<a.length();i++)
  {
    c=a.charAt(i);
    if(typeFlag(c)==typeFlag(l))
    {
      arr[indx]+=c;
      l=c;
    }
    else
    {
      indx++;
      if(indx>5)
      {
        return false;
      }
      arr[indx]+=c;
      l=c;
    }
  }

  //checking
  String tmp="";
  for(int j=0;j<=indx;j++)
  {
    Serial.println(arr[j]+"\t"+stringCode(arr[j]));
    tmp+=stringCode(arr[j]);
  }
  if(tmp.equals("+01+20")||tmp.equals("+02+12")||tmp.equals("+01+20+12"))
  {
    return true;
  }
  
  return false;
}

String stringCode(String a)
{
  String tmp="";
  tmp+=String(typeFlag(a.charAt(0)));
  if(a.length()>1)
  {
    tmp="+"+tmp;
  }
  return tmp;
}

byte typeFlag(char a)
{
  if(a>='0'&&a<='9')
  {
    return 0;
  }
  else if(a>='A'&&a<='Z')
  {
    return 1;
  }
  else if(a>='a'&&a<='z')
  {
    return 2;
  }
  else
  {
    return -1;
  }
}
