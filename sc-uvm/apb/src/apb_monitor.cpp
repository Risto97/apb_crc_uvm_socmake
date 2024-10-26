// #include "sct_assert.h"
#include <string>
#include <systemc>
#include <uvm>

#include "apb_monitor.h"
#include "apb_rw.h"
#include "apb_if.h"
#include "apb_agent.h"

namespace uvc::apb{
    template <class Type>
    inline bool check_onehot(Type bits)
    {
        return bits && !(bits & (bits-1));
    }

    template <class Type>
    inline bool check_onehot_or_zero(Type bits)
    {
        if(bits == 0)
            return true;
        else
            return check_onehot(bits);
    }

    monitor::monitor(uvm::uvm_component_name name) :
        uvm::uvm_monitor(name),
        sigs(nullptr)
    {}

    void monitor::build_phase(uvm::uvm_phase & phase)
    {
        uvm::uvm_monitor::build_phase(phase);

        agent* ag = dynamic_cast<agent*>(get_parent());
        if (ag) {
            sigs = ag->vif;
        }
        else {
            if (!uvm::uvm_config_db<Intf*>::get(this, "", "vif", sigs)) {
                UVM_FATAL("APB/MON/NOVIF", "No virtual interface specified for this monitor instance");
            }
        }
    }

    void monitor::connect_phase(uvm::uvm_phase & phase){
    }

    void monitor::run_monitor(){
        rw* tr;
        tr = rw::type_id::create("tr", this);
        while (1) {
            do{
                sc_core::wait(this->sigs->pclk.posedge_event());
            }
            while (sigs->psel == 0 || sigs->penable == 0);

            tr->kind_e = (sigs->pwrite == 1) ? WRITE : READ;
            tr->addr = sigs->paddr;
            tr->strb = sigs->pstrb;
            tr->slv_err = sigs->pslverr;
            tr->valid = true;

            tr->data = (tr->kind_e == READ) ? sigs->prdata : sigs->pwdata;
            ap.write(*tr);
        }

    }

    void monitor::run_phase(uvm::uvm_phase & phase)
    {
        run_monitor();
    }
}
