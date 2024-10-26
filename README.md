# SoCMake UVM Demo (SC and SV)

This repository demonstrates the capabilities of **SoCMake**, a CMake-based build system, in compiling **UVM verification environments** for both SystemC and SystemVerilog. The aim is to facilitate performance comparisons and provide a robust example of building and running these environments with SoCMake.

A simple [CRC verilog module](https://github.com/alexforencich/verilog-lfsr/tree/master) is used as a DUT.
While the APB register file is generated with PeakRDL-regblock.

## Dependencies

Ensure the following dependencies are installed to fully utilize the repository:

- **[CMake](https://cmake.org/)**: Required for SoCMake
- **[PeakRDL-regblock](https://peakrdl-regblock.readthedocs.io/en/latest/)**: Required for register block generation in both environments.

### SystemC-UVM
- **[Verilator](https://www.veripool.org/wiki/verilator)**: Needed to simulate DUT in SystemC-based simulations.

### SystemVerilog-UVM
- **[Questasim](https://www.mentor.com/products/fv/questasim)**: Used for simulating SystemVerilog UVM environments.

SoCMake will take care of the rest of the dependencies (SystemC, UVM-SystemC, UVM-SystemVerilog, CRCpp).

TODO - SoCMake can also compile Verilator in case it is not present, as well as setup Python virtual environment and install PeakRDL-regblock dependency.

## Directory Structure

- **`apb_crc/`**: Contains APB CRC dut files, RTL sources, and register definitions, as well as SoCMake recipe.
- **`sc-uvm/`**: SystemC UVM environment, using [CRCpp](https://github.com/d-bahr/CRCpp) as ref model.
- **`sv-uvm/`**: SystemVerilog UVM environment, using [CRCpp](https://github.com/d-bahr/CRCpp) through DPI.

## Quickstart

1. Install dependencies
2. Clone the repository

```bash
git clone https://github.com/Risto97/apb_crc_uvm_socmake.git
cd apb_crc_uvm_socmake
```

### SystemC-UVM

3. Configure project

```
cd sc-uvm
mkdir build && cd build
cmake ../
```

4. Print help for possible targets, options, IPs
```
make help_all
```

5. Compile and run

```
make -j
./apb_crc_sc_uvm
```

### SystemVerilog-UVM

3. Configure project

```
cd sc-uvm
mkdir build && cd build
cmake ../
```

4. Print help for possible targets, options, IPs
```
make help_all
```

5. Compile and run

```
make run_crc_tb_top_modelsim
```


## License

This project is licensed under the GPL-3.0 license.
