`include "scoreboard.svh"
// `include "apb_master_seq_lib.sv"
// `include "apb_example_master_seq_lib.sv"
// `include "apb_slave_seq_lib.sv"

`include "simple_sequence.svh"

class env extends uvm_env;

  // Provide implementations of virtual methods such as get_type_name and create
  `uvm_component_utils(env)

  // apb environment
  apb_agent ag;
  protected virtual interface apb_if vif;

  scoreboard sb;

  // new
  function new (string name, uvm_component parent=null);
    super.new(name, parent);
  endfunction : new

  // build_phase
  virtual function void build_phase(uvm_phase phase);
    super.build_phase(phase);

     if(!uvm_config_db#(virtual apb_if)::get(this, "", "vif", vif))
       `uvm_fatal("NOVIF",{"virtual interface must be set for: ",get_full_name(),".vif"});

    uvm_config_db #(int)::set(this, "env.ag.apb_sqr", "do_not_randomize", 1);

    sb = scoreboard::type_id::create("sb", this);

    // set_config_int("ag", "is_active", UVM_ACTIVE);
    // uvm_config_db#(int)::set(this,"ag", 
			 //       "num_slaves", 1);
    
    ag = apb_agent::type_id::create("ag", this);
  endfunction : build_phase

  function void connect_phase(uvm_phase phase);
    // Connect slave0 monitor to scoreboard
    ag.mon.ap.connect(sb.item_collected_export);
  endfunction : connect_phase

  function void end_of_elaboration_phase(uvm_phase phase);
    // Set up slave address map for ag (basic default)
    // ag.set_slave_address_map("slaves[0]", 0, 16'hffff);
  endfunction : end_of_elaboration_phase

endclass : env



