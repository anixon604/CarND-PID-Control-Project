#include "PID.h"
#include <iostream>
#include <cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

  p.push_back(Kp);
  p.push_back(Ki);
  p.push_back(Kd);

  dp.push_back(-0.002);
  dp.push_back(0);
  dp.push_back(-0.002);

  transferParams();

  // max number of tunes before tuning next parameter
  numCyclesCount = 10;
  numCycles = 0;
  // init flag
  twiddleInit = false;
  // index of current parameter being tuned
  paramIndex = 0;

  // keeps track of what code stage to run between calls to twiddle
  // used to gather more next set of error data.
  twiddleStage = 0;
  twiddle = false; // to twiddle or not to twiddle.
}

// 0.15, 0.65
void PID::UpdateError(double cte) {
  d_error = cte - p_error; // p_error = prev_cte before next line assignment
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  total_Error = Kp*p_error + Ki*i_error + Kd*d_error;
  if(!twiddleInit) {
      best_error = pow(total_Error,2);
      twiddleInit = true;
  }
  if(fabs(dp[0]+dp[1]+dp[2]) > 0.2 && fabs(p_error) > 0.5 && twiddle == true) twiddleTune();
  return total_Error;
}

void PID::twiddleTune() {

  // switch to next tunable parameter
  numCycles++;
  if(numCycles == numCyclesCount) {
    paramIndex = (paramIndex+1) % 3;
    best_error = pow(total_Error,2);
    numCycles = 0;
    twiddleStage = 0;
    //dp[paramIndex] = 1.1*dp[paramIndex]; // double the modifier
  }

  if(paramIndex == 1) return; // ignore Ki - don't tune it.

  switch (twiddleStage) {
    case 0:
      std::cout << "HERE IN STAGE ZERO" << std::endl;
      p[paramIndex] += dp[paramIndex];
      transferParams();
      twiddleStage = 1;
      break;
    case 1:
      std::cout << "HERE IN STAGE ONE" << std::endl;
      if (pow(total_Error,2) < best_error) {
        best_error = pow(total_Error,2);
        dp[paramIndex] *= 1.1;
        twiddleStage = 0;
      } else {
        p[paramIndex] -= 2*dp[paramIndex];
        transferParams();
        twiddleStage = 2;
      }
      break;
    case 2:
      std::cout << "HERE IN STAGE TWO" << std::endl;
      if (pow(total_Error,2) < best_error) {
        best_error = pow(total_Error,2);
        dp[paramIndex] *= 1.1;
      } else {
        p[paramIndex] += dp[paramIndex];
        transferParams();
        dp[paramIndex] *= 0.9;
      }
      twiddleStage = 0;
      break;
  }

}

// set parameters to new values
void PID::transferParams() {
  this->Kp = p[0];
  this->Ki = p[1];
  this->Kd = p[2];
}
