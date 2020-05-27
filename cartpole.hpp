#ifndef CARTPOLE_H
#define CARTPOLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <tuple>
#include <random>
#include <unistd.h>

class CartPole
{
  private:
    int num_states;
    int num_actions;
    FILE* gp;

  private:
    const double DT = 5.0e-2;

    const double L = 1.0;
    const double G = 9.8;
    const double M_POLE = 0.5;
    const double M_CART = 8.0;
    const double CART_Y = 0.0;

    const double CART_X_MAX = 2.4;
    const double POLE_X_MAX = 0.73;

    const double PUSH_LEFT   =  0;
    const double PUSH_RIGHT  =  1;
    const double FORCE_LEFT  = -100.0;
    const double FORCE_RIGHT =  100.0;

    const int NUM_STATES  = 4;
    const int NUM_ACTIONS = 2;

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
      if(gp!=NULL){
        pclose(gp);
      }
    }

    int observation_space()
    {
      return num_states;
    }

    int action_space()
    {
      return num_actions;
    }

    std::vector<double> reset()
    {
      if(gp!=NULL){
        std::cout << "gnuplot reset" << std::endl;
        pclose(gp);
      }
      gp = popen("gnuplot", "w");
      fprintf(gp, "set xrange [-3.0:3.0]\n");
      fprintf(gp, "set yrange [-2.5:2.5]\n");
      fprintf(gp, "set xzeroaxis\n");
      fprintf(gp, "set noytics\n");
      fprintf(gp, "set size ratio -1\n");
      fprintf(gp, "set nokey\n");
      fprintf(gp, "set arrow from -3.0, 0.0 to 3.0, 0.0 nohead lw 1 lc rgb 'black'\n");

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
    
      std::vector<double> observation = {cart_x, cart_v, pole_x, pole_v};
      return observation;
    }

    bool render()
    {
      fprintf(gp, "plot \"+\" using(%lf):(%lf) with points pointsize 7 pointtype 5 lc rgb \"black\", ", cart_x, cart_y);
      fprintf(gp, "\"+\" using(%lf):(%lf):(%lf):(%lf) with vectors nohead lw 10 lc rgb \"orange\", ", cart_x, cart_y, (2*L*sin(pole_x)), (2*L*cos(pole_x)));
      fprintf(gp, "\"+\" using(%lf):(%lf) with points pointsize 2 pointtype 7 lc rgb \"gray\"\n", cart_x, cart_y);
      fflush(gp);
      usleep(DT*1000);
      return true;
    }

    std::tuple<std::vector<double>, double, bool> step(bool flag, int action)
    {
      reward = 0.0;
      time_step += 1;
    
      double force = 0.0;
    
      if(flag ==true){
        if(action == PUSH_RIGHT) force = FORCE_RIGHT;
        else if(action == PUSH_LEFT) force = FORCE_LEFT;
        else std::cout << "Invalid action!" << std::endl;
      }
    
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
    
      std::vector<double> observation = {cart_x, cart_v, pole_x, pole_v};

      std::tuple<std::vector<double>, double, bool> send = {observation, reward, done};
    
      return send;
    }
};
#endif //CARTPOLE_H
