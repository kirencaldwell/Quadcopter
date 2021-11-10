#ifndef NAVIGATION_MODULE_H
#define NAVIGATION_MODULE_H

#include "src/base_module.h"

namespace Onboard {

class NavigationModuleData {
  public:
    VectorXd x;
    VectorXd v;
    MatrixXd R;
    VectorXd W;
};

// The outline for this file was autogenerated
/* Please provide Module Documentation here

*/
class NavigationModule : public BaseModule {
  public:

    void Init(std::shared_ptr<ModuleDataCollection> data) override;

  protected:

		NavigationModuleData _navigation_data;
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

};
}

#endif