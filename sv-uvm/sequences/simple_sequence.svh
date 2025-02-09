virtual class base_sequence extends uvm_sequence #(apb_rw);

    function new(string name="apb_base_seq");
        super.new(name);
        uvm_config_db #(int)::get(null, get_full_name(), "do_not_randomize", do_not_randomize);
        set_automatic_phase_objection(1);
    endfunction

    task ARCHI_READ(input int addr, output int data);
        req = apb_rw::type_id::create("req");
        rsp = apb_rw::type_id::create("rsp");

        req.set_name("APB read request");
        req.addr = addr;
        req.kind_e = READ;
        req.strb = 4'h0;
        req.valid = 1'b1;

        
        // Start the sequence
        start_item(req);
        finish_item(req);
        get_response(rsp);

        data = rsp.data;

        // return rsp.data;
    endtask

    task ARCHI_WRITE(input int addr, input int value);
        req = apb_rw::type_id::create("req");

        req.set_name("APB write request");
        req.valid = 1'b1;
        req.kind_e = WRITE;
        req.addr = addr;
        req.strb = 4'hf;
        req.data = value;

        // Start the sequence
        start_item(req);
        finish_item(req);

    endtask
  
endclass : base_sequence

//------------------------------------------------------------------------------
//
// SEQUENCE: read_byte
//
//------------------------------------------------------------------------------

class simple_sequence extends base_sequence;

  function new(string name="simple_sequence");
    super.new(name);
  endfunction
  
  `uvm_object_utils(simple_sequence)

  int data;
  // integer iA;

  virtual task body();

      ARCHI_WRITE(0, 12);
      ARCHI_READ(4, data);

      // iA = myCFunc1();

        for(int i = 0; i < 100000; i++) begin
          ARCHI_WRITE(0, $urandom());
          ARCHI_READ(4, data);
        end
  endtask
  
endclass : simple_sequence

class smoke_sequence extends base_sequence;

  function new(string name="smoke_sequence");
    super.new(name);
  endfunction
  
  `uvm_object_utils(smoke_sequence)

  int data;
  // integer iA;

  virtual task body();

      ARCHI_WRITE(0, 12);
      ARCHI_READ(4, data);

      // iA = myCFunc1();

        for(int i = 0; i < 1; i++) begin
          ARCHI_WRITE(0, i*5);
          ARCHI_READ(4, data);
        end
  endtask
  
endclass : smoke_sequence
