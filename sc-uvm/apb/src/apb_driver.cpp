#include <stdint.h>
#include <string>
#include <systemc>
#include <uvm>

#include "apb_agent.h"
#include "apb_driver.h"
#include "apb_if.h"
#include "apb_modes.h"
#include "apb_rw.h"

namespace uvc::apb{
    driver::driver(uvm::uvm_component_name name)
        : uvm::uvm_driver<rw>(name), sigs(nullptr) {}

    void driver::build_phase(uvm::uvm_phase &phase) {
      UVM_INFO("APB DRIVER build PHASE", "", uvm::UVM_MEDIUM);

      uvm::uvm_driver<rw>::build_phase(phase);

      agent *ag = dynamic_cast<agent *>(get_parent());
      if (ag) {
        sigs = ag->vif;
        mode = ag->mode;
        max_retry_count = ag->max_retry_count;
      } else {
        if (!uvm::uvm_config_db<Intf *>::get(this, "", "vif", sigs)) {
          UVM_FATAL("APB/DRV/NOVIF",
                    "No virtual interface specified for this driver instance");
        }
        if (!uvm::uvm_config_db<mode_t>::get(this, "", "mode", mode)) {
          UVM_FATAL("APB", "No mode defined, aborting simulation");
        }
      }
    }

    void driver::run_phase(uvm::uvm_phase &phase) {

      sc_core::sc_spawn(sc_bind(&driver::drive_clk, this));
      sc_core::sc_spawn(sc_bind(&driver::drive_rst, this));

      if (mode == MASTER) {
        UVM_INFO("CONFIGURED AS MASTER", "", uvm::UVM_MEDIUM);
        sigs->psel = 0;
        sigs->penable = 0;

        while (1) {
          rw req;
          rw rsp;

          seq_item_port->get_next_item(req);

          switch (req.kind_e) {
          case READ:
            rsp = read(req);
            break;
          case WRITE:
            write(req);
            break;
          }

          if (req.kind_e == READ) {
            rsp.set_id_info(req);
            seq_item_port->put_response(rsp);
          }
          seq_item_port->item_done();
        }
      } else if (mode == SLAVE) {
        UVM_INFO("CONFIGURED AS SLAVE", "", uvm::UVM_MEDIUM);
        sigs->pready = 1;
        while (1) {
          sc_core::wait(sigs->pclk.posedge_event());
        }
      }
    }

    rw driver::read(const rw &req) {
      rw rsp("APB read from driver");
      uint32_t retry_count = 0;
      sigs->paddr = req.addr;
      sigs->pwrite = 0;
      sigs->pstrb = req.strb;
      sigs->psel = req.valid;
      sc_core::wait(sigs->pclk.posedge_event());
      sigs->penable = req.valid;
      do {
        sc_core::wait(sigs->pclk.posedge_event());
        retry_count++;
      } while (!sigs->pready && retry_count != max_retry_count);
      if (retry_count == max_retry_count) {
        UVM_ERROR("SLAVE STALLED", "SLAVE HAS STALLED");
        rsp.valid = false;
      } else
        rsp.valid = true;
      rsp.data = sigs->prdata;
      rsp.addr = req.addr;
      rsp.kind_e = req.kind_e;

      sigs->psel = 0;
      sigs->penable = 0;

      return rsp;
    }

    void driver::write(const rw &req) {
      uint32_t retry_count = 0;
      sigs->paddr = req.addr;
      sigs->pwdata = req.data;
      sigs->pstrb = req.strb;
      sigs->pwrite = 1;
      sigs->psel = req.valid;
      sc_core::wait(sigs->pclk.posedge_event());
      sigs->penable = req.valid;
      do {
        sc_core::wait(sigs->pclk.posedge_event());
        retry_count++;
      } while (!sigs->pready && retry_count != max_retry_count);
      if (retry_count == max_retry_count)
        UVM_ERROR("SLAVE STALLED", "SLAVE HAS STALLED");

      sigs->psel = 0;
      sigs->penable = 0;
    }

    void driver::drive_rst(){
        sigs->presetn.write(0);
        sc_core::wait(sigs->pclk.posedge_event());
        sc_core::wait(sigs->pclk.posedge_event());
        sc_core::wait(sigs->pclk.posedge_event());
        sigs->presetn.write(1);

    }

    void driver::drive_clk(){
        while (true) // forever
        {
          sigs->pclk = !(sigs->pclk.read());
         
          sc_core::wait(5.0, sc_core::SC_NS);
        }
    }

}
