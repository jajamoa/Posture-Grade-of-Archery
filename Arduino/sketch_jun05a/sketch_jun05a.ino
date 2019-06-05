
int ledpin = 13;
 
void setup()
{
  pinMode(ledpin, INPUT);//初始化
  Serial.begin(9600);  // 打开串口，设置波特率为9600 bps
}
 
void loop()//Arduino的循环语句
{
  int value = digitalRead(ledpin); //定义传感器检测到的值为value
  if(value==HIGH)//如果它的值为高电平，即检测到有人通过
    {
      Serial.println("Someone!");//输出有人
    }
    else
    {
      Serial.println("Nobody");//输出没人
    }
  delay(1000);    
}
