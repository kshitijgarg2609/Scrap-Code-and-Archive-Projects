import java.io.*;
class FreeGlutCmd
{
String dir,dest,path,deste,desto,patha,pathb;
int er;
File f;
void valid(String a)
{
String tmp;
er=0;
dir=System.getProperty("user.dir").toString()+"\\Saved_Path\\";
dest=a;
validPath();
f=new File(dir);
if(!f.exists())
{
f.mkdir();
}
dir+="gcc_path.txt";
f=new File(dir);
if(!f.exists())
{
try
{
FileWriter fw = new FileWriter(dir);
BufferedWriter bw = new BufferedWriter(fw);
PrintWriter pw = new PrintWriter(bw);
}
catch (IOException e)
{
System.out.println("PROGRAMMING ERROR!");
}
}
try
{
FileReader fw = new FileReader(dir);
BufferedReader br = new BufferedReader(fw);
path=br.readLine();
if(path==null)
{
er=1;
}
else
{
f=new File(path);
if(!f.exists())
{
er=2;
}
else
{
tmp=path.substring(0,path.length()-3);
patha=tmp+"lib\\x64";
pathb=tmp+"include";
}
}
}
catch (IOException e)
{
System.out.println("PROGRAMMING ERROR!");
}
}
void validPath()
{
int x;
if(dest==null)
{
er=3;
return;
}
File f=new File(dest);
desto=null;
deste=null;
if(dest!=null)
{
if(!f.exists())
{
er=3;
return;
}
x=dest.lastIndexOf(".c");
if(x==-1)
{
er=3;
return;
}
desto=dest.substring(0,dest.length()-1)+"o";
deste=dest.substring(0,dest.length()-1)+"exe";
}
}
boolean enterCmd(String a)
{
boolean fl=true;
String msg;
try
{
Process p = Runtime.getRuntime().exec(a);
p.waitFor();
InputStream is=p.getInputStream();
InputStreamReader isr = new InputStreamReader(is);
BufferedReader br = new BufferedReader(isr);
while((msg=br.readLine())!=null)
{
fl=false;
System.out.println(msg);
}
}
catch(Exception e)
{
System.out.println("COMMAND TERMINATED !");
return false;
}
return fl;
}
String q(String a)
{
return (char)34+a+(char)34;
}
public static void main(String args[])
{
String dirfile;
File ff;
String c1,c2,c3;
boolean xy;
if(args.length!=1||args==null)
{
System.out.println("ENTER ONE ARGUEMENT !");
return;
}
ff=new File(args[0]);
if(ff.exists())
{
dirfile=args[0];
}
else
{
dirfile=System.getProperty("user.dir").toString()+"\\"+args[0];
ff=new File(dirfile);
if(!ff.exists())
{
System.out.println("ENTER ONE ARGUEMENT !");
return;
}
}
FreeGlutCmd ob = new FreeGlutCmd();
ob.valid(dirfile);
if(ob.er==0)
{
ff=new File(ob.deste);
if(ff.exists())
{
ff.delete();
}
ff=new File(ob.desto);
if(ff.exists())
{
ff.delete();
}
c1="gcc -c -o "+ob.q(ob.desto)+" "+ob.q(ob.dest)+" -I "+ob.q(ob.pathb);
c2="gcc -o "+ob.q(ob.deste)+" "+ob.q(ob.desto)+" -L "+ob.q(ob.patha);
c2+=" -lfreeglut -lopengl32 -Wl,--subsystem,windows";
c3=ob.q(ob.deste);
System.out.println(c1);
System.out.println(c2);
xy=ob.enterCmd(c1);
ff=new File(ob.desto);
if(!ff.exists())
{
System.out.println("CODE HAS SOME ERRORS");
System.out.println(c1+"\n"+c2+"\n"+c3);
return;
}
xy=ob.enterCmd(c2);
ff=new File(ob.desto);
if(ff.exists())
{
ff.delete();
}
xy=ob.enterCmd(c3);
}
else if(ob.er==1)
{
System.out.println("NO COMPILER PATH ENTERED !");
}
else if(ob.er==2)
{
System.out.println("PATH DOES NOT EXISTS !");
}
else if(ob.er==3)
{
System.out.println("ONLY .C FILE CAN BE COMPILED !");
}
}
}