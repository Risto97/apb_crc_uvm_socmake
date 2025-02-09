package apb_pkg;

   import uvm_pkg::*;

`include "uvm_macros.svh"

   typedef uvm_config_db#(virtual apb_if) apb_vif_config;
   typedef virtual apb_if apb_vif;

`include "apb_rw.svh"

`include "apb_monitor.svh"
`include "apb_sequencer.svh"
`include "apb_driver.svh"
`include "apb_agent.svh"

// `include "apb_env.svh"

endpackage: apb_pkg


