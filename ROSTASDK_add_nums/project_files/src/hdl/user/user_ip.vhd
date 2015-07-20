----------------------------------------------------------------------------------
-- Project     : Rosta Base PCIe project Ver.9
-- File        : user_ip.vhd
-- Version     : 9.0
-- Company     : Rosta
-- Engineer    : urock & rkob & tasha
-- Create Date : 31.10.2013 
-- Comments    : User IP Interface 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library unisim;
use unisim.vcomponents.all;

entity user_ip is 

        port (

                user_rst_n              : in  std_logic;                -- active low
                
                clk_in                          : in  std_logic;

                clk_out                         : out  std_logic;       
                        
                
                -- PCIe FIFO interface
                -- AXIs Slave interface (read from RX_FIFO)
                host_rxd_s_tvalid       : in  std_logic;
                host_rxd_s_tready       : out std_logic;
                host_rxd_s_tdata        : in  std_logic_vector(63 downto 0);

                
                -- AXIs Master interface (write to TX_FIFO)
                host_txd_m_tvalid       : out std_logic; 
                host_txd_m_tready       : in  std_logic;
                host_txd_m_tdata        : out std_logic_vector(63 downto 0);
                
        --  PCIe Registers interface
                Reg_RE          : in  std_logic;
                Reg_WE          : in  std_logic;
                Reg_Addr                : in  std_logic_vector( 7 downto 0);
                Reg_Dout                : in  std_logic_vector(31 downto 0); 
                Reg_Din         : out std_logic_vector(31 downto 0);
                Reg_Valid       : out std_logic;        
                                
                user_int_req    : out std_logic;
                user_int_compl  : in  std_logic;
                
                -- EP tx interface
        -- EP TX CMD FIFO interface 
                ep_tx_cmd_wr_en         : out std_logic;
                ep_tx_cmd_data          : out std_logic_vector(63 downto 0);    -- (addr_32_bits & length_24_bits & tag_8_bits)
                ep_tx_cmd_full          : in  std_logic;  
        
                ep_tx_error                     : in std_logic; 
                ep_tx_tag_error         : in std_logic_vector(7 downto 0); 
                
        -- EP TXD AXIS Master (write to other EP)
                ep_txd_m_tvalid         : out std_logic;
                ep_txd_m_tdata          : out std_logic_vector(63 downto 0);
                ep_txd_m_tready         : in  std_logic;
                
                -- EP RXD AXIS Slave (receive data from other EP) 
                ep_rxd_s_tvalid : in  std_logic;
                ep_rxd_s_tready : out std_logic;
                ep_rxd_s_tdata  : in  std_logic_vector(63 downto 0);
                
                -- Control Bus -- Optional
                -- S6 Register Interface
        -- from CBus
        hardid  : in std_logic_vector( 1 downto 0); 
        mac             : in std_logic_vector(31 downto 0);  
        userid  : in std_logic_vector(31 downto 0);

        InReg0  : in std_logic_vector(31 downto 0);
        InReg1  : in std_logic_vector(31 downto 0);
        InReg2  : in std_logic_vector(31 downto 0);
        InReg3  : in std_logic_vector(31 downto 0);
        InReg4  : in std_logic_vector(31 downto 0);
        InReg5  : in std_logic_vector(31 downto 0);
        InReg6  : in std_logic_vector(31 downto 0);

        -- to CBus
        OutReg0 : out std_logic_vector(31 downto 0);
        OutReg1 : out std_logic_vector(31 downto 0);
        OutReg2 : out std_logic_vector(31 downto 0);
        OutReg3 : out std_logic_vector(31 downto 0);
        OutReg4 : out std_logic_vector(31 downto 0);
        OutReg5 : out std_logic_vector(31 downto 0);
        OutReg6 : out std_logic_vector(31 downto 0);
        
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

end user_ip;



architecture rtl of user_ip is

component clk_wiz
        port
                (-- Clock in ports
                        CLK_IN1           : in     std_logic;
                        -- Clock out ports
                        CLK_OUT1          : out    std_logic
                );
end component;





















-- Version 
constant        UserIPVersion   : std_logic_vector(11 downto 0) := X"001"; 

--- Registers address map
--- mapped to BAR0 region with offset = X"100"
constant CommandReg                     : std_logic_vector(7 downto 0) := X"00"; 

-- CommandReg(31 downto 19) - 12 bits - UserIPVersion - RO - set by hardware
-- CommandReg(18 downto 11) - 8  bits - FPGA device index - RW - set by CPU



-- S2MM
constant RxAddress                      : std_logic_vector(7 downto 0) := X"04"; 
constant RxLength                       : std_logic_vector(7 downto 0) := X"08"; 
constant RxStatus                       : std_logic_vector(7 downto 0) := X"0C"; 
 
-- MM2S
constant TxAddress                      : std_logic_vector(7 downto 0) := X"10"; 
constant TxLength                       : std_logic_vector(7 downto 0) := X"14"; 
constant TxStatus                       : std_logic_vector(7 downto 0) := X"18"; 


-- EP TX
constant EpTxAddress            : std_logic_vector(7 downto 0) := X"1C"; 
constant EpTxLength                     : std_logic_vector(7 downto 0) := X"20"; 
constant EpTxTag                        : std_logic_vector(7 downto 0) := X"24"; 
constant EpTxStatus                     : std_logic_vector(7 downto 0) := X"28"; 

-- Reg test
constant TestRegIn              : std_logic_vector(7 downto 0) :=X"2C"; 
constant TestRegOut             : std_logic_vector(7 downto 0) :=X"30";

constant MaxWordsCnt            : std_logic_vector(7 downto 0)      :=X"48";



-- DWORD SWAP BYTE function : ( big-endian -> little-endian )   -- DONE in DMA master unit
-- host_rd(31 downto 0):= trn_rd(7 downto 0)& trn_rd(15 downto 8)& trn_rd(23 downto 16)& trn_rd(31 downto 24); 

signal CommandReg_c                     : std_logic_vector(31 downto 0); 

-- CommandReg_c(0)      :       

signal RxAddress_c                      : std_logic_vector(31 downto 0); -- transfer address on AXI bus
signal RxLength_c                       : std_logic_vector(31 downto 0); -- transfer length in bytes
signal RxStatus_c                       : std_logic_vector(8  downto 0); -- transfer status
-- RxStatus_c(8)        : status valid


signal TxAddress_c                      : std_logic_vector(31 downto 0); -- transfer address on AXI bus
signal TxLength_c                       : std_logic_vector(31 downto 0); -- transfer length in bytes
signal TxStatus_c                       : std_logic_vector(8  downto 0); -- transfer status
-- TxStatus_c(8)        : status valid

signal RxCmdTag, TxCmdTag       : std_logic_vector(3 downto 0); 

signal EpTxAddress_c            : std_logic_vector(31 downto 0); -- addr_32_bits        - ????? (????????) ??? ??????
signal EpTxLength_c             : std_logic_vector(31 downto 0); -- length_24_bits      - ?????????? DWORDs ??? ??????
signal EpTxTag_c                        : std_logic_vector( 7 downto 0); -- tag_8_bits          - ??? ??????

signal EpTxStatus_c                     : std_logic_vector(31 downto 0); -- tag_8_bits          - ??? ??????            



signal TestRegIn_c                      : std_logic_vector(15 downto 0);
-- TestRegIn_c(15::0)   - input_data 16 bits

signal TestRegOut_c                     : std_logic_vector(31 downto 0);
-- TestRegOut_c(15::0)  - input_data + 1
-- TestRegOut_c(31)             - data valid - set on second cyle after writting to TestRegIn_c, priority reset after host reads data TestRegOut_c

signal test_data_set            : std_logic;


-- MAC address & User ID
constant MAC_RB8 : std_logic_vector(7 downto 0) :=X"70";
constant User_ID : std_logic_vector(7 downto 0) :=X"74";
constant Hard_ID : std_logic_vector(7 downto 0) :=X"78";










signal intercon_selector                : std_logic_vector(2 downto 0);         

signal mac_d : std_logic_vector(31 downto 0);
signal userid_d : std_logic_vector(31 downto 0);
signal In0, In1, In2, In3, In4, In5, In6 : std_logic_vector(31 downto 0);
signal Out0, Out1, Out2, Out3, Out4, Out5, Out6: std_logic_vector(31 downto 0);

signal clk_in_ibuf      : std_logic; 
signal ip_clk           : std_logic; 
























signal ep_tx_counter: std_logic_vector(63 downto 0);
signal tx_counter: std_logic_vector(63 downto 0);
signal len_cnt : std_logic_vector(31 downto 0);

signal cnt_rst_n: std_logic;

signal start: std_logic_vector(1 downto 0);
signal state: std_logic_vector(1 downto 0);


attribute KEEP : string;
--attribute KEEP of TxStatus_c          : signal is "TRUE";
--attribute KEEP of RxStatus_c          : signal is "TRUE";


begin


ip_clk_gen: clk_wiz
port map
(
        CLK_IN1 => clk_in,
        CLK_OUT1 => ip_clk
);

clk_out <= ip_clk; 

user_int_req    <= '0'; 


---------------------------------------------------------------------------------
-- USER IP registers 
-----------------------------
process(ip_clk, user_rst_n)
begin
        
        if user_rst_n = '0' then
                                                          
                CommandReg_c    <= (others => '0'); 
                RxAddress_c     <= (others => '0'); 
                RxLength_c              <= (others => '0'); 
                RxStatus_c              <= (others => '0'); 
                
                TxAddress_c     <= (others => '0'); 
                TxLength_c              <= (others => '0'); 
                TxStatus_c              <= (others => '0'); 
                

                EpTxAddress_c   <= (others => '0'); 
                EpTxLength_c    <= (others => '0'); 
                EpTxTag_c               <= (others => '0'); 
                EpTxStatus_c    <= (others => '0'); 

                Reg_Din                         <= (others => '1'); 
                Reg_Valid                       <= '0'; 
                
                
                RxCmdTag                <= (others => '0');
                TxCmdTag                <= (others => '0');

                TestRegIn_c             <= (others => '0'); 
                TestRegOut_c    <= (others => '0');
                test_data_set   <= '0'; 
                len_cnt<= (others => '0');

                                  
        elsif rising_edge(ip_clk) then
        
        -- set default values
                test_data_set   <= '0';

                Reg_Din         <= (others => '1');
                Reg_Valid       <= '0';

                
        -- Write 
                if Reg_WE = '1' then
                        case Reg_Addr is 
                        
                                when CommandReg         => CommandReg_c         <= Reg_Dout;
                                when EpTxAddress        => EpTxAddress_c        <= Reg_Dout;                            
                                when EpTxLength         => EpTxLength_c         <= Reg_Dout;
                                when EpTxTag            => EpTxTag_c            <= Reg_Dout(7 downto 0);
                                
                                -- S2MM
                                when RxAddress => 
                                        RxAddress_c <= Reg_Dout;
                                
                                when RxLength   => 
                                        RxLength_c              <= Reg_Dout;
                                        RxCmdTag                <= RxCmdTag + 1; 
                                        
                                when RxStatus   => RxStatus_c   <= Reg_Dout(8 downto 0); 
                                        
                                -- MM2S
                                when TxAddress => 
                                        TxAddress_c     <= Reg_Dout;
                                
                                when TxLength   => 
                                        TxLength_c              <= Reg_Dout;             
                                        TxCmdTag                <= TxCmdTag + 1; 
                                        
                                when TxStatus   => TxStatus_c   <= Reg_Dout(8 downto 0); 
                                
                                when MaxWordsCnt    => len_cnt <= Reg_Dout;
                                        
                                
--                              TestRegs                
                                when TestRegIn  => 
                                        TestRegIn_c                     <= Reg_Dout(15 downto 0);
                                        test_data_set           <= '1';  

                
                when others             => null;
                                
                        end case;
                
                                
        -- Read 
                elsif Reg_RE = '1' then
                        
                        case Reg_Addr is 
                        
                                when CommandReg => Reg_Din      <= CommandReg_c(31 downto 0);                   
--                              when CommandReg => Reg_Din      <= InitDoneTop & InitDoneBtm & CommandReg_c(29 downto 0);       
                
                                
                                when EpTxAddress        => Reg_Din      <= EpTxAddress_c;       
                                when EpTxLength         => Reg_Din      <= EpTxLength_c;        
                                when EpTxTag            => Reg_Din      <= X"000000" & EpTxTag_c;                       
                                        
                                when EpTxStatus         => 
                                                Reg_Din                 <= EpTxStatus_c;                                
                                                EpTxStatus_c    <= (others => '0');
                                                                                                                
                                when RxAddress  => Reg_Din      <= RxAddress_c;
                                when RxLength   => Reg_Din      <= RxLength_c;
                                when RxStatus   => Reg_Din(8 downto 0)  <= RxStatus_c; 
                                        
                                
                                
                                when TxAddress  =>      Reg_Din         <= TxAddress_c;
                                when TxLength   =>      Reg_Din         <= TxLength_c;
                                when TxStatus   =>      Reg_Din(8 downto 0)     <= TxStatus_c;
                                         
                                when TestRegOut =>      
                                        Reg_Din         <= TestRegOut_c;
                                        if TestRegOut_c(31) = '1' then
                                                TestRegOut_c(31)        <= '0';
                                        end if; 
                                                                                  
--              MAC & ID
                                when MAC_RB8 => Reg_Din <= mac_d;
                                when User_ID => Reg_Din <= userid_d;
                                when Hard_ID => Reg_Din <= X"0000000" & "00" & hardid;






                                when MaxWordsCnt =>  Reg_Din    <= len_cnt;

                                                                
                                when others => Reg_Din  <= X"12345678"; 
                                
                        
                        end case;
                        
                        Reg_Valid       <= '1'; 
                                
                end if; 
                        
                
                ----------------
                -- EP TX status
                if ep_tx_error = '1' then
                        EpTxStatus_c(31)                        <= '1';
                        EpTxStatus_c(7 downto 0)        <= X"FF";
                end if; 
                        
                -----------------------------   
                -- start EP TX bit
                if CommandReg_c(0) = '1' then
                        CommandReg_c(0) <= '0';
                end if;         
                

                -- Test Regs process
                if test_data_set = '1' then
                        TestRegOut_c(15 downto 0)       <= TestRegIn_c + 1;
                        TestRegOut_c(31)                        <= '1';                         -- test data out valid
                end if; 
                
                        
        end if;
end process; 


ep_tx_cmd_wr_en         <= CommandReg_c(0); 

ep_tx_cmd_data          <= EpTxAddress_c & EpTxLength_c(23 downto 0) & EpTxTag_c; 

------------------------------------
-- Data FIFOs interconnection
------------------------------------
intercon_selector <= CommandReg_c(31 downto 29);

fifo_intercon: process(intercon_selector, host_rxd_s_tdata, ep_tx_counter, tx_counter, host_rxd_s_tvalid, host_txd_m_tready,  
                                                                                  ep_rxd_s_tdata, ep_rxd_s_tvalid, ep_txd_m_tready      )
begin
 CASE intercon_selector IS
when "000"=>
        
        

        host_txd_m_tvalid       <= host_rxd_s_tvalid;
        host_rxd_s_tready       <= host_txd_m_tready; 
        host_txd_m_tdata        <= host_rxd_s_tdata;    
                
        
        -- EP TX        <= EX RX; 
        ep_txd_m_tvalid         <= ep_rxd_s_tvalid; 
        ep_txd_m_tdata          <= ep_rxd_s_tdata; 
        ep_rxd_s_tready         <= ep_txd_m_tready; 
                
                                
when "100"=>
        
        -- HOST TX      <= EP RX;
        host_txd_m_tdata        <= ep_rxd_s_tdata; 
        host_txd_m_tvalid       <= ep_rxd_s_tvalid;     
        ep_rxd_s_tready         <= host_txd_m_tready;
        
        -- EP TX        <= HOST RX; 
        ep_txd_m_tvalid         <= host_rxd_s_tvalid; 
        ep_txd_m_tdata          <= host_rxd_s_tdata; 
        host_rxd_s_tready       <= ep_txd_m_tready; 
        
when "110"=>    

        -- HOST TX      <= EP RX;
        host_txd_m_tdata        <= ep_rxd_s_tdata; 
        host_txd_m_tvalid       <= '0';--ep_rxd_s_tvalid;       
        ep_rxd_s_tready         <= '1';--host_txd_m_tready;
        
        -- EP TX        <= HOST RX; 
        ep_txd_m_tvalid         <= host_rxd_s_tvalid; 
        ep_txd_m_tdata          <= host_rxd_s_tdata; 
        host_rxd_s_tready       <= ep_txd_m_tready; 
        
when "101"=>    
    
        -- HOST TX     <= EP RX;
        host_txd_m_tdata     <= ep_rxd_s_tdata; 
        host_txd_m_tvalid    <= ep_rxd_s_tvalid;     
        ep_rxd_s_tready        <= host_txd_m_tready;
        
        -- EP TX     <= HOST RX; 
        ep_txd_m_tvalid        <= start(1);--'1';--host_rxd_s_tvalid; 
        ep_txd_m_tdata         <= ep_tx_counter; 
        host_rxd_s_tready     <= '0';   
        
when "010"=>    
        
            -- HOST TX     <= EP RX;
            host_txd_m_tdata     <= tx_counter;
            host_txd_m_tvalid    <= start(0);--'1';    
            ep_rxd_s_tready        <= '0';--host_txd_m_tready;
            
            -- EP TX     <= HOST RX; 
            ep_txd_m_tvalid        <= host_rxd_s_tvalid; 
            ep_txd_m_tdata         <= host_rxd_s_tdata; 
            host_rxd_s_tready     <= ep_txd_m_tready;  
            
when "011"=>    
                    
                        -- HOST TX     <= EP RX;
                        host_txd_m_tdata     <= ep_rxd_s_tdata; 
                        host_txd_m_tvalid    <= ep_rxd_s_tvalid;     
                        ep_rxd_s_tready        <= host_txd_m_tready;
                        
                        -- EP TX     <= HOST RX; 
                        ep_txd_m_tvalid        <= '0';--host_rxd_s_tvalid; 
                        ep_txd_m_tdata         <= host_rxd_s_tdata; 
                        host_rxd_s_tready     <= '1';--ep_txd_m_tready;     
                        
when others =>
                        host_txd_m_tvalid       <= host_rxd_s_tvalid;
                        host_rxd_s_tready     <= host_txd_m_tready; 
                        host_txd_m_tdata    <= host_rxd_s_tdata;     
    

                        -- EP TX     <= EX RX; 
                        ep_txd_m_tvalid        <= ep_rxd_s_tvalid; 
                        ep_txd_m_tdata         <= ep_rxd_s_tdata; 
                        ep_rxd_s_tready     <= ep_txd_m_tready;                                        
        
        
end case; 
end process;

cnt_rst_n<=CommandReg_c(1);

process(ip_clk)
variable temp   : std_logic_vector(31 downto 0);
variable start_var: std_logic_vector(5 downto 0);
variable hold_var : std_logic; 
begin
if rising_edge(ip_clk) then
if (cnt_rst_n = '0') then

    tx_counter(63 downto 32) <= X"00000001"; 
    tx_counter(31 downto  0) <= X"00000000";            

    ep_tx_counter(63 downto 32) <= X"00000001"; 
    ep_tx_counter(31 downto  0) <= X"00000000";    
    temp:=(others=>'0');

    start<=(others=>'0');
    hold_var:='0';
    state<="00";
	

else

 case state is
  when "00" =>  
     

    if ((host_txd_m_tready = '1') and (intercon_selector = "010")) then   
        temp:=temp + 1;
         start(0)<='1';
         hold_var:='0';
    end if;
    

    if ((ep_txd_m_tready = '1') and (intercon_selector = "101")) then   
        temp:=temp + 1;
         start(1)<='1';
         hold_var:='0';
    end if;
       
 
   


   if (((host_txd_m_tready = '0') and (intercon_selector = "010")) or ((ep_txd_m_tready = '0') and (intercon_selector = "101")) ) then
       hold_var:='1';
   end if; 
   
  if ((host_txd_m_tready = '1') and (intercon_selector = "010") and (hold_var = '0') and (start(0)='1')) then
     tx_counter(63 downto 32) <= tx_counter(63 downto 32) + 2; 
     tx_counter(31 downto  0) <= tx_counter(31 downto  0) + 2;    
end if;
   

   
   if ((ep_txd_m_tready = '1') and (intercon_selector = "101") and (hold_var = '0') and (start(1)='1')) then
           ep_tx_counter(63 downto 32) <= ep_tx_counter(63 downto 32) + 2; 
           ep_tx_counter(31 downto  0) <= ep_tx_counter(31 downto  0) + 2;  
   end if;
   

    if (temp=(len_cnt+1)) then
     start<=(others => '0');
     state<="01";      
   end if; 
   
  when  others=> NULL;  
      end case;        



end if;
end if;
end process;



--------------------------------------------------------
-- For test CBus
OutReg0 <= InReg0;
OutReg1 <= X"11111111";
OutReg2 <= X"22222222";
OutReg3 <= X"33333333";
OutReg4 <= X"44444444";
OutReg5 <= X"12345678";
OutReg6 <= X"87654321";

process (ip_clk)
begin
        if rising_edge(ip_clk) then
           mac_d <= mac;
           userid_d <= userid;
        end if;
end process;
--------------------------------------------------------
-- For test S6 FIFO 


fifo_rst <= '0';






































































































































end rtl; 
