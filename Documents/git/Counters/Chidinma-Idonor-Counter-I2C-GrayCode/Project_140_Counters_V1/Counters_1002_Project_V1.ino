// ---------------------------------------------------------------------------------------
// LAB 0100 TEMPLATE
// Instructions:
//
// ATENTION DO NOT EDIT CODE EXCEPT IN SPECIFIED AREA
// ---------------------------------------------------------------------------------------


#include "Header.h"


void setup() {
  begin_logic_simulation();
  
  // -------------------------------- EDIT THIS I2C_addr --------------------------------
  I2C_addr = 0x3F;
  // ------------------------------------------------------------------------------------

}

void loop() {


  // ---------------------------------- EDIT ONLY BELOW ----------------------------------
  // ! = Not
  // && = And/*
  // || = OR/+
  // !(a||b) would be a nor opperation
  // !a||b would be, not a OR b
  
  // Feel free to edit equations to play with outputs

  //s_clk = 0;

  alpha = 0;
  beta =  0; 
  gamma = 0;
  delta = 0; 
  
  phi = 0;
  chi = 0;
  psi = 0;
  omega = 0;

  up_counter_clk = clk_10hz; //or replace with other clock(Note this came with harvey code)

  //user defined variables, feel free to make more thought the upcoming labs
  //I used seg_1_0 to represent the LSB of the first segment as an example (nb came with harvey code)
  int seg_1_0 = !a&&(up_count[0])||a&&(grey_0(up_count[3],up_count[2],up_count[1],up_count[0]));
  int seg_1_1 = !a&&(up_count[1])||a&&(grey_1(up_count[3],up_count[2],up_count[1],up_count[0]));
  int seg_1_2 = !a&&(up_count[2])||a&&(grey_2(up_count[3],up_count[2],up_count[1],up_count[0]));
  int seg_1_3 = !a&&(up_count[3])||a&&(grey_3(up_count[3],up_count[2],up_count[1],up_count[0]));


  // On board 7 segment
  seg_1_a = !func_a(seg_1_3,seg_1_2,seg_1_1,seg_1_0);//my custom variables with functions you made last lab
  seg_1_b = !func_b(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_1_c = !func_c(seg_1_3,seg_1_2,seg_1_1,seg_1_0); 
  seg_1_d = !func_d(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_1_e = !func_e(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_1_f = !func_f(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_1_g = !func_g(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_1_dot = 1;


  // Bread-board 7 segments 
  //You can reuse your functions here with different inputs
  seg_2_a = !func_a(seg_1_3,seg_1_2,seg_1_1,seg_1_0);//my custom variables with functions you made last lab
  seg_2_b = !func_b(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_2_c = !func_c(seg_1_3,seg_1_2,seg_1_1,seg_1_0); 
  seg_2_d = !func_d(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_2_e = !func_e(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_2_f = !func_f(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_2_g = !func_g(seg_1_3,seg_1_2,seg_1_1,seg_1_0);
  seg_2_dot = 1;

  // ---------------------------------- EDIT ONLY ABOVE ----------------------------------
  
  logic_simulation();
}


// ---------------------------------- EDIT FUNCTIONS BELOW ----------------------------------

int func_a(int w, int x,int y,int z)
{
  // POS
  return (w || !x || y || z) && (w || x || y || !z) && (!w || !x || y || !z) && (!w || x || !y || !z);
}

int func_b(int w, int x,int y,int z)
{
  // POS
  return (!w || !y || !z) && (!x || !y || z) && (!w || !x || y || z) && (w || !x || y || !z);
}

int func_c(int w, int x,int y,int z)
{
  // POS
  return (!w || !x || !y) && (!w || !x || y || z) && (w || x || !y || z);   
}

int func_d(int w, int x,int y,int z)
{
  // POS
  return (!x || !y || !z) && (!w || x || !y || z) && (w || !x || y || z) && (!w || x || y || !z) && (w || x || y || !z);  
}

int func_e(int w, int x,int y,int z)
{
  // POS
  return (w || !z) && (w || !x || y) && (x || y || !z);
}

int func_f(int w, int x,int y,int z)
{
  return (w || x || !z) && (w || x || !y) && (w || !y || !z) && (!w || !x || y || !z);  
}

int func_g(int w, int x,int y,int z)
{
  return (w || x || y) && (w || !x || !y || !z) && (!w || !x || y || z);  
}














//BE sure to copy over your functions from last lab, you will need them!
int grey_3(int w, int x, int y, int z) // MSB
{
  return w; //becos our derived function for "A" K-map is W  
}
int grey_2(int w, int x, int y, int z)
{
  return w != x; // or you can use (!w&&x)||(w&&!x)-- nb func for B
}
int grey_1(int w, int x, int y, int z)
{
  return (x && !y) || (!x && y);// funcion for "C" Kmap
}
int grey_0(int w, int x, int y, int z) // LSB
{
  return y != z; // Logical XOR. (w != x) = (w xor x) . or you can use (!y&&z)||(y&&!z) nb this func is for D 
}


