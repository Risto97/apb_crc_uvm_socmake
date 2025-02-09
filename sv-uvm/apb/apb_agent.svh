class apb_agent extends uvm_agent;


  apb_driver drv;
  uvm_sequencer#(apb_rw) sqr;
  apb_monitor mon;
  protected virtual interface apb_if vif;

  // Provide implementations of virtual methods such as get_type_name and create
  `uvm_component_utils_begin(apb_agent)
  `uvm_component_utils_end

  // new - constructor
  function new (string name, uvm_component parent);
    super.new(name, parent);
  endfunction : new

  // build_phase
  function void build_phase(uvm_phase phase);
    super.build_phase(phase);
    mon = apb_monitor::type_id::create("mon", this);

    if(get_is_active() == UVM_ACTIVE) begin
      sqr = uvm_sequencer#(apb_rw)::type_id::create("apb_sqr", this);
      drv = apb_driver::type_id::create("drv", this);
    end

     if(!uvm_config_db#(virtual apb_if)::get(this, "", "vif", vif))
       `uvm_fatal("NOVIF",{"virtual interface must be set for: ", get_full_name(),".vif"});

  endfunction : build_phase

  // connect_phase
  function void connect_phase(uvm_phase phase);
    if(get_is_active() == UVM_ACTIVE) begin
      drv.seq_item_port.connect(sqr.seq_item_export);
    end
  endfunction : connect_phase

endclass : apb_agent



