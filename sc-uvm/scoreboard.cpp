#include "uvc_apb.h"

#include "scoreboard.h"
#include <cstdint>
#include <sstream>
#include <tlm_core/tlm_2/tlm_generic_payload/tlm_gp.h>

std::array<std::string, 3> stringify_tlm_command = {
    "TLM_READ_COMMAND",
    "TLM_WRITE_COMMAND",
    "TLM_IGNORE_COMMAND"
};

void scoreboard::build_phase(uvm::uvm_phase &phase) {
    uvm::uvm_scoreboard::build_phase(phase);
    uvm::uvm_config_db<uvm_object *>::set(this, "apb_listener", "sb", this);

    apb_listener =
    uvc::univ_subscriber<uvc::apb::rw, scoreboard,
        &scoreboard::apb_write>::type_id::create("apb_listener", this);
    assert(apb_listener);
}

void scoreboard::connect_phase(uvm::uvm_phase &phase) {
    apb_listener_imp.connect(apb_listener->analysis_export);
    socket.bind(ref.socket);
}

void scoreboard::run_phase(uvm::uvm_phase &phase){ 
}

void scoreboard::apb_write(const uvc::apb::rw &p) {
    // sb_cg.sample_cg(p);
    apb_wdata = p.data.to_uint();

    tlm::tlm_generic_payload *trans = new tlm::tlm_generic_payload;
    sc_core::sc_time delay = sc_core::sc_time(10, sc_core::SC_NS);

    tlm::tlm_command cmd = static_cast<tlm::tlm_command>(p.kind_e);

    trans->set_command(cmd);
    trans->set_address(p.addr.to_uint64());
    trans->set_data_ptr(reinterpret_cast<uint8_t *>(&apb_wdata));
    trans->set_data_length(4);
    trans->set_streaming_width(4);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    socket->b_transport(*trans, delay);

    if( trans->is_response_ok() ){
    }
    if( trans->is_response_error() ){
        UVM_FATAL(this->name(), "Error response from reference model");
    }

    if(cmd == tlm::TLM_READ_COMMAND){
        uint8_t  *ptr = trans->get_data_ptr();
        uint32_t rdata = *(uint32_t*)ptr;

        if(rdata != p.data){
            std::stringstream msg;
            msg << "\033[1;31m"; // BOLD RED COLOUR
            msg << "****** MISMATCH *******\n";
            msg << "Command: " << stringify_tlm_command.at(cmd) << "\n";
            msg << "Address: 0x" << std::hex << p.addr << std::endl;
            msg << "## Mismatch Data:\n";
            msg << "    Dut: 0x" << std::hex << p.data.to_uint() << "\n";
            msg << "    Ref: 0x" << std::hex << rdata << std::endl;
            msg << "\033[0m\n";
            
            UVM_ERROR(this->get_name(), "Mismatch between DUT and REF model\n" + msg.str());
        }

    }

    if(verbosity > uvm::UVM_HIGH){
        UVM_INFO(this->get_name(), "apb_write() got item:", uvm::UVM_HIGH);
        p.print();
    }
    // UVM_INFO("PHASE_WRITE: ", p.pri(), uvm::UVM_MEDIUM);
    apb_e.notify();
}

