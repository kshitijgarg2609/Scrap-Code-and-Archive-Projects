import java.awt.*;
import javax.swing.*;
class RoboUI
{
JPanel jp;
JLabel l = new JLabel("Left",SwingConstants.CENTER);
JLabel r = new JLabel("Right",SwingConstants.CENTER);
JLabel f = new JLabel("Up",SwingConstants.CENTER);
JLabel b = new JLabel("Down",SwingConstants.CENTER);
RoboUI()
{
init();
steering();
}
void init()
{
jp=new JPanel();
jp.setBounds(50,50,400,270);
jp.setBorder(BorderFactory.createLineBorder(Color.orange,5));
jp.setLayout(null);
}
void steering()
{
f.setBounds(155,40,90,40);
f.setOpaque(true);
f.setBackground(Color.magenta);
jp.add(f);

b.setBounds(f.getX(),f.getY()+f.getHeight()+20,90,40);
b.setOpaque(true);
b.setBackground(Color.magenta);
jp.add(b);

l.setBounds(b.getX()-20-90,b.getY(),90,40);
l.setOpaque(true);
l.setBackground(Color.magenta);
jp.add(l);

r.setBounds(b.getX()+20+90,b.getY(),90,40);
r.setOpaque(true);
r.setBackground(Color.magenta);
jp.add(r);
}
}