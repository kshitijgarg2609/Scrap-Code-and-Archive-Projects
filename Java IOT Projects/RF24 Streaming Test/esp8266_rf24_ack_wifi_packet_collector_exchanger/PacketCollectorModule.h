int QMAX=0;
uint8_t *bytebuffer;
int front;
int rear;
int itemCount = 0;

uint16_t total_packet=0;
uint16_t ext_len=0;
uint8_t time_stamp[4]{0,0,0,0};
uint8_t seq_num=-1;
boolean frag_flag=false;


void initPacketCollectorModule(int);
boolean decodePacket(uint8_t*,int);
void setTimeStamp(uint8_t,uint8_t,uint8_t,uint8_t);
boolean matchTimeStamp(uint8_t,uint8_t, uint8_t, uint8_t);
uint16_t convertByteToInt(uint8_t,uint8_t);

void resetQueue();
bool isEmptyQueue();
bool isFullQueue();
int getQueueSize();
void insertData(uint8_t);
uint8_t popData();
///////////////////////////
long e1;
long e2;
long e3;

//###############################################################################################################
void initPacketCollectorModule(int a)
{
  QMAX=a;
  bytebuffer=(uint8_t*)calloc(QMAX,sizeof(uint8_t));
}

boolean decodePacket(uint8_t *a,int len)
{
  //Serial.println((char)a[0]);
  //Serial.println((char)a[1]);
  char c_flag=(char)a[1];
  if(c_flag=='F')
  {
    e1=millis();
    uint16_t clen=convertByteToInt(a[9],a[10]);
    //Serial.println("F:"+String(clen));
    //Serial.println("check 1");
    //Serial.println("clen : "+String(clen));
    //Serial.println("len : "+String(len));
    if(len==(clen+11))
    {
      resetQueue();
      setTimeStamp(a[2],a[3],a[4],a[5]);
      total_packet=convertByteToInt(a[7],a[8]);
      Serial.println("____________________________ :_ "+String(total_packet));
      frag_flag=true;
      ext_len=clen;
      for(int i=11;i<len;i++)
      {
        insertData(a[i]);
      }
      //Serial.println("Entered Condition First Frame :- "+String(clen));
    }
  }
  else if(frag_flag && (char)a[1]=='L')
  {
    uint16_t clen=convertByteToInt(a[7],a[8]);
    uint8_t c_seq=a[6];
    //Serial.println("Entered Condition 3 # "+String(a[7])+" @ "+String(a[8]));
    //Serial.println("L:"+String(clen));
    if(len==clen+9 && matchTimeStamp(a[2],a[3],a[4],a[5]))
    {
      //Serial.println("Entered Condition 2 $");
      ext_len+=clen;
      for(int i=9;i<len;i++)
      {
        insertData(a[i]);
      }
      //Serial.println("Entered Condition Last Frame :- "+String(clen));
      e2=millis();
      e3=e2-e1;
      Serial.println("TIME : "+String(e3));
      return true;
    }
  }
  else if(frag_flag && (char)a[1]=='M')
  {
    //Serial.println("Entered Condition 3 # "+String(a[7])+" @ "+String(a[8]));
    uint16_t clen=convertByteToInt(a[7],a[8]);
    uint8_t c_seq=a[6];
    //Serial.println("L:"+String(clen));
   // Serial.println("check 1");
    //Serial.println("clen : "+String(clen));
    //frag_flag=false;
    if(len==clen+9  && matchTimeStamp(a[2],a[3],a[4],a[5]))
    {
      //Serial.println("Entered Condition 3 $");
      ext_len+=clen;
      for(int i=9;i<len;i++)
      {
        insertData(a[i]);
      }
      //return true;
      //Serial.println("Entered Condition Middle Frame :- "+String(clen));
    }
  }
  else if((char)a[1]=='N')
  {
    uint16_t clen=convertByteToInt(a[7],a[8]);
    frag_flag=false;
    if(len==clen+4)
    {
      ext_len=clen;
      for(int i=4;i<len;i++)
      {
        insertData(a[i]);
      }
      return true;
    }
  }
  //Serial.println("EXT : "+String(ext_len));
  return false;
}

void setTimeStamp(uint8_t a,uint8_t b, uint8_t c, uint8_t d)
{
  time_stamp[0]=a;
  time_stamp[1]=b;
  time_stamp[2]=c;
  time_stamp[3]=d;
}

boolean matchTimeStamp(uint8_t a,uint8_t b, uint8_t c, uint8_t d)
{
  return (time_stamp[0]==a && time_stamp[1]==b && time_stamp[2]==c && time_stamp[3]==d);
}

uint16_t convertByteToInt(uint8_t a,uint8_t b)
{
  return (a*256)+b;
}
//###############################################################################################################
void resetQueue()
{
  front=-1;
  rear=-1;
}

bool isEmptyQueue()
{
   return (front ==(QMAX-1));
}

bool isFullQueue()
{
   return (rear == (QMAX-1));
}

int getQueueSize()
{
   return (rear+1);
}  

void insertData(uint8_t a)
{
   if(!isFullQueue())
   {
      bytebuffer[++rear] = a;
   }
}

uint8_t popData()
{
   uint8_t a=0;
   if(front<=rear)
   {
      a=bytebuffer[++front];
   }
   return a;  
}
