#include "pid.h"

float pid_solve(pid_param_t *pid, float error)
{
  
    pid->out_d = error - pid->out_p;
    
    pid->out_p = error;
    
    pid->out_i += error;
    if(pid->ki != 0) pid->out_i = MINMAX(pid->out_i, -pid->i_max / pid->ki, pid->i_max / pid->ki);

    return pid->kp * pid->out_p + pid->ki * pid->out_i + pid->kd * pid->out_d;
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


int BangBang_error = 9 , BangBang_output = 15000;  //偏差大，BangBang

int offline_error = 2;  
float offline_k  = 0.4 , online_K = 1.14;

int mid_error = 6;

float expert_pid_solve(pid_param_t *pid, float error)
{
    float expert_out;
    pid -> error = error;

    
    //BangBang
    if(error>BangBang_error || error<-BangBang_error)
    {
      expert_out =  (error > 0) ? BangBang_output : (-BangBang_output);
    }
    //误差较小,调小比例
    else if(error< offline_error && error> -offline_error)
    {
       pid->out_p = offline_k * pid->kp  * (error - pid->pre_error);
      
       pid->out_i = offline_k * pid->ki / 5 * error;
        
       expert_out = MINMAX(pid->out_p, -pid->p_max, pid->p_max)
                   + MINMAX(pid->out_i, -pid->i_max, pid->i_max);
    }
    
    //中等偏差
    else
    {
      //偏差在朝向偏差绝对值增大的方向变化，或者偏差为某一固定值
      if(error * (error - pid->pre_error) > 0 || (error - pid->pre_error) == 0)
      {
        
          if(error > mid_error || error < mid_error)
          {
            pid->out_d = online_K * pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
            pid->out_p = online_K * pid->kp * (error - pid->pre_error);
            pid->out_i = online_K * pid->ki * error;
            
            expert_out = MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
                     +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
                     +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);
            
          }
        
        //偏差是向绝对值增大的方向变化，但是偏差绝对值本身并不是很大
        else if(error <= mid_error && error >= -mid_error)
        {
          pid->out_d = pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
          pid->out_p = pid->kp * (error - pid->pre_error);
          pid->out_i = pid->ki * error;
          
         expert_out = MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
                   +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
                   +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);

        }
      }
      //说明偏差的绝对值向减小的方向变化，或者已经达到平衡状态，此时保持控制器输出不变即可
      else if(error * (error - pid->pre_error) < 0 && 
               ((error - pid->pre_error) * (pid->pre_error - pid->pre_pre_error) > 0 || error == 0))
     {
        expert_out = 0;
      }
      //偏差处于极限状态
      else if(error * (error - pid->pre_error) < 0 && 
               ((error - pid->pre_error) * (pid->pre_error - pid->pre_pre_error) < 0))
      {
         if(error> mid_error || error< - mid_error)
         {
           pid->out_d = online_K * pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
            pid->out_p = online_K * pid->kp * (error - pid->pre_error);
            pid->out_i = online_K * pid->ki * error;
            
            expert_out = MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
                     +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
                     +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);         
         }
         else
         {
             pid->out_d = pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
             pid->out_p = pid->kp * (error - pid->pre_error);
             pid->out_i = pid->ki * error;
          
             expert_out = MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
                       +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
                       +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);
           
          }
      
      }
    
    }
    
    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;
    
    return expert_out;
}






float change_kib = 4;

//变积分PID，e大i小
float changable_pid_solve(pid_param_t *pid, float error)
{

    pid->out_d = pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
    
    pid->out_p = pid->kp * (error - pid->pre_error);
    
    float ki_index = pid->ki;
    
    if (error >1  &&  pid->pre_error>1)
    {
        ki_index = (pid->ki) - (pid->ki) / (1 + exp(change_kib - 0.2 * fabs(error)));    //变积分控制
    }
    
    pid->out_i = ki_index * error;
    
    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;
    
   return MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
         +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
         +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);
}

float bangbang_out = 0;
float bangbang_pid_solve(pid_param_t *pid, float error)
{
    float BangBang_output = 15000, BangBang_error = 8;
    pid -> error = error;

    //BangBang
    if(error>BangBang_error || error<-BangBang_error)
    {
       bangbang_out =  (error > 0) ? BangBang_output : (-BangBang_output);
    }
    else
    {
          pid->out_d = pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
    
          pid->out_p = pid->kp * (error - pid->pre_error);
          
          pid->out_i = pid->ki * error;
          
          bangbang_out = MINMAX(pid->out_p,  -pid->p_max, pid->p_max)
                       +  MINMAX(pid->out_i, -pid->i_max, pid->i_max)
                       +  MINMAX(pid->out_d, -pid->d_max, pid->d_max);

    }
    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;
    
    return bangbang_out;
}


