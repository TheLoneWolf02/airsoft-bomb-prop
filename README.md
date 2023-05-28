
# DISCLAIMER
This project and code os design for a bomb PROP, this is not a weapon and can not be used as one.

# GENERAL INFO
A interactive bomb prop for airsoft game / scenarioes. A project based on a ardunio nano and a couple simple components.

# GIVEN'S
This github gives access to the code and the gerber files.

# REQUIRED HARDWARE
I used :
1 LED 5V.
1 ARDUINO NANO
3 CHERRY SPEC KEYBOARD SWITCHES
1 16 by 32 OLED I2C SCREEN


# HOW TO USE
## SETTING THE TIMER
After powering on the prop, a splash screen will appear, followed by a prompt to choose the bomb timer.
You can increase and decrease the amount of time in minute increments by using buttons 2 and 3.
After setting the wanted amount of time, press button 1.

## CHOOSING DEFUSE WIRE NUMBER ORDER
The next prompt will ask for "d order" this refers to the order and number of wires that must be removed to "defuse the bomb" and win.
Connect wires from both ends of the defuse slots. The defuses order will correspond to the order in which was connected the wires.
You do not need to indicate the number of wires used as program will determine it on it's own.
You can see the progress of the defuse order on the screen as you connect the wires.
If you enter this stage with defuse connection already down, the order will correspond to the order of the connection from top to bottom or in descending order (9 10 11 12).
Once the order completed , the user must press button 1 and 2. Once this done the LED will flash the number of time that there is defuse connection and then the timer will start.

## GAME PHASE
On the screen the number of minutes will be indicated. Once under a minute the screen will show the seconds left.
Under the timer there will be X's, the same number as the number of defuse connections, indicating the progress of the the defuse.
The X's will become O's when the player breaks the connections in the correct orders, once all wires are cut in the correct order than the bomb is defused.
A very annoying jingle will be played and a message will shown on the screen saying bomb defused.
If a player cuts the connection to a wire that isnt the next one to be cut, a jingle will be played, the bomb has "exploded" and a flashing message" will be shown.
After the timer runs out the bomb will also "explode".
In anycase, the prop will return to time length selection menu.

### EXAMPLE
You set the timer to 5 using button 2.
Press button 1 to enter the next menu.
You connect slots 9 12 11 in that order. The players that have to defuse the bomb must remove or cut the connection of the slots by cutting wire 9 then wire 12 and finally wire 11.
The game starts.
You have to defuse the bomb, you find the "bomb". You have the info on the first two connections to cut, you cut the connections; the first 2  X's become O's, now you have to guess the last 1.
1. you guess right and win.
2. you guess wrong and you lose.


Here you can see the diagrame and a view of the pcb traces:

![Diagram](https://github.com/TheLoneWolf02/airsoft-bomb-prop/assets/29492892/899fae50-0cc8-4eda-bd0b-b741c8bb3de5)

![PCB VIEW](https://github.com/TheLoneWolf02/airsoft-bomb-prop/assets/29492892/57dffb50-691f-4207-aafc-84425259ba01)
