<h1>PID Reflection</h1>

###Describe the effect each of the P, I, D components had in your implementation:


The P component is the proportional component (Kp * p_error) which controls the intensity of the correction steering angle. When I chose a higher Kp ratio then the car would turn more aggressively back to center.

The I component is the integral component (Ki * i_error) this is based on the rolling sum of all iterations of CTE error. The component is able to correct for bias or consistent deviation over time. A higher Ki ratio will minimize the effect of a drift if you had one.

The D component is the derivative component (Kd * d_error). The d_error tracks the difference in CTE between i and i+1 iterations. Tuning the Kd ratio has an effect on the oscillations of your correction over time. The higher the more strength you put into the Kd, the more dampened the overshoot of across center you'll have.

###Describe how the final hyperparameters were chosen:

To chose my parameters I did some broad guess work to get a starting poi nt. I realized that since it was a computer simulation of a car I would expect there to be no issues with tire alignment, or wind, or other bias concerns. So I decided to set the I-component to 0 and ignore it. For the P and D components I made them negative since I wanted the angle steering to be a correction based on the total_error. So to get the car to steer back they should be negative. I started guessing with -0.5 and -0.75 values for Kp and Kd. This got my car to drive fairly well. I decided to expriment with a twiddle algorithm which was challenging because there was no obvious way to collect recorded data and adjust parameters. In the end, I used a timeframe for tuning each parameter that was based on a count of iterations (numCyclesCount on line 28). Using this it would tune a given parameter for a short duration then move on to the next parameter for the same duration. Because the track was so varied and twiddling such short timeframes I made the dp value very low so only small tunes would happen. This worked a little bit for fine tuning a fairly good estimate of parameters, but was very poor for a general solution or tuning parameters from 0 or a poor starting point.

With guess and check and some minor twiddle tuning I chose Kp = -0.24, Ki = 0, Kd = -1.4 for my final parameters. The car drives quite well and is fairly smooth for most of the track. A video of my car driving a lap can be seen here.

https://www.youtube.com/watch?v=Awl6DFL9FhU&t=2s