class apb_driver extends uvm_driver #(apb_rw);

  // The virtual interface used to drive and view HDL signals.
  protected virtual apb_if vif;
    protected apb_rw rsp;

  // Master Id

  // Provide implmentations of virtual methods such as get_type_name and create
  `uvm_component_utils_begin(apb_driver)
  `uvm_component_utils_end

  // new - constructor
  function new (string name, uvm_component parent);
    super.new(name, parent);
    rsp = new();
  endfunction : new

  function void build_phase(uvm_phase phase);
    super.build_phase(phase);
     if(!uvm_config_db#(virtual apb_if)::get(this, "", "vif", vif))
       `uvm_fatal("NOVIF",{"virtual interface must be set for: ",get_full_name(),".vif"});
  endfunction: build_phase

  // run phase
  virtual task run_phase(uvm_phase phase);
    vif.psel = 1'b0;
    vif.penable = 1'b0;
    fork
      get_and_drive();
      drive_rst();
      drive_clk();
    join
  endtask : run_phase

  // get_and_drive 
  virtual protected task get_and_drive();

    @(posedge vif.presetn);
    forever begin
      @(posedge vif.pclk);
      seq_item_port.get_next_item(req);
      // $cast(rsp, req.clone());
      drive_transfer(req);

      seq_item_port.item_done();

      if(req.kind_e == READ) begin
          rsp.set_id_info(req);
          seq_item_port.put_response(rsp);
      end
    end
  endtask : get_and_drive

  // drive_rst 
  virtual protected task drive_rst();
        vif.presetn = 1'b0;

        @(posedge vif.pclk);
        @(posedge vif.pclk);
        @(posedge vif.pclk);

        vif.presetn = 1'b1;
  endtask : drive_rst 

  // drive_clk 
  virtual protected task drive_clk();
    forever begin
        vif.pclk = 1'b1;
        #5;
        vif.pclk = 1'b0;
        #5;
    end
  endtask : drive_clk 

  // drive_transfer
  virtual protected task drive_transfer (input apb_rw req);
    if(req.kind_e == READ) begin

        vif.paddr = req.addr;
        vif.pwrite = 1'b0;
        vif.pstrb = req.strb;
        vif.psel = req.valid;

        @(posedge vif.pclk);
        vif.penable = req.valid;

        do begin
            @(posedge vif.pclk);
        end while(vif.pready === 1'b0);

        rsp.valid = 1'b1;

        rsp.data = vif.prdata;
        rsp.addr = req.addr;
        rsp.kind_e = req.kind_e;

        vif.psel = 1'b0;
        vif.penable = 1'b0;

    end else if(req.kind_e == WRITE) begin
        vif.paddr = req.addr;
        vif.pwdata = req.data;
        vif.pstrb = req.strb;
        vif.pwrite = 1'b1;
        vif.psel = req.valid;

        @(posedge vif.pclk);
        vif.penable = req.valid;

        do begin
            @(posedge vif.pclk);
        end while(vif.pready === 1'b0);

        vif.psel = 1'b0;
        vif.penable = 1'b0;

    end


  endtask : drive_transfer

  // // arbitrate_for_bus
  // virtual protected task arbitrate_for_bus();
  //   // vif.sig_request[master_id] <= 1;
  //   // @(posedge vif.sig_clock iff vif.sig_grant[master_id] === 1);
  //   // vif.sig_request[master_id] <= 0;
  // endtask : arbitrate_for_bus
  //
  // // drive_address_phase
  // virtual protected task drive_address_phase (apb_rw req);
  //   vif.sig_addr <= req.addr;
  //   drive_size(req.size);
  //   drive_read_write(req.read_write);
  //   @(posedge vif.sig_clock);
  //   vif.sig_addr <= 32'bz;
  //   vif.sig_size <= 2'bz;
  //   vif.sig_read <= 1'bz;
  //   vif.sig_write <= 1'bz;  
  // endtask : drive_address_phase
  //
  // // drive_data_phase
  // virtual protected task drive_data_phase (apb_rw req);
  //   bit err;
  //   for(int i = 0; i <= req.size - 1; i ++) begin
  //     if (i == (req.size - 1))
  //       vif.sig_bip <= 0;
  //     else
  //       vif.sig_bip <= 1;
  //     case (req.read_write)
  //       READ    : read_byte(req.data[i], err);
  //       WRITE   : write_byte(req.data[i], err);
  //     endcase
  //   end //for loop
  //   vif.sig_data_out <= 8'bz;
  //   vif.sig_bip <= 1'bz;
  // endtask : drive_data_phase
  //
  // // read_byte
  // virtual protected task read_byte (output bit [7:0] data, output bit error);
  //   vif.rw <= 1'b0;
  //   @(posedge vif.sig_clock iff vif.sig_wait === 0);
  //   data = vif.sig_data;
  // endtask : read_byte
  //
  // // write_byte
  // virtual protected task write_byte (bit[7:0] data, output bit error);
  //   vif.rw <= 1'b1;
  //   vif.sig_data_out <= data;
  //   @(posedge vif.sig_clock iff vif.sig_wait === 0);
  //   vif.rw <= 'h0;
  // endtask : write_byte
  //
  // // drive_size
  // virtual protected task drive_size (int size);
  //   case (size)
  //     1: vif.sig_size <=  2'b00;
  //     2: vif.sig_size <=  2'b01;
  //     4: vif.sig_size <=  2'b10;
  //     8: vif.sig_size <=  2'b11;
  //   endcase
  // endtask : drive_size
  //
  // // drive_read_write            
  // virtual protected task drive_read_write(ubus_read_write_enum rw);
  //   case (rw)
  //     NOP   : begin vif.sig_read <= 0; vif.sig_write <= 0; end
  //     READ  : begin vif.sig_read <= 1; vif.sig_write <= 0; end
  //     WRITE : begin vif.sig_read <= 0; vif.sig_write <= 1; end
  //   endcase
  // endtask : drive_read_write

endclass : apb_driver



