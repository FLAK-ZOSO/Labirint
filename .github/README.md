# Labirint
```
         LLL             AAAAAA      BBBBBBBBB   IIIII  RRRRRRRRR   IIIII  NNNNNN    NNN TTTTTTTTTTT
         LLL            AAA  AAA     BBB    BBB   III   RRR    RRR   III   NNN NNN   NNN     TTT
         LLL           AAA    AAA    BBBBBBBBB    III   RRRRRRRRR    III   NNN  NNN  NNN     TTT
         LLL          AAAAAAAAAAAA   BBB    BBB   III   RRR RRR      III   NNN   NNN NNN     TTT
         LLLLLLLLLL  AAA        AAA  BBBBBBBBB   IIIII  RRR  RRRR   IIIII  NNN    NNNNNN     TTT
                                v4.2.1  By FLAK-ZOSO & AsiaMarcheluzzo
```
## Instructions
- Download [`labirint.exe`](https://github.com/FLAK-ZOSO/Labirint/blob/main/labirint.exe?raw=true)
- Open your `terminal`
- Go to the `C:\Users\YOUR_USERNAME\Downloads>` folder
```
C:\Users\YOUR_USERNAME\Downloads>
```
- Run `labirint` (add the `--help` option for more information)
```
C:\Users\YOUR_USERNAME\Downloads>labirint
```
- You will see the logo, press `ENTER`
- You will see a blank leaderboard, press `ENTER`
- Insert your options, like suggested below
```
Username: MyUsername
Bonus frequency (period): 10
Cloud max width: 15
Duration of a frame: 0.1
Color: matrix
```
- The game will start

## Game
- Your pawn is the first letter of your `Username`, in our case it will be `M` from `MyUsername`
- You can move the pawn inserting `a`/`b` to move up/down ("alto"/"basso"), or `d`/`s` to move right/left ("destra"/"sinistra")
- If you touch a `*` or a `-` you lose
- If you touch a `$` you get `10` extra points
- If you touch a `@` you get a `z-fuel`, a bonus that you can use as described below

## Values
```
##################################################
#                                                #
#                                                #
#                                                #
#                       M                        #
#                                                #
#                                                #
#---------------------                   --------#
#---------------------                   --------#
#--------------------                   ---------#
#--------------------                   ---------#
#--------------------                   ---------#
#-------------------           *****   ----------#
#-------------------                   ----------#
#-------------------            ****** ----------#
#-------------------                   ----------#
#------------------   *************** -----------#
#------------------         @         -----------#
#------------------                   -----------#
#------------------                   -----------#
#------------------            *******-----------#
##################################################
14
X=24 Y=3 Z=1
Z Fuel: 0
```

In the lower area of the screen you will see this `3` lines of variables:
- In the first one you will see your points
- In the second one you will see your coordinates
- In the third one you will see how much `z-fuel` you have

## Z-fuel
The `z-fuel` allows you to trepass the `*`, a fuel will last for `10 frames`, and can be used inserting `z` as input. 
During this time you will see the `Z` coordinate set to `0`.
