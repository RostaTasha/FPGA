-------------------------------------------------------------------------------
-- Project     : Rosta Base PCIe project Ver.10
-- File        : rc_2000_top.vhd
-- Version     : 10.0
-- Company     : Rosta
-- Engineer    : rkob & urock
-- Create Date : 14.03.2014 
-- Comments    : Top level 
-- Description : PCI Express Endpoint 
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

library unisim;
use unisim.vcomponents.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity rc_pcie_base_2000_11 is
  port (
	pci_exp_txp	: out std_logic_vector(3 downto 0);
	pci_exp_txn	: out std_logic_vector(3 downto 0);
	pci_exp_rxp	: in std_logic_vector(3 downto 0);
	pci_exp_rxn	: in std_logic_vector(3 downto 0);

	sys_clk_p	: in std_logic;
	sys_clk_n	: in std_logic;
	sys_rst_n	: in std_logic;

	-- Identifier FPGA: "00" - LD, "01" - LU, "10" - RD, "11" - RU
    -- - - - - - - - - - C0 - - - - C1 - - - - C2 - - - - C3 - - -	                       
    id			: in std_logic_vector(1 downto 0);
	
	-- Command bus: need for transmit MAC-Address and ID
    strtcmd		: in std_logic;
    command		: inout std_logic_vector(7 downto 0);
    dval   		: inout std_logic;


    clk100		: in std_logic; -- user clock from S6 - 100 mhz

    aclk_p      : in std_logic; -- user diff.clock - 100 mhz
    aclk_n      : in std_logic
);
end rc_pcie_base_2000_11;

architecture base of rc_pcie_base_2000_11 is


attribute buffer_type : string;
attribute buffer_type of pci_exp_txp : signal is "none";
attribute buffer_type of pci_exp_txn : signal is "none";
attribute buffer_type of pci_exp_rxp : signal is "none";
attribute buffer_type of pci_exp_rxn : signal is "none";

attribute buffer_type of sys_clk_p : signal is "none";
attribute buffer_type of sys_clk_n : signal is "none";
attribute buffer_type of sys_rst_n : signal is "none";

