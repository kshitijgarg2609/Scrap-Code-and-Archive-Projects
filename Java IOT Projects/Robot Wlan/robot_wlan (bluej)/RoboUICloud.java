import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
class RoboUICloud
{
Dimension dim;
int w,h;
int width=550,height=600;
ServoCmd sci = new ServoCmd(0,1,0,1);
ServoCmd lr = new ServoCmd(0,180,90,6);
ServoCmd ud = new ServoCmd(90,180,90,6);
ServoCmd sng = new ServoCmd(30,150,90,120);
//FirebaseModule fm = new FirebaseModule();
UdpRW udp = new UdpRW(421,4210);
static boolean harvest=false;
static boolean sow=false;

String ip="192.168.2.1";

int mov=0;
int hrvt=0;

JLabel lb;
JLabel x,y,hr,so;
//JLax=new JLabel(SwingConstants.CENTER);
JPanel jp1;
JLabel dr[] = new JLabel[11];

Thread inf = new Thread()
{
public void run()
{
String a;
while(true)
{
a="";
a+=sci.exe()+"@"+sng.exe()+"#"+lr.exe()+"$"+ud.exe()+"%"+mov+"^"+hrvt;
udp.send(ip,a);
//
System.out.println(a);
updates();
delay(2);
if(mov==1)
{
dr[8].setBackground(Color.cyan);
}
else if(mov==2)
{
dr[9].setBackground(Color.cyan);
}
else if(mov==3)
{
dr[10].setBackground(Color.cyan);
}
else
{
dr[8].setBackground(new Color(4,150,5));
dr[9].setBackground(new Color(4,150,5));
dr[10].setBackground(new Color(4,150,5));
}
}
}
}
;

JFrame jf;
RoboUICloud()
{
dim=(Toolkit.getDefaultToolkit()).getScreenSize();
w=(int)(dim.getWidth());
h=(int)(dim.getHeight());
jf=new JFrame("Robo Controller");
jf.setBounds(((w-width)/2),((h-height)/2),width,height);
jf.setResizable(false);
jf.setLayout(null);
jf.setDefaultCloseOperation(jf.EXIT_ON_CLOSE);
jf.addKeyListener(new KeyListener()
{
public void keyTyped(KeyEvent e)
{
}
public void keyPressed(KeyEvent e)
{
if(e.getKeyCode()==KeyEvent.VK_A)
{
lr.inc();
dr[2].setBackground(Color.green);
//fm.updateLr(lr.exe());
}
else if(e.getKeyCode()==KeyEvent.VK_D)
{
lr.dec();
dr[3].setBackground(Color.green);
//fm.updateLr(lr.exe());
}
else if(e.getKeyCode()==KeyEvent.VK_W)
{
ud.dec();
dr[0].setBackground(Color.green);
//m2.inc();
}
else if(e.getKeyCode()==KeyEvent.VK_S)
{
ud.inc();
dr[1].setBackground(Color.green);
//m2.dec();
}
else if(e.getKeyCode()==KeyEvent.VK_Y)
{
sci.inc();
dr[6].setBackground(Color.green);
}
else if(e.getKeyCode()==KeyEvent.VK_H)
{
hrvt=1;
}
else if(e.getKeyCode()==KeyEvent.VK_Z)
{
mov=1;
}
else if(e.getKeyCode()==KeyEvent.VK_X)
{
//dr[9].setBackground(Color.cyan);
mov=2;
}
else if(e.getKeyCode()==KeyEvent.VK_C)
{
//dr[10].setBackground(Color.cyan);
mov=3;
}
}
public void keyReleased(KeyEvent e)
{
if(e.getKeyCode()==KeyEvent.VK_A)
{
dr[2].setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_D)
{
dr[3].setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_W)
{
dr[0].setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_S)
{
dr[1].setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_Y)
{
sci.dec();
dr[6].setBackground(new Color(153,50,53));
}
else if(e.getKeyCode()==KeyEvent.VK_H)
{
hrvt=0;
}
else if(e.getKeyCode()==KeyEvent.VK_Z)
{
//dr[9].setBackground(new Color(4,150,5));
mov=0;
}
else if(e.getKeyCode()==KeyEvent.VK_X)
{
//dr[10].setBackground(new Color(4,150,5));
mov=0;
}
else if(e.getKeyCode()==KeyEvent.VK_C)
{
//dr[11].setBackground(new Color(4,150,5));
mov=0;
}
}
}
);
init1();
jf.requestFocus();
jf.setVisible(true);
jf.repaint();
jf.revalidate();
inf.start();
}
void init1()
{
jp1=new JPanel();
jp1.setBounds(50,50,400,370);
jp1.setBorder(BorderFactory.createLineBorder(Color.orange,5));
jp1.setLayout(null);
lb=new JLabel("ROBO ARM CONTROLS",SwingConstants.CENTER);
lb.setBounds(50,jp1.getY()-15,150,15);
lb.setOpaque(true);
lb.setBackground(Color.orange);

dr[0]=new JLabel("Up",SwingConstants.CENTER);
dr[0].setBounds(155,40,90,40);
dr[0].setOpaque(true);
dr[0].setBackground(Color.magenta);
jp1.add(dr[0]);

dr[1]=new JLabel("Down",SwingConstants.CENTER);
dr[1].setBounds(dr[0].getX(),dr[0].getY()+dr[0].getHeight()+20,90,40);
dr[1].setOpaque(true);
dr[1].setBackground(Color.magenta);
jp1.add(dr[1]);

dr[2]=new JLabel("Left",SwingConstants.CENTER);
dr[2].setBounds(dr[1].getX()-20-90,dr[1].getY(),90,40);
dr[2].setOpaque(true);
dr[2].setBackground(Color.magenta);
jp1.add(dr[2]);

dr[3]=new JLabel("Right",SwingConstants.CENTER);
dr[3].setBounds(dr[1].getX()+20+90,dr[1].getY(),90,40);
dr[3].setOpaque(true);
dr[3].setBackground(Color.magenta);
jp1.add(dr[3]);

dr[4]=new JLabel("",SwingConstants.CENTER);
dr[4].setBounds(dr[1].getX(),dr[1].getY()+40+40,45,40);
dr[4].setOpaque(true);
dr[4].setBackground(Color.yellow);
jp1.add(dr[4]);

dr[5]=new JLabel("",SwingConstants.CENTER);
dr[5].setBounds(dr[4].getX()+45,dr[4].getY(),45,40);
dr[5].setOpaque(true);
dr[5].setBackground(Color.cyan);
jp1.add(dr[5]);

dr[6]=new JLabel("",SwingConstants.CENTER);
dr[6].setBounds(dr[2].getX(),dr[2].getY()+40+40,90,40);
dr[6].setOpaque(true);
dr[6].setBackground(new Color(153,50,53));
jp1.add(dr[6]);

dr[7]=new JLabel("",SwingConstants.CENTER);
dr[7].setBounds(dr[3].getX(),dr[3].getY()+40+40,90,40);
dr[7].setOpaque(true);
dr[7].setBackground(new Color(4,150,5));
jp1.add(dr[7]);

dr[8]=new JLabel("Left Turn",SwingConstants.CENTER);
dr[8].setBounds(dr[6].getX(),dr[6].getY()+40+40,90,40);
dr[8].setOpaque(true);
dr[8].setBackground(new Color(4,150,5));
jp1.add(dr[8]);

dr[9]=new JLabel("Forward",SwingConstants.CENTER);
dr[9].setBounds(dr[4].getX(),dr[4].getY()+40+40,90,40);
dr[9].setOpaque(true);
dr[9].setBackground(new Color(4,150,5));
jp1.add(dr[9]);

dr[10]=new JLabel("Right Turn",SwingConstants.CENTER);
dr[10].setBounds(dr[7].getX(),dr[7].getY()+40+40,90,40);
dr[10].setOpaque(true);
dr[10].setBackground(new Color(4,150,5));
jp1.add(dr[10]);
/*
y=new JLabel("",SwingConstants.CENTER);
y.setBounds(x.getX(),x.getY()+x.getHeight()+20,120,40);
y.setOpaque(true);
y.setBackground(Color.GREEN);
jp1.add(y);

cut=new JLabel();
cut.setBounds(ud.getX(),ud.getY()+ud.getHeight()+20,120,40);
cut.setOpaque(true);
cut.setBackground(Color.ORANGE);
*/
jf.add(jp1);
}
void updates()
{
//x.setText("Angle (X) : "+lr.exe());
//y.setText("Angle (Y) : "+ud.exe());
dr[4].setText("X:"+lr.exe());
dr[5].setText("Y:"+ud.exe());
}
void delay(int a)
{
try
{
Thread.sleep(a);
}
catch (InterruptedException e)
{
System.out.println(e);
}
}
void onSci()
{
harvest=true;
}
void offSci()
{
harvest=false;
}
void onSng()
{
sow=true;
}
void offSng()
{
sow=false;
}
}