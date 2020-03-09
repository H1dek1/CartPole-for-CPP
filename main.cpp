#include "cartpole.hpp"

int main(void){
  std::cout << "Hello" << std::endl;

  CartPole env;
  for(int i = 0; i < 1; i++){

    double cart_x;
    double cart_v;
    double pole_x;
    double pole_v;
    double reward;
    bool   done;

    std::tie(cart_x, cart_v, pole_x, pole_v) = env.reset();
    for(int t = 0; t < 2000; t++){
      int action;
      std::string filename = "episode_" + std::to_string(i);
      env.render(filename);
      if((t % 2) == 0) action = 0;
      else             action = 1;

      std::tie(cart_x, cart_v, pole_x, pole_v, reward, done) = env.step(action);

      if(done){
        std::cout << "Episode" << i << " finished after " << t+1 << " timesteps" << std::endl;
        //break;
      }
    }
  }

  return 0;
}
