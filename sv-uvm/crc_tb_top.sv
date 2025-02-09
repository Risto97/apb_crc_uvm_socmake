`timescale 1ns/1ps

`include "apb_pkg.sv"
`include "apb_if.sv"

module crc_tb_top;
    import uvm_pkg::*;
    import apb_pkg::*;
    `include "base_test.svh" 

    apb_if vif();


    apb_crc dut(
        .clk(vif.pclk),
        .rstn(vif.presetn),
        .s_paddr(vif.paddr),
        .s_psel(vif.psel),
        .s_penable(vif.penable),
        .s_pready(vif.pready),
        .s_pwrite(vif.pwrite),
        .s_prdata(vif.prdata),
        .s_pstrb(vif.pstrb),
        .s_pwdata(vif.pwdata),
        .s_pslverr(vif.pslverr)
    );


    initial begin automatic uvm_coreservice_t cs_ = uvm_coreservice_t::get();

      uvm_config_db#(virtual apb_if)::set(cs_.get_root(), "*", "vif", vif);
      // uvm_config_db#(virtual apb_crc)::set(cs_.get_root(), "*", "dut", dut);
      run_test();
    end

    // initial begin
    //   vif.sig_reset <= 1'b1;
    //   vif.sig_clock <= 1'b1;
    //   #51 vif.sig_reset = 1'b0;
    // end
    //
    // //Generate Clock
    // always
    //   #5 vif.sig_clock = ~vif.sig_clock;

endmodule

