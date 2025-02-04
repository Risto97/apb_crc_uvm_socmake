`include "env.sv"

class base_test extends uvm_test;

    `uvm_component_utils(base_test)

    env tb;

    function new(string name = "base_test", uvm_component parent=null);
        super.new(name,parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        tb = env::type_id::create("env", this);
    endfunction : build_phase

    task run_phase(uvm_phase phase);
        phase.raise_objection(this);
      `uvm_info("+++++++++++++:", "IT SHOULD RUN HERE", UVM_LOW);
        phase.phase_done.set_drain_time(this, 1000000);
        wait(1us);
        phase.drop_objection(this);
    endtask : run_phase

endclass : base_test



class simple_test extends base_test;

  `uvm_component_utils(simple_test)

  function new(string name = "simple_test", uvm_component parent=null);
    super.new(name,parent);
  endfunction : new

  virtual function void build_phase(uvm_phase phase);
  begin
      `uvm_info("+++++++++++++:", "HELLLOOOOO", UVM_LOW);
    uvm_config_db#(uvm_object_wrapper)::set(this,
		    "env.ag.apb_sqr.run_phase", 
			       "default_sequence",
				simple_sequence::type_id::get());
    // uvm_config_db#(uvm_object_wrapper)::set(this,
		  //   "ubus_example_tb0.ubus0.slaves[0].sequencer.run_phase", 
			 //       "default_sequence",
				// slave_memory_seq::type_id::get());
    // Create the tb
    super.build_phase(phase);
  end
  endfunction : build_phase

  virtual function void end_of_elaboration_phase(uvm_phase phase);
  begin
    // uvm_top.print_topology();

  end
  endfunction : end_of_elaboration_phase

endclass : simple_test
