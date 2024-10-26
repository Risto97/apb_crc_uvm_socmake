module apb_crc_core (
    input logic clk,
    input logic rstn,

    output apb_crc_regblock_pkg::apb_crc_regblock__in_t hwif_out,
    input apb_crc_regblock_pkg::apb_crc_regblock__out_t hwif_in
);

    reg write_valid_swmod_dly;
    always_ff @(posedge clk) begin
        write_valid_swmod_dly <= hwif_in.write.data.swmod;
    end


    lfsr_crc #(
        .LFSR_WIDTH(32),
        .LFSR_POLY(32'h04c11db7),
        .LFSR_INIT({32{1'b0}}),
        .LFSR_CONFIG("GALOIS"),
        .REVERSE(0),
        .INVERT(0),
        .DATA_WIDTH(8),
        .STYLE("AUTO")
        ) lfsr_crc_i (
            .clk(clk),
            .rst(!rstn),

            .data_in(hwif_in.write.data.value),
            .data_in_valid(write_valid_swmod_dly),

            .crc_out(hwif_out.read.data.next)
        );

endmodule
