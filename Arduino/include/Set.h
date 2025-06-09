#ifndef SETDATA_H
#define SETDATA_H

#include <cstddef>

struct RepData {
  float duration;
  float eccentric_duration;
  float concetric_duration;
  float avg_eccentric_force;
  float avg_concentric_force;
  float muscle_imbalance_score;
  float rom;
};

struct SetData {
  size_t reps;
  float avg_duration;
  float avg_eccentric_duration;
  float avg_concentric_duration;
  float avg_eccentric_force;
  float avg_concentric_force;
  float avg_muscle_imbalance_score;
  float avg_rom;
};


class Set {
    public: 
        Set();

        void push_back(RepData rep){
          if(size>25){
            return;
          }
          reps_[size] = rep;
          size++;
        }

        SetData get_stats(){
          return {
            size,
            avg_duration,
            avg_eccentric_duration,
            avg_concentric_duration,
            avg_eccentric_force,
            avg_concentric_force,
            avg_muscle_imbalance_score,
            avg_rom,
          };
        }

    private:
        RepData reps_[25];
        size_t size;
        float avg_duration;
        float avg_eccentric_duration;
        float avg_concentric_duration;
        float avg_eccentric_force;
        float avg_concentric_force;
        float avg_muscle_imbalance_score;
        float avg_rom;
};

#endif