component base_ip is
port (
    pci_exp_txp     : out std_logic_vector(3 downto 0);
    pci_exp_txn     : out std_logic_vector(3 downto 0);
    pci_exp_rxp     : in std_logic_vector(3 downto 0);
    pci_exp_rxn     : in std_logic_vector(3 downto 0);
    sys_clk_p       : in std_logic;
    sys_clk_n       : in std_logic;
    sys_rst_n       : in std_logic;
    
---------------------------------------------------
-- User IP interface

	ip_clk		    : in  std_logic;
	user_rst_n		: out std_logic;

-- HOST DMA Data 	
	-- RX FIFO
	m_user_tvalid	: out std_logic;
	m_user_tready	: in  std_logic;
	m_user_tdata		: out std_logic_vector(63 downto 0); 
	 
	-- TX FIFO
	s_user_tvalid	: in  std_logic;
	s_user_tready		: out std_logic;		
	s_user_tdata		: in  std_logic_vector(63 downto 0);		

--  Register interface
	Reg_RE		: out std_logic;
	Reg_WE		: out std_logic; 
	Reg_Addr	: out std_logic_vector( 7 downto 0); 
	Reg_Dout	: out std_logic_vector(31 downto 0); 
	Reg_Din		: in  std_logic_vector(31 downto 0);
	Reg_Valid	: in  std_logic; 	
	
	pcie_int_req	: in  std_logic;
	pcie_int_compl	: out std_logic;
    	
   	-- EP tx interface
  	-- EP TX CMD FIFO interface 
   	ep_tx_cmd_wr_en	: in  std_logic;
   	ep_tx_cmd_data	: in  std_logic_vector(63 downto 0);-- (addr_32_bits & length_24_bits & tag_8_bits)
   	ep_tx_cmd_full	: out std_logic;  
    	
   	ep_tx_error		: out std_logic;	
   	ep_tx_tag_error	: out std_logic_vector(7 downto 0); 
    		
   	ep_txd_s_tvalid	: in  std_logic;
   	ep_txd_s_tdata	: in  std_logic_vector(63 downto 0);
   	ep_txd_s_tready	: out std_logic;
    		
   	-- EP rx interface	    		
   	ep_rxd_m_tvalid	: out std_logic;
   	ep_rxd_m_tready : in  std_logic;
   	ep_rxd_m_tdata	: out std_logic_vector(63 downto 0);
   	


-- CBUS section

	cbus_clk  	: in  std_logic;

	id      : in std_logic_vector(1 downto 0);
	strtcmd : in std_logic;
	command	: inout std_logic_vector(7 downto 0);
	dval    : inout std_logic;

    -- Register Interface
    -- to USER IP
	hardid	: out std_logic_vector( 1 downto 0); 
	mac		: out std_logic_vector(31 downto 0);  
	userid	: out std_logic_vector(31 downto 0);

	OutReg0	: out std_logic_vector(31 downto 0);
	OutReg1	: out std_logic_vector(31 downto 0);
	OutReg2	: out std_logic_vector(31 downto 0);
	OutReg3	: out std_logic_vector(31 downto 0);
	OutReg4	: out std_logic_vector(31 downto 0);
	OutReg5	: out std_logic_vector(31 downto 0);
	OutReg6	: out std_logic_vector(31 downto 0);

    -- from USER IP
	InReg0	: in std_logic_vector(31 downto 0);
	InReg1	: in std_logic_vector(31 downto 0);
	InReg2	: in std_logic_vector(31 downto 0);
	InReg3	: in std_logic_vector(31 downto 0);
	InReg4	: in std_logic_vector(31 downto 0);
	InReg5	: in std_logic_vector(31 downto 0);
	InReg6	: in std_logic_vector(31 downto 0);
	
    -- S6 FIFO Interface
    fifo_rst : in std_logic;

    -- RX FIFO
    s6_v7_empty : out std_logic;
    s6_v7_dout  : out std_logic_vector(31 downto 0);
    s6_v7_rd_en : in std_logic;
    s6_v7_data_count : out std_logic_vector(10 downto 0);

    -- TX FIFO
    v7_s6_din   : in std_logic_vector(31 downto 0);
    v7_s6_wr_en : in std_logic;
    v7_s6_full  : out std_logic
	
    );
end component;

component user_ip is 
port (
	user_rst_n		: in  std_logic;-- active low

	clk_in   		: in  std_logic;
	clk_out   		: out  std_logic;
		
	-- FIFO interface
	-- AXIs Slave interface (read from RX_FIFO)
	host_rxd_s_tvalid 	: in  std_logic;
	host_rxd_s_tready 	: out std_logic;
	host_rxd_s_tdata  	: in  std_logic_vector(63 downto 0);
		
	-- AXIs Master interface (write to TX_FIFO)
	host_txd_m_tvalid	: out std_logic; 
	host_txd_m_tready	: in  std_logic;
	host_txd_m_tdata	: out std_logic_vector(63 downto 0);
	
	--  Registers interface
	Reg_RE		: in  std_logic;
	Reg_WE		: in  std_logic;
	Reg_Addr	: in  std_logic_vector( 7 downto 0);
	Reg_Dout	: in  std_logic_vector(31 downto 0); 
	Reg_Din		: out std_logic_vector(31 downto 0);
	Reg_Valid	: out std_logic; 	
				
	user_int_req	: out std_logic;
	user_int_compl	: in  std_logic;
		
	-- EP tx interface
	-- EP TX CMD FIFO interface 
	ep_tx_cmd_wr_en		: out std_logic;
	ep_tx_cmd_data		: out std_logic_vector(63 downto 0);	-- (addr_32_bits & length_24_bits & tag_8_bits)
	ep_tx_cmd_full		: in  std_logic;  
   	
	ep_tx_error			: in std_logic;	
	ep_tx_tag_error		: in std_logic_vector(7 downto 0); 
   		
   	-- EP TXD AXIS Master (write to other EP)
	ep_txd_m_tvalid		: out std_logic;
	ep_txd_m_tdata		: out std_logic_vector(63 downto 0);
	ep_txd_m_tready		: in  std_logic;
   		
	-- EP RXD AXIS Slave (receive data from other EP) 
	ep_rxd_s_tvalid	: in  std_logic;
	ep_rxd_s_tready : out std_logic;
	ep_rxd_s_tdata	: in  std_logic_vector(63 downto 0);
	
	-- Control Bus
	-- Register Interface
    -- from CBus
	hardid	: in std_logic_vector( 1 downto 0); 
	mac		: in std_logic_vector(31 downto 0);  
	userid	: in std_logic_vector(31 downto 0);
	InReg0	: in std_logic_vector(31 downto 0);
	InReg1	: in std_logic_vector(31 downto 0);
	InReg2	: in std_logic_vector(31 downto 0);
	InReg3	: in std_logic_vector(31 downto 0);
	InReg4	: in std_logic_vector(31 downto 0);
	InReg5	: in std_logic_vector(31 downto 0);
	InReg6	: in std_logic_vector(31 downto 0);

	-- to CBus
	OutReg0	: out std_logic_vector(31 downto 0);
	OutReg1	: out std_logic_vector(31 downto 0);
	OutReg2	: out std_logic_vector(31 downto 0);
	OutReg3	: out std_logic_vector(31 downto 0);
	OutReg4	: out std_logic_vector(31 downto 0);
	OutReg5	: out std_logic_vector(31 downto 0);
	OutReg6	: out std_logic_vector(31 downto 0);
	
    -- S6 FIFO Interface
    fifo_rst : out std_logic;

    -- RX FIFO
    s6_v7_empty : in std_logic;
    s6_v7_dout  : in std_logic_vector(31 downto 0);
    s6_v7_rd_en : out std_logic;
    s6_v7_data_count : in std_logic_vector(10 downto 0);

    -- TX FIFO
    v7_s6_din   : out std_logic_vector(31 downto 0);
    v7_s6_wr_en : out std_logic;
    v7_s6_full  : in std_logic
    

    
	);
