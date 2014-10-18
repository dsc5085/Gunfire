#include <string>

class IProfilerOutputHandler
{
public:
  virtual void BeginOutput(float tTime)=0;
  virtual void Sample(float fMin, float fAvg, float fMax, float tAvg, 
                      int callCount, std::string name, int parentCount)=0;
  virtual void EndOutput()=0;
};