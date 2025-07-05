#include <Wire.h>

int a, b, c, d, w, x ,y ,z; // Switches
int alpha, beta, gamma, delta, phi, chi, psi, omega; //outputs
int b_nc, b_no; //buttons
int seg_1_a, seg_1_b, seg_1_c, seg_1_d, seg_1_e, seg_1_f, seg_1_g, seg_1_dot; //PCB segment
int seg_2_a, seg_2_b, seg_2_c, seg_2_d, seg_2_e, seg_2_f, seg_2_g, seg_2_dot; // Breadboard Segment

int I2C_addr = 0x3F;

//64 Bit D flip flop bank
int D[64];
int D_Q[64];
int D_lst_clk[64];
int D_clk[64];

// 4 bit sequencer:
bool s[4]; 
bool s_clk;
bool s_prev_clk = 0;


//Up counter
int up_counter_out = 0;
bool up_count[8];
bool up_counter_clr = 0;
bool up_counter_clk = 0;
bool up_counter_prev_clk = 0;
bool up_counter_async_clr = 0;


bool clk_2hz = false;
bool clk_10hz = false;
bool clk_20hz = false;
bool clk_50hz = false;

unsigned long clk2prevMil = 0; 
const unsigned long clk2interval = 500; 
unsigned long clk10prevMil = 0; 
const unsigned long clk10interval = 100; 
unsigned long clk20prevMil = 0; 
const unsigned long clk20interval = 50; 
unsigned long clk50prevMil = 0; 
const unsigned long clk50interval = 20; 


void begin_logic_simulation(){
  Wire.begin();
  s[0] = 1;
}


void logic_simulation(){

  //byte seg_1 = (seg_1_a << 7) | (seg_1_b << 6) | (seg_1_c << 5) | (seg_1_d << 4) | (seg_1_e << 3) | (seg_1_f << 2) | (seg_1_g << 1) | seg_1_dot;
  //byte seg_1 = (seg_1_dot << 7) | (seg_1_g << 6) | (seg_1_f << 5) | (seg_1_e << 4) | (seg_1_d << 3) | (seg_1_c << 2) | (seg_1_b << 1) | seg_1_a;
  //byte seg_2 = (seg_2_dot << 7) | (seg_2_g << 6) | (seg_2_f << 5) | (seg_2_e << 4) | (seg_2_d << 3) | (seg_2_c << 2) | (seg_2_b << 1) | seg_2_a;

  byte seg_1 = (seg_1_d << 7) | (seg_1_e << 6) | (seg_1_g << 5) | (seg_1_f << 4) | (seg_1_a << 3) | (seg_1_b << 2) | (seg_1_c << 1) | seg_1_dot;
  byte seg_2 = (seg_2_d << 7) | (seg_2_e << 6) | (seg_2_g << 5) | (seg_2_f << 4) | (seg_2_a << 3) | (seg_2_b << 2) | (seg_2_c << 1) | seg_2_dot;

  //byte output = (alpha << 7) | (beta << 6) | (gamma << 5) | (delta << 4) | (phi << 3) | (chi << 2) | (psi << 1) | omega;
  byte output = (omega << 7) | (psi << 6) | (chi << 5) | (phi << 4) | (delta << 3) | (gamma << 2) | (beta << 1) | alpha;


  a = digitalRead(2);
  b = digitalRead(3);
  c = digitalRead(4);
  d = digitalRead(5);
  w = digitalRead(6);
  x = digitalRead(7);
  y = digitalRead(8);
  z = digitalRead(9);

  b_nc = digitalRead(12);
  b_no = digitalRead(13);
  
  Wire.beginTransmission(0x39); //Keep this one 
  Wire.write(seg_1);              
  Wire.endTransmission();    

  Wire.beginTransmission(0x38);       
  Wire.write(output);              
  Wire.endTransmission();

  Wire.beginTransmission(I2C_addr);//change this one!
  Wire.write(seg_2);              
  Wire.endTransmission();

  //Load flip flop banks on rising edges
  for(int i = 0; i < 64; i++){
      if(D_clk[i] == 1 && D_lst_clk[i] == 0){
        D_Q[i] = D[i];
    }
    D_lst_clk[i] = D_clk[i];
  }

  

  unsigned long currentMillis = millis();

  if (currentMillis - clk2prevMil >= clk2interval) {
    clk2prevMil = currentMillis;
    clk_2hz = !clk_2hz;
  }

  if (currentMillis - clk50prevMil >= clk50interval) {
    clk50prevMil = currentMillis;
    clk_50hz = !clk_50hz;
  }

  if (currentMillis - clk10prevMil >= clk10interval) {
    clk10prevMil = currentMillis;
    clk_10hz = !clk_10hz;
  }

  if (currentMillis - clk20prevMil >= clk20interval) {
    clk20prevMil = currentMillis;
    clk_20hz = !clk_20hz;
  }

  //seq code
  if(s_clk && !s_prev_clk) {
    for(int i = 0; i < 4; i++){
      if(s[i] == 1){
        if(i == 3){    
          s[0] = 1;
        }else{
          s[i+1] = 1;
        }
        s[i] = 0;
        break;
      }   
    }
  }
  s_prev_clk = s_clk;



  //Upcounter sim
  if(up_counter_async_clr){
      up_counter_out = 0;
      for (int i = 0; i < 8; i++) {
        up_count[i] = 0;
      }
  }
  
  if (up_counter_clk && !up_counter_prev_clk) {
    if (!up_counter_clr) {
      // Increment the counter
      up_counter_out++;
      if (up_counter_out > 255) {
        up_counter_out = 0;  // Wrap around at 255
      }
      
      // Update up_count array to match up_counter_out
      for (int i = 0; i < 8; i++) {
        up_count[i] = (up_counter_out >> i) & 1;
      }
    } else {
      // Clear the counter and array if up_counter_clr is set
      up_counter_out = 0;
      for (int i = 0; i < 8; i++) {
        up_count[i] = 0;
      }
    }
  }
  up_counter_prev_clk = up_counter_clk;

  //delay(50);
}