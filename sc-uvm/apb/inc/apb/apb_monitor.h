#ifndef APB_MONITOR_H_
#define APB_MONITOR_H_

#include <systemc>
#include <uvm>

#include "apb_if.h"
#include "apb_rw.h"

namespace uvc::apb{
    class monitor : public uvm::uvm_monitor
    {
        public:
            Intf* sigs;

            uvm::uvm_analysis_port<rw> ap;

            UVM_COMPONENT_UTILS(monitor);

            monitor(uvm::uvm_component_name name);

            virtual void build_phase(uvm::uvm_phase & phase);
            virtual void connect_phase(uvm::uvm_phase & phase);
            virtual void run_phase(uvm::uvm_phase & phase);
            virtual void run_monitor();
    };
}

#endif /* APB_MONITOR_H_ */
