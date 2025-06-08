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
};

struct SetData {
  size_t reps;
  float avg_duration;
  float avg_eccentric_duration;
  float avg_concentric_duration;
  float avg_eccentric_force;
  float avg_concetric_force;
  float avg_muscle_imbalance_score;
};


class Set {
    public: 
        Set();

        void push_back(RepData rep);

        SetData get_stats();

    private:
        RepData reps_[25];
        size_t size;
        float avg_duration;
        float avg_eccentric_duration;
        float avg_concentric_duration;
        float avg_eccentric_force;
        float avg_concetric_force;
        float avg_muscle_imbalance_score;
};

#endif