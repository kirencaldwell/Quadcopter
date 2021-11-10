#ifndef GUIDANCE_MODULE_H
#define GUIDANCE_MODULE_H
#include <eigen3/Eigen/Dense>

#include "external/ConcurrentModuleFramework/src/base_module.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Onboard {

class GuidanceModuleData {
  public:
    VectorXd xd;
    VectorXd b1d;
};

// The outline for this file was autogenerated
/* Please provide Module Documentation here

*/
class GuidanceModule : public BaseModule {
  public:

    void Init(std::shared_ptr<ModuleDataCollection> data) override;

  protected:

		GuidanceModuleData _guidance_data;
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

};
} // Onboard

#endif