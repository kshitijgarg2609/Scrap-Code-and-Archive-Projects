import java.net.*;
class UdpRW
{
int destport;
DatagramSocket ds;
DatagramPacket ps,pr;
UdpRW(int src,int dest)
{
try
{
destport=dest;
ds=new DatagramSocket(src);
ds.setSoTimeout(2000);
}
catch(Exception e)
{
}
}
boolean send(String ip,String data)
{
int i;
byte add[] = new byte[4];
String arr[]=ip.split("\\.");
if(arr.length==4)
{
for(i=0;i<4;i++)
{
add[i]=(Integer.valueOf(arr[i])).byteValue();
}
try
{
InetAddress ipv4 = InetAddress.getByAddress(add);
ps=new DatagramPacket(data.getBytes(),data.length(),ipv4,destport);
ds.send(ps);
}
catch(Exception e)
{
return false;
}
return true;
}
return false;
}
String recieve()
{
String rdata="ERR";
try
{
byte rbyte[] = new byte[256];
pr=new DatagramPacket(rbyte,rbyte.length);
ds.receive(pr);
rdata=new String(pr.getData(),0,pr.getLength());
}
catch(Exception e)
{
}
return rdata;
}
String RxTx(String ip,String data)
{
int i;
byte add[] = new byte[4];
String arr[]=ip.split("\\.");
String rdata="ERR";
if(arr.length==4)
{
for(i=0;i<4;i++)
{
add[i]=(Integer.valueOf(arr[i])).byteValue();
}
try
{
InetAddress ipv4 = InetAddress.getByAddress(add);
ps=new DatagramPacket(data.getBytes(),data.length(),ipv4,destport);
ds.send(ps);
return recieve();
}
catch(Exception e)
{
}
}
return rdata;
}
void test()
{
int i;
String rdata,str;
byte rbyte[];

for(i=1;i<=1000;i++)
{
str="Packet number :";
str+=i;
if(send("192.168.2.1",str))
{
try
{
rbyte = new byte[256];
pr=new DatagramPacket(rbyte,rbyte.length);
ds.receive(pr);
rdata=new String(pr.getData(),0,256);
System.out.println("Received data : "+rdata);
}
catch(SocketTimeoutException e)
{
System.out.println("Timeout for : "+str);
}
catch(Exception e)
{
System.out.println("Receiver error !!!");
}
}
}
}
}