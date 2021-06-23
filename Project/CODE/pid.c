#include "pid.h"

float pid_solve(pid_param_t *pid, float error)
{
  
    pid->out_d = pid->kd * (error - pid->out_p);
    
    pid->out_p = pid->kp * error;
    
    pid->out_i += error;
    pid->out_i = MINMAX(pid->ki * pid->out_i, -pid->i_max, pid->i_max);

    return pid->out_p + pid->out_i + pid->out_d;
}


float increment_pid_solve(pid_param_t *pid, float error)
{
  
    pid->out_d = MINMAX(pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error), -pid->d_max, pid->d_max);
    
    pid->out_p = MINMAX(pid->kp * (error - pid->pre_error), -pid->p_max, pid->p_max);
    
    pid->out_i = MINMAX(pid->ki * error, -pid->i_max, pid->i_max);
    
    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;
    
    return pid->out_p + pid->out_i + pid->out_d;
}
