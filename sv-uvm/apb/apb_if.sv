interface apb_if;
    logic        pclk;
    logic        presetn;
    logic [31:0] paddr;
    logic        psel;
    logic        penable;
    logic        pwrite;
    logic        pready;
    logic [31:0] prdata;
    logic [3:0]  pstrb;
    logic [31:0] pwdata;
    logic        pslverr;
endinterface : apb_if

