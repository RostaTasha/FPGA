-------------------------------------------------------------------------------
-- Project     : Rosta Base PCIe project Ver.9
-- File        : cbus.vhd
-- Version     : 3.0
-- Company     : Rosta
-- Engineer    : rkob
-- Create Date : 13.08.2014 
-- Comments    : New Control Bus Controller 
--              
--              05.12.2014 urock added IO buffers instantiations
------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library unisim;
use unisim.vcomponents.all;

entity cbus is 

	port (

		cbus_clk  		: in  std_logic;

		id          : in std_logic_vector(1 downto 0);
		strtcmd     : in std_logic;
		command     : inout std_logic_vector(7 downto 0);
		dval        : inout std_logic;

        -- Reg's Interface

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
        fifo_clk : in std_logic;
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

end cbus;

architecture rtl of cbus is

component s6_v7
port(
        rst : in std_logic;
        wr_clk : in std_logic;
        rd_clk : in std_logic;
        din : in std_logic_vector(7 downto 0);
        wr_en : in std_logic;
        rd_en : in std_logic;
        dout : out std_logic_vector(31 downto 0);
        full : out std_logic;
        empty : out std_logic;
        rd_data_count : out std_logic_vector(10 downto 0)
		);
end component;

component v7_s6
port(
        rst : in std_logic;
        wr_clk : in std_logic;
        rd_clk : in std_logic;
        din : in std_logic_vector(31 downto 0);
        wr_en : in std_logic;
        rd_en : in std_logic;
        dout : out std_logic_vector(7 downto 0);
        full : out std_logic;
        empty : out std_logic;
        rd_data_count : out std_logic_vector(12 downto 0)
		);
end component;

--- Registers address map
signal command_t      : std_logic;
signal command_i, command_o: std_logic_vector (7 downto 0);

signal wr_en, rd_en: std_logic := '0'; 
signal cnt: std_logic_vector(3 downto 0);
signal bytecnt: std_logic_vector(3 downto 0);
signal cmd: std_logic_vector(7 downto 0);
signal wr_data: std_logic_vector(31 downto 0);
signal rd_data: std_logic_vector(31 downto 0);

signal mac_d, userid_d: std_logic_vector(31 downto 0);
signal In0, In1, In2, In3, In4, In5, In6 : std_logic_vector(31 downto 0);
signal Out0, Out1, Out2, Out3, Out4, Out5, Out6: std_logic_vector(31 downto 0);

signal uclkreg: std_logic_vector(4 downto 0);
signal uclk: std_logic;
signal starter: std_logic;

--- new signals
signal wr_fifo, rd_fifo: std_logic;
signal wr_en_fifo, rd_en_fifo: std_logic;
signal wr_fifo_full, rd_fifo_empty: std_logic;
signal rd_data_fifo: std_logic_vector(7 downto 0);
signal wr_data_fifo: std_logic_vector(7 downto 0);
signal rd_fifo_data_count: std_logic_vector(12 downto 0);

signal dval_i: std_logic := '1';
signal dval_o: std_logic;
signal rd_count: std_logic_vector(7 downto 0);

signal clk	: std_logic; 

signal strtcmd_s	: std_logic; 

signal id_s: std_logic_vector(1 downto 0);

signal cbus_clk_ibuf	: std_logic; 

attribute KEEP : string;

attribute KEEP of dval_i : signal is "TRUE";      
attribute KEEP of dval_o : signal is "TRUE";      
attribute KEEP of rd_count : signal is "TRUE";      


begin

cbusclk_ibuf: IBUF
port map
 (O => cbus_clk_ibuf,
  I => cbus_clk);

  
cbusclk_bufg: BUFG
port map
 (O => clk,
  I => cbus_clk_ibuf);

  
str_ibuf: IBUF
port map
( O => strtcmd_s,
  I => strtcmd);  

id0_ibuf: IBUF
port map
( O => id_s(0),
  I => id(0));  
  
id1_ibuf: IBUF
port map
( O => id_s(1),
  I => id(1));  

hardid	<= id_s; 

process (clk) 
begin
   if (clk'event and clk = '1') then

       	mac		<= mac_d;  
       	userid	<= userid_d;

--		if wr_en = '0' then
            In0 <= InReg0;
            In1 <= InReg1;
            In2 <= InReg2;
            In3 <= InReg3;
            In4 <= InReg4;
            In5 <= InReg5;
            In6 <= InReg6;
--        end if;

--		if rd_en = '0' then
            OutReg0 <= Out0;
            OutReg1 <= Out1;
            OutReg2 <= Out2;
            OutReg3 <= Out3;
            OutReg4 <= Out4;
            OutReg5 <= Out5;
            OutReg6 <= Out6;
--        end if;
        
   end if;
end process;

VALID : IOBUF port map (I => not rd_fifo, O => dval_o, IO => dval, T => dval_i );

loop_io : for i in 0 to 7 generate 
cmdbus : IOBUF port map (I => command_i(i), O => command_o(i), IO => command(i), T => command_t );
end generate ;
-- xxx_T = 1 - input, xxx_T = 0 - output
command_t <= '0' when strtcmd_s = '0' and (rd_en = '1' or rd_fifo = '1') else '1';

-- Clocking CBus
process (clk, strtcmd_s) 
begin
   if (clk'event and clk = '0') then
		if (strtcmd_s = '1') and (starter = '0') then -- new command & reset counter
			starter <= '1'; -- rissing edge strtcmd_s
			uclkreg <= "00000";
		else
            uclkreg <= uclkreg + 1;
            if uclkreg = "11000" then -- 1 uclck = 4 v7_clk |=> 6 x 4 = 24
                starter <= '0'; -- wait new rissing edge strtcmd_s
            end if;
        end if;
   end if;
end process;

--uclk <= uclkreg(1); -- v7_clk/4 => Def 100/4=25 MHz
uclk_bufg: BUFG
port map
 (O => uclk,
  I => uclkreg(1));

			
-- Controller CBus
process (uclk, strtcmd_s)

variable Mode_v: integer range 0 to 7;
 
begin
   if (uclk'event and uclk = '1') then

		if (strtcmd_s = '1') then -- new command
		
    		Mode_v:= 0;
			cmd <= command_o;
			bytecnt <= command_o(3 downto 0);
			cnt <= "0000";
			rd_count <= "00000000";
			wr_en <= '0';			
			rd_en <= '0';
			wr_fifo <= '0';
			rd_fifo <= '0';
			wr_en_fifo <= '0';
			rd_en_fifo <= '0';
			dval_i <= '1';

----------------------------------------------------------------------------------			
			-- S6 FIFO Interface
			if command_o(3 downto 0) = "1111" then -- Packet Tranfer
                --  Write FIFO
    			if command_o(7 downto 4) = "0000" then
    				wr_fifo   <= '1';
                --  Read FIFO
    			elsif command_o(7 downto 4) = "0001" then
    				rd_fifo   <= '1';

    				if rd_fifo_empty = '0' then -- need rd_en for FIFO FWFT
                        rd_en_fifo <= '1';
                    end if;            

				-- FIFO Status Register
				elsif command_o(7 downto 4) = "0010" then
					rd_data <= "00000000000000" & wr_fifo_full & rd_fifo_empty 
			                     & "000" & rd_fifo_data_count;
					rd_en <= '1';
    			end if;
----------------------------------------------------------------------------------			
			-- S6 Register Interface
			elsif command_o(3 downto 0) = "0100" then -- 4 Byte -- 32 bit Reg's

                --  Write Regs
    			if command_o(7 downto 4) <= "1000" then
	   	       		wr_en <= '1';
                --  Read Regs
    			elsif (command_o(7 downto 4) >= "1001") then -- Read Regs
	       			rd_en <= '1';

			     	if command_o = "10010100" then
					   rd_data <= In0;
				    elsif command_o = "10100100" then
					   rd_data <= In1;
				    elsif command_o = "10110100" then
					   rd_data <= In2;
				    elsif command_o = "11000100" then
					   rd_data <= In3;
				    elsif command_o = "11010100" then
					   rd_data <= In4;
				    elsif command_o = "11100100" then
					   rd_data <= In5;
				    elsif command_o = "11110100" then
					   rd_data <= In6;
				    end if;
			     end if;
		     end if;
----------------------------------------------------------------------------------			

		else --- data

----------------------------------------------------------------------------------			
---     Reg's
			if wr_en = '1' then

    			case Mode_v is
	       			when 0 =>
                        wr_data(7 downto 0) <= command_o;	       			
    					Mode_v := 1; 
	       			when 1 =>
                        wr_data(15 downto 8) <= command_o;
    					Mode_v := 2; 
                    when 2 =>
                        wr_data(23 downto 16) <= command_o;
                        Mode_v := 3;
                    when 3 =>
                        wr_data(31 downto 24)  <= command_o;
                        Mode_v := 4;
                    when 4 =>
                        Mode_v := 5;
                    
						if cmd = "00000100" then
							mac_d <= wr_data;
						elsif cmd = "00010100" then
							userid_d <= wr_data;
						elsif cmd = "00100100" then
							Out0 <= wr_data;
						elsif cmd = "00110100" then
							Out1 <= wr_data;
						elsif cmd = "01000100" then
							Out2 <= wr_data;
						elsif cmd = "01010100" then
							Out3 <= wr_data;
						elsif cmd = "01100100" then
							Out4 <= wr_data;
						elsif cmd = "01110100" then
							Out5 <= wr_data;
						elsif cmd = "10000100" then
							Out6 <= wr_data;
						end if;

                    when 5 => wr_en <= '0';
					when others => null;
				end case;
			
			elsif rd_en = '1' then

    			case Mode_v is
	       			when 0 =>
                        command_i <= rd_data(7 downto 0);	       			
    					Mode_v := 1; 
	       			when 1 =>
                        command_i <= rd_data(15 downto 8);
                        Mode_v := 2; 
                    when 2 =>
                        command_i <= rd_data(23 downto 16);
                        Mode_v := 3;
                    when 3 =>
                        command_i <= rd_data(31 downto 24);
                        Mode_v := 4;
                    when 4 => rd_en <= '0';
					when others => null;
				end case;

--			end if;

----------------------------------------------------------------------------------			
---     Packet
			elsif wr_fifo = '1' then 
                if dval_o = '0' then
				    wr_data_fifo <= command_o;
				    wr_en_fifo   <= '1';
    			 else
				    wr_en_fifo   <= '0';
				    wr_fifo   <= '0';
                end if;
            			
			elsif rd_fifo = '1' then

       			if rd_fifo_empty = '0' then
          			command_i <= rd_data_fifo;
                    rd_en_fifo <= '1';
                    dval_i <= '0';
                else			
                    rd_en_fifo <= '0';
                    rd_fifo <= '0';
                end if;
----------------------------------------------------------------------------------			
			end if;
		end if;
	end if;
end process;


s6_rx_fifo: s6_v7
port map
(
    rst  => '0',
    wr_clk => uclk, 
    rd_clk => fifo_clk,
    din => wr_data_fifo,
    wr_en => wr_en_fifo,
    rd_en => s6_v7_rd_en,
    dout => s6_v7_dout,
    full => wr_fifo_full,
    empty => s6_v7_empty,
    rd_data_count => s6_v7_data_count
);

s6_tx_fifo: v7_s6
port map
(
    rst  => fifo_rst,
    wr_clk => fifo_clk, 
    rd_clk => uclk,
    din => v7_s6_din,
    wr_en => v7_s6_wr_en,
    rd_en => rd_en_fifo,
    dout => rd_data_fifo,
    full => v7_s6_full,
    empty => rd_fifo_empty,
    rd_data_count => rd_fifo_data_count
);

end rtl; 
