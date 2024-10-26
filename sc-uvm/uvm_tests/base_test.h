#ifndef _BASE_TEST_H__
#define _BASE_TEST_H__

#include <uvm>
#include "env.h"

class base_test : public uvm::uvm_test {
public:
    env *tb;

    base_test( uvm::uvm_component_name name = "base_test") : 
        uvm::uvm_test(name), 
        tb()
    {

    }

    UVM_COMPONENT_UTILS(base_test);


    virtual void build_phase(uvm::uvm_phase &phase){
        uvm::uvm_test::build_phase(phase);

        tb = env::type_id::create("env", this);
        assert(tb);

    }

    virtual void run_phase(uvm::uvm_phase &phase){
        phase.raise_objection(this);

        UVM_FATAL(get_name(), "Tests base_test is not meant to be run");

        phase.drop_objection(this);

    }

};

#endif


