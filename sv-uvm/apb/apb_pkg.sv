package apb_pkg;

   import uvm_pkg::*;

`include "uvm_macros.svh"

   typedef uvm_config_db#(virtual apb_if) apb_vif_config;
   typedef virtual apb_if apb_vif;

`include "apb_rw.sv"

`include "apb_monitor.sv"
`include "apb_sequencer.sv"
`include "apb_driver.sv"
`include "apb_agent.sv"

// `include "apb_env.sv"

endpackage: apb_pkg


