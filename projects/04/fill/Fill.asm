// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
(INIT)
@SCREEN 
D=A
@i 
M=D
@8192 
D=A 
@n 
M=D



(LOOP)
    @KBD 
    D=M 
    @WHITE
    D; JEQ
    @BLACK
    D; JGT


(BLACK)
    @i 
    D=M 
    A=D
    M=-1
    @16
    D=A
    M=M + D
    @LOOP 
    0; JMP

(WHITE)
    @i 
    D=M 
    A=D
    M=0
    @16
    D=A
    M=M - D
    @LOOP 
    0; JMP 