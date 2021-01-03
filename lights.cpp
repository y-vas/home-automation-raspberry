#include <iostream>
#include <string>
#include <unordered_map>

#include <unistd.h> // sleep for linux
#include "gpio.cpp"

using namespace std;

unordered_map<int, int> PINS {{
  { 4, 3 },
  { 0, 2 },
  { 2, 2 },
  { 6, 2 },
  { 8, 2 },
  { 1, 1 },
  { 3, 1 },
  { 5, 1 },
  { 7, 1 }
}};

unordered_map<int, string> PINS_RUTINES {{
  { 4, "06-22" },
  { 0, "00-24" },
}};



// detects the sound from where it comes  and returns the pin to switch
int detect_sound(){

  // waiting for the sound detectors to test software
  int pin_detected  = 3;
  int pin_to_switch = PINS[ pin_detected ];
  return pin_to_switch;
}

// switches the light
int switch_light( int pin ){

  return 1;
}

int main(){
  // setup_gpio( 17 , INPUT , PUD_OFF );

  // for (auto x : pins)
  //     cout << x.first << " " << x.second << endl;

  while ( 1 ) {

    int pin_to_switch = detect_sound();


    // usleep( 100000 );
    // cout << "World" << endl;




  }


  return 0;
}
