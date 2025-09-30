#include "Soundpipe/h/soundpipe.h"
#include "Soundpipe/h/granule.h"

namespace scriptnode {

struct GranuleNode : public hise::dsp::Processor
{
    // …
};

REGISTER_PROCESSOR(GranuleNode, "fx.granule");

}
