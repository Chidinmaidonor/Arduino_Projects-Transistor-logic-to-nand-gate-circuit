// ---------------------------------------------------------------------------------------
// LAB 0000 TEMPLATE
// Instructions:
// Upload Code as is to test board
// ATENTION DO NOT EDIT CODE EXCEPT IN SPECIFIED AREA
// ---------------------------------------------------------------------------------------


#include "ECE_2163_v0.h"


void setup() {
  begin_logic_simulation();
}

void loop() {


  // ---------------------------------- EDIT ONLY BELOW ----------------------------------
  // ! = Not
  // && = And/*
  // || = OR/+
  // !(a||b) would be a nor opperation
  // !a||b would be, not a OR b

  
  
  alpha = !(!(w && x) && !(x && y) && !(w && y)); // any two
  beta = 0; 
  gamma = 0;
  delta = 0; 
  phi = 0;
  chi = 0;
  psi = 0;
  omega = 0;
  
  seg_1_a = b_nc;
  seg_1_b = b_nc;
  seg_1_c = !b_no;
  seg_1_d = !b_no;
  seg_1_e = !b_no;
  seg_1_f = b_nc;
  seg_1_g = !(b_no || !b_nc);
  seg_1_dot = !clk_2hz;
  

  // ---------------------------------- EDIT ONLY ABOVE ----------------------------------
  
  logic_simulation();
}




