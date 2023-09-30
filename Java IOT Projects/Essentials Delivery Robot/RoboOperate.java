import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
class RoboOperate
{
//start
Dimension dim;
int w,h;
int width=550,height=400;
JFrame jf;
//integrate
UdpRW udp = new UdpRW(421,4210);
RoboUI ui = new RoboUI();
//network
String ip="192.168.2.1";
//process
static String msg="op:0";
Thread loop = new Thread()
{
public void run()
{
while(true)
{
delay(20);
cmd();
}
}
}
;
RoboOperate()
{
dim=(Toolkit.getDefaultToolkit()).getScreenSize();
w=(int)(dim.getWidth());
h=(int)(dim.getHeight());
jf=new JFrame("COVID-19 ROBOT");
jf.setBounds(((w-width)/2),((h-height)/2),width,height);
jf.setResizable(false);
jf.setLayout(null);
jf.setDefaultCloseOperation(jf.EXIT_ON_CLOSE);
init();
addKeyboardEvent();
jf.setVisible(true);
jf.repaint();
jf.revalidate();
jf.requestFocus();
loop.start();
}
void init()
{
jf.add(ui.jp);
}
void cmd()
{
System.out.println("check : "+msg);
udp.RxTx(ip,msg);
}
void addKeyboardEvent()
{
jf.addKeyListener(new KeyListener()
{
public void keyTyped(KeyEvent e)
{
}
public void keyPressed(KeyEvent e)
{
if(e.getKeyCode()==KeyEvent.VK_A)
{
msg="op:1";
ui.l.setBackground(Color.green);
}
else if(e.getKeyCode()==KeyEvent.VK_D)
{
msg="op:2";
ui.r.setBackground(Color.green);
}
else if(e.getKeyCode()==KeyEvent.VK_W)
{
msg="op:3";
ui.f.setBackground(Color.green);
}
else if(e.getKeyCode()==KeyEvent.VK_S)
{
msg="op:4";
ui.b.setBackground(Color.green);
}
}
public void keyReleased(KeyEvent e)
{
if(e.getKeyCode()==KeyEvent.VK_A)
{
msg="op:0";
ui.l.setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_D)
{
msg="op:0";
ui.r.setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_W)
{
msg="op:0";
ui.f.setBackground(Color.magenta);
}
else if(e.getKeyCode()==KeyEvent.VK_S)
{
msg="op:0";
ui.b.setBackground(Color.magenta);
}
}
}
);
}
void delay(int a)
{
try
{
Thread.currentThread().sleep(a);
}
catch (InterruptedException e)
{
System.out.println(e);
}
}
}