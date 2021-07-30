using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern drivetrain Drivetrain;
extern motor Lifter;
extern motor Loader;
extern controller Controller1;
extern signature CAM__APPLE;
extern signature CAM__AVACADO;
extern signature CAM__LEMON;
extern signature CAM__SIG_4;
extern signature CAM__SIG_5;
extern signature CAM__SIG_6;
extern signature CAM__SIG_7;
extern vision CAM;
extern sonar Basket;
extern pot CountFlap;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );