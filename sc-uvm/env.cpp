#include <systemc>
#include <uvm>

#include "env.h"

void env::build_phase(uvm::uvm_phase& phase) {

    uvm::uvm_env::build_phase(phase);
    uvm::uvm_config_db_options::turn_on_tracing();

    if(! uvm::uvm_config_db<uvc::apb::Intf*>::get(this, "", "vif", vif))
        UVM_FATAL("NOVIF", "virtual interface must be set for: " + get_full_name() + ".vif");

    if(! uvm::uvm_config_db<Vapb_crc*>::get(this, "", "dut", dut))
        UVM_FATAL("NODUT", "DUT pointer must be set for: " + get_full_name() + ".dut");

    ag = new uvc::apb::agent("ag");
    uvm::uvm_config_db<int>::set(this, "ag", "is_active", uvm::UVM_ACTIVE);
    uvm::uvm_config_db<uvc::apb::mode_t>::set(this, "ag", "mode", uvc::apb::MASTER);
    // uvm::uvm_config_db<uvc::apb::Intf*>::set(this, "ag", "vif", vif);
    uvm::uvm_config_db<uint32_t>::set(this, "ag", "max_retry_count", 20);

    // apb_m_seq = master_sequence::type_id::create("apb_m_seq");

    sb = scoreboard::type_id::create("sb", this);
    assert(sb);
}

void env::connect_phase(uvm::uvm_phase& phase) {
    ag->mon->ap.connect(sb->apb_listener_imp);
}

void env::reset_phase(uvm::uvm_phase& phase) {
    phase.raise_objection(this);
    open_trace("trace.vcd");
    phase.drop_objection(this);
}

void env::report_phase(uvm::uvm_phase& phase) {}

void env::final_phase(uvm::uvm_phase& phase) { close_trace(); }

void env::main_phase(uvm::uvm_phase& phase) {
    phase.raise_objection(this);

    // sc_core::wait(10 * T);

    phase.drop_objection(this);
}

void env::open_trace(const char* vcdname) {
#if (defined TRACE && defined VERILATOR)
    m_trace = new VerilatedVcdSc;
    dut->trace(m_trace, 99);
    m_trace->open("trace.vcd");

    vif->trace(wf);
#endif
}

void env::close_trace(void) {
#ifdef TRACE
    sc_close_vcd_trace_file(wf);
#ifdef VERILATOR
    m_trace->flush();
    m_trace->close();
    m_trace = nullptr;
#endif
#endif
}

