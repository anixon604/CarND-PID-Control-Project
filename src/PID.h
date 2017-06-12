#ifndef PID_H
#define PID_H

#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double best_error;
  double total_Error;

  int numCycles;
  int numCyclesCount;
  int paramIndex;
  bool twiddleInit;
  bool twiddle;
  int twiddleStage;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  std::vector<double> p;
  std::vector<double> dp;

  bool subTwiddleFlag;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void twiddleTune();

  void transferParams();

};

#endif /* PID_H */
