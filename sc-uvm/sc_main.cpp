#include <systemc>
#include "clipp.h"
#include <uvm>
#include <uvc_apb.h>

#include "Vapb_crc.h"

int sc_main(int argc, char **argv) {
    /*=======================
     * Command line arguments
     ========================*/
    enum class verb {low, medium, high, debug};
    std::string verbosity = "UVM_MEDIUM";
    int seed = 0;

    auto cli = clipp::with_suffix("=",
       (clipp::option("--verbosity") &  clipp::value("verbosity=UVM_MEDIUM", verbosity))
            .doc("UVM verbosity level, the higher the value more information is printed, possible options [UVM_NONE, UVM_LOW, UVM_MEDIUM, UVM_HIGH, UVM_FULL, UVM_DEBUG]"),

       (clipp::option("--seed") & clipp::value("seed=-1", seed))
            .doc("Seed used for randomization, by default -1 is used, which means randomize seed and print it in log")
    );

    std::stringstream help_string;
    help_string << clipp::make_man_page(cli, argv[0])
        .prepend_section("Description", "   UVM testbench for APB_CRC\n \
    The command line arguments are split in 2 prefixes\n \
        - With '--' prefix, these arguments are only used in C++ code\n \
        - With '+' prefix, these arguments are passed to verilog model, and can be used within verilog \n")
        .prepend_section("LICENSE", "    GPL3")
        .prepend_section("Author", "    Risto Pejašinović")
        .prepend_section("--------------------------------------------", "-------- APB CRC UVM testbench --------");
        

    if(!clipp::parse(argc, argv, cli)) {
        std::cout << help_string.str();
        std::exit(1);
    }
#ifdef VERILATOR
    Verilated::commandArgs(argc, argv);
#ifdef TRACE
    Verilated::traceEverOn(true);
#endif
#endif

    // sc_core::sc_time CLK_PERIOD(10, sc_core::SC_NS);
    // sc_core::sc_clock clk("clk", CLK_PERIOD);
    // sc_core::sc_signal<bool> rstn; // TODO move to intf

    // Create verbosity enum from argument string
    std::map<std::string, uvm::uvm_verbosity> verbosityMap = {
        {"UVM_NONE",   uvm::UVM_NONE},
        {"UVM_LOW",    uvm::UVM_LOW},
        {"UVM_MEDIUM", uvm::UVM_MEDIUM},
        {"UVM_HIGH",   uvm::UVM_HIGH},
        {"UVM_FULL",   uvm::UVM_FULL},
        {"UVM_DEBUG",  uvm::UVM_DEBUG}
    };

    auto verb_it = verbosityMap.find(verbosity);
    if(verb_it != verbosityMap.end()){
        uvm::uvm_config_db<int>::set(NULL, "*", "recording_detail", verb_it->second);
        uvm::uvm_config_db<int>::set(NULL, "*", "verbosity_level", verb_it->second);
        uvm::uvm_set_verbosity_level(verb_it->second);
    } else {
        std::cout << help_string.str();
        std::cerr << "Verbosity level provided not available: " << verbosity << "\n";
        exit(1);
    }

    uvc::apb::Intf* vif = new uvc::apb::Intf("vif");
    uvm::uvm_config_db<uvc::apb::Intf*>::set(uvm::uvm_root::get(), "*", "vif", vif);

// DUT instantiation
    Vapb_crc dut("dut");

    dut.clk(vif->pclk);
    dut.rstn(vif->presetn);
    dut.s_penable(vif->penable);
    dut.s_pwrite(vif->pwrite);
    dut.s_paddr(vif->paddr);
    dut.s_psel(vif->psel);
    dut.s_pwdata(vif->pwdata);
    dut.s_pstrb(vif->pstrb);
    dut.s_prdata(vif->prdata);
    dut.s_pready(vif->pready);
    dut.s_pslverr(vif->pslverr);

    uvm::uvm_config_db<Vapb_crc*>::set(uvm::uvm_root::get(), "*", "dut", &dut);

    uvm::run_test("simple_test");

    return 0;
}

