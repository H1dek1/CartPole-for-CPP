#ifndef __CARTPOLE__
#define __CARTPOLE__

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <tuple>

#define MAX_TIME_STEP 100
#define DT            1.0e-2

#define G 9.8
#define L 1.0
#define M_POLE 2.0
#define M_CART 1.0

#define CART_X_MAX 2.4
#define POLE_X_MAX 0.5

#define PUSH_LEFT        0
#define PUSH_RIGHT       1
#define FORCE_LEFT      -20.0
#define FORCE_RIGHT      20.0

class CartPole
{
  private:
    double cart_x;
    const double cart_y = 0.0;
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
    CartPole();
    ~CartPole();

  public:
    /* 初期化 */
    std::tuple<double, double, double, double> reset();
    /* 記録、動画に出力 */
    bool render(std::string episode_name);
    /* 実行 */
    std::tuple<double, double, double, double, double, bool> step(int action);
};

CartPole::CartPole()
{
}

CartPole::~CartPole()
{
}

std::tuple<double, double, double, double> CartPole::reset()
{
  time_step = 0;

  cart_x = 0.0;
  cart_v = 0.0;
  pole_x = 0.75 * M_PI;
  pole_v = 0.0;

  reward = 0.0;
  done   = false;

  return std::forward_as_tuple(cart_x, cart_v, pole_x, pole_v);
}

bool CartPole::render(std::string episode_name)
{
  movie_name = "data/" + episode_name + ".dat";
  fout.open(movie_name, std::ios::app);
  
  if(!fout){
    std::cout << "File open failed!" << std::endl;
    return false;
  }

  fout << time_step << " " << cart_x << " " << cart_y << " " << pole_x << std::endl;
  fout << std::endl;

  std::cout << "File: " << episode_name << " updated !" << std::endl;
  fout.close();
  return true;
}

std::tuple<double, double, double, double, double, bool> CartPole::step(int action)
{
  reward = 0.0;
  time_step += 1;

  double force;

  if(action == PUSH_RIGHT) force = FORCE_RIGHT;
  else if(action == PUSH_LEFT) force = FORCE_LEFT;
  else std::cout << "ERROR!" << std::endl;

  force = 0.0;

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

  return std::forward_as_tuple(cart_x, cart_v, pole_x, pole_v, reward, done);

}

#endif //__CARTPOLE__
