import "DPI-C" function int unsigned  crc_dpi(input int unsigned data, input int unsigned initial_value);

class scoreboard extends uvm_scoreboard;

  uvm_analysis_imp#(apb_rw, scoreboard) item_collected_export;

  protected bit disable_scoreboard = 0;
  int unsigned crc_dpi_data = 0;

  protected int unsigned m_mem_expected[int unsigned];

  // Provide implementations of virtual methods such as get_type_name and create
  `uvm_component_utils_begin(scoreboard)
    `uvm_field_int(disable_scoreboard, UVM_DEFAULT)
  `uvm_component_utils_end

  // new - constructor
  function new (string name, uvm_component parent);
    super.new(name, parent);
  endfunction : new

  //build_phase
  function void build_phase(uvm_phase phase);
    item_collected_export = new("item_collected_export", this);
  endfunction

  // write
  virtual function void write(apb_rw trans);
        if(trans.kind_e == WRITE) begin
              crc_dpi_data = crc_dpi(trans.data, crc_dpi_data);
        end else if(trans.kind_e == READ) begin


            if(crc_dpi_data != trans.data) begin
              `uvm_info(get_type_name(),
                $sformatf("DUT: %h", trans.data), UVM_LOW)

              `uvm_info(get_type_name(),
                $sformatf("REF: %h", crc_dpi_data), UVM_LOW)
              `uvm_error(get_type_name(),
                $sformatf("MISMATCH"))

            end
        end
  endfunction : write

  // // memory_verify
  // protected function void memory_verify(input apb_rw trans);
  //   int unsigned data, exp;
  //   for (int i = 0; i < trans.size; i++) begin
  //     // Check to see if entry in associative array for this address when read
  //     // If so, check that transfer data matches associative array data.
  //     if (m_mem_expected.exists(trans.addr + i)) begin
  //       if (trans.read_write == READ) begin
  //         data = trans.data[i];
  //         `uvm_info(get_type_name(),
  //           $sformatf("%s to existing address...Checking address : %0h with data : %0h", 
  //           trans.read_write.name(), trans.addr, data), UVM_LOW)
  //         assert(m_mem_expected[trans.addr + i] == trans.data[i]) else begin
  //           exp = m_mem_expected[trans.addr + i];
  //           `uvm_error(get_type_name(),
  //             $sformatf("Read data mismatch.  Expected : %0h.  Actual : %0h", 
  //             exp, data))
	 //      sbd_error = 1;
  //         end
  //         num_init_reads++;
  //       end
  //       if (trans.read_write == WRITE) begin
  //         data = trans.data[i];
  //         `uvm_info(get_type_name(),
  //           $sformatf("%s to existing address...Updating address : %0h with data : %0h", 
  //           trans.read_write.name(), trans.addr + i, data), UVM_LOW)
  //         m_mem_expected[trans.addr + i] = trans.data[i];
  //         num_writes++;
  //       end
  //     end
  //     // Check to see if entry in associative array for this address
  //     // If not, update the location regardless if read or write.
  //     else begin
  //       data = trans.data[i];
  //       `uvm_info(get_type_name(),
  //         $sformatf("%s to empty address...Updating address : %0h with data : %0h", 
  //         trans.read_write.name(), trans.addr + i, data), UVM_LOW)
  //       m_mem_expected[trans.addr + i] = trans.data[i];
  //       if(trans.read_write == READ)
  //         num_uninit_reads++;
  //       else if (trans.read_write == WRITE)
  //         num_writes++;
  //     end
  //   end
  // endfunction : memory_verify

  // report_phase
  virtual function void report_phase(uvm_phase phase);
      `uvm_info(get_type_name(),
        $sformatf("Reporting scoreboard information...\n%s", this.sprint()), UVM_LOW)
  endfunction : report_phase

endclass : scoreboard