end component; 


-- EP tx interface
-- EP TX CMD FIFO interface 
signal ep_tx_cmd_wr_en		: std_logic;
signal ep_tx_cmd_data		: std_logic_vector(63 downto 0);	-- (addr_32_bits & length_24_bits & tag_8_bits)
signal ep_tx_cmd_full		: std_logic;  
    	
signal ep_tx_error			: std_logic;	
signal ep_tx_tag_error		: std_logic_vector(7 downto 0); 
    		
signal ep_txd_s_tvalid		: std_logic;
signal ep_txd_s_tdata		: std_logic_vector(63 downto 0);
signal ep_txd_s_tready		: std_logic;
    		
-- EP rx interface	    		
signal ep_rxd_m_tvalid	: std_logic;
signal ep_rxd_m_tready 	: std_logic;
signal ep_rxd_m_tdata	: std_logic_vector(63 downto 0); 

-- FIFO interface
-- AXIs Slave interface (read from RX_FIFO)
signal host_rxd_s_tvalid 	: std_logic;
signal host_rxd_s_tready 	: std_logic;
signal host_rxd_s_tdata  	: std_logic_vector(63 downto 0);

-- AXIs Master interface (write to TX_FIFO)
signal host_txd_m_tvalid	: std_logic; 
signal host_txd_m_tready	: std_logic;
signal host_txd_m_tdata		: std_logic_vector(63 downto 0);

-- User Interface	
signal Reg_RE			: std_logic;
signal Reg_WE			: std_logic; 
signal Reg_Addr			: std_logic_vector( 7 downto 0); 
signal Reg_Dout			: std_logic_vector(31 downto 0); 
signal Reg_Din			: std_logic_vector(31 downto 0); 
signal Reg_Valid		: std_logic; 
	
signal user_rst_n		: std_logic; 
signal user_int_req 	: std_logic; 
signal user_int_compl   : std_logic; 

signal aclk : std_logic; 
signal ip_clk : std_logic; 

signal sys_reset_c : std_logic; 

-- CBus
signal hardid : std_logic_vector(1 downto 0);
signal userid : std_logic_vector(31 downto 0);
signal mac    : std_logic_vector(31 downto 0);  

