#ifndef _ENV_H__
#define _ENV_H__

#include <Vapb_crc.h>
#include <systemc>
#include <uvm>

#if defined (VERILATOR) && defined (TRACE)
#include "verilated_vcd_sc.h"
#endif

#include "scoreboard.h"

#include <uvc_apb.h>

class env : public uvm::uvm_env {
public:
#ifdef TRACE
#ifdef VERILATOR 
    VerilatedVcdSc* m_trace;
#endif
    sc_core::sc_trace_file* wf = sc_core::sc_create_vcd_trace_file("sc_trace");
#endif

    uvc::apb::Intf* vif;
    Vapb_crc *dut;

    uvc::apb::agent* ag;

    scoreboard *sb;

    UVM_COMPONENT_UTILS(env);

    env(uvm::uvm_component_name name)
        : uvm::uvm_env(name) {}

    void build_phase(uvm::uvm_phase& phase);
    void connect_phase(uvm::uvm_phase& phase);
    void reset_phase(uvm::uvm_phase& phase);
    virtual void main_phase(uvm::uvm_phase& phase);
    void report_phase(uvm::uvm_phase &phase);
    void final_phase(uvm::uvm_phase& phase);

    virtual void open_trace(const char* vcdname);
    virtual void close_trace(void);
};

#endif

