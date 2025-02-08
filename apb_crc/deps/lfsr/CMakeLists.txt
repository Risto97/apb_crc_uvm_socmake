CPMAddPackage(
    NAME verilog-lfsr
    GIT_TAG d4918ba
    GIT_REPOSITORY "https://github.com/alexforencich/verilog-lfsr.git"
    )

add_ip(alexforencich::ip::lfsr::0.0.1
    DESCRIPTION "Fully parametrizable combinatorial parallel LFSR/CRC module"
    )

ip_sources(${IP} VERILOG
    ${verilog-lfsr_SOURCE_DIR}/rtl/lfsr.v
    ${verilog-lfsr_SOURCE_DIR}/rtl/lfsr_crc.v
    )
