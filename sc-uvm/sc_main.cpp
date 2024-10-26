#include <systemc>
#include <uvm>
#include <uvc_apb.h>

#include "Vapb_crc.h"

int sc_main(int argc, char **argv) {
#ifdef VERILATOR
    Verilated::commandArgs(argc, argv);
#ifdef TRACE
    Verilated::traceEverOn(true);
#endif
#endif

    // sc_core::sc_time CLK_PERIOD(10, sc_core::SC_NS);
    // sc_core::sc_clock clk("clk", CLK_PERIOD);
    // sc_core::sc_signal<bool> rstn; // TODO move to intf

    uvm::uvm_set_verbosity_level(uvm::UVM_LOW);

    uvc::apb::Intf* vif = new uvc::apb::Intf("vif");
    uvm::uvm_config_db<uvc::apb::Intf*>::set(uvm::uvm_root::get(), "*", "vif", vif);

// DUT instantiation
    Vapb_crc dut("dut");

    dut.clk(vif->pclk);
    dut.rstn(vif->presetn);
    dut.s_penable(vif->penable);
    dut.s_pwrite(vif->pwrite);
    dut.s_paddr(vif->paddr);
    dut.s_psel(vif->psel);
    dut.s_pwdata(vif->pwdata);
    dut.s_pstrb(vif->pstrb);
    dut.s_prdata(vif->prdata);
    dut.s_pready(vif->pready);
    dut.s_pslverr(vif->pslverr);

    uvm::uvm_config_db<Vapb_crc*>::set(uvm::uvm_root::get(), "*", "dut", &dut);

    uvm::run_test("simple_test");

    return 0;
}

