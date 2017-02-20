#include "Target.h"


nlohmann::json Target::to_json() const {
   nlohmann::json  j = {{getTag(), {
            {"type", getType()},
            {"path", getPath()}
          }
    }};
    return j;
}


