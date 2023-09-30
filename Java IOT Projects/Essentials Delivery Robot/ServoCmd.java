class ServoCmd
{
int pos,spd;
int cmd;
String base;
int lb,ub;
ServoCmd(int l,int u,int p,int s)
{
lb=l;
ub=u;
cmd=pos=p;
spd=s;
}
boolean valid(int a)
{
return (a>=lb&&a<=ub);
}
void inc()
{
int temp;
temp=pos+spd;
if(valid(temp))
{
pos=temp;
cmd=pos;
}
else
{
cmd=ub;
}
}
void dec()
{
int temp;
temp=pos-spd;
if(valid(temp))
{
pos=temp;
cmd=pos;
}
else
{
cmd=lb;
}
}
int exe()
{
return cmd;
}
}