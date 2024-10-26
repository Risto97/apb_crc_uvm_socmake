module apb_crc #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 32
) (
    input  wire clk,
    input  wire rstn,

    input  wire [ADDR_WIDTH-1:0] s_paddr,
    input  wire [DATA_WIDTH-1:0] s_pwdata,
    output wire [DATA_WIDTH-1:0] s_prdata,
    output wire                  s_pslverr,
    input  wire                  s_pwrite,
    input  wire                  s_psel,
    input  wire                  s_penable,
    output wire                  s_pready,
    input  wire [ 3:0]           s_pstrb
);
    apb_crc_regblock_pkg::apb_crc_regblock__in_t regblock_in;
    apb_crc_regblock_pkg::apb_crc_regblock__out_t regblock_out;

/* verilator lint_off MULTIDRIVEN */
// verilator lint_off MULTIDRIVEN
    apb_crc_regblock apb_crc_regblock_i(
        .clk(clk),
        .rst(!rstn),

        .s_apb_psel(s_psel),
        .s_apb_penable(s_penable),
        .s_apb_pprot(3'b000),
        .s_apb_paddr(s_paddr[3:0]),
        .s_apb_pwdata(s_pwdata),
        .s_apb_pwrite(s_pwrite),
        .s_apb_pstrb(s_pstrb),
        .s_apb_pready(s_pready),
        .s_apb_prdata(s_prdata),
        .s_apb_pslverr(s_pslverr),
        .hwif_in(regblock_in),
        .hwif_out(regblock_out)
    );
/* verilator lint_on MULTIDRIVEN */
// verilator lint_on MULTIDRIVEN

    apb_crc_core  apb_crc_core_i (
        .clk(clk),
        .rstn(rstn),

        .hwif_out(regblock_in),
        .hwif_in(regblock_out)
    );

endmodule

