// Takes initial populations of rabbits and foxes and simulates the change in populations
// of both over each step and plots the populations on a simple ASCII chart where the 
// y axis going down simulates steps (time) and x axis simulates the size of the population
// depending on the given scalewith 'F' being the population of the foxes and 'r' being
// the population of the rabbits. 

#include <iostream>
#include <cmath>

using namespace std;

// Takes an int 'number' and a char 'character' and outputs 'number' spaces and then
// outputs 'character'. 
void plotCharacter(int number, char character){
  for(int i = 0; i < number; i++){
    cout << " ";
  }
  
  cout << character;
}

// Takes a pointer to an int and increments the value stored at where the pointer is pointing to.
void incrementCounter(int* num){
  *num = *num + 1;
}

// Takes a double 'numRabbits', a double 'numFoxes', and a double 'scale'. The 'scale' is used with both nums 
// to calculate what position their corresponding char 'F' or 'r' should be outputed in order to create one row
// of an ASCII table. If the positions will be the same, a '*' is placed in the position instead of 'r' or 'F' to
// show and overlap of positions at the current step. Ends with a newline to proceed to the next line.
void chartPopulations(double numRabbits, double numFoxes, double scale){
  int rabbitPos = floor(numRabbits*scale) + 1;
  int foxPos = floor(numFoxes*scale) + 1;

  if(rabbitPos == foxPos){
    plotCharacter(rabbitPos, '*');
  }else if(rabbitPos < foxPos){
    plotCharacter(rabbitPos, 'r');
    plotCharacter(foxPos-rabbitPos, 'F');
  }else{
    plotCharacter(foxPos, 'F');
    plotCharacter(rabbitPos-foxPos, 'r');
  }
  
  cout << endl;
}

// Takes input parameters for functions used to find the change in rabbit and fox populations. Also takes in 
// references to the population of rabbits and foxes. Using the corresponding input parameters, the deltas for
// rabbits and foxes are calculated and then the references to the populations of rabbits and foxes are updated by
// adding the corresponding deltas to them.
void updatePopulations(double g, double p, double c, double m, double K, double& numRabbits, double& numFoxes){
  double deltaRabbit;
  double deltaFoxes;
  
  // Formulas:
  //   deltaRabbit = gR(1-R/K) - pRF
  //   deltaFoxes = cpRF - mF
  
  deltaRabbit = (g * numRabbits * (1-(numRabbits/K))) - (p * numRabbits * numFoxes);
  deltaFoxes = (c * p * numRabbits * numFoxes) - (m * numFoxes);

  numRabbits += deltaRabbit;
  numFoxes += deltaFoxes;
}

// Asks the user to enter in an inital populations for rabbits and foxes. Program terminates if user input
// can not be parsed to a double for either. Program then runs for 500 steps or while the population of rabbits 
// or foxes is greater than 0. For each step the population is charted using the chartPopulations function and the
// population is updated according to the deltas generated in the updatePopulations function. Count (steps) is then
// incremented the the cycle repeats creating an ASCII chart. 
int main(){
  const int MAX_STEPS = 500;
  double numRabbits;
  double numFoxes;
  int count = 0;

  double g = 0.2;
  double p = 0.002;
  double c = 0.6;
  double m = 0.2;
  double K = 1000.0;

  cout << "Enter the initial amount of rabbits: ";
  
  if(!(cin >> numRabbits)){
    cout << "Could not parse initial rabbit value to double. Ending Program..." << endl;
    return -1;
  }

  cout << "Enter the initial amount of foxes: ";
  if(!(cin >> numFoxes)){
    cout << "Could not parse inital fox  value to double. Ending Program..." << endl;
    return -1;
  }
  
  // Chart initial population
  chartPopulations(numRabbits, numFoxes, 0.1);

  while(count < MAX_STEPS && numRabbits > 0 && numFoxes > 0){
    updatePopulations(g, p, c, m, K, numRabbits, numFoxes);
    chartPopulations(numRabbits, numFoxes, 0.1);
    incrementCounter(&count);
  }

}
