import java.io.*;
import java.util.*;
import com.google.firebase.*;
import com.google.firebase.database.*;
import com.google.auth.oauth2.*;
import java.util.*;
class FirebaseModule
{
DatabaseReference ref;
String dir;
Map<String,Object> dta;
static int rx=0;
static int tx=1;
static String rxd="";
static String txd="";
static boolean flgtx=false;
FirebaseModule()
{
try
{
dir=System.getProperty("user.dir")+"\\json\\";
File f = new File(dir);
int indx;
String fbio="";
for(String x : f.list())
{
if(x.indexOf(".json")!=-1)
{
indx=x.indexOf("-firebase-");
fbio=x.substring(0,indx);
dir+=x;
break;
}
}
fbio="https://"+fbio+".firebaseio.com";
//System.out.println(fbio);
//System.out.println(dir);
FileInputStream serviceAccount = new FileInputStream(dir);
//System.out.println("Tested : 1");
//GoogleCredentials gc;// = GoogleCredentials.fromStream(serviceAccount);

FirebaseOptions options = new FirebaseOptions.Builder()
  .setCredentials(GoogleCredentials.fromStream(serviceAccount))
  .setDatabaseUrl(fbio)
  .build();

FirebaseApp.initializeApp(options);
dta=new HashMap<String,Object>();
dta.put("rx",(new Integer(0)));
dta.put("tx",(new Integer(0)));
dta.put("rxd",(new String("")));
dta.put("txd",(new String("")));

/*
dta.put("sci",(new Integer(90)));
dta.put("lr",(new Integer(90)));
dta.put("ud",(new Integer(90)));
dta.put("sng",(new Integer(90)));
dta.put("flg",(new Integer(90)));
*/
//dta.put();
FirebaseDatabase database = FirebaseDatabase.getInstance();
ref=database.getReference();
ref.setValue(dta,null);
initRT();
}
catch(Exception e)
{
}
//myRef.child("java").child("test").push().setValue("Tested",null);
}
void updateMovement(int a,int b,int c,int d)
{
ref.child("sci").setValue(a,null);
ref.child("lr").setValue(b,null);
ref.child("ud").setValue(c,null);
ref.child("sng").setValue(d,null);
}
void updateSci(int a)
{
ref.child("sci").setValue(a,null);
}
void updateLr(int b)
{
ref.child("lr").setValue(b,null);
}
void updateUd(int c)
{
ref.child("ud").setValue(c,null);
}
void updateSng(int d)
{
ref.child("sng").setValue(d,null);
}
void initRT()
{
ref.child("rx").addValueEventListener(new ValueEventListener()
{
public void onDataChange(DataSnapshot e)
{
Integer a=e.getValue(Integer.class);
//System.out.println("Rx="+a.intValue());
}
public void onCancelled(DatabaseError e)
{
}
}
);
ref.child("rxd").addValueEventListener(new ValueEventListener()
{
public void onDataChange(DataSnapshot e)
{
}
public void onCancelled(DatabaseError e)
{
}
}
);
ref.child("tx").addValueEventListener(new ValueEventListener()
{
public void onDataChange(DataSnapshot e)
{
Integer a=e.getValue(Integer.class);
//System.out.println("Tx="+a.intValue());
//System.out.println(txd);
if(a.intValue()==1)//txd!="")
{
//System.out.println("tested !!!");
System.out.println(txd.trim());
ref.child("tx").setValue((new Integer(0)),null);
}
}
public void onCancelled(DatabaseError e)
{
}
}
);
ref.child("txd").addValueEventListener(new ValueEventListener()
{
public void onDataChange(DataSnapshot e)
{
String a=e.getValue(String.class);
txd=a;
//System.out.println(a);
}
public void onCancelled(DatabaseError e)
{
}
}
);
}
void send(String a)
{
if(rx==1)
{
return;
}
ref.child("rxd").setValue(a,null);
ref.child("rx").setValue((new Integer(1)),null);
}
}