signal OutReg0	: std_logic_vector(31 downto 0);
signal OutReg1	: std_logic_vector(31 downto 0);
signal OutReg2	: std_logic_vector(31 downto 0);
signal OutReg3	: std_logic_vector(31 downto 0);
signal OutReg4	: std_logic_vector(31 downto 0);
signal OutReg5	: std_logic_vector(31 downto 0);
signal OutReg6	: std_logic_vector(31 downto 0);
signal InReg0	: std_logic_vector(31 downto 0);
signal InReg1	: std_logic_vector(31 downto 0);
signal InReg2	: std_logic_vector(31 downto 0);
signal InReg3	: std_logic_vector(31 downto 0);
signal InReg4	: std_logic_vector(31 downto 0);
signal InReg5	: std_logic_vector(31 downto 0);
signal InReg6	: std_logic_vector(31 downto 0);

signal fifo_clk	: std_logic;
signal fifo_rst	: std_logic;

signal s6_v7_empty	: std_logic;
signal s6_v7_rd_en	: std_logic;
signal s6_v7_dout	: std_logic_vector(31 downto 0);
signal s6_v7_data_count	: std_logic_vector(10 downto 0);

signal v7_s6_wr_en	: std_logic;
signal v7_s6_din	: std_logic_vector(31 downto 0);
signal v7_s6_full	: std_logic;


begin



diffclk_ibuf : IBUFDS_GTE2
     port map(
       O       => aclk,
       ODIV2   => open,
       I       => aclk_p,
       IB      => aclk_n,
       CEB     => '0');

base : base_ip 
port map (
    pci_exp_txp  => pci_exp_txp,
    pci_exp_txn  => pci_exp_txn,
    pci_exp_rxp  => pci_exp_rxp,  
    pci_exp_rxn  => pci_exp_rxn,
    
    sys_clk_p    => sys_clk_p,     
    sys_clk_n    => sys_clk_n,
    sys_rst_n    => sys_rst_n,   

    user_rst_n	=> user_rst_n,
    ip_clk		=> ip_clk,   
     	
    -- FIFO interface - AXI Stream
    -- RX FIFO
    m_user_tvalid => host_rxd_s_tvalid,
    m_user_tready => host_rxd_s_tready,
    m_user_tdata	 => host_rxd_s_tdata,
     
    -- TX FIFO
    s_user_tvalid => host_txd_m_tvalid,
    s_user_tready	 => host_txd_m_tready,		
    s_user_tdata	 => host_txd_m_tdata,	
    	
    --  Registers interface
    Reg_RE		=> Reg_RE,	
    Reg_WE		=> Reg_WE,	
    Reg_Addr	=> Reg_Addr,
    Reg_Dout	=> Reg_Dout,
    Reg_Din		=> Reg_Din,
    Reg_Valid	=> Reg_Valid,
    
    pcie_int_req	=> user_int_req,
    pcie_int_compl	=> user_int_compl,
	
    -- EP tx interface
    -- EP TX CMD FIFO interface 
    ep_tx_cmd_wr_en	=> ep_tx_cmd_wr_en,
    ep_tx_cmd_data	=> ep_tx_cmd_data,
    ep_tx_cmd_full	=> ep_tx_cmd_full,
    	
    ep_tx_error		=> ep_tx_error,
    ep_tx_tag_error	=> ep_tx_tag_error,
    	
    ep_txd_s_tvalid	=> ep_txd_s_tvalid,
    ep_txd_s_tdata	=> ep_txd_s_tdata,
    ep_txd_s_tready	=> ep_txd_s_tready,
    
    -- EP rx interface	
    ep_rxd_m_tvalid	=> ep_rxd_m_tvalid,
    ep_rxd_m_tready => ep_rxd_m_tready,
    ep_rxd_m_tdata	=> ep_rxd_m_tdata,

	
-- CBUS section	
	cbus_clk  	=> clk100,

	id      => id,
	strtcmd => strtcmd,
	command	=> command,
	dval    => dval,

    -- CBus 
    -- to USER IP
    hardid	=> hardid,
    mac		=> mac,
    userid	=> userid,

    OutReg0	=> InReg0,
    OutReg1	=> InReg1,
    OutReg2	=> InReg2,
    OutReg3	=> InReg3,
    OutReg4	=> InReg4,
    OutReg5	=> InReg5,
    OutReg6	=> InReg6,

    -- from USER IP
    InReg0	=> OutReg0,
   	InReg1	=> OutReg1,
   	InReg2	=> OutReg2,
   	InReg3	=> OutReg3,
   	InReg4	=> OutReg4,
   	InReg5	=> OutReg5,
   	InReg6	=> OutReg6,
   	
    -- S6 FIFO Interface
    fifo_rst 	=> fifo_rst,
    -- RX FIFO
    s6_v7_empty => s6_v7_empty,
    s6_v7_dout 	=> s6_v7_dout,
    s6_v7_rd_en => s6_v7_rd_en,
    s6_v7_data_count => s6_v7_data_count,
    -- TX FIFO
    v7_s6_din 	=> v7_s6_din,
    v7_s6_wr_en => v7_s6_wr_en,
    v7_s6_full  => v7_s6_full
    	
 );
  

