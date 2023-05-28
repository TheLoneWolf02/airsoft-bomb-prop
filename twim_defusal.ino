




#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
//OBJECT PINS
int buzzerPin = 5;

int buttonPin2 = 4;
int buttonPin1 = 3;
int buttonPin0 = 2;

//DEFUSE PINS

int defuse9 = 9;
int defused9 = 0;

int defuse10 = 10;
int defused10 =0;

int defuse11 = 11;
int defused11 =0;

int defuse12 = 12;
int defused12 =0;


//DEFUSE INFO
int defuseNbr = -1;
int defuseProgress = 0;
int defuse[4];
int defuseStartCount;
int ledPin = 6;

//BUTTON STATES
int buttonState0;
int buttonState1;
int buttonState2;


//DEFUSE STATES

int defuseState9;
int defuseState10;
int defuseState11;
int defuseState12;

// MENU VARIABLES
int inMenu = 1;
int defuseChosen = 0;
int timerStarted = 0;
int gameEnded = 0;

 

// GAME VARIABLES
int gameTimeStart = 1; // in minutes
int gameChrono = 0;


void setup() {
  Serial.begin(9600);


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }


  pinMode(defuse9,INPUT_PULLUP);
  pinMode(defuse10,INPUT_PULLUP);
  pinMode(defuse11,INPUT_PULLUP);
  pinMode(defuse12,INPUT_PULLUP);

  pinMode(buttonPin0,INPUT_PULLUP);
  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);


  pinMode(buzzerPin,OUTPUT);
  pinMode(ledPin, OUTPUT);

  showIntro();


  


}

void loop() {


  // put your main code here, to run repeatedly:
  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  defuseState9 = digitalRead(defuse9);
  defuseState10 = digitalRead(defuse10);
  defuseState11 = digitalRead(defuse11);
  defuseState12 = digitalRead(defuse12);
  
  


  if(inMenu == 1)
  {
    showTimerSetup();
    timerCheck();
    display.clearDisplay();
  }
  else if(inMenu == 0)
  {
    if(gameEnded)
    {
     resetValues();

    }
    else if(gameEnded == 0)
    {
      if(defuseChosen == 0)
      {
        display.clearDisplay();
        getDefuseOrder();
        if(buttonState0 == 0 && buttonState1 == 0)
        { 
          if(defuseNbr == -1)
          {
            showDefuseErrorMessage();
          }
          else
            defuseChosen = 1;
        }        
      }
      else if(timerStarted == 0)
      {
        //showGameStart();
        gameChrono = gameTimeStart * 60;
        defuseStartCount = defuseNbr;
        timerStarted = 1;
        for(int i = 0;i < defuseNbr ;i++){
          tone(buzzerPin,((i*100) + 50));
        delay(250);
        noTone(buzzerPin);
        delay(100);
        }
        
      }
      else if(timerStarted == 1)
      {
        checkEndGame();
        checkDefuse();
        showCountdown();
        gameChrono -= 1;
        display.clearDisplay();
        delay(1000);
        

        
        }
      }
    }
  }



void resetValues()
{
  
      inMenu = 1;
      timerStarted = 0;
      gameEnded = 0;
      defuseNbr = -1;
      defuseProgress = 0;
      defuseChosen = 0;
      defused9 = 0;
      defused10 = 0;
      defused11 = 0;
      defused12 = 0;
}

void checkDefuse()
{
  
  if(defuseState9 == 1)
  {
    if(checkInDefuseList(defuse9) && !defused9)
    {
    
      if(defuse[defuseProgress] == defuse9)
      {
        defuseProgress++;
        defused9 = 1;
        Serial.println("progress");
        
      }
      else
        gameEnd();
    }
      
  }

  if(defuseState10 == 1)
  {
    if(checkInDefuseList(defuse10) && !defused10)
    {
    
      if(defuse[defuseProgress] == defuse10)
      {
        defuseProgress++;
        defused10 = 1;
        Serial.println("progress");

      }
      else
        gameEnd();
    }
  }

  if(defuseState11 == 1)
  {
   if(checkInDefuseList(defuse11))
    {
      if(checkInDefuseList(defuse11) && !defused11)
    {
      
      if(defuse[defuseProgress] == defuse11)
      {
        defuseProgress++;
        defused11 = 1;
        Serial.println("progress");

      }
      else
        gameEnd();
    }
    }
  }

  if(defuseState12 == 1)
  {
    if(checkInDefuseList(defuse12) && !defused12)
    {
    
      if(defuse[defuseProgress] == defuse12)
      {
        defuseProgress++;
        defused12 = 1;
        Serial.println("progress");

      }
      else
        gameEnd();
    }
  }
  if(defuseProgress >= defuseNbr)
    gameWin();
}

void showCountdown()
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);

  if(gameChrono / 60 <= 1)
  {
    char time[4];
  itoa(gameChrono,time,10);
  display.println(time);
  display.setCursor(40, 0);
  display.setTextSize(1);
  display.println("seconds");
  display.setTextSize(2);
  }else
  {
    display.println("~");
    display.setCursor(18, 0);

    char time[4];
    int minutes = (gameChrono / 60) + 1;
    itoa(minutes,time,10);
    display.println(time);
    display.setCursor(40, 0);
    display.setTextSize(1);
    display.println("minutes");
    display.setTextSize(2);
  }

  





  for(int i = 0; i < defuseNbr;i++)
  {
    display.setCursor(i*(64/defuseNbr),17);
    if((defuseProgress -1) >= i)
      display.println("O");
    else
      display.println("X");

  }
  display.display();

  display.clearDisplay();

}
void showIntro()
{
display.clearDisplay();
  digitalWrite(ledPin, HIGH);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Bomb");

  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Defusal");

  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("By TWIM");


  display.display();
  delay(1000);

  display.clearDisplay();
  display.display();
  digitalWrite(ledPin, LOW);

}


