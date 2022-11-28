#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

#define CYCLES 100
#define ADDRESS_WIDTH 8
#define ROM_SIZE 256
int main(int argc, char **argv, char **ldv){
    int i;
    int clk;

    Verilated::commandArgs(argc,argv);
    Vsinegen* top= new Vsinegen;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;

    top->trace (tfp, 99);
    tfp->open("sinegen.vcd");

    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 2: SigGen");

    top->clk = 1;
    top->rst = 0;
    top->en = 1;
    top->incr=1;

     // run the simulation over 300 clk cycles
    for (i = 0; i<300; i++) {
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }

        // Sldd count value to Vbuddy
        vbdPlot(int(top->dout), 0, 255);
        vbdCycle(i+1);
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
            exit(0);    
    }
    vbdClose();
    tfp->close();
    exit(0);
    
}