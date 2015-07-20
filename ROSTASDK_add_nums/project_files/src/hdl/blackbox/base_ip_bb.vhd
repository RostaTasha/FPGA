

library ieee;
use ieee.std_logic_1164.all;

library unisim;
use unisim.vcomponents.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity base_ip is
  generic (
   C_DATA_WIDTH         : integer range 64 to 128 := 64
  );
  port (
		pci_exp_txp		: out std_logic_vector(3 downto 0);
		pci_exp_txn		: out std_logic_vector(3 downto 0);
		pci_exp_rxp		: in std_logic_vector(3 downto 0);
		pci_exp_rxn		: in std_logic_vector(3 downto 0);

		sys_clk_p		: in std_logic;
		sys_clk_n		: in std_logic;
		sys_rst_n		: in std_logic;
  
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
	ep_tx_cmd_wr_en		: in  std_logic;
	ep_tx_cmd_data		: in  std_logic_vector(63 downto 0);	-- (addr_32_bits & length_24_bits & tag_8_bits)
	ep_tx_cmd_full		: out std_logic;  
	
	ep_tx_error			: out std_logic;	
	ep_tx_tag_error		: out std_logic_vector(7 downto 0); 
	
	ep_txd_s_tvalid		: in  std_logic;
	ep_txd_s_tdata		: in  std_logic_vector(63 downto 0);
	ep_txd_s_tready		: out std_logic;
	
	-- EP rx interface	
	ep_rxd_m_tvalid	: out std_logic;
	ep_rxd_m_tready : in  std_logic;
	ep_rxd_m_tdata	: out std_logic_vector(63 downto 0);
	
	
-----------------------------------------------------------------		
-- Debug interface
--        debug_clk       : out std_logic;
--		debug_rst       : out std_logic;		-- active high			
--        debug_trig      : out std_logic; 
--        debug_data      : out std_logic_vector(31 downto 0);

-----------------------------------------------------------------				
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
end base_ip;

architecture bb of base_ip is
   

begin


end bb;