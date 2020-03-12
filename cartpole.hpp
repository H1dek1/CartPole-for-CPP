#ifndef __CARTPOLE__
#define __CARTPOLE__

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <tuple>
#include <random>

#define MAX_TIME_STEP 200
#define DT            5.0e-2

#define G 9.8
#define L 1.0
#define M_POLE 1.0
#define M_CART 4.0

#define CART_X_MAX 2.4
#define POLE_X_MAX 0.5

#define PUSH_LEFT        0
#define PUSH_RIGHT       1
#define FORCE_LEFT      -50.0
#define FORCE_RIGHT      50.0

#define NUM_STATES 4
#define NUM_ACTIONS 2
#define CART_Y 0.0

class CartPole
{
  private:
    int num_states;
    int num_actions;

  private:
    double cart_x;
    double cart_y;
    double cart_v;
    double cart_a;

    double pole_x;
    double pole_v;
    double pole_a;

    int    time_step;
    double time;
    double reward;
    bool   done;

  private:
    std::string movie_name;
    std::ofstream fout;

  public:
    CartPole()
    {
      num_states = NUM_STATES;
      num_actions = NUM_ACTIONS;
      cart_y = CART_Y;
    }

    ~CartPole()
    {
    }

    int observation_space()
    {
      return num_states;
    }

    int action_space()
    {
      return num_actions;
    }

    std::tuple<double, double, double, double> reset()
    {
      time_step = 0;
    
      std::random_device rdm;
      std::mt19937 mst(rdm());
      std::uniform_real_distribution<double> range(-0.05, 0.05);
    
      cart_x = range(mst);
      cart_v = range(mst);
      pole_x = range(mst);
      pole_v = range(mst);
    
      reward = 0.0;
      done   = false;
    
      return std::forward_as_tuple(cart_x, cart_v, pole_x, pole_v);
    }

    bool render()
    {
      movie_name = "data/result.dat";
      fout.open(movie_name, std::ios::app);
      
      if(!fout){
        std::cout << "File open failed!" << std::endl;
        return false;
      }
    
      fout << time_step << " " << cart_x << " " << cart_y << " " << pole_x << std::endl;
      fout << std::endl;
    
      //std::cout << "result.dat created !" << std::endl;
      fout.close();
      return true;
    }

//std::tuple<double, double, double, double, double, bool> CartPole::step(int action)
    std::tuple<std::vector<double>, double, bool> step(int action)
    {
      reward = 0.0;
      time_step += 1;
    
      double force = 0.0;
    
      if(action == PUSH_RIGHT) force = FORCE_RIGHT;
      else if(action == PUSH_LEFT) force = FORCE_LEFT;
      else std::cout << "ERROR!" << std::endl;
    
      double numerator   = force - M_POLE * G * sin(pole_x) * cos(pole_x) + M_POLE * L * pole_v * pole_v * sin(pole_x);
      double denominator = M_POLE * sin(pole_x) * sin(pole_x) + M_CART;
    
      cart_a = numerator / denominator;
    
      cart_v += cart_a * DT;
      cart_x += cart_v * DT;
    
      pole_a = G / L * sin(pole_x) - cart_a / L * cos(pole_x);
      pole_v += pole_a * DT;
      pole_x += pole_v * DT;
    
      if(std::fabs(cart_x) > CART_X_MAX) done = true;
      if(std::fabs(pole_x) > POLE_X_MAX) done = true;
    
      if(done == false) reward = 1;
    
      //return std::forward_as_tuple(cart_x, cart_v, pole_x, pole_v, reward, done);
      std::vector<double> tmp = {cart_x, cart_v, pole_x, pole_v};
    
      return std::forward_as_tuple(tmp, reward, done);
    }
};
#endif //__CARTPOLE__
