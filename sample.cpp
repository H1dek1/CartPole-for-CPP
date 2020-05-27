#include "cartpole.hpp"
#include <random>

int main(void){
  const double MAX_ITER = 5;
  const bool   ANIM = true;

  CartPole env;
  double reward;
  bool   done;
  std::vector<double> observation;

  for(int iter = 0; iter < MAX_ITER; iter++){
    observation = env.reset();

    if(ANIM) if(iter == MAX_ITER - 1) env.render();

    /* 1 episode */
    int time_step;
    for(time_step = 0; time_step < 200; time_step++){
      /* random */
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_int_distribution<int> which(0, 1);

      /* decide action */
      int action = which(mt);

      std::tie(observation, reward, done) = env.step(true, action);

      /* animation */
      if(ANIM) if(iter == MAX_ITER - 1) env.render();

      if(done) break;
    }
    std::cout << "Episode:" << iter << " finished after " << time_step+1 << " timesteps" << std::endl;
  }

  std::cout << "Training finish!" << std::endl;

  return 0;
}
