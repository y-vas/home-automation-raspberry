#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<int, int> pins;

// detects the sound from where it comes  and returns the pin to switch
int detect_sound(){



  return 1;
}

// switches the light
int switch_light( int pin ){

  return 1;
}

int main (){
  pins[5] = 1;

  for (auto x : pins)
      cout << x.first << " " << x.second << endl;

  while ( 1 ) {
    int switch_pin = detect_sound();



  }

  return 0;
}
