
#pragma once

#include <JuceHeader.h>
#include "src/dfxplugin.h"

namespace destroyfx::bufferoverride {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/brokenfft.h"

//#include "src/bufferoverrideformalities.cpp"
#include "src/brokenfft.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_NODE(BufferOverride);

}  // namespace project
