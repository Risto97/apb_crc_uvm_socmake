#ifndef _SCOREBOARD_H__
#define _SCOREBOARD_H__

#include <vector>
#include <string>

#include <uvm>

#include "univ_subscriber.h"
#include "uvc_apb.h"
#include "apb_crc_ref.h"

// #include "coverage.h"

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

class scoreboard : public uvm::uvm_scoreboard {
public:
    int verbosity;

    // std::vector<uvc::apb::rw> apb_vec;
    uint32_t apb_wdata;
    sc_core::sc_event apb_e;

    apb_crc_ref ref;
    // sc_core::sc_signal<bool> ref_irq;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> ref_gpio_out;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> ref_gpio_in;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> ref_gpio_dir;
    //
    // sc_core::sc_signal<bool> dut_irq;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> dut_gpio_out;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> dut_gpio_in;
    // sc_core::sc_signal<sc_dt::sc_uint<N_PORTS*16>> dut_gpio_dir;

    tlm_utils::simple_initiator_socket<scoreboard, 32> socket;

    uvm::uvm_analysis_export<uvc::apb::rw> apb_listener_imp;

    void apb_write(const uvc::apb::rw &p);

    uvc::univ_subscriber<uvc::apb::rw, scoreboard, &scoreboard::apb_write>
      *apb_listener;

    // sb_coverage sb_cg;

    scoreboard(uvm::uvm_component_name name): uvm::uvm_scoreboard(name)
        ,ref("ref")
    {}
    UVM_COMPONENT_UTILS(scoreboard);

    // void check_gpio_out();
    // void check_gpio_dir();
    // void check_irq();

    void build_phase(uvm::uvm_phase &phase);
    void connect_phase(uvm::uvm_phase &phase);
    void run_phase(uvm::uvm_phase &phase);
};

#endif

