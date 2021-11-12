#ifndef NAVIGATION_MODULE_H
#define NAVIGATION_MODULE_H

#include "src/base_module.h"

namespace Onboard {

// The outline for this file was autogenerated
/* Please provide Module Documentation here

*/
class NavigationModule : public BaseModule {
  public:
    NavigationModule();

  protected:

    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

};
}

#endif