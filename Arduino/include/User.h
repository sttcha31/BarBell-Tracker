#ifndef USER_H
#define USER_H

struct RepROM {
    float full;
    float partial; 
};

enum Exercise {
    BenchPress = 0,
    BackSquat = 1,
    DeadLift = 2,
    PowerClean = 3,
};

class User {
    private:
        char* name_;
        RepROM exercise_to_rom_[5];
    public:
        void set_ROM(Exercise exercise, RepROM ROM);
        RepROM get_ROM(Exercise exercise) const;

};

#endif