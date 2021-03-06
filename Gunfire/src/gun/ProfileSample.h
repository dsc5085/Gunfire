#define MAX_PROFILER_SAMPLES 50

#include <string>
#include <assert.h>
#include <SFML\Graphics.hpp>

#include "ProfilerOutputHandler.h"

class ProfileSample
{
public:
  ProfileSample(std::string sampleName);
  ~ProfileSample();

  static void Output();

  static void ResetSample(std::string sampleName);
  static void ResetAll();

  static IProfilerOutputHandler *outputHandler;

protected:
  //index into the array of samples
  int iSampleIndex;
  int iParentIndex;

  inline float GetTime()
  {
	  time += clock.getElapsedTime().asSeconds();
	  return time;
  }

  static struct profileSample
  {
    profileSample()
    {
      bIsValid=false; 
      dataCount=0;
      averagePc=minPc=maxPc=-1;
    }

    bool bIsValid;    //whether or not this sample is valid to be used
    bool bIsOpen;     //is this sample currently being profiled?
    unsigned int callCount; //number of times this sample has been executed, this frame
    std::string name; //name of the sample
    
    float startTime;  //starting time on the clock, in seconds
    float totalTime;  //total time recorded across all executions of this sample, this frame
    float childTime;  //total time taken by children of this sample, this frame

    int parentCount;  //number of parents this sample has (useful for neat indenting)

    float averagePc;  //average percentage of game loop time taken up
    float minPc;      //minimum percentage of game loop time taken up
    float maxPc;      //maximum percentage of game loop time taken up
    unsigned long dataCount; //number of times values have been stored since
                             //sample creation/reset
  } samples[MAX_PROFILER_SAMPLES];
  static sf::Clock clock;
  static float time;
  static bool bProfilerIsRunning;
  static int lastOpenedSample;
  static int openSampleCount;
  static float rootBegin, rootEnd;
};