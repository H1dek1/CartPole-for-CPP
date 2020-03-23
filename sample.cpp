#include "cartpole.hpp"
#include <random>

#define MAX_ITER 1
#define _MOVIE_ 0

int main(void){
  CartPole env;
  double reward;
  bool   done;
  std::vector<double> observation;
  std::string input = "data/result.dat";

  for(int iter = 0; iter < MAX_ITER; iter++){
    observation = env.reset();

    if(iter == MAX_ITER - 1) env.render(input);

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

      double reward;
      bool done;
      std::tie(observation, reward, done) = env.step(true, action);

      /* 動画 */
      if(iter == MAX_ITER - 1) env.render(input);

#ifndef _MOVIE_
      if(done) break;
#endif //_MOVIE_
    }
    std::cout << "Episode:" << iter << " finished after " << time_step+1 << " timesteps" << std::endl;
  }

  std::cout << "Training finish!" << std::endl;

  return 0;
}
