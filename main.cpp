#include "cartpole.hpp"
#include <random>

#define MAX_ITER 1
#define _MOVIE_ 0

int main(void){
  CartPole env;
  for(int iter = 0; iter < MAX_ITER; iter++){
    double cart_x;
    double cart_v;
    double pole_x;
    double pole_v;
    double reward;
    bool   done;
    std::vector<double> observation;
    std::string input = "data/result.dat";

    observation = env.reset();

#ifdef _MOVIE_
    if(iter == MAX_ITER - 1) env.render(input);
#endif //_MOVIE_

    /* 1 play */
    int time_step;
    for(time_step = 0; time_step < MAX_TIME_STEP; time_step++){
      /* 乱数の準備 */
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_int_distribution<int> which(0, 1);

      /* 行動決定 */
      int action = 0;
      action = which(mt);
      bool flag = false;
      if(time_step % 20 == 0){
        flag = true;
        action = 0;
        if(time_step % 40 == 0){
          flag = true;
          action = 1;
        }
      }

      double reward;
      bool done;
      std::tie(observation, reward, done) = env.step(flag, action);

      /* 動画 */
#ifdef _MOVIE_
      if(iter == MAX_ITER - 1) env.render(input);
#endif //_MOVIE_

#ifndef _MOVIE_
      if(done) break;
#endif //_MOVIE_
      //if(done) break;
    }
    std::cout << "Episode:" << iter << " finished after " << time_step+1 << " timesteps" << std::endl;
  }

  std::cout << "Training finish!" << std::endl;

  return 0;
}
