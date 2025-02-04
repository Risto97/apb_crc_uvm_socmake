class apb_monitor extends uvm_monitor;

  protected virtual apb_if vif;

  uvm_analysis_port #(apb_rw) ap;
  protected apb_rw tr;

  // Provide implementations of virtual methods such as get_type_name and create
  `uvm_component_utils_begin(apb_monitor)
  `uvm_component_utils_end

  // new - constructor
  function new (string name, uvm_component parent);
    super.new(name, parent);
    ap = new("ap", this);
    tr = new();
  endfunction : new

  function void build_phase(uvm_phase phase);
    super.build_phase(phase);
    if(!uvm_config_db#(virtual apb_if)::get(this, "", "vif", vif))
       `uvm_fatal("NOVIF",{"virtual interface must be set for: ",get_full_name(),".vif"});
  endfunction: build_phase

  // run phase
  virtual task run_phase(uvm_phase phase);
    run_monitor();
  endtask : run_phase

  // run_monitor
  virtual protected task run_monitor();
    forever begin
        do begin
          @(posedge vif.pclk);
          #1; // TODO hack fix this, zero transactions appear in scoreboard 
        end while(vif.psel === 1'b0 || vif.penable === 1'b0);

        tr.kind_e = vif.pwrite === 1'b1 ? WRITE : READ;
        tr.addr = vif.paddr;
        tr.strb = vif.pstrb;
        tr.slv_err = vif.pslverr;
        tr.valid = 1'b1;

        tr.data = tr.kind_e == READ ? vif.prdata : vif.pwdata;

        ap.write(tr);
    end
  endtask : run_monitor


endclass : apb_monitor