user :  user_ip 
	port map (
	user_rst_n		=> user_rst_n,		-- active low
	
	clk_in			=> aclk,
	clk_out			=> ip_clk, 	 	

	-- FIFO interface
	-- AXIs Slave interface (read from RX_FIFO) 
	host_rxd_s_tvalid	=> host_rxd_s_tvalid,
	host_rxd_s_tready	=> host_rxd_s_tready,
	host_rxd_s_tdata	=> host_rxd_s_tdata, 

	-- AXIs Master interface (write to TX_FIFO)	
	host_txd_m_tvalid	=> host_txd_m_tvalid, 
	host_txd_m_tready	=> host_txd_m_tready,
	host_txd_m_tdata	=> host_txd_m_tdata,

--  Registers interface
	Reg_RE		=> Reg_RE,	
	Reg_WE		=> Reg_WE,
	Reg_Addr	=> Reg_Addr,
	Reg_Dout	=> Reg_Dout,
	Reg_Din		=> Reg_Din,
	Reg_Valid	=> Reg_Valid,
	
	user_int_req   => user_int_req,
	user_int_compl => user_int_compl,
	
	-- EP tx interface
	-- EP TX CMD FIFO interface 
	ep_tx_cmd_wr_en		=> ep_tx_cmd_wr_en,
	ep_tx_cmd_data		=> ep_tx_cmd_data,
	ep_tx_cmd_full		=> ep_tx_cmd_full,
	
	ep_tx_error			=> ep_tx_error,
	ep_tx_tag_error		=> ep_tx_tag_error,
	
	-- EP TXD AXIS Master (write to other EP)
	ep_txd_m_tvalid		=> ep_txd_s_tvalid,
	ep_txd_m_tdata		=> ep_txd_s_tdata,
	ep_txd_m_tready		=> ep_txd_s_tready,
	
	-- EP rx interface	
	-- EP RXD AXIS Slave (receive data from other EP) 
	ep_rxd_s_tvalid	=> ep_rxd_m_tvalid,
	ep_rxd_s_tready => ep_rxd_m_tready,
	ep_rxd_s_tdata	=> ep_rxd_m_tdata,
	
	-- Control Bus
	-- Register Interface
     -- to USER IP
    hardid	=> hardid,
    mac		=> mac,
    userid	=> userid,

    OutReg0	=> OutReg0,
    OutReg1	=> OutReg1,
    OutReg2	=> OutReg2,
    OutReg3	=> OutReg3,
    OutReg4	=> OutReg4,
    OutReg5	=> OutReg5,
    OutReg6	=> OutReg6,

    -- from USER IP
    InReg0	=> InReg0,
   	InReg1	=> InReg1,
   	InReg2	=> InReg2,
   	InReg3	=> InReg3,
   	InReg4	=> InReg4,
   	InReg5	=> InReg5,
   	InReg6	=> InReg6,

    -- S6 FIFO Interface
    fifo_rst 	=> fifo_rst,
    -- RX FIFO
    s6_v7_empty => s6_v7_empty,
    s6_v7_dout 	=> s6_v7_dout,
    s6_v7_rd_en => s6_v7_rd_en,
    s6_v7_data_count => s6_v7_data_count,
    -- TX FIFO
    v7_s6_din 	=> v7_s6_din,
    v7_s6_wr_en => v7_s6_wr_en,
    v7_s6_full 	=> v7_s6_full
    
  ); 


end base;
