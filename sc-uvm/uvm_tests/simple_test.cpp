#include <uvm>
#include "base_test.h"
#include "env.h"
#include "simple_seq.h"

class simple_test : public base_test {
public:

    simple_test(uvm::uvm_component_name name) : 
        base_test(name) {

    }

    UVM_COMPONENT_UTILS(simple_test);


virtual void run_phase(uvm::uvm_phase &phase){
    phase.raise_objection(this);

    UVM_INFO(get_name(), "** UVM TEST STARTED **", uvm::UVM_NONE);

    sc_core::wait(100, sc_core::SC_NS); // Wait a bit for reset, should be done with another reset sequence TODO

    simple_seq seq{"simple_seq"};
    seq.start(tb->ag->sqr);
    seq.wait_for_sequence_state(uvm::UVM_FINISHED);

    // sc_core::wait(15000, sc_core::SC_NS); // Wait a bit for reset, should be done with another reset sequence TODO

    phase.drop_objection(this);

}

};