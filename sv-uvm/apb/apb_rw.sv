typedef enum { READ,
               WRITE
             } rw_enum;

//------------------------------------------------------------------------------
//
// CLASS: apb_rw
//
//------------------------------------------------------------------------------

class apb_rw extends uvm_sequence_item;                                  

  rand bit [31:0]           addr;
  rand rw_enum              kind_e;
  rand bit [31:0]           data;
  rand bit [3:0]            strb;
  rand bit [0:0]            slv_err;
  rand bit [0:0]            valid;

  `uvm_object_utils_begin(apb_rw)
    `uvm_field_int      (addr,            UVM_DEFAULT)
    // `uvm_field_enum     (rw_enum, kind_e, UVM_DEFAULT)
    `uvm_field_int(data,                  UVM_DEFAULT)
    `uvm_field_int(strb,                  UVM_DEFAULT)
    `uvm_field_int      (slv_err,         UVM_DEFAULT)
    `uvm_field_int      (valid,           UVM_DEFAULT)
  `uvm_object_utils_end

  // new - constructor
  function new (string name = "ubus_transfer_inst");
    super.new(name);
  endfunction : new
endclass : apb_rw

