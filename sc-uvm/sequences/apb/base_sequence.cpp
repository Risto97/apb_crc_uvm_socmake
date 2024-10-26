#include <string>
#include <iostream>
#include <cstdint>

#include "uvc_apb.h"

#include "base_sequence.h"

uint32_t base_sequence::ARCHI_READ(uint32_t addr) {
    uvc::apb::rw req;
    uvc::apb::rw rsp;

    req.valid = true;
    req.set_name("APB Archi read request");
    req.kind_e = uvc::apb::READ;
    req.addr = addr;
    req.strb = 0x0;
    // req->print();
    // req->data = value;

    start_item(&req);
    finish_item(&req);
    get_response(&rsp);
    // rsp->print();
    return rsp.data.to_uint();
}

void base_sequence::ARCHI_WRITE(uint32_t addr, uint32_t value) {
    uvc::apb::rw req;

    req.valid = true;
    req.kind_e = uvc::apb::WRITE;
    req.addr = addr;
    req.strb = 0xf;
    req.data = value;

    // req->print();
    start_item(&req);
    finish_item(&req);
}

void base_sequence::body() {
    UVM_INFO(this->get_name(), "** Starting Base Sequence **", uvm::UVM_MEDIUM);
}

void base_sequence::message(const uvc::apb::rw& p) {
    std::stringstream ss;
    ss << std::hex << p.data.to_uint();
    std::string msg = ss.str();
    UVM_INFO(" Generated data:", msg, uvm::UVM_MEDIUM);
}

void base_sequence::pre_body() {}
void base_sequence::post_body() {}
