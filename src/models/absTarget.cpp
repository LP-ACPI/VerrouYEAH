#include "absTarget.h"

using json=nlohmann::json;

 int AbsTarget::counter = 0;

 AbsTarget::AbsTarget(const AbsTarget &target)
      :  targetTag(target.getPath()),
          targetPath(target.getPath()),
          targetType(target.getType())
 {}

json& operator <<(json &j, const AbsTarget &target){
     j = target.to_json();
    return j;
}
