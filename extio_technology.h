#ifndef __EXTIO_TECH__
#define __EXTIO_TECH__

#include <iostream>
#include "parameter.h"


class IOTechParam
{
  public:
    IOTechParam(InputParameter *);
    ~IOTechParam();
    double num_mem_ca; /* Number of loads on the address bus
            based on total number of memories in the channel.For registered DIMMs 
            or buffered topologies, the num_mem_dq and num_mem_ca is per buffer. */
    double num_mem_clk; /* Number of loads on the clock as total
            memories in the channel / number of clock lines available */
    double max_bw; /* Max. bandwidth achievable if data bus is operating at max.
            data-rate (in GBytes per second) */
    double max_capacity; /* Max. capacity based on memory density and number of
            memories (in GB) */


		//Technology Parameters
    // IO Supply voltage (V) 
    double vdd_io; /* Voltage swing on CLK/CLKB (V) (swing on the CLK pin if it
            is differentially terminated) */
    double v_sw_clk;

   	// Loading parameters

    double c_int; /*Internal IO loading (pF) (loading within the IO, due to
            predriver nets) */
    double c_tx; /* IO TX self-load including package (pF) (loading at the
            CPU TX pin) */
    double c_data; /* Device loading per memory data pin (pF) (DRAM device
            load for DQ per die) */
    double c_addr; /* Device loading per memory address pin (pF) (DRAM
            device load for CA per die) */
    double i_bias; /* Bias current (mA) (includes bias current for the whole memory
            bus due to RX Vref based receivers */
    double i_leak; // Active leakage current per pin (nA) 



      // IO Area coefficients

     double ioarea_c; /* sq.mm. (IO Area baseline coeeficient for control
            circuitry and overhead) */
     double ioarea_k0; /* sq.mm * ohms (IO Area coefficient for the driver, for
            unit drive strength or output impedance) */
     double ioarea_k1; /* sq.mm * ohms / MHz (IO Area coefficient for the
            predriver final stage, based on fanout needed) */
     double ioarea_k2; /* sq.mm * ohms / MHz^2 (IO Area coefficient for
            predriver middle stage, based on fanout needed) */
     double ioarea_k3; /* sq.mm * ohms / MHz^3 (IO Area coefficient for
            predriver first stage, based on fanout needed) */


      // Timing parameters (ps)

	    double t_ds;  //DQ setup time at DRAM
	    double t_is;  //CA setup time at DRAM
	    double t_dh;  //DQ hold time at DRAM
	    double t_ih;  //CA hold time at DRAM
	    double t_dcd_soc;   //Duty-cycle distortion at the CPU/SOC
	    double t_dcd_dram;  //Duty-cycle distortion at the DRAM
	    double t_error_soc; //Timing error due to edge placement uncertainty of the DLL
	    double t_skew_setup;//Setup skew between DQ/DQS or CA/CLK after deskewing the lines
	    double t_skew_hold; //Hold skew between DQ/DQS or CA/CLK after deskewing the lines
	    double t_dqsq;  //DQ-DQS skew at the DRAM output during Read
	    double t_qhs;   //DQ-DQS hold factor at the DRAM output during Read
	    double t_soc_setup; //Setup time at SOC input dueing Read
	    double t_soc_hold;  //Hold time at SOC input during Read
      double t_jitter_setup; /* Half-cycle jitter on the DQS at DRAM input
            affecting setup time */
      double t_jitter_hold; /* Half-cycle jitter on the DQS at the DRAM input
            affecting hold time */
      double t_jitter_addr_setup; /* Half-cycle jitter on the CLK at DRAM input
            affecting setup time */
      double t_jitter_addr_hold; /* Half-cycle jitter on the CLK at the DRAM
            input affecting hold time */

	    	//Termination Parameters

      double r_diff_term; /* Differential termination resister if
            used for CLK (Ohm) */


      // ODT related termination resistor values (Ohm)

	    double rtt1_dq_read; //DQ Read termination at CPU
	    double rtt2_dq_read; //DQ Read termination at inactive DRAM
	    double rtt1_dq_write; //DQ Write termination at active DRAM
	    double rtt2_dq_write; //DQ Write termination at inactive DRAM
	    double rtt_ca; //CA fly-by termination
	    double rs1_dq; //Series resistor at active DRAM
	    double rs2_dq; //Series resistor at inactive DRAM
	    double r_stub_ca; //Series resistor for the fly-by channel
	    double r_on; //Driver impedance
	    double r_on_ca; //CA driver impedance

	    double z0; //Line impedance (ohms): Characteristic impedance of the route.
      double t_flight; /* Flight time of the interconnect (ns) (approximately
            180ps/inch for FR4) */
      double t_flight_ca; /* Flight time of the Control/Address (CA)
            interconnect (ns) (approximately 180ps/inch for FR4) */

     		// Voltage noise coeffecients

	    double k_noise_write; //Proportional noise coefficient for Write mode
	    double k_noise_read; //Proportional noise coefficient for Read mode
	    double k_noise_addr; //Proportional noise coefficient for Address bus
	    double v_noise_independent_write; //Independent noise voltage for Write mode
	    double v_noise_independent_read; //Independent noise voltage for Read mode
	    double v_noise_independent_addr; //Independent noise voltage for Address bus


	    //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE

      /* This is a user-defined section that depends on the channel sensitivity
       * to IO and DRAM parameters. The t_jitter_* and k_noise_* are the
       * parameters that are impacted based on the channel analysis. The user
       * can define any relationship between the termination, loading and
       * configuration parameters AND the t_jitter/k_noise parameters. E.g. a
       * linear relationship, a non-linear analytical relationship or a lookup
       * table. The sensitivity coefficients are based on channel analysis
       * performed on the channel of interest. Given below is an example of such
       * a sensitivity relationship */ //FIXME How representative is the example?

	    double k_noise_write_sen; 
	    double k_noise_read_sen; 
	    double k_noise_addr_sen;
	    double t_jitter_setup_sen;
	    double t_jitter_hold_sen;
	    double t_jitter_addr_setup_sen;
	    double t_jitter_addr_hold_sen;

	    //SWING AND TERMINATION CALCULATIONS
  	  //R|| calculation

      double rpar_write;
      double rpar_read;

	    //Swing calculation

      double v_sw_data_read_load1; //Swing for DQ at dram1 during READ
      double v_sw_data_read_load2; //Swing for DQ at dram2 during READ
      double v_sw_data_read_line; //Swing for DQ on the line during READ
	    double v_sw_addr; //Swing for the address bus
	    double v_sw_data_write_load1; //Swing for DQ at dram1 during WRITE
      double v_sw_data_write_load2; //Swing for DQ at dram2 during WRITE
      double v_sw_data_write_line; //Swing for DQ on the line during WRITE

};

#endif