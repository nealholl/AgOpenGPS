void CalcSteeringPID(void) {
  
  //Proportional
  pValue = Kp * steerAngleError *Ko;  

  //if (abs(distanceFromLine) < 15)
  //{
    //Integral
    integrated_error = integrated_error + steerAngleError;
  //}
  //else
  {
    //integrated_error = integrated_error + distanceFromLine/10;    
  }

  if (integrated_error > maxIntErr) integrated_error = maxIntErr;
  if (integrated_error < -maxIntErr) integrated_error = -maxIntErr;

  //once it passes near center zero out the integrator error
  if (steerAngleError > 0) steerCurrentSign = 1;
  else steerCurrentSign = 0;

  //did we cross zero?
  if (steerCurrentSign - steerPrevSign) integrated_error = 0; //zero out the integrator
  steerPrevSign = steerCurrentSign;  //save a copy for next time
  
  iValue = Ki * integrated_error;  
  if (iValue > maxIntegralValue) iValue = maxIntegralValue;
  if (iValue < -maxIntegralValue) iValue = -maxIntegralValue;


  

  //Derivative
  dError = steerAngleError - lastLastError;
  dValue = Kd * (dError) * Ko;
  
  //save history of errors
  lastLastError = lastError;
  lastError = steerAngleError;

  drive = pValue + dValue + iValue;
  pwmDrive = (constrain(drive, -255, 255));

 }
