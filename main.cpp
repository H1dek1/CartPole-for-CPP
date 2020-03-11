#include "cartpole.hpp"
#include <random>

#define MAX_ITER 20

int main(void){
  CartPole env;
  for(int iter = 0; iter < MAX_ITER; iter++){
    double cart_x;
    double cart_v;
    double pole_x;
    double pole_v;
    double reward;
    bool   done;

    std::tie(cart_x, cart_v, pole_x, pole_v) = env.reset();

#ifdef _MOVIE_
    if(iter == MAX_ITER - 1) env.render();
#endif //_MOVIE_

    /* 1 play */
    int time_step;
    for(time_step = 0; time_step < MAX_TIME_STEP; time_step++){
      /* 乱数の準備 */
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_int_distribution<int> which(0, 1);

      /* 行動決定 */
      int action;
      action = which(mt);

      std::tie(cart_x, cart_v, pole_x, pole_v, reward, done) = env.step(action);

      /* 動画 */
#ifdef _MOVIE_
      if(iter == MAX_ITER - 1) env.render();
#endif //_MOVIE_

#ifndef _MOVIE_
      if(done) break;
#endif //_MOVIE_
    }
    std::cout << "Episode:" << iter << " finished after " << time_step+1 << " timesteps" << std::endl;
  }

  std::cout << "Training finish!" << std::endl;

  return 0;
}