void gameWin()
{
    showWinningMessage();
    for(int i = 0; i < 5;i++)
    {
      z
    gameEnded = 1;
}

void showWinningMessage()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BOMB");
  display.setCursor(0, 17);
  display.println("DEFUSED");

  display.display();
  for( int i = 0; i< 10; i++)
  {
    display.invertDisplay(true);
  delay(250);
    display.display();
    display.invertDisplay(false);
    delay(250);
    display.display();
  }
  display.invertDisplay(true);
  display.display();
  delay(2500);
  display.invertDisplay(false);
  display.display();
  display.clearDisplay();
}

void showDefuseErrorMessage()
{
 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("PLS CHOOSE");
  display.setCursor(0, 17);
  display.println("1 or +");

  display.display();
  for( int i = 0; i< 10; i++)
  {
    display.invertDisplay(true);
  delay(250);
    display.display();
    display.invertDisplay(false);
    delay(250);
    display.display();
  }
  display.clearDisplay();

}

void showLosingMessage()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BOMB");
  display.setCursor(0, 17);
  display.println("EXPLODED");
  display.display();
  for( int i = 0; i< 10; i++)
  {
    display.invertDisplay(true);
  delay(250);
    display.display();
    display.invertDisplay(false);
    delay(250);
    display.display();
  }
  display.clearDisplay();
}

void checkEndGame()
{
  if(gameChrono <= 0)
  {
    gameEnd();
  }
}

void gameEnd()
{
  gameEnded = 1;
    for(int i = 0; i < 5;i++)
    {
      tone(buzzerPin,((i*100) + 50));
      delay(250);
      noTone(buzzerPin);
      delay(200);
    }
    showLosingMessage();
}

void showGameStart()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("GAME START");
  display.display();
  delay(100);
  display.clearDisplay();
}

void showTimerSetup()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);

  char timerValue[4];
  itoa(gameTimeStart,timerValue,10);
  

  display.println("Timer : ");
  display.setTextSize(1);
  display.setCursor(40, 25);

  display.println("minutes");
  display.setTextSize(2);

  display.setCursor(0, 17);
  
  display.println(timerValue);
  display.display();
}


bool checkInDefuseList(int defuseCheck)
{
  if(defuseNbr < -1)
    return false;
  for(int i =0;i <defuseNbr;i++)
  {
    if(defuse[i] == defuseCheck)
      return true;
  }
  return false;
}

void getDefuseOrder()
{
  showDefuseOrderMessage();
  if(defuseState9 == 0)
  {
    if(!checkInDefuseList(defuse9))
    {

      if(defuseNbr < 0)
      {
      defuseNbr =0;
      }
      defuse[defuseNbr] = defuse9;
      defuseNbr++;
    
    }
      
  }
  if(defuseState10 == 0)
  {
    if(!checkInDefuseList(defuse10))
    {
      
      if(defuseNbr < 0)
      {
      defuseNbr =0;
      }
      defuse[defuseNbr] = defuse10;
      defuseNbr++;
   
    }
  }
  if(defuseState11 == 0)
  {
   if(!checkInDefuseList(defuse11))
    {
     
      if(defuseNbr < 0)
      {
      defuseNbr =0;

      }
      defuse[defuseNbr] = defuse11;
      defuseNbr++;
      
      
    }
  }
  if(defuseState12 == 0)
  {
    if(!checkInDefuseList(defuse12))
    {
      if(defuseNbr < 0)
      {
        defuseNbr = 0;
      }
      defuse[defuseNbr] = defuse12;
      defuseNbr++;
    }
  }
}


void showDefuseOrderMessage()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);

  display.println("D Order :");
  display.setTextSize(2);
  display.setCursor(0, 17);
  if(defuseNbr >= 0)
  {
    for(int i = 0; i < defuseNbr; i++)
    {
      char timerValue[4];
      itoa(defuse[i],timerValue,10);
      display.setCursor(30*i, 17);
      display.print(timerValue);
    }
  }
  display.display();
  
}

void timerCheck()
{
  if(buttonState1 == 0)
    {
      gameTimeStart++;
      delay(250);
    }
    if(buttonState2 == 0)
    {
      gameTimeStart--;
      if(gameTimeStart < 1)
        gameTimeStart = 1;
      delay(250);
    }
    if(buttonState0 == 0)
    {
      display.clearDisplay();
      inMenu = 0;
      delay(500);
    }
}


void LEDDefuseCounter()
{
  for(int i = 0; i < defuseNbr;i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  }
}

void getDefuseList()
{
  defuseNbr = 0;
  if(defuseState9 == 0)
  {
    
    defuseNbr++;
    defused9 = 0;
  }
  if(defuseState10 == 0)
  {
    defused10 = 0;
    defuseNbr++;
  }
  if(defuseState11 == 0)
  {
    defused11 = 0;
    defuseNbr++;
  }
   if(defuseState12 == 0)
  {
    defused11 = 0;
    defuseNbr++;
  }
}